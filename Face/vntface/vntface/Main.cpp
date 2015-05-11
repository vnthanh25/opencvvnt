#include "Header\Utilities.h"
#include "Header\FaceDataSet.h"
#include "Header\ColorFeret.h"
#include "Header\HeadPose.h"
#include "Header\FaceTrackDB.h"
#include "Header\VNTDataSet.h"

using namespace vnt;

/*
- Doc cac file anh trong thu muc cua "HeadPose" thanh doi tuong Mat. Luu cac doi tuong Mat nay vao trong FaceDataSet.
- Khoi tao csdl:
+ Rut trich dac trung LBP (la vector 2 chieu kieu int) cua tat ca anh (bo tri theo facetrack).
+ Luu vao doi tuong FaceTrackDB (co ghi ra file).
*/

//\\ Khoi tao dataset
void aMeanCosDataSetInitDiv()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosVNTDataSetInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";
	std::string vSourePath = exePath + "/VNTDataSet/DataSetHeadPoseDownload/";

	FaceDataSet vFaceDataSet;
	//\\ Khoi tao dataset.
	FaceDataSetBase* vFaceDataSetBase;
	HeadPose vHeadPose;
	vFaceDataSetBase = &vHeadPose;
	vFaceDataSet.aDataSetInitDiv(vFaceDataSetBase, vSourePath, vDataSetPath, 1);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aMeanCosVNTDataSetInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao features.
