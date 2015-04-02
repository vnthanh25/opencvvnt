#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

// Global variables
// Copy this file from opencv/data/haarscascades to target folder
std::string face_cascade_name = "cascades/haarcascade_frontalface_alt.xml";
cv::CascadeClassifier face_cascade;

// Detect face.
std::vector<cv::Mat> detectAndDisplay(cv::Mat image)
{
	std::vector<cv::Mat> result;
	std::vector<cv::Rect> faces;
	cv::Mat face;

	// Detect faces
	face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

	// Get Region of Interest
	cv::Rect roi;
	for (size_t i = 0; i < faces.size(); i++)
	{
		roi.x = faces[i].x;
		roi.y = faces[i].y;
		roi.width = faces[i].width;
		roi.height = faces[i].height;

		face = image(roi);
		result.push_back(face);
	}
	return result;
}

// Function main
int main(void)
{
	// Load the cascade
	if (!face_cascade.load(face_cascade_name))
	{
		printf("--(!)Error loading\n");
		return (-1);
	};

	// Read the image file
	cv::Mat image = cv::imread("images/lena.png", CV_8UC1);
	std::vector<cv::Mat> faces = detectAndDisplay(image);

	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::imshow("image" + std::to_string(i), faces[i]);
	}

	cv::waitKey();
	return 0;
}
