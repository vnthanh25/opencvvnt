#include "..\Header\Rotation.h"
#include "..\Header\Utilities.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;
using namespace vnt;

vector<Point> Rotation::findRect(Mat src_gray)
{
	vector<Point> vctPoint;
	// Find contours
	vector<vector<Point> > contours;
	Mat dst = src_gray.clone();
	findContours(dst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<Point> approx;

	for (int i = 0; i < contours.size(); i++)
	{
		// Approximate contour with accuracy proportional
		// to the contour perimeter
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

		// Skip small or non-convex objects 
		double area = fabs(contourArea(contours[i]));
		if ((0 < area && area < 1000) || !isContourConvex(approx))
			continue;

		if (approx.size() ==  4)
		{
			return approx;
		}
	}
	return vctPoint;
}

bool Rotation::isLeft(vector<Point> vctPoint)
{
	Point pMinX = vctPoint[0];
	Point pMinY = vctPoint[0];
	for(int i = 1; i < vctPoint.size(); i++)
	{
		if(pMinX.x > vctPoint[i].x)
			pMinX = vctPoint[i];
		if(pMinY.y > vctPoint[i].y)
			pMinY = vctPoint[i];
	}
	if(abs(pMinX.x - pMinY.x) < abs(pMinX.y - pMinY.y))
	{
		return false;// Rotate Right.
	}
	else
	{
		return true;// Rotate Left.
	}
}

Mat Rotation::RotationWithHough(Mat src_gray)
{
	Mat dst;
	Canny(src_gray, dst, 50, 200, 3);
	//dst = src_gray.clone();
	float angle = 0;
	float degree = 0;
	Point p1 , p2;

	/// Use contour to find rectangle.
	vector<Point> fourPoint = findRect(dst);
	if(fourPoint.size() > 3)
	{
		Mat test = Mat::zeros(src_gray.size(), CV_8UC1);
		/// Craw line
		//int len = fourPoint.size() - 1;
		//for (int i = 0; i < len; i++)
		//{
		//	line(test, fourPoint[i], fourPoint[i+1], Scalar(255,255,255), 2);
		//}
		//line(test, fourPoint[len], fourPoint[0], Scalar(255,255,255), 2);
		line(test, fourPoint[0], fourPoint[1], Scalar(255,255,255), 2);
		circle(test, fourPoint[0], 5, Scalar(255), 2);

		imwrite("images/test.png", test);

		if(isLeft(fourPoint))
		{
			p1 = fourPoint[1];
			p2 = fourPoint[0];
		}
		else
		{
			p1 = fourPoint[0];
			p2 = fourPoint[3];
		}
	}
	/// Use HoughLines to find 2 Point
	else
	{
		vector<Vec2f> lines;
		HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );
		for( size_t i = 0; i < lines.size(); i++ )
		{
			float rho = lines[i][0], theta = lines[i][1];
			double a = cos(theta), b = sin(theta);
			double x0 = a*rho, y0 = b*rho;
			int y1 = cvRound(y0 + 1000*(a));
			int y2 = cvRound(y0 - 1000*(a));
			if(i == 0 || abs(y1 - y2) + 2 < abs(p1.y - p2.y))
			{
				p1.x = cvRound(x0 + 1000*(-b));
				p1.y = y1;
				p2.x = cvRound(x0 - 1000*(-b));
				p2.y = y2;
			}
		}

		//vector<Vec4i> lines;
		//HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
		//for( size_t i = 0; i < lines.size(); i++ )
		//{
		//	Vec4i l = lines[i];
		//	//line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
		//	int y1 = l[1];
		//	int y2 = l[3];
		//	if(i == 0 || abs(y1 - y2) + 2 < abs(p1.y - p2.y))
		//	{
		//		p1.x = l[0];
		//		p1.y = l[1];
		//		p2.x = l[2];
		//		p2.y = l[3];
		//	}
		//}
	}

	///calculate angle in radian,  if you need it in degrees just do angle * 180 / PI
	angle = atan2(p1.y - p2.y, p1.x - p2.x);
	degree = angle * 180 / CV_PI;
	//line( dst, p1, p2, Scalar(0,0,255), 3, CV_AA);

	/// Rotation src image.
	double scale = 1.0;
	Point2f center(dst.cols/2, dst.rows/2);
	degree = -1 * (180 - degree);
	Mat rot_Mat = getRotationMatrix2D(center, degree, scale);
	warpAffine(dst, dst, rot_Mat, dst.size());

	rot_Mat.release();

	return dst;
}

Rotation::Rotation()
{
}

Rotation::~Rotation()
{
}