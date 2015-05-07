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
void aMeanCosHeadPoseDataSetInit()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosVNTDataSetInit: " << util.currentDateTime() << std::endl;

	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = exePath + "/VNTDataSet/";

	FaceDataSet vFaceDataSet;
	//\\ Khoi tao dataset.
	FaceDataSetBase* vFaceDataSetBase;
	HeadPose vHeadPose;
	vFaceDataSetBase = &vHeadPose;
	vFaceDataSet.aDataSetInit(vFaceDataSetBase, vDataSetPath + "DataSetHeadPoseDownload/", vDataSetPath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aMeanCosVNTDataSetInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl
void aMeanCosHeadPoseDatabaseInit()
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

	//\\ Khoi tao csdl.
	FaceTrackDB vFaceTrackDB;
	vFaceTrackDB.aDatabaseInit(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetSumPose(), vDataSetPath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aMeanCosVNTDataSetInit: " << util.currentDateTime() << std::endl;
}

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

	FaceDataSet vFaceDataSet;
	//\\ Khoi tao dataset.
	FaceDataSetBase* vFaceDataSetBase;
	HeadPose vHeadPose;
	vFaceDataSetBase = &vHeadPose;
	vFaceDataSet.aDataSetInitDiv(vFaceDataSetBase, vDataSetPath + "DataSetHeadPoseDownload/", vDataSetPath, 3);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aMeanCosVNTDataSetInit: " << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl
void aMeanCosDatabaseInitDiv()
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
	vFaceDataSet.aDataSetRead("00", "44", "00", "30", vDataSetPath);

	//\\ Khoi tao csdl.
	FaceTrackDB vFaceTrackDB;
	vFaceTrackDB.aDatabaseInit(vFaceDataSet.aGetFaceTraks(), vFaceDataSet.aGetPoses(), vFaceDataSet.aGetSumPose(), vDataSetPath);

	//\\ Hien thi thoi gian ket thuc.
	cout << "aMeanCosVNTDataSetInit: " << util.currentDateTime() << std::endl;
}

double aMeanCosHeadPoseMAPNotPose()
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
	vFaceTrackDB.aDatabaseRead("00", "17", "0", "0", vFaceTracksPath); //\\ n = 3, m = 6;
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
	size_t m = 6;
	size_t n = csdl.size() / 6;
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
	cout << "aMeanCosHeadPoseMAP: " << util.currentDateTime() << std::endl;
	return vMAP;
}

double aMeanCosHeadPoseMAP1NotPose()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosHeadPoseMAP1: " << util.currentDateTime() << std::endl;

	FaceDataSet vFaceDataSet;
	FaceTrackDB vFaceTrackDB;
	//\\ Duong dan den nguon du lieu.
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vFaceTracksPath = exePath + "/VNTDataSet/";
	//\\ Doc csdl: Co n x m mat nguoi (moi mat nguoi goc chia thanh m mat nguoi)
	vFaceTrackDB.aDatabaseRead("00", "17", "0", "0", vFaceTracksPath); //\\ n = 3, m = 6;
	//\\ Doc dataset: Co n x m mat nguoi tuong ung voi csdl de kiem tra.
	vFaceDataSet.aDataSetRead("00", "17", "00", "30", vFaceTracksPath);

	//\\ So khop.
	/*
	- Lap qua 3 mat nguoi goc.
	- Lap qua 6 mat nguoi duoc chia nho cua tung mat nguoi goc.
	- Tinh vector dac trung trung binh cua tung mat nguoi. (*)
	- So khop tung mat nguoi voi csdl facetrack: ket qua la thu tu so khop.
	- Tinh do chinh xac MAP.
	*/
	std::vector<std::vector<cv::Mat>> vFaceTracks = vFaceDataSet.aGetFaceTraks();
	std::vector<std::vector<std::vector<std::vector<double>>>> csdl = vFaceTrackDB.aGetFaceTrackDatabase();
	std::vector<double> vAPs;
	size_t m = 6;
	size_t n = vFaceTracks.size() / 6;
	//\\ Lap n mat nguoi goc.
	for (size_t i = 0; i < n; i++)
	{
		//\\ Lap qua m mat nguoi dung.
		for (size_t j = 0; j < m; j++)
		{
			//\\ Facetrack truy van.
			std::vector<cv::Mat> vFaceTrackQuery = vFaceTracks[i * m + j];

			//\\ Hien thi thoi gian bat dau.
			cout << "avg" << std::to_string(i * m + j) << ": " << util.currentDateTime() << std::endl;

			//\\ Lay vector dac trung trung binh cua facetrack truy van.
			std::vector<std::vector<std::vector<int>>> vFeaturesQuery = vFaceTrackDB.aGetsFeature(vFaceTrackQuery);
			std::vector<std::vector<double>> vAvgFeatureQuery = vFaceTrackDB.aAvgFeatureNotPose(vFeaturesQuery);
			std::vector<std::vector<std::vector<double>>> vQuery = { vAvgFeatureQuery };

			//\\ Hien thi thoi gian ket thuc.
			cout << "avg" << std::to_string(i * m + j) << ": " << util.currentDateTime() << std::endl;

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
	cout << "aMeanCosHeadPoseMAP1: " << util.currentDateTime() << std::endl;
	return vMAP;
}

// Function main
int main(void)
{
	//int pose = 110;
	//int sum = 11280;
	//double avg = 1.0 * pose / sum;
	//aMeanCosVNTDataSetInit();
	//aMeanCosDataSetInitDiv();
	aMeanCosDatabaseInitDiv();
	////\\ Ket qua
	//double vMAP = aMeanCosHeadPoseMAP();//\\ 0.84. Vector dac trung trung binh cua facetrack query duoc lay tu trong csdl.
	//cout << "vMAP: " << vMAP << std::endl;
	////double vMAP1 = aMeanCosHeadPoseMAP1();//\\ 0.60. Vector dac trung trung binh cua facetrack query can phai tinh.
	////cout << "vMAP1: " << vMAP1 << std::endl;

	_getwch();
	return 0;
}
