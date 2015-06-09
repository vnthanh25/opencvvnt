#include "..\Header\Matching.h"

using namespace vnt;

//\\ Detect HeadPose with serie 1.
void Matching::aHeadPoseFaceDetectSerie1(std::string pCascadeName)
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
void Matching::aHeadPoseFaceDetectSerie2(std::string pCascadeName)
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
void Matching::aHeadPoseFaceDetect()
{
	//std::string vCascadeName = "haarcascade_frontalface_default";
	std::string vCascadeName = "haarcascade_profileface";
	aHeadPoseFaceDetectSerie1(vCascadeName);
	aHeadPoseFaceDetectSerie2(vCascadeName);
}


//\\ Khoi tao DataSet: Serie 1 + Not Div
void Matching::aHeadPoseDataSetInitSerie1NotDiv()
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
	vFaceDataSet.aDataSetInitDiv(vFaceDataSetBase, vSourePath, vSavePath, 1, true);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aHeadPoseDataSetInitSerie1NotDiv: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao DataSet: Serie 1 + Div (3).
void Matching::aHeadPoseDataSetInitSerie1Div()
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

	//\\ Hien thi thoi gian ket thuc.
	cout << "aHeadPoseDataSetInitSerie1Div: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao DataSet: Serie 2 + Not Div
void Matching::aHeadPoseDataSetInitSerie2NotDiv()
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
	vFaceDataSet.aDataSetInitDiv(vFaceDataSetBase, vSourePath, vSavePath, 1, true);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aHeadPoseDataSetInitSerie2NotDiv: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao DataSet: Serie 2 + Div (3).
void Matching::aHeadPoseDataSetInitSerie2Div()
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
void Matching::aHeadPoseDataSetInit()
{
	aHeadPoseDataSetInitSerie1NotDiv();
	aHeadPoseDataSetInitSerie1Div();
	aHeadPoseDataSetInitSerie2NotDiv();
	aHeadPoseDataSetInitSerie2Div();
}


