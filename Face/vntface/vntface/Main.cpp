#include "Utilities.h"
#include "Header\FaceDataSet.h"
#include "Header\ColorFeret.h"
#include "Header\HeadPose.h"
#include "Header\FaceTrack.h"

using namespace vnt;


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
	std::string vFolderPath = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/";

	HeadPose vHeadPose;
	std::string vId = vHeadPose.aGetId(0);
	vFolderPath += vHeadPose.aGetPath(vId);
	//Utilites util;
	//id = util.increaseNumber(vId, 1);
	//\\ Lay tat ca ten file anh cua 1 nguoi.
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
void aMeanCos()
{
	//\\ Facetrack yeu cau.
	std::vector<cv::Mat> query;
	//\\ Danh sach facetrack trong csdl.
	std::vector<std::vector<cv::Mat>> csdl;
	//\\ Ket qua so khop.
	std::vector<std::vector<cv::Mat>> matching;
}

// Function main
int main(void)
{
	//aColorFeret();
	aHeadPose();
	//aAvgFaceTrackOne();
	//aAvgFaceTrackAll();
	//aCosineTwoVector();
	//aEuclidTwoVector();


	//aMeanCos();

	cv::waitKey();
	return 0;
}
