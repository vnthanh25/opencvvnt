#include "Header\Matching.h"

using namespace vnt;

// Function main
int main(void)
{
	Matching vMatching;
	//////\\ 
	////Utilites util;
	////util.FileCopy("D:/Temp/person04100-90+0.jpg", "D:/Temp/1person04100-90+0.jpg");
	//cv::Mat vMat = imread("images/lena.png", CV_8UC1);
	//imshow("lena", vMat);
	//cv::waitKey();

	//\\ Phat hien mat nguoi trong anh.
	//vMatching.aHeadPoseFaceDetect();

	//\\ Khoi tao DataSet
	//vMatching.aHeadPoseDataSetInit();

	//\\ Khoi tao Feature
	//vMatching.aFeaturesInit();

	//\\ Khoi tao Database
	//vMatching.aDatabaseInit();

	//\\ So khop
	//vMatching.aMatchingHeadPose();

	//\\ Kiem tra so khop.
	//vMatching.aMatchingHeadPoseCheck();

	//\\ So khop dung MAP
	vMatching.aMatchingHeadPoseMAP();

	cout << "Done.";
	_getwch();
	return 0;
}
