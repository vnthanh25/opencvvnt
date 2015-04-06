#include "..\Header\FaceDetect.h"

using namespace vnt;
/********** Constructor **********/
FaceDetect::FaceDetect()
{
}
FaceDetect::~FaceDetect()
{
}

/********** private Methods **********/
//\\ Khoi tao bo phan lop.
bool FaceDetect::aLoadFaceCascade()
{
	if (mFaceCascade.load(mFaceCascadeName))
		return true;
	return false;
}
bool FaceDetect::aLoadFaceCascade(const std::string pFaceCascadeName)
{
	mFaceCascadeName = pFaceCascadeName;
	if (mFaceCascade.load(mFaceCascadeName))
		return true;
	return false;
}

/********** public Methods **********/
//\\ Tim tat ca mat nguoi trong anh.
std::vector<cv::Rect> FaceDetect::aGetsRect(const cv::Mat pImage)
{
	std::vector<cv::Rect> result;
	//\\ Khoi tao bo phan lop.
	if (aLoadFaceCascade())
	{
		//\\ Tim thong qua bo phan lop.
		mFaceCascade.detectMultiScale(pImage, result, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	}
	return result;
}
std::vector<cv::Mat> FaceDetect::aGetsMat(const cv::Mat pImage)
{
	std::vector<cv::Mat> result;
	//\\ Tim bien chua mat nguoi.
	std::vector<cv::Rect> faces = aGetsRect(pImage);
	//\\ Dua ket qua vao vector<Mat>
	for (size_t i = 0; i < faces.size(); i++)
	{
		result.push_back(pImage(faces[i]));
	}
	return result;
}
//\\ Tim tat ca mat nguoi trong anh. Co tham so.
std::vector<cv::Rect> FaceDetect::aGetsRect(const cv::Mat pImage, const std::string pFaceCascadeName)
{
	std::vector<cv::Rect> result;
	//\\ Khoi tao bo phan lop.
	if (aLoadFaceCascade(pFaceCascadeName))
	{
		//\\ Tim thong qua bo phan lop.
		mFaceCascade.detectMultiScale(pImage, result, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	}
	return result;
}
std::vector<cv::Mat> FaceDetect::aGetsMat(const cv::Mat pImage, const std::string pFaceCascadeName)
{
	std::vector<cv::Mat> result;
	//\\ Tim bien chua mat nguoi.
	std::vector<cv::Rect> faces = aGetsRect(pImage, pFaceCascadeName);
	//\\ Dua ket qua vao vector<Mat>
	for (size_t i = 0; i < faces.size(); i++)
	{
		result.push_back(pImage(faces[i]));
	}
	return result;
}