void aMeanCosFeaturesInitDiv()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosVNTDataSetInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";

	FaceDataSet vFaceDataSet;
	//\\ Doc facetrack vao DataSet.
	vFaceDataSet.aDataSetRead("00", "14", "00", "92", vDataSetPath);

	FaceTrackDB vFaceTrackDB;
	//\\ Khoi tao features.
	vFaceTrackDB.aFeatureInit(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetSumPose(), vDataSetPath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aMeanCosVNTDataSetInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl.
void aMeanCosDatabaseInitDiv()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead("00", "14", "00", "92", vDataSetPath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInit(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetPoses(), vFaceTrackDB.aGetSumPose(), vDataSetPath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl. Not pose
void aMeanCosDatabaseInitDivNotPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureReadNotPose("00", "14", "00", "92", vDataSetPath);
	//\\ Khoi tao csdl.
	vFaceTrackDB.aDatabaseInitNotPoseNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vDataSetPath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}
//\\ So khop: query lay tu csdl.
double aMeanCosMAPDiv()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosHeadPoseMAP: " << util.currentDateTime() << std::endl;

	FaceDataSet vFaceDataSet;
	FaceTrackDB vFaceTrackDB;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vFaceTracksPath = exePath + "/VNTDataSet/";

	//\\ Doc csdl: Co n x m mat nguoi (moi mat nguoi goc chia thanh m mat nguoi)
	vFaceTrackDB.aDatabaseRead("00", "44", "0", "0", vFaceTracksPath); //\\ n = 3, m = 6;
	//vFaceDataSet.aDataSetRead("00", "17", "00", "00", vFaceTracksPath); //\\ n = 3, m = 6;

	//\\ So khop.
	/*
	- Lap qua 3 mat nguoi goc.
	- Lap qua 6 mat nguoi duoc chia nho cua tung mat nguoi goc.
	- So khop tung mat nguoi voi csdl facetrack: ket qua la thu tu so khop.
	- Tinh do chinh xac MAP.
	*/
	std::vector<std::vector<std::vector<std::vector<double>>>> csdl = vFaceTrackDB.aGetFaceTrackDatabase();
	std::vector<double> vAPs;
	size_t m = 3;
	size_t n = csdl.size() / m;
	//\\ Lap n mat nguoi goc.
	for (size_t i = 0; i < n; i++)
	{
		//\\ Lap qua m mat nguoi dung.
		for (size_t j = 0; j < m; j++)
		{
			std::vector<std::vector<std::vector<double>>> vQuery = csdl[i * m + j];
			//\\ So khop.
			std::vector<int> vMatchingIndex = vFaceTrackDB.aMeanCosMatchingIndex(vQuery, csdl);
			//\\ Tinh do chinh xa.
			double vAP = 0;
			double Nr = 1;
			size_t vMatchingIndexSize = vMatchingIndex.size();
			//\\ Tim gia tri index dung trong ket qua MatchingIndex tra ve.
			for (size_t k = 0; k < vMatchingIndexSize; k++)
			{
				//\\ Gia tri index dung trong tham so truyen vao la tu i*m den i*m + m.
				int iMatchStartIndex = i * m;
				if (iMatchStartIndex <= vMatchingIndex[k] && vMatchingIndex[k] < iMatchStartIndex + m)
				{
					//\\ Tinh AP.
					vAP += Nr / (k + 1);
					Nr++;
				}
			}
			//\\ Tinh AP trung binh. AP chia m mat nguoi dung. (m = 3).
			vAP /= m;
			vAPs.push_back(vAP);
		}
	}
	//\\ Tinh do chinh xac cho n x m truy van.
	double vMAP = 0;
	size_t vAPsSize = vAPs.size();
	for (size_t i = 0; i < vAPsSize; i++)
	{
		vMAP += vAPs[i];
	}
	vMAP /= vAPsSize;
	//\\ Hien thi thoi gian ket thuc.
	cout << "aMeanCosHeadPoseMAP: " << util.currentDateTime() << std::endl;
	cout << "vMAP: " << vMAP << std::endl;
	return vMAP;
}
//\\ So khop: query lay tu csdl test. 
double aMeanCosMAPDivTest()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "MAP: " << util.currentDateTime() << std::endl;

	FaceTrackDB vFaceTrackDB;
	FaceTrackDB vFaceTrackDBTest;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vFaceTracksPath = exePath + "/VNTDataSet/";
	//\\ Doc csdl: Co n x m mat nguoi (moi mat nguoi goc chia thanh m mat nguoi)
	vFaceTrackDB.aDatabaseRead("00", "44", "0", "0", vFaceTracksPath); //\\ n = 15, m = 3;
	//\\ Doc dataset: Co n x m mat nguoi tuong ung voi csdl de kiem tra.
	vFaceTrackDBTest.aDatabaseRead("00", "44", "0", "0", vFaceTracksPath + "Test/"); //\\ n = 15, m = 3;

	//\\ So khop.
	/*
	- Lap qua 15 mat nguoi goc.
	- Lap qua 3 mat nguoi duoc chia nho cua tung mat nguoi goc.
	- So khop tung mat nguoi voi csdl facetrack: ket qua la thu tu so khop.
	- Tinh do chinh xac MAP.
	*/
	std::vector<std::vector<std::vector<std::vector<double>>>> csdl = vFaceTrackDB.aGetFaceTrackDatabase();
	std::vector<std::vector<std::vector<std::vector<double>>>> csdlTest = vFaceTrackDBTest.aGetFaceTrackDatabase();
	std::vector<double> vAPs;
	size_t m = 3;
	size_t n = csdl.size() / m;
	//\\ Lap n mat nguoi goc.
	for (size_t i = 0; i < n; i++)
	{
		//\\ Lap qua m mat nguoi dung.
		for (size_t j = 0; j < m; j++)
		{
			//\\ Lay query tu csdl1.
			std::vector<std::vector<std::vector<double>>> vQuery = csdlTest[i * m + j];
			//\\ So khop.
			std::vector<int> vMatchingIndex = vFaceTrackDB.aMeanCosMatchingIndex(vQuery, csdl);
			//\\ Tinh do chinh xa.
			double vAP = 0;
			double Nr = 1;
			size_t vMatchingIndexSize = vMatchingIndex.size();
			//\\ Tim gia tri index dung trong ket qua MatchingIndex tra ve.
			for (size_t k = 0; k < vMatchingIndexSize; k++)
			{
				//\\ Gia tri index dung trong tham so truyen vao la tu i*m den i*m + m.
				if (i * m <= vMatchingIndex[k] && vMatchingIndex[k] < i * m + m)
				{
					//\\ Tinh AP.
					vAP += Nr / (k + 1);
					Nr++;
				}
			}
			//\\ Tinh AP trung binh. AP chia m mat nguoi dung. (m = 6).
			vAP /= m;
			vAPs.push_back(vAP);
		}
	}
	//\\ Tinh do chinh xac cho n x m truy van.
	double vMAP = 0;
	size_t vAPsSize = vAPs.size();
	for (size_t i = 0; i < vAPsSize; i++)
	{
		vMAP += vAPs[i];
	}
	vMAP /= vAPsSize;
	//\\ Hien thi thoi gian ket thuc.
	cout << "MAP: " << util.currentDateTime() << std::endl;
	cout << "vMAP: " << vMAP << std::endl;
	return vMAP;
}