//\\ Khoi tao features: Serie1 + Khong chia + co Pose.
void Matching::aFeaturesInitSerie1NotDiv()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie1NotDiv: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/NotDiv/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/";

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead3(0, 14, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInit3(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetFileNames(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetPoseNames(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie1NotDiv: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie1 + chia + co Pose.
void Matching::aFeaturesInitSerie1Div()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie1Div: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/Div/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/";

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead3(0, 44, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInit3(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetFileNames(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetPoseNames(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie1Div: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie2 + Khong chia + co Pose.
void Matching::aFeaturesInitSerie2NotDiv()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie2NotDiv: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/NotDiv/Test/";
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/Test/";

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead3(0, 14, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInit3(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetFileNames(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetPoseNames(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie2NotDiv: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features: Serie2 + chia + co Pose.
void Matching::aFeaturesInitSerie2Div()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aFeaturesInitSerie2Div: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/Div/Test/";
	std::string vSavePath = vPath + "/VNTDataSet/Div/Test/";

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead3(0, 44, vSourePath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInit3(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetFileNames(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetPoseNames(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aFeaturesInitSerie2Div: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao feature
void Matching::aFeaturesInit()
{
	//aFeaturesInitSerie1NotDiv();
	aFeaturesInitSerie1Div();
	//aFeaturesInitSerie2NotDiv();
	//aFeaturesInitSerie2Div();
}


//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
void Matching::aDatabaseInit_Serie12_NotDiv_NotPoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_NotDiv_NotPoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath;
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "NotPose/Normalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\" + util.replaceAll(pTestPath, "/", "\\") + "NotPose\\Normalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead3(0, 14, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotPose(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetFileNames(), vFaceTrackDB.aGetPoses(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_NotDiv_NotPoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
void Matching::aDatabaseInit_Serie12_NotDiv_NotPoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_NotDiv_NotPoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath;
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "NotPose/NotNormalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\" + util.replaceAll(pTestPath, "/", "\\") + "NotPose\\NotNormalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead3(0, 14, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotPoseNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetFileNames(), vFaceTrackDB.aGetPoses(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_NotDiv_NotPoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
void Matching::aDatabaseInit_Serie12_NotDiv_PoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie1_NotDiv_PoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath;
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "Pose/Normalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\" + util.replaceAll(pTestPath, "/", "\\") + "Pose\\Normalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead3(0, 14, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInit(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetFileNames(), vFaceTrackDB.aGetPoses(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_NotDiv_PoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
void Matching::aDatabaseInit_Serie12_NotDiv_PoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_NotDiv_PoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath;
	std::string vSavePath = vPath + "/VNTDataSet/NotDiv/" + pTestPath + "Pose/NotNormalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\NotDiv\\" + util.replaceAll(pTestPath, "/", "\\") + "Pose\\NotNormalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead3(0, 14, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetFileNames(), vFaceTrackDB.aGetPoses(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_NotDiv_PoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}

//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
void Matching::aDatabaseInit_Serie12_Div_NotPoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_Div_NotPoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/Div/" + pTestPath;
	std::string vSavePath = vPath + "/VNTDataSet/Div/" + pTestPath + "NotPose/Normalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\" + util.replaceAll(pTestPath, "/", "\\") + "NotPose\\Normalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead3(0, 44, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotPose(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetFileNames(), vFaceTrackDB.aGetPoses(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_Div_NotPoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
void Matching::aDatabaseInit_Serie12_Div_NotPoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_Div_NotPoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/Div/" + pTestPath;
	std::string vSavePath = vPath + "/VNTDataSet/Div/" + pTestPath + "NotPose/NotNormalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\" + util.replaceAll(pTestPath, "/", "\\") + "NotPose\\NotNormalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead3(0, 44, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotPoseNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetFileNames(), vFaceTrackDB.aGetPoses(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_Div_NotPoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
void Matching::aDatabaseInit_Serie12_Div_PoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_Div_PoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/Div/" + pTestPath;
	std::string vSavePath = vPath + "/VNTDataSet/Div/" + pTestPath + "Pose/Normalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\" + util.replaceAll(pTestPath, "/", "\\") + "Pose\\Normalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead3(0, 44, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInit(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetFileNames(), vFaceTrackDB.aGetPoses(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_Div_PoseNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
void Matching::aDatabaseInit_Serie12_Div_PoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aDatabaseInit_Serie12_Div_PoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourcePath = vPath + "/VNTDataSet/Div/" + pTestPath;
	std::string vSavePath = vPath + "/VNTDataSet/Div/" + pTestPath + "Pose/NotNormalize/";
	util.makeDir(vExePath + "\\VNTDataSet\\Div\\" + util.replaceAll(pTestPath, "/", "\\") + "Pose\\NotNormalize");

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead3(0, 44, vSourcePath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetFileNames(), vFaceTrackDB.aGetPoses(), vSavePath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aDatabaseInit_Serie12_Div_PoseNotNormalize: " + pTestPath << util.currentDateTime() << std::endl;
}

//\\ Khoi tao csdl.
void Matching::aDatabaseInit()
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


std::vector<int> Matching::aMatching(FaceTrackDB pFaceTrackDB, FaceTrackDB pFaceTrackDBQuery, int pNum)
{
	std::vector<int> result;
	std::vector<std::vector<std::vector<std::vector<double>>>> vDatabase = pFaceTrackDB.aGetFaceTrackDatabase();
	std::vector<std::vector<std::vector<std::vector<double>>>> vDatabaseQuery = pFaceTrackDBQuery.aGetFaceTrackDatabase();
	std::vector<std::vector<std::vector<std::vector<int>>>> vFeatrues = pFaceTrackDB.aGetFacetrackFeatures();
	std::vector<std::vector<std::vector<std::vector<int>>>> vFeatruesQuery = pFaceTrackDBQuery.aGetFacetrackFeatures();
	std::vector<std::vector<std::string>> vPoseNames = pFaceTrackDB.aGetPoseNames();
	std::vector<std::vector<std::string>> vPoseNamesQuery = pFaceTrackDBQuery.aGetPoseNames();
	/*
	- Lap qua 15 mat nguoi goc.
	- Lap qua 3 mat nguoi duoc chia nho cua tung mat nguoi goc.
	- So khop tung mat nguoi voi csdl facetrack: ket qua la thu tu so khop.
	- Tinh do chinh xac MAP.
	*/
	std::vector<double> vAPs;
	size_t n = vDatabaseQuery.size() / pNum;

	ofstream of("Doc/Matching.txt", std::ofstream::app);
	std::vector<int> vFalses;
	//\\ Lap n mat nguoi goc.
	for (size_t i = 0; i < n; i++)
	{
		//\\ Lap qua m mat nguoi dung.
		for (size_t j = 0; j < pNum; j++)
		{
			int indexQuery = i * pNum + j;
			//\\ Lay query tu csdl.
			std::vector<std::vector<std::vector<double>>> vQuery = vDatabaseQuery[indexQuery];
			//\\ Lay feature cua query.
			std::vector<std::vector<std::vector<int>>> vFeatureQuery = vFeatruesQuery[indexQuery];
			//\\ Lay filename cua query.
			std::vector<std::string> vPoseName = vPoseNamesQuery[indexQuery];
			//\\ So khop.
			std::vector<int> vMatchingIndex = pFaceTrackDB.aMeanCosMatchingIndex3(vQuery, vDatabase, vFeatureQuery, vFeatrues, vPoseName, vPoseNames, 0);

			of << "MatchingIndex " << std::to_string(indexQuery) << " - " << std::to_string(i) << " : ";
			for (size_t k = 0; k < vMatchingIndex.size(); k++)
			{
				of << vMatchingIndex[k] << " ";
			}

			if (vMatchingIndex[0] == i)
			{
				of << "(=)";
				result.push_back(indexQuery);
			}
			else
			{
				of << "(*)";
				vFalses.push_back(indexQuery);
			}

			of << endl << endl;
		}
	}
	of << "vFalses(" << std::to_string(vFalses.size()) << "): ";
	for (size_t i = 0; i < vFalses.size(); i++)
	{
		of << vFalses[i] << " ";
	}
	of << std::endl;
	of.close();

	return result;
}
//\\ So khop: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia).
std::vector<int> Matching::aMatchingHeadPose_NotDiv_Div(std::string pDatabasePath, std::string pQueryPath, std::string pDatabaseFeaturePath, std::string pQueryFeaturePath, int pNum)
{
	ofstream of("Doc/Matching.txt", std::ofstream::app);
	std::vector<int> result;
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << pDatabasePath + " - " + pQueryPath + " : " << util.currentDateTime() << std::endl;
	of << "MatchingHeadPose: " << pDatabasePath + " - " + pQueryPath + " : " << util.currentDateTime() << std::endl;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";

	FaceTrackDB vFaceTrackDB;
	FaceTrackDB vFaceTrackDBQuery;

	//\\ Doc csdl: Co n mat nguoi goc.
	vFaceTrackDB.aDatabaseAndFeatureRead(0, 14, vDataSetPath + pDatabasePath, vDataSetPath + pDatabaseFeaturePath);
	//\\ Doc csdl: Co n x m mat nguoi tuong ung voi csdl de kiem tra.
	vFaceTrackDBQuery.aDatabaseAndFeatureRead(0, 44, vDataSetPath + pQueryPath, vDataSetPath + pQueryFeaturePath);

	//\\ So khop tung facetrack trong DBTest.
	result = aMatching(vFaceTrackDB, vFaceTrackDBQuery, pNum);

	//\\ Hien thi thoi gian va ket qua.
	int countTrue = result.size();
	size_t querySize = vFaceTrackDBQuery.aGetFaceTrackDatabase().size();
	cout << pDatabasePath + " - " + pQueryPath + " : " << util.currentDateTime() << std::endl;
	cout << "countTrue: " << countTrue << " / " << querySize << " = " << 1.0 * countTrue / querySize << std::endl;
	of << "MatchingHeadPose: " << pDatabasePath + " - " + pQueryPath + " : " << util.currentDateTime() << " ";
	of << "countTrue: " << countTrue << " / " << querySize << " = " << 1.0 * countTrue / querySize << std::endl;
	of << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << std::endl;
	of.close();
	return result;
}
//\\ So khop:
void Matching::aMatchingHeadPose()
{
	//ofstream of("Doc/Matching.txt");
	//of.clear();
	//of.close();

	////\\ Csdl khong chia. Query chia 3. Query trong csdl.
	//std::vector<int> result1 = aMatchingHeadPose_NotDiv_Div("NotDiv/NotPose/Normalize/", "Div/NotPose/Normalize/", "NotDiv/", "Div/", 3);//\\ Khong co Pose + csdl co chuan hoa.
	//std::vector<int> result2 = aMatchingHeadPose_NotDiv_Div("NotDiv/NotPose/NotNormalize/", "Div/NotPose/NotNormalize/", "NotDiv/", "Div/", 3);//\\ Khong co Pose + csdl khong chuan hoa.
	//std::vector<int> result3 = aMatchingHeadPose_NotDiv_Div("NotDiv/Pose/Normalize/", "Div/Pose/Normalize/", "NotDiv/", "Div/", 3);//\\ Co Pose + co chuan hoa.
	//std::vector<int> result4 = aMatchingHeadPose_NotDiv_Div("NotDiv/Pose/NotNormalize/", "Div/Pose/NotNormalize/", "NotDiv/", "Div/", 3);//\\ Co Pose + khong chuan hoa.

	////\\ Csdl khong chia. Query chia 3. Query trong test.
	//std::vector<int> result5 = aMatchingHeadPose_NotDiv_Div("NotDiv/NotPose/Normalize/", "Div/Test/NotPose/Normalize/", "NotDiv/", "Div/Test/", 3);//\\ Khong co Pose + csdl co chuan hoa.
	std::vector<int> result6 = aMatchingHeadPose_NotDiv_Div("NotDiv/NotPose/NotNormalize/", "Div/Test/NotPose/NotNormalize/", "NotDiv/", "Div/Test/", 3);//\\ Khong co Pose + csdl khong chuan hoa.
	//std::vector<int> result7 = aMatchingHeadPose_NotDiv_Div("NotDiv/Pose/Normalize/", "Div/Test/Pose/Normalize/", "NotDiv/", "Div/Test/", 3);//\\ Co Pose + co chuan hoa.
	//std::vector<int> result8 = aMatchingHeadPose_NotDiv_Div("NotDiv/Pose/NotNormalize/", "Div/Test/Pose/NotNormalize/", "NotDiv/", "Div/Test/", 3);//\\ Co Pose + khong chuan hoa.
}


//\\ Tinh vector dac trung trung binh.
std::vector<std::vector<double>> Matching::aFeatureAvg(std::string pSourcePath, bool pIsPose)
{
	std::vector<std::vector<double>> result;
	Utilites util;
	//\\ Khoi tao dataset.
	HeadPose vHeadPose;

	//\\ Lay tat ca ten file anh.
	std::vector<std::vector<std::string>> vAllFileNames;
	std::vector<std::vector<int>> vAllPoses;
	std::vector<std::string> vAllIds = vHeadPose.aGetsAllIds();
	for (size_t i = 0; i < vAllIds.size(); i++)
	{
		std::string vId = vAllIds[i];
		std::vector<std::string> vFileNames = vHeadPose.aGetsAllFileName(vId);
		std::vector<int> vPoses = vHeadPose.aGetsAllPose(vId);
		vAllFileNames.push_back(vFileNames);
		vAllPoses.push_back(vPoses);
	}
	//\\ Doc anh va chuyen thanh doi tuong Mat.
	std::vector<cv::Mat> vFaceTrack;
	std::vector<int> vPoses;
	for (size_t i = 0; i < vAllFileNames.size(); i++)
	{
		for (size_t j = 0; j < vAllFileNames[i].size(); j++)
		{
			cv::Mat vFace = cv::imread(pSourcePath + vAllFileNames[i][j], CV_8UC1);
			if (!vFace.empty())
			{
				vFaceTrack.push_back(vFace);
				vPoses.push_back(vAllPoses[i][j]);
			}
		}
	}

	//\\ Tinh vector dac trung.
	FaceTrackDB vFaceTrackDB;
	std::vector<std::vector<std::vector<int>>> vFeatures = vFaceTrackDB.aGetsFeature(vFaceTrack);

	if (pIsPose)
	{
		//\\ Tinh vector dac trung trung binh. Co tich hop Pose.
		result = vFaceTrackDB.aAvgFeature1(vFeatures, vPoses);
	}
	else
	{
		//\\ Tinh vector dac trung trung binh. Khong co tich hop Pose.
		result = vFaceTrackDB.aAvgFeatureNotPose1(vFeatures);
	}
	return result;
}
void Matching::aMatchingHeadPoseCheck(bool pIsPose)
{
	ofstream of("Doc/MatchingFull.txt", std::ofstream::app);

	Utilites util;
	//\\ Hien thi thoi gian.
	if (pIsPose)
	{
		cout << "aMatchingHeadPoseCheck (Pose): " << util.currentDateTime() << std::endl;
		of << "aMatchingHeadPoseCheck (Pose): " << util.currentDateTime() << std::endl;
	}
	else
	{
		cout << "aMatchingHeadPoseCheck (NotPose): " << util.currentDateTime() << std::endl;
		of << "aMatchingHeadPoseCheck (NotPose): " << util.currentDateTime() << std::endl;
	}

	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath();
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	std::string vSourePath = vPath + "/VNTDataSet/NotDiv/DataSet/FaceTrack";
	std::string vIndexQuery = "9";
	std::string vSoureQuery = vPath + "/VNTDataSet/Div/DataSet/FaceTrack" + vIndexQuery + "/";
	cout << "vIndexQuery: " << vIndexQuery << std::endl;
	of << "vIndexQuery: " << vIndexQuery << std::endl;

	//\\ Tinh vector dac trung trung binh cua Facetrack Query.
	std::vector<std::vector<double>> vFeatureAvgQuery = aFeatureAvg(vSoureQuery, pIsPose);
	//\\ Tinh vector dac trung trung binh cua csdl.
	std::vector<std::vector<std::vector<double>>> vFeatureAvgs;
	for (size_t i = 0; i < 15; i++)
	{
		std::vector<std::vector<double>> vFeatureAvg = aFeatureAvg(vSourePath + std::to_string(i) + "/", pIsPose);
		vFeatureAvgs.push_back(vFeatureAvg);
	}
	//\\ So khop.
	FaceTrackDB vFaceTrackDB;
	for (size_t i = 0; i < vFeatureAvgs.size(); i++)
	{
		double vCosine = vFaceTrackDB.aCosine1(vFeatureAvgQuery, vFeatureAvgs[i]);
		cout << std::to_string(i) << " vCosine: " << vCosine << std::endl;
		of << std::to_string(i) << " vCosine: " << vCosine << std::endl;
	}
	//\\ Hien thi thoi gian.
	if (pIsPose)
	{
		cout << "aMatchingHeadPoseCheck (Pose): " << util.currentDateTime() << std::endl;
		of << "aMatchingHeadPoseCheck (Pose): " << util.currentDateTime() << std::endl;
	}
	else
	{
		cout << "aMatchingHeadPoseCheck (NotPose): " << util.currentDateTime() << std::endl;
		of << "aMatchingHeadPoseCheck (NotPose): " << util.currentDateTime() << std::endl;
	}
	of << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << std::endl;
	of.close();
}
void Matching::aMatchingHeadPoseCheck()
{
	aMatchingHeadPoseCheck(false);
	aMatchingHeadPoseCheck(true);
}



double Matching::aMatchingHeadPoseMAP1(std::string pDatabasePath)
{
	ofstream of("Doc/Matching.txt", std::ofstream::app);
	double result;
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	std::cout << pDatabasePath + " : " << util.currentDateTime() << std::endl;
	of << "MatchingHeadPoseMAP: " << pDatabasePath + " : " << util.currentDateTime() << std::endl;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";

	FaceTrackDB vFaceTrackDB;

	size_t n = 30;
	//\\ Doc csdl: Facetrack 0->15 la csdl (serie1) va 16->29 la test (serie2).
	vFaceTrackDB.aDatabaseRead3(0, n - 1, vDataSetPath + pDatabasePath);

	std::vector<std::vector<std::vector<std::vector<double>>>> vDatabase = vFaceTrackDB.aGetFaceTrackDatabase();

	double vMAP = 0;
	//\\ Lap n mat nguoi.
	for (size_t i = 0; i < n; i++)
	{
		std::vector<std::vector<std::vector<double>>> vQuery = vDatabase[i];
		//\\ So khop.
		std::vector<int> vMatchingIndex = vFaceTrackDB.aMeanCosMatchingIndex1(vQuery, vDatabase);
		//\\ Tinh do chinh xa.
		double Nr = 1;
		int vCountTrue = 0;
		size_t vMatchingIndexSize = vMatchingIndex.size();
		//\\ Tim gia tri index dung trong ket qua MatchingIndex tra ve.
		for (size_t k = 0; k < vMatchingIndexSize; k++)
		{
			//\\ Gia tri index dung trong tham so truyen vao la tu i*m den i*m + m.
			if (i == vMatchingIndex[k] || vMatchingIndex[k] == i + n / 2)
			{
				//\\ Tinh AP.
				vMAP += Nr / (k + 1);
				Nr++;
				vCountTrue++;
			}
		}
		vMAP /= vCountTrue;
	}
	//\\ Tinh AP trung binh. AP chia m mat nguoi dung. (m = 6).
	vMAP /= n;

	//\\ Hien thi thoi gian va ket qua.
	std::cout << pDatabasePath + " : " << util.currentDateTime() << std::endl;
	std::cout << "MeanCos: " << vMAP << std::endl;
	of << "MatchingHeadPoseMAP: " << pDatabasePath + " : " << util.currentDateTime() << " ";
	of << "MeanCos: " << vMAP << std::endl;
	of << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << std::endl;
	of.close();

	result = vMAP;
	return result;
}

double Matching::aMatchingHeadPoseMAP2(std::string pDatabasePath, std::string pDatabaseFeaturePath, int pCountMax)
{
	ofstream of("Doc/Matching.txt", std::ofstream::app);
	double result;
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	std::cout << pDatabasePath + " : " << util.currentDateTime() << std::endl;
	of << "MatchingHeadPoseMAP: " << pDatabasePath + " : " << util.currentDateTime() << std::endl;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";

	FaceTrackDB vFaceTrackDB;

	size_t n = 30;
	//\\ Doc csdl: Facetrack 0->15 la csdl (serie1) va 16->29 la test (serie2).
	vFaceTrackDB.aDatabaseAndFeatureRead(0, n - 1, vDataSetPath + pDatabasePath, vDataSetPath + pDatabaseFeaturePath);

	std::vector<std::vector<std::vector<std::vector<double>>>> vDatabase = vFaceTrackDB.aGetFaceTrackDatabase();
	std::vector<std::vector<std::vector<std::vector<int>>>> vFeatrues = vFaceTrackDB.aGetFacetrackFeatures();
	std::vector<std::vector<std::string>> vPoseNames = vFaceTrackDB.aGetPoseNames();

	double vMAPAll = 0;
	int vCountTrue = 0;
	//\\ Lap n mat nguoi.
	for (size_t i = 0; i < n; i++)
	{
		std::vector<std::vector<std::vector<double>>> vQuery = vDatabase[i];
		//\\ Lay feature cua query.
		std::vector<std::vector<std::vector<int>>> vFeatureQuery = vFeatrues[i];
		//\\ Lay filename cua query.
		std::vector<std::string> vPoseName = vPoseNames[i];
		//\\ So khop.
		std::vector<int> vMatchingIndex = vFaceTrackDB.aMeanCosMatchingIndex3(vQuery, vDatabase, vFeatureQuery, vFeatrues, vPoseName, vPoseNames, pCountMax);
		//\\ Tinh do chinh xa.
		double vMAP = 0;
		double Nr = 0;
		size_t vMatchingIndexSize = vMatchingIndex.size();
		std::cout << "vMatchingIndex: query:" + std::to_string(i);
		of << "vMatchingIndex: query:" + std::to_string(i);
		std::string vMatch = "01";
		std::string vMatchResult = "";
		//\\ Tim gia tri index dung trong ket qua MatchingIndex tra ve.
		for (size_t k = 0; k < vMatchingIndexSize; k++)
		{
			//\\ Gia tri index dung trong tham so truyen vao la tu i*m den i*m + m.
			//if (i == vMatchingIndex[k] || vMatchingIndex[k] == i + n / 2)
			if (i % 15 == vMatchingIndex[k] % 15)
			{
				//\\ Tinh AP.
				Nr++;
				vMAP += Nr / (k + 1);
				std::cout << " facetrack:" + std::to_string(vMatchingIndex[k]) + " index:" + std::to_string(k);
				of << " facetrack:" + std::to_string(vMatchingIndex[k]) + " index:" + std::to_string(k);
				vMatchResult += std::to_string(k);
			}
		}
		//vMAPAll += vMAP / Nr;
		vMAP /= Nr;
		vMAPAll += vMAP;
		std::cout << " AP=(1 + 2/(index+1))/2:" + std::to_string(vMAP);
		of << " AP=(1 + 2/(index+1))/2:" + std::to_string(vMAP);
		if (vMatch == vMatchResult)
		{
			vCountTrue++;
			std::cout << " (=)";
			of << " (=)";
		}
		else
		{
			std::cout << " (*)";
			of << " (*)";
		}
		std::cout << std::endl;
		of << std::endl;
		of << std::endl;
	}
	//\\ Tinh AP trung binh. AP chia m mat nguoi dung. (m = 6).
	vMAPAll /= n;

	//\\ Hien thi thoi gian va ket qua.
	std::cout << pDatabasePath + " : " << util.currentDateTime() << std::endl;
	std::cout << "CountTrue: " << vCountTrue << " Size: " << n << " MeanCos: " << vMAPAll << std::endl;
	of << "MatchingHeadPoseMAP: " << pDatabasePath + " : " << util.currentDateTime() << " ";
	of << "CountTrue: " << vCountTrue << " Size: " << n << " MeanCos: " << vMAPAll << std::endl;
	of << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << "---------------------------------------------------------------------------------------------------------" << std::endl;
	of << std::endl;
	of.close();

	result = vMAPAll;
	return result;
}
//\\ Tron serie1 va serie2 cua HeadPose de lam csdl va tinh MAP.
void Matching::aMatchingHeadPoseMAP()
{
	//ofstream of("Doc/Matching.txt");
	//of.clear();
	//of.close();

	//double vMAP1 = aMatchingHeadPoseMAP1("NotDiv/NotPose/NotNormalize/");
	//double vMAP2 = aMatchingHeadPoseMAP1("NotDiv/Pose/NotNormalize/");
	//double vMAP3 = aMatchingHeadPoseMAP1("NotDiv/NotPose/Normalize/");
	//double vMAP4 = aMatchingHeadPoseMAP1("NotDiv/Pose/Normalize/");

	int vCountMax = 0;
	double vMAP1 = aMatchingHeadPoseMAP2("NotDiv/NotPose/NotNormalize/", "NotDiv/", vCountMax);
	double vMAP2 = aMatchingHeadPoseMAP2("NotDiv/Pose/NotNormalize/", "NotDiv/", vCountMax);
	double vMAP3 = aMatchingHeadPoseMAP2("NotDiv/NotPose/Normalize/", "NotDiv/", vCountMax);
	double vMAP4 = aMatchingHeadPoseMAP2("NotDiv/Pose/Normalize/", "NotDiv/", vCountMax);
}
