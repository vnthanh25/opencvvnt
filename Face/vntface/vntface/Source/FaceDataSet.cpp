/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "../Header/FaceDataSet.h"

using namespace vnt;

/********** Constructor **********/
FaceDataSet::FaceDataSet(){ mDataSet = new ColorFeret; }
FaceDataSet::~FaceDataSet(){}

/********** public Methods **********/
//\\ Lay 1 anh cua 1 nguoi. Mac dinh la lay anh dau tien neu co nhieu anh.
cv::Mat FaceDataSet::aGetFace(const std::string pId, const std::string pPath)
{
	cv::Mat result;
	ColorFeret dataset = *((ColorFeret*)(mDataSet));
	//\\ Lay duong dan thu muc.
	std::string path = pPath + dataset.aGetPath(pId);
	//\\ Lay tat ca ten file anh co the co.
	std::vector<std::string> fileNames = dataset.aGetsAllFileName(pId);
	//\\ Tra ve anh dau tien duoc tim thay trong thu muc.
	for (size_t i = 0; i < fileNames.size(); i++)
	{
		result = cv::imread(path + fileNames[i], CV_8UC1);
		if (!result.empty())
			break;
	}
	return result;
}
//\\ Lay 1 facetrack cua 1 nguoi.
std::vector<cv::Mat> FaceDataSet::aGetsAllFace(const std::string pId, const std::string pPath)
{
	std::vector<cv::Mat> result;
	ColorFeret dataset = *((ColorFeret*)(mDataSet));
	//\\ Lay duong dan thu muc.
	std::string path = pPath + dataset.aGetPath(pId);
	//\\ Lay tat ca ten file anh co the co.
	std::vector<std::string> fileNames = dataset.aGetsAllFileName(pId);
	//\\ Tra ve anh dau tien duoc tim thay trong thu muc.
	cv::Mat face;
	for (size_t i = 0; i < fileNames.size(); i++)
	{
		face = cv::imread(path + fileNames[i], CV_8UC1);
		if (!face.empty())
			result.push_back(face);
	}
	return result;
}
