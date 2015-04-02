/*
VNThanh
- Show image.
*/

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

int main(int argc, const char *argv[]) {
	std::string fullImageName;
	std::cout << argc;
	if (argc == 1)
	{
		std::cout << "Image fullname:";
		std::cin >> fullImageName;
	}
	else
	{
		fullImageName = argv[1];
	}
	//std::cout << fullImageName;
	cv::Mat image = cv::imread(fullImageName, CV_LOAD_IMAGE_GRAYSCALE);
	imshow("image", image);
	cv::waitKey(0);
	//_getwch();
	return 0;
}