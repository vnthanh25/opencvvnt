#include "..\Header\Utilities.h"
#include "..\Header\DataMat.h"
#include <ctime>

using namespace vnt;

/********** Constructor **********/
Utilites::Utilites()
{
}
Utilites::~Utilites()
{
}

double Utilites::angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void Utilites::setLabel(Mat& im, const string label, vector<Point>& contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	Size text = getTextSize(label, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(im, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
	putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

//\\ Bo sung ky tu "c" ve ben trai chuoi ky tu.
string Utilites::leftPad(string s, int len, char c)
{
	std::string result = s;
	for (int i = s.length(); i < len; i++)
	{
		result = c + result;
	}
	return result;
}
//\\ Ghi Mat ra file.
void Utilites::writeMatUChar(Mat img, string fname)
{
	FileStorage file(fname, FileStorage::WRITE);
	//file << "mat" << img;
	file << "mat" << "[:";
	string sValue = "";
	for (int x = 0; x < img.cols; x++)
	{
		stringstream out;
		out << x;
		string value = out.str();
		sValue += leftPad(value, 3, ' ') + " ";
	}
	file << "{" << "x" << sValue + "-1" << "}";
	for (int y = 0; y < img.rows; y++)
	{
		sValue = "";
		for (int x = 0; x < img.cols; x++)
		{
			int iv = (int)img.at<uchar>(Point(x, y));
			stringstream out;
			out << iv;
			string value = out.str();
			sValue += leftPad(value, 3, ' ') + " ";
		}
		stringstream out;
		out << y;
		file << "{" << "y" << sValue + out.str() << "}";
	}
	file << "]";
	file.release();
}
void Utilites::writeMatInt(Mat img, string fname)
{
	FileStorage file(fname, FileStorage::WRITE);
	//file << "mat" << img;
	file << "mat" << "[:";
	string sValue = "";
	for (int x = 0; x < img.cols; x++)
	{
		stringstream out;
		out << x;
		string value = out.str();
		sValue += leftPad(value, 3, ' ') + " ";
	}
	file << "{" << "x" << sValue + "-1" << "}";
	for (int y = 0; y < img.rows; y++)
	{
		sValue = "";
		for (int x = 0; x < img.cols; x++)
		{
			int iv = img.at<int>(Point(x, y));
			stringstream out;
			out << iv;
			string value = out.str();
			sValue += leftPad(value, 3, ' ') + " ";
		}
		stringstream out;
		out << y;
		file << "{" << "y" << sValue + out.str() << "}";
	}
	file << "]";
	file.release();
}
void Utilites::writeMatBasic(Mat img, string fname)
{
	FileStorage storage(fname, cv::FileStorage::WRITE);
	storage << "image" << img;
	storage.release();
}
void Utilites::readMatBasic(Mat img, string fname)
{
	FileStorage storage(fname, cv::FileStorage::READ);
	storage["image"] >> img;
	storage.release();
}
Mat Utilites::convolutionInt(Mat img, Mat tmp)
{
	Mat src = Mat::zeros(img.rows + tmp.rows - 1, img.cols + tmp.cols - 1, CV_32SC1);
	img.copyTo(src.rowRange(0, img.rows).colRange(0, img.cols));
	Mat dst = Mat::zeros(img.size(), CV_32SC1);
	// Step by step of the source image.
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			int sum = 0;
			// Step by step of the template.
			for (int m = 0; m < tmp.rows; m++)
			{
				for (int n = 0; n < tmp.cols; n++)
				{
					int isrc = src.at<int>(y + m, x + n);
					int itmp = tmp.at<int>(m, n);
					sum += src.at<int>(y + m, x + n) * tmp.at<int>(m, n);
				}
			}
			dst.at<int>(y, x) = sum;
		}
	}
	return dst;
}


//\\ Chuyen doi so thanh chuoi nhi phan.
std::string Utilites::convertUnsignedIntToBinary(int pValue)
{
	std::string result = "";
	while (pValue > 0)
	{
		result = std::to_string(pValue % 2) + result;
		pValue = pValue / 2;
	}
	return result;
}

//\\ Chuyen vector<vector<int>> thanh Mat.
cv::Mat Utilites::convertV2IToMat(std::vector<std::vector<int>> lbpFeature, int width, int height)
{
	cv::Mat result = cv::Mat::zeros(height, width, CV_32FC1);
	for (size_t y = 0; y < lbpFeature.size(); y++)
	{
		for (size_t x = 0; x < lbpFeature[y].size(); x++)
		{
			result.at<int>(y, x) = lbpFeature[y][x];
		}
	}
	return result;
}
//\\ Chuyen Mat thanh vector<vector<int>>.
std::vector<std::vector<int>> Utilites::convertMatToV2I(cv::Mat image)
{
	std::vector<std::vector<int>> result;
	size_t rows = image.rows;
	size_t cols = image.cols;
	for (size_t y = 0; y < rows; y++)
	{
		std::vector<int> col;
		for (size_t x = 0; x < cols; x++)
		{
			col.push_back(image.at<int>(y, x));
		}
		result.push_back(col);
	}
	return result;
}
//\\ Chuyen vector<vector<double>> thanh Mat.
cv::Mat Utilites::convertV2DToMat(std::vector<std::vector<double>> lbpFeature, int width, int height)
{
	cv::Mat result = cv::Mat::zeros(height, width, CV_64FC1);
	for (size_t y = 0; y < lbpFeature.size(); y++)
	{
		for (size_t x = 0; x < lbpFeature[y].size(); x++)
		{
			result.at<double>(y, x) = lbpFeature[y][x];
		}
	}
	return result;
}
//\\ Chuyen Mat thanh vector<vector<double>>.
std::vector<std::vector<double>> Utilites::convertMatToV2D(cv::Mat image)
{
	std::vector<std::vector<double>> result;
	size_t rows = image.rows;
	size_t cols = image.cols;
	for (size_t y = 0; y < rows; y++)
	{
		std::vector<double> col;
		for (size_t x = 0; x < cols; x++)
		{
			col.push_back(image.at<double>(y, x));
		}
		result.push_back(col);
	}
	return result;
}

//\\ Lay so tiep theo tu chuoi so truyen vao.
std::string Utilites::increaseNumber(const std::string pNumber, const int pIncrease)
{
	std::string result;
	int len = pNumber.length();
	int number = std::stoi(pNumber) + pIncrease;
	result = std::to_string(number);
	result = leftPad(result, len, '0');
	return result;
}

//\\ Get current date/time, format is YYYY-MM-DD.HH:mm:ss
std::string Utilites::currentDateTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

//\\ Tao thu muc.
int Utilites::makeDir(std::string folderName)
{
	std::string folderCreateCommand = "mkdir " + folderName;
	system(folderCreateCommand.c_str());
	return 1;
}


Mat DataMat::src, DataMat::gray, DataMat::filter, DataMat::edge, DataMat::dst;

Mat Utilites::detectsimpleshape(Mat img)
{
	//Mat gray, filter, edge, dst;
	DataMat::src = img;
	//filter = src.clone();
	GaussianBlur(DataMat::src, DataMat::filter, Size(5, 5), 0, 0, BORDER_DEFAULT);
	medianBlur(DataMat::filter, DataMat::filter, 3);
	// Convert to grayscale
	cvtColor(DataMat::filter, DataMat::gray, CV_BGR2GRAY);
	// Use Canny instead of threshold to catch squares with gradient shading
	Canny(DataMat::gray, DataMat::edge, 128, 255, 5);
	//threshold(gray, edge, 128, 255, CV_THRESH_BINARY);
	//\\ Sobel filter
	//edge = getSobel(gray);

	// Find contours
	vector<vector<Point> > contours;
	findContours(DataMat::edge.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<Point> approx;
	DataMat::dst = DataMat::src.clone();

	for (int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));

		// Approximate contour with accuracy proportional to the contour perimeter
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

		// Skip small or non-convex objects 
		if (fabs(contourArea(contours[i])) < 10 || !isContourConvex(approx))
			continue;

		if (approx.size() == 3)
		{
			drawContours(DataMat::dst, contours, i, color, -1);
		}
		else if (approx.size() >= 4 && approx.size() <= 6)
		{
			// Number of vertices of polygonal curve
			int vtc = approx.size();

			// Get the cosines of all corners
			vector<double> cos;
			for (int j = 2; j < vtc + 1; j++)
				cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));

			// Sort ascending the cosine values
			sort(cos.begin(), cos.end());

			// Get the lowest and the highest cosine
			double mincos = cos.front();
			double maxcos = cos.back();

			// Use the degrees obtained above and the number of vertices
			// to determine the shape of the contour
			if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
			{
				drawContours(DataMat::dst, contours, i, color, -1);
			}
			else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
			{
				drawContours(DataMat::dst, contours, i, color, -1);
			}
			else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
			{
				drawContours(DataMat::dst, contours, i, color, -1);
			}
		}
		else
		{
			// Detect and label circles
			double area = contourArea(contours[i]);
			Rect r = boundingRect(contours[i]);
			int radius = r.width / 2;

			if (abs(1 - ((double)r.width / r.height)) <= 0.2 &&
				abs(1 - (area / (CV_PI * pow(radius, 2.0)))) <= 0.2)
			{
				drawContours(DataMat::dst, contours, i, color, -1);
			}
		}

	}

	return DataMat::dst;
}
