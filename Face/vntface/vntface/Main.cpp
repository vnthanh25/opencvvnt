#include "Header\Utilities.h"
#include "Header\FaceDataSet.h"
#include "Header\ColorFeret.h"
#include "Header\HeadPose.h"
#include "Header\FaceTrack.h"
#include "Header\VNTDataSet.h"

using namespace vnt;

void aFaceDataSetBase()
{
	FaceDataSetBase* vFaceDataSetBase;
	ColorFeret vColorFeret;
	vFaceDataSetBase = &vColorFeret;
	std::string s1 = vFaceDataSetBase->aGetPath("00001");
	std::vector<std::string> vAllIds1 = vFaceDataSetBase->aGetsAllIds();
	HeadPose vHeadPose;
	vFaceDataSetBase = &vHeadPose;
	std::string s2 = vFaceDataSetBase->aGetPath("01");
	std::vector<std::string> vAllIds2 = vFaceDataSetBase->aGetsAllIds();
}
void aColorFeret()
{
	FaceDataSet vFaceDataSet;
	//\\ Duong dan den thu muc dataset.
	std::string vFolderPath = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/colorferet_2/colorferet/";

	ColorFeret vColorFeret;
	//\\ Lay id cua nguoi dau tien.
	std::string vId = vColorFeret.aGetId(0);
	vFolderPath += vColorFeret.aGetPath(vId);
	//Utilites util;
	//id = util.increaseNumber(vId, 1);
	//\\ Lay tat ca ten file anh cua 1 nguoi.
	std::vector<std::string> vAllFileName = vColorFeret.aGetsAllFileName(vId);

	std::vector<cv::Mat> vFaceTrack = vFaceDataSet.aReadsImage(vAllFileName, vFolderPath);
	size_t vFaceTrackSize = vFaceTrack.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		cv::imshow("face" + std::to_string(i), vFaceTrack[i]);
	}
}
void aHeadPose()
{
	FaceDataSet vFaceDataSet;
	//\\ Duong dan den thu muc dataset.
	//std::string vFolderPath = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/HeadPoseImageDatabase/";
	std::string vFolderPath = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/HeadPose/";

	HeadPose vHeadPose;
	std::string vId = vHeadPose.aGetId(0);
	vFolderPath += vHeadPose.aGetPath(vId);
	//Utilites util;
	//id = util.increaseNumber(vId, 1);

	//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
	std::vector<std::string> vAllFileName = vHeadPose.aGetsAllFileName(vId);

	std::vector<cv::Mat> vFaceTrack = vFaceDataSet.aReadsImage(vAllFileName, vFolderPath);
	size_t vFaceTrackSize = vFaceTrack.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		cv::imshow("face" + std::to_string(i), vFaceTrack[i]);
	}
}

