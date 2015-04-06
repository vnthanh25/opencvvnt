#include "Header\FaceDataSet.h"
#include "Utilities.h"

using namespace vnt;

void FDS()
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
// Function main
int main(void)
{
	FDS();

	cv::waitKey();
	return 0;
}
