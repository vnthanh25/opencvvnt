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
	class DetectFace
	{
	public:
		DetectFace();
		~DetectFace();
		/********** private Members **********/
	private:
		std::string mFaceCascadeName = "cascades/haarcascade_frontalface_alt.xml";
		cv::CascadeClassifier mFaceCascade;

		/********** private Methods **********/
		bool aLoadFaceCascade();
		bool aLoadFaceCascade(const std::string pFaceCascadeName);

		/********** public Methods **********/
	public:
		//\\ Tim tat ca mat nguoi trong anh.
		std::vector<cv::Rect> aGetsRect(cv::Mat pImage);
		std::vector<cv::Mat> aGetsMat(cv::Mat pImage);
		//\\ Tim tat ca mat nguoi trong anh co tham so.
		std::vector<cv::Rect> DetectFace::aGetsRect(const cv::Mat pImage, const std::string pFaceCascadeName);
		std::vector<cv::Mat> DetectFace::aGetsMat(const cv::Mat pImage, const std::string pFaceCascadeName);
	};

}