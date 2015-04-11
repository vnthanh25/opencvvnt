#include "Header\Utilities.h"
#include "Header\FaceDataSet.h"
#include "Header\ColorFeret.h"
#include "Header\HeadPose.h"
#include "Header\FaceTrack.h"

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

//\\ Thuat toan sap xep theo mean-cos.
/*
- Doc cac file anh trong thu muc cua "HeadPose" thanh doi tuong Mat. Luu cac doi tuong Mat nay vao trong FaceDataSet.
- Khoi tao csdl:
  + Rut trich dac trung LBP (la vector 2 chieu kieu int) cua tat ca anh (bo tri theo facetrack).
  + Luu vao doi tuong FaceTrack (co ghi ra file).
*/
//\\ Khoi tao csdl
void aMeanCosHeadPoseInit(FaceDataSet pFaceDataSet, FaceTrack pFaceTrack, std::string pFaceTracksFolder)
{
	Utilites util;
	//\\ Hien thi thoi gian bat dau.
	cout << "aMeanCosHeadPoseInit:" << std::endl;
	cout << util.currentDateTime() << std::endl;

	//\\ * Load tat ca anh vao FaceDataSet.
	FaceDataSetBase* vFaceDataSetBase;
	HeadPose vHeadPose;
	//std::string vFolderPath = "../../Data/HeadPose/";
	std::string vFolderPath = "../../Data/HeadPose/Test/";
	vFaceDataSetBase = &vHeadPose;
	//\\ Lay tat ca Ids co trong nguon anh.
	std::vector<std::string> vAllIds = vFaceDataSetBase->aGetsAllIds();
	std::vector<std::vector<cv::Mat>> vFaceTracks;
	size_t vAllIdsSize = vAllIds.size();
	for (size_t i = 0; i < vAllIdsSize; i++)
	{
		std::string vId = vAllIds[i];
		//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
		std::vector<std::string> vAllFileName = vHeadPose.aGetsAllFileName(vId);
		std::vector<cv::Mat> vFaceTrack = pFaceDataSet.aReadsImage(vAllFileName, vFolderPath + vHeadPose.aGetPath(vId));
		vFaceTracks.push_back(vFaceTrack);
	}// for i.
	pFaceDataSet.aSetFaceTracks(vFaceTracks);
	//\\ * Khoi tao csdl co ghi ra file.
	pFaceTrack.aDatabaseInit(vFaceTracks, pFaceTracksFolder);

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

void aMeanCosHeadPose()
{
	FaceDataSet vFaceDataSet;
	FaceTrack vFaceTrack;
	//\\ Khoi tao csdl. Chi chay 1 lan.
	//std::string vFolderPath = "../../Data/HeadPose/Test/";
	//aMeanCosHeadPoseInit(vFaceDataSet, vFaceTrack);
	//\\ 
	std::vector<std::vector<cv::Mat>> facetracks = vFaceDataSet.aGetFaceTraks();
	std::vector<std::vector<cv::Mat>> facetracksMatching = aMeanCosHeadPoseMatching(facetracks[1], facetracks, vFaceTrack);
}

void Test()
{
	FaceDataSet vFaceDataSet;
	FaceTrack vFaceTrack;
	//\\ Khoi tao csdl. Chi chay 1 lan.
	std::string vFolderPath = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/HeadPose/Test/";
	aMeanCosHeadPoseInit(vFaceDataSet, vFaceTrack, vFolderPath);

	//FaceTrack vFaceTrack;
	//vFaceTrack.aDatabaseRead("0", "1", "0", "0", "");

	//Utilites util;
	//std::string s = "images/lena/.png";
	//std::string s1 = util.replace(s, "/", "\\");
	//std::string s2 = util.replaceAll(s, "/", "\\");
	//cv::Mat image = cv::imread("images/lena.png", CV_8UC1);
	//util.writeMatBasic(image, "images/lena.avg");

	//cv::Mat lena = util.readMatBasic("images/lena.avg");
}

// Function main
int main(void)
{
	Test();
	//aFaceDataSetBase();
	//aColorFeret();
	//aHeadPose();
	//aAvgFaceTrackOne();
	//aAvgFaceTrackAll();
	//aCosineTwoVector();
	//aEuclidTwoVector();

	//aMeanCosHeadPose();
	
	cv::waitKey();
	return 0;
}
