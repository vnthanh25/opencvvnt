/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "../Header/FaceDataSet.h"

using namespace vnt;

/********** Constructor **********/
FaceDataSet::FaceDataSet(){}
FaceDataSet::~FaceDataSet(){}

/********** public Methods **********/
////\\ Lay nguon anh.
//FaceDataSetBase FaceDataSet::aGetDataSetBase()
//{
//	return *mDataSetBase;
//}
////\\ Gan nguon anh.
//void FaceDataSet::aSetDataSetBase(FaceDataSetBase pDataSetBase)
//{
//	mDataSetBase = &pDataSetBase;
//}
////\\ Lay danh sach facetrack.
//std::vector<std::vector<cv::Mat>> FaceDataSet::aGetFaceTraks()
//{
//	return mFaceTracks;
//}
////\\ Gan danh sach facetrack.
//void FaceDataSet::aSetFaceTracks(std::vector<std::vector<cv::Mat>> pFaceTracks)
//{
//	mFaceTracks = pFaceTracks;
//}

//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack.
std::vector<cv::Mat> FaceDataSet::aReadsImage(std::vector<std::string> pAllFileName, const std::string pPath)
{
	std::vector<cv::Mat> result;
	size_t vAllFileNameSize = pAllFileName.size();
	for (size_t i = 0; i < vAllFileNameSize; i++)
	{
		cv::Mat face = cv::imread(pPath + pAllFileName[i], CV_8UC1);
		if (!face.empty())
			result.push_back(face);
	}
	return result;
}
