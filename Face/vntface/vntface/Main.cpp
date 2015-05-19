#include "Header\Utilities.h"
#include "Header\FaceDetect.h"
#include "Header\HeadPose.h"
#include "Header\FaceDataSet.h"
#include "Header\FaceTrackDB.h"

using namespace vnt;

//\\ Detect HeadPose with serie 1.
void aHeadPoseFaceDetectSerie1(std::string pCascadeName)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseFaceDetectSerie1: " << util.currentDateTime() << std::endl;

	std::string vPath = util.GetExePath();
	std::string vImagePath = vPath + "/VNTDataSet/DataSetHeadPoseDownload/";
	std::string vSavePath = vPath + "/VNTDataSet/DetectedFace/" + pCascadeName + "/";
	std::string vFolderPath = util.replaceAll(vSavePath, "/", "\\");
	util.makeDir(vFolderPath);
	//vSavePath += "Test/";
	//vFolderPath += "Test\\";
	//util.makeDir(vFolderPath);

	vnt::FaceDetect vFaceDetect;
	vFaceDetect.aLoadFaceCascade("cascades/" + pCascadeName + ".xml");
	HeadPose vHeadPose;
	vHeadPose.aSetSerie("1");
	std::string vFaceTrackName = "Person";
	std::string vFaceTrackIndex = "01";
	while (vFaceTrackIndex != "16")
	{
		//\\ Tao thu muc.
		util.makeDir(vFolderPath + vFaceTrackName + vFaceTrackIndex);
		std::vector<std::string> vImageNames = vHeadPose.aGetsAllFileName(vFaceTrackIndex);
		vFaceDetect.aGetsMat(vImageNames, vImagePath + vFaceTrackName + vFaceTrackIndex + "/", vSavePath + vFaceTrackName + vFaceTrackIndex + "/");
		vFaceTrackIndex = util.increaseNumber(vFaceTrackIndex, 1);
	}
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseFaceDetectSerie1: " << util.currentDateTime() << std::endl;
}
//\\ Detect HeadPose with serie 2.
void aHeadPoseFaceDetectSerie2(std::string pCascadeName)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseFaceDetectSerie2: " << util.currentDateTime() << std::endl;

	std::string vPath = util.GetExePath();
	std::string vImagePath = vPath + "/VNTDataSet/DataSetHeadPoseDownload/";
	std::string vSavePath = vPath + "/VNTDataSet/DetectedFace/" + pCascadeName + "/";
	std::string vFolderPath = util.replaceAll(vSavePath, "/", "\\");
	util.makeDir(vFolderPath);
	vSavePath += "Test/";
	vFolderPath += "Test\\";
	util.makeDir(vFolderPath);

	vnt::FaceDetect vFaceDetect;
	vFaceDetect.aLoadFaceCascade("cascades/" + pCascadeName + ".xml");
	HeadPose vHeadPose;
	vHeadPose.aSetSerie("2");
	std::string vFaceTrackName = "Person";
	std::string vFaceTrackIndex = "01";
	while (vFaceTrackIndex != "16")
	{
		//\\ Tao thu muc.
		util.makeDir(vFolderPath + vFaceTrackName + vFaceTrackIndex);
		std::vector<std::string> vImageNames = vHeadPose.aGetsAllFileName(vFaceTrackIndex);
		vFaceDetect.aGetsMat(vImageNames, vImagePath + vFaceTrackName + vFaceTrackIndex + "/", vSavePath + vFaceTrackName + vFaceTrackIndex + "/");
		vFaceTrackIndex = util.increaseNumber(vFaceTrackIndex, 1);
	}
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseFaceDetectSerie2: " << util.currentDateTime() << std::endl;
}
//\\ Detect HeadPose with serie 1 and 2.
void aHeadPoseFaceDetect()
{
	//std::string vCascadeName = "haarcascade_frontalface_default";
	std::string vCascadeName = "haarcascade_profileface";
	aHeadPoseFaceDetectSerie1(vCascadeName);
	aHeadPoseFaceDetectSerie2(vCascadeName);
}