//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
void aDatabaseInit_NotDiv_NotPoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/NotDiv/" + pTestPath;

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureReadNotPose("00", "14", "00", "92", vDataSetPath);
	//\\ Khoi tao csdl.
	util.makeDir(util.replaceAll(vDataSetPath + "Database_NotPoseNormalize", "/", "\\"));
	vFaceTrackDB.aDatabaseInitNotPose(vFaceTrackDB.aGetFacetrackFeatures(), vDataSetPath + "Database_NotPoseNormalize/");

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
void aDatabaseInit_NotDiv_NotPoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/NotDiv/" + pTestPath;

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureReadNotPose("00", "14", "00", "92", vDataSetPath);
	//\\ Khoi tao csdl.
	util.makeDir(util.replaceAll(vDataSetPath + "Database_NotPoseNotNormalize", "/", "\\"));
	vFaceTrackDB.aDatabaseInitNotPoseNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vDataSetPath + "Database_NotPoseNotNormalize/");

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
void aDatabaseInit_NotDiv_PoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/NotDiv/" + pTestPath;

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead("00", "14", "00", "92", vDataSetPath);
	//\\ Khoi tao csdl.
	util.makeDir(util.replaceAll(vDataSetPath + "Database_PoseNormalize", "/", "\\"));
	vFaceTrackDB.aDatabaseInit(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetPoses(), vFaceTrackDB.aGetSumPose(), vDataSetPath + "Database_PoseNormalize/");

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
void aDatabaseInit_NotDiv_PoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/NotDiv/" + pTestPath;

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead("00", "14", "00", "92", vDataSetPath);
	//\\ Khoi tao csdl.
	util.makeDir(util.replaceAll(vDataSetPath + "Database_PoseNotNormalize", "/", "\\"));
	vFaceTrackDB.aDatabaseInitNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetPoses(), vFaceTrackDB.aGetSumPose(), vDataSetPath + "Database_PoseNotNormalize/");

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}

//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
void aDatabaseInit_Div_NotPoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/Div/" + pTestPath;

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureReadNotPose("00", "44", "00", "30", vDataSetPath);
	//\\ Khoi tao csdl.
	util.makeDir(util.replaceAll(vDataSetPath + "Database_NotPoseNormalize", "/", "\\"));
	vFaceTrackDB.aDatabaseInitNotPose(vFaceTrackDB.aGetFacetrackFeatures(), vDataSetPath + "Database_NotPoseNormalize/");

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
void aDatabaseInit_Div_NotPoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/Div/" + pTestPath;

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureReadNotPose("00", "44", "00", "30", vDataSetPath);
	//\\ Khoi tao csdl.
	util.makeDir(util.replaceAll(vDataSetPath + "Database_NotPoseNotNormalize", "/", "\\"));
	vFaceTrackDB.aDatabaseInitNotPoseNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vDataSetPath + "Database_NotPoseNotNormalize/");

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
void aDatabaseInit_Div_PoseNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/Div/" + pTestPath;

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead("00", "44", "00", "30", vDataSetPath);
	//\\ Khoi tao csdl.
	util.makeDir(util.replaceAll(vDataSetPath + "Database_PoseNormalize", "/", "\\"));
	vFaceTrackDB.aDatabaseInit(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetPoses(), vFaceTrackDB.aGetSumPose(), vDataSetPath + "Database_PoseNormalize/");

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
void aDatabaseInit_Div_PoseNotNormalize(std::string pTestPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/Div/" + pTestPath;

	FaceTrackDB vFaceTrackDB;
	//\\ Doc features.
	vFaceTrackDB.aFeatureRead("00", "44", "00", "30", vDataSetPath);
	//\\ Khoi tao csdl.
	util.makeDir(util.replaceAll(vDataSetPath + "Database_PoseNotNormalize", "/", "\\"));
	vFaceTrackDB.aDatabaseInitNotNormalize(vFaceTrackDB.aGetFacetrackFeatures(), vFaceTrackDB.aGetPoses(), vFaceTrackDB.aGetSumPose(), vDataSetPath + "Database_PoseNotNormalize/");

	//\\ Hien thi thoi gian ket thuc.
	cout << "DatabaseInit: " << util.currentDateTime() << std::endl;
}



