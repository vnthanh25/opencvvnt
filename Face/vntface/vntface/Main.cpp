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
	Matching vMatching;
	Utilites util;

	//std::string Path = "E:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/vntface/vntface/Debug/VNTDataSet/HeadPose/NotPose/NotNormalize/";
	//int vIdx = Path.rfind("/Pose/");
	//if (vIdx == -1)
	//	vIdx = Path.rfind("/NotPose/");
	//Path = Path.substr(0, vIdx + 1);
	//std::string Path1 = "E:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/vntface/vntface/Debug/VNTDataSet/HeadPose/Pose/NotNormalize/";
	//int vIdx1 = Path1.rfind("/Pose/");
	//if (vIdx1 == -1)
	//	vIdx1 = Path1.rfind("/NotPose/");
	//Path1 = Path1.substr(0, vIdx + 1);

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	//std::string vSourePath = vPath + "/VNTDataSet/DataSetHeadPoseDetectedFace/";
	//std::string vSourePath = vPath + "/VNTDataSet/DataSetHeadPoseDownload/";
	std::string vSourePath = vPath + "/VNTDataSet/colorferetDownload/";

	//std::ifstream ifSetting("Setting.txt");
	//std::string vValue;
	//std::vector<std::string> vSettings;
	//while (!ifSetting.eof())
	//{
	//	std::getline(ifSetting, vValue);
	//	vSettings.push_back(vValue);
	//}
	//ifSetting.close();

	//\\ Phat hien mat nguoi trong anh.
	//vMatching.aHeadPoseFaceDetect();

	//\\ Khoi tao DataSet
	//vMatching.aHeadPoseDataSetInit();

	//\\ Khoi tao Feature
	//vMatching.aFeaturesInit();

	//\\ Khoi tao Database
	//vMatching.aDatabaseInit();
	//vMatching.aDatabaseInitFull(vSourePath);

	//\\ So khop
	//vMatching.aMatchingHeadPose();

	//\\ Kiem tra so khop.
	//vMatching.aMatchingHeadPoseCheck();

	//\\ So khop dung MAP
	vMatching.aMatchingHeadPoseMAP();
	//vMatching.aMatchingColorFeretMAP();


	cout << "Done.";
	_getwch();
	return 0;
}
