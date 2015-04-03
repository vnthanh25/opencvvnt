#include<opencv2/opencv.hpp> 
#include<opencv2/highgui/highgui.hpp>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
using namespace cv;

CascadeClassifier faceCade;

String faceCascadeName = "cascades/lbpcascade_frontalface.xml";
String FaceDetectWindow = "Face Detector Window";
String FaceDetectGrayWindow = "Face Detector Gray Window";


int main() {

	VideoCapture cap(0);
	Mat camFrames, grayFrames;
	vector<Rect> faces;
	long imageIndex = 0;

	int preX = 0, preY = 0;
	int j = 0;

	if (!faceCade.load(faceCascadeName)){ cout << "--(!)Error loading\n"; return -1; };

	while (1) {
		cap >> camFrames;

		cvtColor(camFrames, grayFrames, CV_BGR2GRAY);
		equalizeHist(grayFrames, grayFrames);

		faceCade.detectMultiScale(grayFrames, faces, 1.1, 2, 0, Size(160, 160));

		for (int i = 0; i < faces.size(); i++)
		{
			Mat faceROI = grayFrames(faces[i]);

			rectangle(camFrames, Rect(faces[i].x - 25, faces[i].y - 25, faces[i].width + 35, faces[i].height + 35), Scalar(0, 0, 255), 1, 1, 0);

			Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);


			cout << "\nx = " << faces[i].x << "\ty = " << faces[i].y;

			//while(j==10)
			//{
			if ((faces[i].y<125) && (faces[i].x<255))
			{
				printf("  RU");
				system("xte 'mousermove 10 -10'");
			}
			else if ((faces[i].y>185) && (faces[i].x<255)){
				printf("  RD");
				system("xte 'mousermove 10 10'");
			}
			else if ((faces[i].y>185) && (faces[i].x>305)){
				printf("  LD");
				system("xte 'mousermove -10 10'");
			}
			else if ((faces[i].y<125) && (faces[i].x<255)){
				printf("  LU");
				system("xte 'mousermove -10 -10'");
			}
			else if ((faces[i].y>185) && (faces[i].x>255) && (faces[i].x<305)){
				printf("  Down");
				system("xte 'mousermove 0 10'");
			}
			else if ((faces[i].y<125) && (faces[i].x>255) && (faces[i].x<305)){
				printf("  up");
				system("xte 'mousermove 0 -10'");
			}
			else if ((faces[i].y>125) && (faces[i].y<185) && (faces[i].x<255)){
				printf("  L");
				system("xte 'mousermove -10 0'");
			}
			else if ((faces[i].y>125) && (faces[i].y<185) && (faces[i].x>305)){
				printf("  R");
				system("xte 'mousermove 10 0'");
			}
			preX = faces[i].x;
			preY = faces[i].y;
			j = 0;
		}
		//j++;
		//}

		imshow(FaceDetectWindow, camFrames);
		imshow(FaceDetectGrayWindow, grayFrames);
		if (waitKey(30) >= 0) break;

	}

}