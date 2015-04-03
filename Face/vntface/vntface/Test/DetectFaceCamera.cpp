#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

// Function main
int main(void)
{
	std::string face_cascade_name = "cascades/haarcascade_frontalface_alt.xml";
	cv::CascadeClassifier face_cascade;
	//// Load the cascade
	if (!face_cascade.load(face_cascade_name))
	{
		printf("--(!)Error loading\n");
		return (-1);
	};

	//// Read the image file
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
			face_cascade.detectMultiScale(image_gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

			for (size_t i = 0; i < faces.size(); i++)
			{
				cv::rectangle(image, faces[i], cv::Scalar(0, 0, 255));
			}
			cv::imshow("image", image);
			if (cv::waitKey(30) >= 0) break;
		}
	}
	return 0;
}
