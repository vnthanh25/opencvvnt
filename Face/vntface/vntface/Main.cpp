#include "Header\Matching.h"

using namespace vnt;

void Test()
{
	Utilites util;
	//std::string vTime = util.subTime("11:04:54", "11:05 : 11");
	//std::string vPose = "";
	//std::vector<std::string> aPose = util.splitString(vPose, ";");
	////util.FileCopy("D:/Temp/person04100-90+0.jpg", "D:/Temp/1person04100-90+0.jpg");
	//cv::Mat vMat = imread("images/lena.png", CV_8UC1);
	//imshow("lena", vMat);
	//cv::waitKey();

	double num = 16.0;
	double div = 1.0 / 4;
	double numpow = pow(num, div);
	std::vector<std::string> vAllFileName1;
	cv::Mat face = cv::imread("E:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/vntface/vntface/Debug/VNTDataSet/colorferetDownload/dvd1/data/images/00011/00010_930831_fa.ppm", CV_8UC1);
}

// Function main
int main(void)
{
	//Test();

	//Matching vMatching;
	//vMatching.Feret();

	cout << "Done.";
	_getwch();
	return 0;
}