int aMatching(FaceTrackDB pFaceTrackDB, FaceTrackDB pFaceTrackDBTest, int pNum)
{
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
	int countTrue = 0;
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
				countTrue++;
		}
	}
	return countTrue;
}
//\\ So khop: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
double aMatching_NotDivInDiv_NotPoseNormalize()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aNotDivInDiv_NotPoseNormalize: " << util.currentDateTime() << std::endl;

	FaceTrackDB vFaceTrackDB;
	FaceTrackDB vFaceTrackDBTest;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";
	//\\ Doc csdl: Co n x m mat nguoi (moi mat nguoi goc chia thanh m mat nguoi)
	vFaceTrackDB.aDatabaseRead("00", "14", "0", "0", vDataSetPath + "NotDiv/Database_NotPoseNormalize/"); //\\ n = 15, m = 3;
	//\\ Doc dataset: Co n x m mat nguoi tuong ung voi csdl de kiem tra.
	//vFaceTrackDBTest.aDatabaseRead("00", "14", "0", "0", vFaceTracksPath); //\\ n = 15, m = 3;
	vFaceTrackDBTest.aDatabaseRead("00", "44", "0", "0", vDataSetPath + "Div/Database_NotPoseNormalize/"); //\\ n = 15, m = 3;

	//\\ So khop tung facetrack trong DBTest.
	int countTrue = aMatching(vFaceTrackDB, vFaceTrackDBTest, 3);
	size_t testSize = vFaceTrackDBTest.aGetFaceTrackDatabase().size();
	//\\ Hien thi thoi gian ket thuc.
	cout << "aNotDivInDiv_NotPoseNormalize: " << util.currentDateTime() << std::endl;
	cout << "countTrue: " << countTrue << "/ " << testSize << " = " << 1.0 * countTrue / testSize << std::endl;
	return countTrue;
}
//\\ So khop: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
double aMatching_NotDivInDiv_NotPoseNotNormalize()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aNotDivInDiv_NotPoseNotNormalize: " << util.currentDateTime() << std::endl;

	FaceTrackDB vFaceTrackDB;
	FaceTrackDB vFaceTrackDBTest;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";
	//\\ Doc csdl: Co n x m mat nguoi (moi mat nguoi goc chia thanh m mat nguoi)
	vFaceTrackDB.aDatabaseRead("00", "14", "0", "0", vDataSetPath + "NotDiv/Database_NotPoseNotNormalize/"); //\\ n = 15, m = 3;
	//\\ Doc dataset: Co n x m mat nguoi tuong ung voi csdl de kiem tra.
	//vFaceTrackDBTest.aDatabaseRead("00", "14", "0", "0", vFaceTracksPath); //\\ n = 15, m = 3;
	vFaceTrackDBTest.aDatabaseRead("00", "44", "0", "0", vDataSetPath + "Div/Database_NotPoseNotNormalize/"); //\\ n = 15, m = 3;

	//\\ So khop tung facetrack trong DBTest.
	int countTrue = aMatching(vFaceTrackDB, vFaceTrackDBTest, 3);
	size_t testSize = vFaceTrackDBTest.aGetFaceTrackDatabase().size();
	//\\ Hien thi thoi gian ket thuc.
	cout << "aNotDivInDiv_NotPoseNotNormalize: " << util.currentDateTime() << std::endl;
	cout << "countTrue: " << countTrue << "/ " << testSize << " = " << 1.0 * countTrue / testSize << std::endl;
	return countTrue;
}
//\\ So khop: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
double aMatching_NotDivInDiv_PoseNormalize()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aNotDivInDiv_PoseNormalize: " << util.currentDateTime() << std::endl;

	FaceTrackDB vFaceTrackDB;
	FaceTrackDB vFaceTrackDBTest;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";
	//\\ Doc csdl: Co n x m mat nguoi (moi mat nguoi goc chia thanh m mat nguoi)
	vFaceTrackDB.aDatabaseRead("00", "14", "0", "0", vDataSetPath + "NotDiv/Database_PoseNormalize/"); //\\ n = 15, m = 3;
	//\\ Doc dataset: Co n x m mat nguoi tuong ung voi csdl de kiem tra.
	//vFaceTrackDBTest.aDatabaseRead("00", "14", "0", "0", vFaceTracksPath); //\\ n = 15, m = 3;
	vFaceTrackDBTest.aDatabaseRead("00", "44", "0", "0", vDataSetPath + "Div/Database_PoseNormalize/"); //\\ n = 15, m = 3;

	//\\ So khop tung facetrack trong DBTest.
	int countTrue = aMatching(vFaceTrackDB, vFaceTrackDBTest, 3);
	size_t testSize = vFaceTrackDBTest.aGetFaceTrackDatabase().size();
	//\\ Hien thi thoi gian ket thuc.
	cout << "aNotDivInDiv_PoseNormalize: " << util.currentDateTime() << std::endl;
	cout << "countTrue: " << countTrue << "/ " << testSize << " = " << 1.0 * countTrue / testSize << std::endl;
	return countTrue;
}
//\\ So khop: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
double aMatching_NotDivInDiv_PoseNotNormalize()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aNotDivInDiv_PoseNotNormalize: " << util.currentDateTime() << std::endl;

	FaceTrackDB vFaceTrackDB;
	FaceTrackDB vFaceTrackDBTest;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";
	//\\ Doc csdl: Co n x m mat nguoi (moi mat nguoi goc chia thanh m mat nguoi)
	vFaceTrackDB.aDatabaseRead("00", "14", "0", "0", vDataSetPath + "NotDiv/Database_PoseNotNormalize/"); //\\ n = 15, m = 3;
	//\\ Doc dataset: Co n x m mat nguoi tuong ung voi csdl de kiem tra.
	//vFaceTrackDBTest.aDatabaseRead("00", "14", "0", "0", vFaceTracksPath); //\\ n = 15, m = 3;
	vFaceTrackDBTest.aDatabaseRead("00", "44", "0", "0", vDataSetPath + "Div/Database_PoseNotNormalize/"); //\\ n = 15, m = 3;

	//\\ So khop tung facetrack trong DBTest.
	int countTrue = aMatching(vFaceTrackDB, vFaceTrackDBTest, 3);
	size_t testSize = vFaceTrackDBTest.aGetFaceTrackDatabase().size();
	//\\ Hien thi thoi gian ket thuc.
	cout << "aNotDivInDiv_PoseNotNormalize: " << util.currentDateTime() << std::endl;
	cout << "countTrue: " << countTrue << "/ " << testSize << " = " << 1.0 * countTrue / testSize << std::endl;
	return countTrue;
}

