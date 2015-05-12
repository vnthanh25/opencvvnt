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
/********** public Methods **********/
std::string FaceDetect::getFaceCascadeName()
{
	return mFaceCascadeName;
}
void FaceDetect::setFaceCascadeName(std::string pFaceCascadeName)
{
	mFaceCascadeName = pFaceCascadeName;
}
cv::CascadeClassifier FaceDetect::getFaceCascade()
{
	return mFaceCascade;
}
void FaceDetect::setFaceCascade(cv::CascadeClassifier pFaceCascade)
{
	mFaceCascade = pFaceCascade;
}

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
//\\ Tim tat ca mat nguoi trong anh. Co tham so. Co ghi ra file.
std::vector<cv::Mat> FaceDetect::aGetsMat(const std::vector<std::string> pFileNames, const std::string pSourcePath, const std::string pSavePath)
{
	std::vector<cv::Mat> result;
	size_t fileSize = pFileNames.size();
	for (size_t i = 0; i < fileSize; i++)
	{
		//\\ Doc anh.
		cv::Mat vFace = cv::imread(pSourcePath + pFileNames[i], CV_8UC1);
		//\\ Detect face.

		//std::vector<cv::Mat> faces = detFace.aGetsMat(cv::imread("images/lena.png", CV_8UC1));
		std::vector<cv::Mat> faces = aGetsMat(vFace);

		//\\ Find face larger.
		int vFaceSize = 0;
		int vIndex = 0;
		for (size_t j = 0; j < faces.size(); j++)
		{
			cv::Size vSize = faces[j].size();
			if (vFaceSize < vSize.height * vSize.width)
			{
				vIndex = j;
			}
			vFaceSize = vSize.height * vSize.width;
		}
		//\\ Ghi ra file.
		if (vFaceSize > 0)
		{
			//cv::imshow("image_" + vImageIndex + "_" + std::to_string(i), faces[i]);
			cv::imwrite(pSavePath + pFileNames[i], faces[vIndex]);
			result.push_back(faces[vIndex]);
		}
	}
	return result;
}
std::vector<cv::Mat> FaceDetect::aGetsMat(const std::vector<std::string> pFileNames, const std::string pSourcePath, const std::string pSavePath, const std::string pFaceCascadeName)
{
	std::vector<cv::Mat> result;
	size_t fileSize = pFileNames.size();
	for (size_t i = 0; i < fileSize; i++)
	{
		//\\ Doc anh.
		cv::Mat vFace = cv::imread(pSourcePath + pFileNames[i], CV_8UC1);
		//\\ Detect face.

		//std::vector<cv::Mat> faces = detFace.aGetsMat(cv::imread("images/lena.png", CV_8UC1));
		std::vector<cv::Mat> faces = aGetsMat(vFace, pFaceCascadeName);

		//\\ Find face larger.
		int vFaceSize = 0;
		int vIndex = 0;
		for (size_t j = 0; j < faces.size(); j++)
		{
			cv::Size vSize = faces[j].size();
			if (vFaceSize < vSize.height * vSize.width)
			{
				vIndex = j;
			}
			vFaceSize = vSize.height * vSize.width;
		}
		//\\ Ghi ra file.
		if (vFaceSize > 0)
		{
			//cv::imshow("image_" + vImageIndex + "_" + std::to_string(i), faces[i]);
			cv::imwrite(pSavePath + pFileNames[i], faces[vIndex]);
			result.push_back(faces[vIndex]);
		}
	}
	return result;
}