//\\ Tinh vector trung binh cho 1 facetrack.
void aAvgFaceTrackOne()
{
	FaceTrack faceTrack;
	//\\ Gia lap danh sach dac trung cho 1 facetrack.
	std::vector<std::vector<std::vector<int>>> featurefacetrack = faceTrack.aGetsFeatureFake(3, 3, 3);
	//\\ Tinh vector trung binh cho facetrack.
	faceTrack.aAvgFeature(featurefacetrack);
}
//\\ Tinh vector trung binh cho tat ca facetrack.
void aAvgFaceTrackAll()
{
	FaceTrack faceTrack;
	//\\ Gia lap: moi face track co 1 vector trung binh
	std::vector<std::vector<std::vector<double>>> avgfeaturefacetrack = faceTrack.aGetsAvgFeatureFake(3, 3, 3);
	//\\ Tinh vector trung binh cho tat ca facetrack.
	std::vector<std::vector<double>> avgFeature = faceTrack.aAvgFeature(avgfeaturefacetrack);

	//\\ Gia lap: moi factrack co nhieu vector dac trung.
	std::vector<std::vector<std::vector<std::vector<int>>>> avgfeaturefacetrack1 = faceTrack.aGetsFeaturesFake(3, 3, 3, 3);
	//\\ Tinh vector trung binh cho tat ca facetrack.
	std::vector<std::vector<double>> avgFeature1 = faceTrack.aAvgFeature(avgfeaturefacetrack1);
}
//\\ Tinh khoang cach cosine cua 2 vector.
void aCosineTwoVector()
{
	FaceTrack faceTrack;
	//\\ Gia lap 2 vector.
	std::vector<std::vector<double>> vector1 = faceTrack.aAvgFetureFake(1, 2, 1);
	std::vector<std::vector<double>> vector2 = faceTrack.aAvgFetureFake(1, 2, 2);
	//\\ Tinh khoang cach cosine cua 2 vector.
	double cosine = faceTrack.aCosine(vector1, vector2);
}
//\\ Tinh khoang cach hinh hoc (Euclidean) cua 2 vector.
void aEuclidTwoVector()
{
	FaceTrack faceTrack;
	//\\ Gia lap 2 vector.
	std::vector<std::vector<double>> vector1 = faceTrack.aAvgFetureFake(1, 2, 1);
	std::vector<std::vector<double>> vector2 = faceTrack.aAvgFetureFake(1, 2, 2);
	//\\ Tinh khoang cach cosine cua 2 vector.
	double cosine = faceTrack.aEuclid(vector1, vector2);
}

//\\ So khop cac facetrack.
void aMatchingFaceTrack()
{
	FaceTrack faceTrack;
	//\\ Gia lap danh sach facetrack. Moi facetrack co nhieu vector dac trung trung binh.
	size_t numFaceTrack = 3; //\\ So luong facetrack trong CSDL.
	size_t numFeature = 2; //\\ So luong vector dac trung trong moi facetrack.
	size_t numRow = 1; //\\ So luong vung dac trung (LBP: co 9 vung).
	size_t numCol = 2; //\\ So luong dac trung trong moi vung (LBP: co 59 dac trung).

	std::vector<std::vector<std::vector<std::vector<int>>>> facetracks = faceTrack.aGetsFeaturesFake(numFaceTrack, numFeature, numRow, numCol);
}

