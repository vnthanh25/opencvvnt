#include "Header\FaceDetect.h"

//\\ Phat hien mat nguoi trong anh.
void FaceDetect()
{
	vnt::FaceDetect detFace;
	std::vector<cv::Mat> faces = detFace.aGetsMat(cv::imread("images/lena.png", CV_8UC1));
	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::imshow("image" + std::to_string(i), faces[i]);
	}
}
//\\ Phat hien mat nguoi trong camera.
void FaceDetectFromCamera()
{
	vnt::FaceDetect detFace;
	cv::Mat image;
	cv::Mat image_gray;
	std::vector<cv::Rect> faces;
	cv::VideoCapture cap(0);
	while (1)
	{
		bool hasFrame = cap.read(image);
		if (hasFrame)
		{
			cv::cvtColor(image, image_gray, CV_BGR2GRAY);
			cv::equalizeHist(image_gray, image_gray);
			// Detect faces
			faces = detFace.aGetsRect(image_gray);

			for (size_t i = 0; i < faces.size(); i++)
			{
				cv::rectangle(image, faces[i], cv::Scalar(0, 0, 255));
			}
			cv::imshow("image", image);
			if (cv::waitKey(30) >= 0) break;
		}
	}
}
// Function main
int main(void)
{
	//\\ Phat hien mat nguoi trong anh.
	FaceDetect();
	//\\ Phat hien mat nguoi trong camera.
	FaceDetectFromCamera();

	cv::waitKey();
	return 0;
}