// Function main
int main(void)
{
	//aMeanCosDataSetInitDiv();
	//aMeanCosFeaturesInitDiv();
	//aMeanCosDatabaseInitDiv();
	//aMeanCosDatabaseInitDivNotPose();
	//aMeanCosMAPDiv();//\\ csdl khong chuan hoa + query lay tu csdl. MAP = 1.
	//aMeanCosMAPDivTest();//\\ csdl khong chuan hoa + query lay tu facetrack. MAP = 1.

	////\\ Khoi tao csdl.
	//aDatabaseInit_NotDiv_NotPoseNormalize("");
	//aDatabaseInit_NotDiv_NotPoseNotNormalize("");
	//aDatabaseInit_NotDiv_PoseNormalize("");
	//aDatabaseInit_NotDiv_PoseNotNormalize("");
	//aDatabaseInit_Div_NotPoseNormalize("");
	//aDatabaseInit_Div_NotPoseNotNormalize("");
	//aDatabaseInit_Div_PoseNormalize("");
	//aDatabaseInit_Div_PoseNotNormalize("");

	//aDatabaseInit_NotDiv_NotPoseNormalize("Test/");
	//aDatabaseInit_NotDiv_NotPoseNotNormalize("Test/");
	//aDatabaseInit_NotDiv_PoseNormalize("Test/");
	//aDatabaseInit_NotDiv_PoseNotNormalize("Test/");
	//aDatabaseInit_Div_NotPoseNormalize("Test/");
	//aDatabaseInit_Div_NotPoseNotNormalize("Test/");
	//aDatabaseInit_Div_PoseNormalize("Test/");
	//aDatabaseInit_Div_PoseNotNormalize("Test/");

	//\\ So khop.
	aMatching_NotDivInDiv_NotPoseNormalize();
	aMatching_NotDivInDiv_NotPoseNotNormalize();
	aMatching_NotDivInDiv_PoseNormalize();
	aMatching_NotDivInDiv_PoseNotNormalize();

	cout << "Done." << std::endl;
	_getwch();
	return 0;
}