//\\ Khoi tao DataSet: Serie 1 + Not Div
void aHeadPoseDataSetInitSerie1NotDiv()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseDataSetInitSerie1NotDiv: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/DataSetHeadPoseDetectedFace/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv");

	FaceDataSet vFaceDataSet;
	//\\ Khoi tao dataset.
	FaceDataSetBase* vFaceDataSetBase;
	HeadPose vHeadPose;
	vHeadPose.aSetSerie("1");
	vFaceDataSetBase = &vHeadPose;
	vFaceDataSet.aDataSetInitDiv(vFaceDataSetBase, vSourePath, vSavePath, 1);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aHeadPoseDataSetInitSerie1NotDiv: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao DataSet: Serie 1 + Div (3).
void aHeadPoseDataSetInitSerie1Div()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseDataSetInitSerie1Div: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/DataSetHeadPoseDetectedFace/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div");

	FaceDataSet vFaceDataSet;
	//\\ Khoi tao dataset.
	FaceDataSetBase* vFaceDataSetBase;
	HeadPose vHeadPose;
	vHeadPose.aSetSerie("1");
	vFaceDataSetBase = &vHeadPose;
	vFaceDataSet.aDataSetInitDiv(vFaceDataSetBase, vSourePath, vSavePath, 3, true);
	//\\ Do kich thuoc cac facetrack khong bang nhau nen phai chia lai:
	std::vector<std::vector<cv::Mat>> vFaceTracks = vFaceDataSet.aGetFaceTraks();
	size_t vFaceTracksSize = vFaceTracks.size();
	for (size_t i = 0; i < vFaceTracksSize; i++)
	{
		size_t vFaceTrackSize = vFaceTracks[i].size();

	}

	//\\ Hien thi thoi gian ket thuc.
	cout << "aHeadPoseDataSetInitSerie1Div: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao DataSet: Serie 2 + Not Div
void aHeadPoseDataSetInitSerie2NotDiv()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseDataSetInitSerie2NotDiv: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/DataSetHeadPoseDetectedFace/Test/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/Test/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\Test");

	FaceDataSet vFaceDataSet;
	//\\ Khoi tao dataset.
	FaceDataSetBase* vFaceDataSetBase;
	HeadPose vHeadPose;
	vHeadPose.aSetSerie("2");
	vFaceDataSetBase = &vHeadPose;
	vFaceDataSet.aDataSetInitDiv(vFaceDataSetBase, vSourePath, vSavePath, 1);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aHeadPoseDataSetInitSerie2NotDiv: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao DataSet: Serie 2 + Div (3).
void aHeadPoseDataSetInitSerie2Div()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aHeadPoseDataSetInitSerie2Div: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/DataSetHeadPoseDetectedFace/Test/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/Test/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\Test");

	FaceDataSet vFaceDataSet;
	//\\ Khoi tao dataset.
	FaceDataSetBase* vFaceDataSetBase;
	HeadPose vHeadPose;
	vHeadPose.aSetSerie("2");
	vFaceDataSetBase = &vHeadPose;
	vFaceDataSet.aDataSetInitDiv(vFaceDataSetBase, vSourePath, vSavePath, 3, true);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aHeadPoseDataSetInitSerie2Div: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao DataSet
void aHeadPoseDataSetInit()
{
	aHeadPoseDataSetInitSerie1NotDiv();
	aHeadPoseDataSetInitSerie1Div();
	aHeadPoseDataSetInitSerie2NotDiv();
	aHeadPoseDataSetInitSerie2Div();
}


