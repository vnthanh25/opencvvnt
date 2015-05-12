/*
VNThanh
- Phat hien mat nguoi trong anh.
*/
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

namespace vnt
{
	class FaceDetect
	{
	private:
		/********** private Members **********/
		std::string mFaceCascadeName;
		cv::CascadeClassifier mFaceCascade;

		/********** private Methods **********/

	public:
		/********** Constructor **********/
		FaceDetect();
		~FaceDetect();
		/********** public Methods **********/
		std::string getFaceCascadeName();
		void setFaceCascadeName(std::string pFaceCascadeName);
		cv::CascadeClassifier getFaceCascade();
		void setFaceCascade(cv::CascadeClassifier pFaceCascade);


		//\\ Khoi tao phan lop.
		bool aLoadFaceCascade();
		bool aLoadFaceCascade(const std::string pFaceCascadeName);
		//\\ Tim tat ca mat nguoi trong anh.
		std::vector<cv::Rect> aGetsRect(cv::Mat pImage);
		std::vector<cv::Mat> aGetsMat(cv::Mat pImage);
		//\\ Tim tat ca mat nguoi trong anh. Co tham so.
		std::vector<cv::Rect> aGetsRect(const cv::Mat pImage, const std::string pFaceCascadeName);
		std::vector<cv::Mat> aGetsMat(const cv::Mat pImage, const std::string pFaceCascadeName);
		//\\ Tim tat ca mat nguoi trong anh. Co tham so. Co ghi ra file.
		std::vector<cv::Mat> aGetsMat(const std::vector<std::string> pFileNames, const std::string pSourcePath, const std::string pSavePath);
		std::vector<cv::Mat> aGetsMat(const std::vector<std::string> pFileNames, const std::string pSourcePath, const std::string pSavePath, const std::string pFaceCascadeName);
	};

}