//\\ Khoi tao csdl
void aMeanCosVNTDataSetInit()
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosHeadPoseInit:" << std::endl;
	cout << util.currentDateTime() << std::endl;

	//\\ * Load tat ca anh vao FaceDataSet.
	FaceDataSetBase* vFaceDataSetBase;
	VNTDataSet vVNTDataSet;
	vFaceDataSetBase = &vVNTDataSet;

	std::string vDataSourcePath = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/HeadPose/VNTDataSet/DataSetHeadPose/";
	//std::string exePath = util.GetExePath();
	//exePath = util.replaceAll(exePath, "\\", "/");
	std::string vDataSetPath = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/HeadPose/VNTDataSet/DataSet/";

	////\\ Khoi tao VNTDataSet.
	//FaceDataSet vFaceDataSet;
	//vVNTDataSet.aVNTDataSetInit(vFaceDataSetBase, vDataSourcePath, vDataSetPath, 6);

	//\\ Doc facetrack query.
	std::string vDataSourcePathQuery = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/HeadPose/VNTDataSet/";
	FaceDataSet vFaceDataSetQuery;
	vFaceDataSetQuery.aDataSetRead("15", "17", "00", "30", vDataSourcePathQuery);

	//\\ Khoi tao csdl.
	FaceTrack vFaceTrack;
	std::string vFaceTracksPath = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/HeadPose/VNTDataSet/";
	vFaceTrack.aDatabaseInit(vFaceDataSetQuery.aGetFaceTraks(), vFaceTracksPath);

	//\\ Hien thi thoi gian ket thuc.
	cout << util.currentDateTime() << std::endl;
}
//\\ Khoi tao csdl
void aMeanCosHeadPoseInit(FaceDataSet pFaceDataSet, FaceTrack pFaceTrack, std::string pDataSourcePath, std::string pFolderPath)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosHeadPoseInit:" << std::endl;
	cout << util.currentDateTime() << std::endl;

	//\\ * Load tat ca anh vao FaceDataSet.
	FaceDataSetBase* vFaceDataSetBase;
	HeadPose vHeadPose;
	vFaceDataSetBase = &vHeadPose;

	//\\ Khoi tao dataset.
	pFaceDataSet.aDataSetInit(vFaceDataSetBase, pDataSourcePath, pFolderPath);
	//\\ Khoi tao csdl.
	pFaceTrack.aDatabaseInit(pFaceDataSet.aGetFaceTraks(), pFolderPath);

	//\\ Hien thi thoi gian ket thuc.
	cout << util.currentDateTime() << std::endl;
}
//\\ So khop facetrack
std::vector<std::vector<cv::Mat>> aMeanCosHeadPoseMatching(std::vector<cv::Mat> pFaceTrackQuery, std::vector<std::vector<cv::Mat>> pFaceTracks, FaceTrack pFaceTrack)
{
	std::vector<std::vector<cv::Mat>> result;
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosHeadPoseMatching:" << std::endl;
	cout << util.currentDateTime() << std::endl;
	//\\ Lay vector dac trung trung binh cua facetrack truy van.
	std::vector<std::vector<std::vector<int>>> vFeaturesQuery = pFaceTrack.aGetsFeature(pFaceTrackQuery);
	std::vector<std::vector<double>> vAvgFeatureQuery = pFaceTrack.aAvgFeature(vFeaturesQuery);
	std::vector<std::vector<std::vector<double>>> vQuery = { vAvgFeatureQuery };
	//\\ Lay vector dac trung trung binh cua tat ca facetrack.
	std::vector<std::vector<std::vector<std::vector<double>>>> csdl = pFaceTrack.aGetFaceTrackDatabase();
	//\\ So khop facetrack truy van va cac facetrack trong csdl.
	std::vector<int> vFaceTracksMatchingIndex = pFaceTrack.aMeanCosMatchingIndex(vQuery, csdl);
	//\\ Lay tat ca hinh anh co trong facetrack.
	size_t vFaceTracksMatchingIndexsize = vFaceTracksMatchingIndex.size();
	for (size_t i = 0; i < vFaceTracksMatchingIndexsize; i++)
	{
		size_t idx = vFaceTracksMatchingIndex[i];
		result.push_back(pFaceTracks[idx]);
	}
	//std::vector<std::vector<cv::Mat>> vFaceTracksMatching = vFaceTrack.aMeanCos(vFaceTracks[1], vFaceTracks);

	//\\ Hien thi thoi gian ket thuc.
	cout << util.currentDateTime() << std::endl;

	return result;
}

//\\ So khop facetrack
std::vector<int> aMeanCosHeadPoseMatchingIndex(std::vector<cv::Mat> pFaceTrackQuery, FaceTrack pFaceTrack)
{
	std::vector<int> result;
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosHeadPoseMatching:" << std::endl;
	cout << util.currentDateTime() << std::endl;
	//\\ Lay vector dac trung trung binh cua facetrack truy van.
	std::vector<std::vector<std::vector<int>>> vFeaturesQuery = pFaceTrack.aGetsFeature(pFaceTrackQuery);
	std::vector<std::vector<double>> vAvgFeatureQuery = pFaceTrack.aAvgFeature(vFeaturesQuery);
	std::vector<std::vector<std::vector<double>>> vQuery = { vAvgFeatureQuery };
	//\\ Lay vector dac trung trung binh cua tat ca facetrack.
	std::vector<std::vector<std::vector<std::vector<double>>>> csdl = pFaceTrack.aGetFaceTrackDatabase();
	//\\ So khop facetrack truy van va cac facetrack trong csdl.
	result = pFaceTrack.aMeanCosMatchingIndex(vQuery, csdl);
	return result;
}

