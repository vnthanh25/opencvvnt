/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#ifndef _FaceDataSetBase_
#define _FaceDataSetBase_
#include "FaceDataSetBase.h"
#endif

namespace vnt
{
	/********** FaceDataSet: Data player **********/
	class FaceDataSet
	{
	private:
		FaceDataSetBase* mDataSetBase;
		//\\ Danh sach facetrack
		std::vector<std::vector<cv::Mat>> mFaceTracks;
		std::string mFolderPath = "";
		std::string mFaceTrackName = "FaceTrack";//\\ Ex: "FaceTrack01", "FaceTrack02", ...
		std::string mDataSetFolder = "DataSet";//\\ Chua gia tri Mat cua anh.
		std::string mImageType = ".img";
		std::string mImageName = "Image";
	public:
		/********** Constructor **********/
		FaceDataSet();
		~FaceDataSet();
	
		/********** public Methods **********/
		//\\ Lay nguon anh.
		FaceDataSetBase* aGetDataSetBase();
		//\\ Gan nguon anh.
		void aSetDataSetBase(FaceDataSetBase* pDataSetBase);
		//\\ Lay danh sach facetrack.
		std::vector<std::vector<cv::Mat>> aGetFaceTraks();
		//\\ Gan danh sach facetrack.
		void aSetFaceTracks(std::vector<std::vector<cv::Mat>> pFaceTracks);
	
		//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack.
		std::vector<cv::Mat> aReadsImage(std::vector<std::string> pAllFileName, const std::string pDataSourcePath);
		//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack. Co luu ra file.
		std::vector<cv::Mat> aReadsImage(std::vector<std::string> pAllFileName, const std::string pDataSourcePath, std::string pFolderPath);

		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
		int aDataSetInit(FaceDataSetBase* pFaceDataSetBase, std::string pDataSourcePath);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDataSetInit(FaceDataSetBase* pFaceDataSetBase, std::string pDataSourcePath, std::string pFolderPath);
		//\\ Doc cac anh tu file va dua vao csdl.
		int aDataSetRead(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);

	};
}