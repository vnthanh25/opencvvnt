#include "Header\FaceDataSet.h"
#include "Header\FaceTrack.h"
#include "Utilities.h"

using namespace vnt;

void aFaceDataSet()
{
	ColorFeret colorFeret;
	//\\ Test get index.
	//std::string s = colorFeret.aGetType(-1);
	//std::string s0 = colorFeret.aGetType(0);
	//std::string s1 = colorFeret.aGetType(1);
	//std::string s2 = colorFeret.aGetType(2);
	//std::string s3 = colorFeret.aGetType(3);

	//\\ Lay id cua nguoi dau tien.
	std::string id = colorFeret.aGetId(0);
	//Utilites util;
	//id = util.increaseNumber(id, 1);
	//\\ Test get list.
	//std::vector<std::string> fileNames = colorFeret.aGetsAllFileName(id);

	FaceDataSet faceDataSet;
	//\\ Duong dan den thu muc dataset.
	std::string path = "D:/VNThanh/Dev/OpenCV/WorkSpace/opencvvnt/Face/Data/colorferet_2/colorferet/";
	//cv::Mat face = faceDataSet.aGetFace(id, path);
	//cv::imshow("face", face);
	std::vector<cv::Mat> faces = faceDataSet.aGetsAllFace(id, path);
	for (size_t i = 0; i < faces.size(); i++)
	{
		cv::imshow("face" + std::to_string(i), faces[i]);
	}
}

//\\ Tinh vector trung binh cho 1 facetrack.
void aAvgFaceTrackOne()
{
	FaceTrack faceTrack;
	//\\ Gia lap danh sach dac trung cho 1 facetrack.
	std::vector<std::vector<std::vector<int>>> featurefacetrack = faceTrack.aGetsFeatureFake(3,3,3);
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
//\\ Tinh khoang cach hinh hoc cua 2 vector.
void aDistanceGeometryTwoVector()
{
	FaceTrack faceTrack;
	//\\ Gia lap 2 vector.
	std::vector<std::vector<double>> vector1 = faceTrack.aAvgFetureFake(1, 2, 1);
	std::vector<std::vector<double>> vector2 = faceTrack.aAvgFetureFake(1, 2, 2);
	//\\ Tinh khoang cach cosine cua 2 vector.
	double cosine = faceTrack.aEuclid(vector1, vector2);
}

// Function main
int main(void)
{
	//aFaceDataSet();
	//aAvgFaceTrackOne();
	//aAvgFaceTrackAll();
	//aCosineTwoVector();
	aDistanceGeometryTwoVector();

	cv::waitKey();
	return 0;
}