/*
- Doc cac file anh trong thu muc cua "HeadPose" thanh doi tuong Mat. Luu cac doi tuong Mat nay vao trong FaceDataSet.
- Khoi tao csdl:
+ Rut trich dac trung LBP (la vector 2 chieu kieu int) cua tat ca anh (bo tri theo facetrack).
+ Luu vao doi tuong FaceTrack (co ghi ra file).
*/
//\\ Thuat toan sap xep theo mean-cos.
double aMeanCosHeadPose()
{
	FaceDataSet vFaceDataSet;
	FaceTrack vFaceTrack;
	Utilites util;
	std::string vDataSourcePath = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/HeadPose/VNTDataSet/";
	std::string exePath = util.GetExePath();
	exePath = util.replaceAll(exePath, "\\", "/");
	std::string vFaceTracksPath = exePath + "/";
	vFaceTracksPath = vDataSourcePath;

	////\\ Khoi tao csdl. Chi chay 1 lan.
	//aMeanCosHeadPoseInit(vFaceDataSet, vFaceTrack, vDataSourcePath, vFaceTracksPath);

	//\\ Doc csdl: Co n x m mat nguoi (moi mat nguoi goc chia thanh m mat nguoi)
	vFaceTrack.aDatabaseRead("00", "17", "0", "0", vFaceTracksPath); //\\ n = 3, m = 6;
	//\\ Doc dataset: Co n x m mat nguoi tuong ung voi csdl de kiem tra.
	vFaceDataSet.aDataSetRead("00", "17", "00", "01", vFaceTracksPath);

	////\\ Doc facetrack query.
	//std::string vDataSourcePathQuery = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/HeadPose/";
	//FaceDataSet vFaceDataSetQuery;
	//vFaceDataSetQuery.aDataSetRead("00", "01", "000", "030", vDataSourcePathQuery);
	//std::vector<std::vector<cv::Mat>> facetracksquery = vFaceDataSetQuery.aGetFaceTraks();
	//////\\ Tinh vector trung binh cho facetrack query.
	////std::vector<std::vector<double>> vAvgFeature = vFaceTrack.aAvgFeature(vFaceDataSetQuery.aGetFaceTraks()[0]);

	//\\ So khop.
	/*
	- Lap qua 3 mat nguoi goc.
	- Lap qua 6 mat nguoi duoc chia nho cua tung mat nguoi goc.
	- So khop tung mat nguoi voi csdl facetrack: ket qua la thu tu so khop.
	- Tinh do chinh xac MAP.
	*/
	std::vector<std::vector<cv::Mat>> facetracks = vFaceDataSet.aGetFaceTraks();
	std::vector<double> vAPs;
	size_t m = 6;
	size_t n = facetracks.size() / 6;
	//\\ Lap n mat nguoi goc.
	for (size_t i = 0; i < n; i++)
	{
		//\\ Lap qua m mat nguoi dung.
		for (size_t j = 0; j < m; j++)
		{
			//std::vector<std::vector<cv::Mat>> facetracksMatching = aMeanCosHeadPoseMatching(facetracks[1], facetracks, vFaceTrack);
			std::vector<int> vMatchingIndex = aMeanCosHeadPoseMatchingIndex(facetracks[i * m + j], vFaceTrack);
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
	return vMAP;
}

// Function main
int main(void)
{
	//aFaceDataSetBase();
	//aColorFeret();
	//aHeadPose();
	//aAvgFaceTrackOne();
	//aAvgFaceTrackAll();
	//aCosineTwoVector();
	//aEuclidTwoVector();
	//aMeanCosVNTDataSetInit();

	//\\ Ket qua
	double vMAP = aMeanCosHeadPose();
	
	cv::waitKey();
	return 0;
}
