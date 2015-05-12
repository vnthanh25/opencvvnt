#include "Header\Utilities.h"
#include "Header\FaceDetect.h"
#include "Header\HeadPose.h"

using namespace vnt;

//\\ Phat hien mat nguoi trong anh.
void FaceDetect1()
{
	vnt::FaceDetect detFace;
	std::vector<cv::Mat> faces = detFace.aGetsMat(cv::imread("images/lena.png", CV_8UC1));
	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::imshow("image" + std::to_string(i), faces[i]);
	}
}
//\\ Phat hien mat nguoi trong camera.
void FaceDetectFromCamera1()
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

//\\ Detect HeadPose with serie 1.
void aHeadPoseFaceDetect()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseFaceDetect: " << util.currentDateTime() << std::endl;

	vnt::FaceDetect detFace;
	detFace.aLoadFaceCascade("cascades/lbpcascade_frontalface.xml");

	std::string vPath = util.GetExePath();
	vPath = util.replaceAll(vPath, "\\", "/");
	std::string vFolderName = "Person";
	std::string vImagePath = vPath + "/VNTDataSet/DataSetHeadPoseDownload/";
	std::string vSavePath = vPath + "/VNTDataSet/DetectedFace/lbpcascade_frontalface/";

	HeadPose vHeadPose;
	std::string vFaceTrackIndex = "01";
	while (vFaceTrackIndex != "16")
	{
		//\\ Tao thu muc.
		util.makeDir(util.replaceAll(vSavePath, "/", "\\") + vFolderName + vFaceTrackIndex);
		std::vector<std::string> vImageNames = vHeadPose.aGetsAllFileName(vFaceTrackIndex);
		detFace.aGetsMat(vImageNames, vImagePath + vFolderName + vFaceTrackIndex + "/", vSavePath + vFolderName + vFaceTrackIndex + "/");
		vFaceTrackIndex = util.increaseNumber(vFaceTrackIndex, 1);
	}
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseFaceDetect: " << util.currentDateTime() << std::endl;
}
//\\ Detect HeadPose with serie 2.
void aHeadPoseFaceTestDetect()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseFaceDetect: " << util.currentDateTime() << std::endl;

	vnt::FaceDetect detFace;
	detFace.aLoadFaceCascade("cascades/lbpcascade_frontalface.xml");

	std::string vPath = util.GetExePath();
	vPath = util.replaceAll(vPath, "\\", "/");
	std::string vFolderName = "Person";
	std::string vImagePath = vPath + "/VNTDataSet/DataSetHeadPoseDownload/";
	std::string vSavePath = vPath + "/VNTDataSet/DetectedFace/lbpcascade_frontalface/Test/";

	HeadPose vHeadPose;
	std::string vFaceTrackIndex = "01";
	while (vFaceTrackIndex != "16")
	{
		//\\ Tao thu muc.
		util.makeDir(util.replaceAll(vSavePath, "/", "\\") + vFolderName + vFaceTrackIndex);
		std::vector<std::string> vImageNames = vHeadPose.aGetsAllFileName(vFaceTrackIndex);
		detFace.aGetsMat(vImageNames, vImagePath + vFolderName + vFaceTrackIndex + "/", vSavePath + vFolderName + vFaceTrackIndex + "/");
		vFaceTrackIndex = util.increaseNumber(vFaceTrackIndex, 1);
	}
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseFaceDetect: " << util.currentDateTime() << std::endl;
}

//\\ Phat hien mat nguoi trong anh.
void aFaceDetect()
{
	Utilites util;
	vnt::FaceDetect detFace;
	std::string vCascadePath = "cascades/lbpcascade_frontalface.xml";

	std::string vPath = util.GetExePath();
	std::string vImagePath = vPath + "/VNTDataSet/DataSetHeadPose/FaceTrack00/Image";
	std::string vDetectedFacePath = vPath + "/VNTDataSet/DetectedFace/lbpcascade_frontalface/FaceTrack00/Image";
	//\\ Detect image from "00" to "30".
	std::string vImageIndex = "000";
	while (vImageIndex != "185")
	{
		cv::Mat vImage = cv::imread(vImagePath + vImageIndex + ".jpg", CV_8UC1);
		//std::vector<cv::Mat> faces = detFace.aGetsMat(cv::imread("images/lena.png", CV_8UC1));
		std::vector<cv::Mat> faces = detFace.aGetsMat(vImage, vCascadePath);
		for (size_t i = 0; i < faces.size(); i++)
		{
			//cv::imshow("image_" + vImageIndex + "_" + std::to_string(i), faces[i]);
			cv::imwrite(vDetectedFacePath + vImageIndex + "_" + std::to_string(i) + ".jpg", faces[i]);
		}
		vImageIndex = util.increaseNumber(vImageIndex, 1);
	}
}
//\\ Phat hien mat nguoi trong camera.
void aFaceDetectFromCamera()
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
	//aHeadPoseFaceDetect();
	aHeadPoseFaceTestDetect();
	////\\ Phat hien mat nguoi trong camera.
	//aFaceDetectFromCamera();

	cout << "Done.";
	_getwch();
	return 0;
}