//\\ Khoi tao features: Serie1 + Khong chia + co Pose.
void aFeaturesInitSerie1NotDivPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie1NotDivPose: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/NotDiv/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/Pose/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\Pose");

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead(0, 14, 0, 92, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInit(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetSumPose(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie1NotDivPose: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie1 + Khong chia + khong Pose.
void aFeaturesInitSerie1NotDivNotPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie1NotDivNotPose: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/NotDiv/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/NotPose/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\NotPose");

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead(0, 14, 0, 92, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInitNotPose(vFaceDataSet.aGetFaceTraks(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie1NotDivNotPose: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie1 + chia + co Pose.
void aFeaturesInitSerie1DivPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie1DivPose: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/Div/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/Pose/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\Pose");

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead(0, 44, 0, 30, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInit(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetSumPose(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie1DivPose: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie1 + chia + khong Pose.
void aFeaturesInitSerie1DivNotPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie1DivNotPose: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/Div/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/NotPose/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\NotPose");

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead(0, 44, 0, 30, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInitNotPose(vFaceDataSet.aGetFaceTraks(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie1DivNotPose: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie2 + Khong chia + co Pose.
void aFeaturesInitSerie2NotDivPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie2NotDivPose: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/NotDiv/Test/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/Test/Pose/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\Test\\Pose");

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead(0, 14, 0, 92, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInit(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetSumPose(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie2NotDivPose: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie2 + Khong chia + khong Pose.
void aFeaturesInitSerie2NotDivNotPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie2NotDivNotPose: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/NotDiv/Test/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/Test/NotPose/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\Test\\NotPose");

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead(0, 14, 0, 92, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInitNotPose(vFaceDataSet.aGetFaceTraks(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie2NotDivNotPose: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie2 + chia + co Pose.
void aFeaturesInitSerie2DivPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie2DivPose: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/Div/Test/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/Test/Pose/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\Test\\Pose");

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead(0, 44, 0, 30, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInit(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetSumPose(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie2DivPose: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie2 + chia + khong Pose.
void aFeaturesInitSerie2DivNotPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie2DivNotPose: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/Div/Test/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/Test/NotPose/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\Test\\NotPose");

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead(0, 44, 0, 30, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInitNotPose(vFaceDataSet.aGetFaceTraks(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie2DivNotPose: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao feature
void aFeaturesInit()
{
	aFeaturesInitSerie1NotDivPose();
	aFeaturesInitSerie1NotDivNotPose();
	aFeaturesInitSerie1DivPose();
	aFeaturesInitSerie1DivNotPose();
	aFeaturesInitSerie2NotDivPose();
	aFeaturesInitSerie2NotDivNotPose();
	aFeaturesInitSerie2DivPose();
	aFeaturesInitSerie2DivNotPose();
}


//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
void aDatabaseInit_Serie12_NotDiv_NotPoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_NotDiv_NotPoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "NotPose/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "NotPose/Normalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\" + util.replaceAll(pTestPath, "/", "\\") + "NotPose\\Normalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureReadNotPose(0, 14, 0, 92, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotPose(vFaceTrackDB.aGetFacetrackFeatures(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_NotDiv_NotPoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
void aDatabaseInit_Serie12_NotDiv_NotPoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_NotDiv_NotPoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "NotPose/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "NotPose/NotNormalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\" + util.replaceAll(pTestPath, "/", "\\") + "NotPose\\NotNormalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureReadNotPose(0, 14, 0, 92, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotPoseNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_NotDiv_NotPoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
void aDatabaseInit_Serie12_NotDiv_PoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie1_NotDiv_PoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "Pose/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "Pose/Normalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\" + util.replaceAll(pTestPath, "/", "\\") + "Pose\\Normalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead(0, 14, 0, 92, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInit(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetPoses(), vFaceTrackDB.aGetSumPose(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_NotDiv_PoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
void aDatabaseInit_Serie12_NotDiv_PoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_NotDiv_PoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "Pose/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "Pose/NotNormalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\" + util.replaceAll(pTestPath, "/", "\\") + "Pose\\NotNormalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead(0, 14, 0, 92, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetPoses(), vFaceTrackDB.aGetSumPose(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_NotDiv_PoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}

//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
void aDatabaseInit_Serie12_Div_NotPoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_Div_NotPoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/Div/" + pTestPath + "NotPose/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/" + pTestPath + "NotPose/Normalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\" + util.replaceAll(pTestPath, "/", "\\") + "NotPose\\Normalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureReadNotPose(0, 44, 0, 30, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotPose(vFaceTrackDB.aGetFacetrackFeatures(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_Div_NotPoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
void aDatabaseInit_Serie12_Div_NotPoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_Div_NotPoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/Div/" + pTestPath + "NotPose/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/" + pTestPath + "NotPose/NotNormalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\" + util.replaceAll(pTestPath, "/", "\\") + "NotPose\\NotNormalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureReadNotPose(0, 44, 0, 30, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotPoseNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_Div_NotPoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
void aDatabaseInit_Serie12_Div_PoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_Div_PoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/Div/" + pTestPath + "Pose/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/" + pTestPath + "Pose/Normalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\" + util.replaceAll(pTestPath, "/", "\\") + "Pose\\Normalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead(0, 44, 0, 30, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInit(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetPoses(), vFaceTrackDB.aGetSumPose(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_Div_PoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
void aDatabaseInit_Serie12_Div_PoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_Div_PoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/Div/" + pTestPath + "Pose/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/" + pTestPath + "Pose/NotNormalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\" + util.replaceAll(pTestPath, "/", "\\") + "Pose\\NotNormalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead(0, 44, 0, 30, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetPoses(), vFaceTrackDB.aGetSumPose(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_Div_PoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}

//\\ Khoi tao csdl.
void aDatabaseInit()
{
	aDatabaseInit_Serie12_NotDiv_NotPoseNormalize("");
	aDatabaseInit_Serie12_NotDiv_NotPoseNotNormalize("");
	aDatabaseInit_Serie12_NotDiv_PoseNormalize("");
	aDatabaseInit_Serie12_NotDiv_PoseNotNormalize("");
	aDatabaseInit_Serie12_Div_NotPoseNormalize("");
	aDatabaseInit_Serie12_Div_NotPoseNotNormalize("");
	aDatabaseInit_Serie12_Div_PoseNormalize("");
	aDatabaseInit_Serie12_Div_PoseNotNormalize("");

	aDatabaseInit_Serie12_NotDiv_NotPoseNormalize("Test/");
	aDatabaseInit_Serie12_NotDiv_NotPoseNotNormalize("Test/");
	aDatabaseInit_Serie12_NotDiv_PoseNormalize("Test/");
	aDatabaseInit_Serie12_NotDiv_PoseNotNormalize("Test/");
	aDatabaseInit_Serie12_Div_NotPoseNormalize("Test/");
	aDatabaseInit_Serie12_Div_NotPoseNotNormalize("Test/");
	aDatabaseInit_Serie12_Div_PoseNormalize("Test/");
	aDatabaseInit_Serie12_Div_PoseNotNormalize("Test/");
}


std::vector<int> aMatching(FaceTrackDB pFaceTrackDB, FaceTrackDB pFaceTrackDBTest, int pNum)
{
	std::vector<int> result;
	std::vector<std::vector<std::vector<std::vector<double>>>> csdl = pFaceTrackDB.aGetFaceTrackDatabase();
	std::vector<std::vector<std::vector<std::vector<double>>>> csdlTest = pFaceTrackDBTest.aGetFaceTrackDatabase();
	/*
	- Lap qua 15 mat nguoi goc.
	- Lap qua 3 mat nguoi duoc chia nho cua tung mat nguoi goc.
	- So khop tung mat nguoi voi csdl facetrack: ket qua la thu tu so khop.
	- Tinh do chinh xac MAP.
	*/
	std::vector<double> vAPs;
	size_t n = csdlTest.size() / pNum;
	//\\ Lap n mat nguoi goc.
	for (size_t i = 0; i < n; i++)
	{
		//\\ Lap qua m mat nguoi dung.
		for (size_t j = 0; j < pNum; j++)
		{
			int indexQuery = i * pNum + j;
			//\\ Lay query tu csdl1.
			std::vector<std::vector<std::vector<double>>> vQuery = csdlTest[indexQuery];
			//\\ So khop.
			std::vector<int> vMatchingIndex = pFaceTrackDB.aMeanCosMatchingIndex(vQuery, csdl);
			if (vMatchingIndex[0] == i)
			{
				result.push_back(indexQuery);
			}
		}
	}
	return result;
}
//\\ So khop: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia).
std::vector<int> aMatchingHeadPose_NotDiv_Div(std::string pDatabasePath, std::string pQueryPath, int pNum)
{
	std::vector<int> result;
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << pDatabasePath + " - " + pQueryPath + " : " << util.currentDateTime() << std::endl;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";

	FaceTrackDB vFaceTrackDB;
	FaceTrackDB vFaceTrackDBQuery;
	//\\ Doc csdl: Co n x m mat nguoi (moi mat nguoi goc chia thanh m mat nguoi)
	vFaceTrackDB.aDatabaseRead(0, 14, 0, 0, vDataSetPath + pDatabasePath);
	//\\ Doc dataset: Co n x m mat nguoi tuong ung voi csdl de kiem tra.
	vFaceTrackDBQuery.aDatabaseRead(0, 44, 0, 0, vDataSetPath + pQueryPath);

	//\\ So khop tung facetrack trong DBTest.
	result = aMatching(vFaceTrackDB, vFaceTrackDBQuery, pNum);
	int countTrue = result.size();
	size_t querySize = vFaceTrackDBQuery.aGetFaceTrackDatabase().size();
	//\\ Hien thi thoi gian ket thuc.
	cout << pDatabasePath + " - " + pQueryPath + " : " << util.currentDateTime() << std::endl;
	cout << "countTrue: " << countTrue << "/ " << querySize << " = " << 1.0 * countTrue / querySize << std::endl;
	return result;
}
//\\ So khop:
void aMatchingHeadPose()
{
	//\\ Csdl khong chia. Query chia 3. Query trong csdl.
	std::vector<int> result1 = aMatchingHeadPose_NotDiv_Div("NotDiv/NotPose/Normalize/", "Div/NotPose/Normalize/", 3);//\\ Khong co Pose + csdl co chuan hoa.
	std::vector<int> result2 = aMatchingHeadPose_NotDiv_Div("NotDiv/NotPose/NotNormalize/", "Div/NotPose/NotNormalize/", 3);//\\ Khong co Pose + csdl khong chuan hoa.
	std::vector<int> result3 = aMatchingHeadPose_NotDiv_Div("NotDiv/Pose/Normalize/", "Div/Pose/Normalize/", 3);//\\ Co Pose + co chuan hoa.
	std::vector<int> result4 = aMatchingHeadPose_NotDiv_Div("NotDiv/Pose/NotNormalize/", "Div/Pose/NotNormalize/", 3);//\\ Co Pose + khong chuan hoa.

	//\\ Csdl khong chia. Query chia 3. Query trong test.
	std::vector<int> result5 = aMatchingHeadPose_NotDiv_Div("NotDiv/NotPose/Normalize/", "Div/Test/NotPose/Normalize/", 3);//\\ Khong co Pose + csdl co chuan hoa.
	std::vector<int> result6 = aMatchingHeadPose_NotDiv_Div("NotDiv/NotPose/NotNormalize/", "Div/Test/NotPose/NotNormalize/", 3);//\\ Khong co Pose + csdl khong chuan hoa.
	std::vector<int> result7 = aMatchingHeadPose_NotDiv_Div("NotDiv/Pose/Normalize/", "Div/Test/Pose/Normalize/", 3);//\\ Co Pose + co chuan hoa.
	std::vector<int> result8 = aMatchingHeadPose_NotDiv_Div("NotDiv/Pose/NotNormalize/", "Div/Test/Pose/NotNormalize/", 3);//\\ Co Pose + khong chuan hoa.
}


// Function main
int main(void)
{
	//\\ Phat hien mat nguoi trong anh.
	//aHeadPoseFaceDetect();

	//\\ Khoi tao DataSet
	//aHeadPoseDataSetInit();

	//\\ Khoi tao Feature
	//aFeaturesInit();

	//\\ Khoi tao Database
	//aDatabaseInit();

	//\\ So khop
	aMatchingHeadPose();

	cout << "Done.";
	_getwch();
	return 0;
}
