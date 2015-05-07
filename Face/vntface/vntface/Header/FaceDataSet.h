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
		//\\ Danh sach pose cua tung anh trong moi facetrack.
		std::vector<std::vector<int>> mPoses;
		//\\ Tong cac tri pose.
		int mSumPose;
		std::string mFolderPath = "";
		std::string mFaceTrackName = "FaceTrack";//\\ Ex: "FaceTrack01", "FaceTrack02", ...
		std::string mDataSetFolder = "DataSet";//\\ Chua gia tri Mat cua anh.
		std::string mImageType = ".img";
		std::string mImageName = "Image";
		std::string mPoseName = "Pose";
		std::string mSumPoseName = "SumPose";
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
		//\\ Lay danh sach pose.
		std::vector<std::vector<int>> aGetPoses();
		//\\ Gan danh sach pose.
		void aSetPoses(std::vector<std::vector<int>> pPoses);
		//\\ Lay tong pose.
		int aGetSumPose();
		//\\ Gan tong pose.
		void aSetSumPose(int pSumPose);

		//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack.
		std::vector<cv::Mat> aReadsImage(std::vector<std::string> pAllFileName, const std::string pDataSourcePath);
		//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack. Co luu ra file.
		std::vector<cv::Mat> aReadsImage(std::vector<std::string> pAllFileName, std::vector<int> pPoses, const std::string pDataSourcePath, std::string pFolderPath);
		//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack. Co luu ra file.
		std::vector<cv::Mat> aReadsImageNotPose(std::vector<std::string> pAllFileName, const std::string pDataSourcePath, std::string pFolderPath);

		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
		int aDataSetInit(FaceDataSetBase* pFaceDataSetBase, std::string pDataSourcePath);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDataSetInit(FaceDataSetBase* pFaceDataSetBase, std::string pDataSourcePath, std::string pFolderPath);
		
		//\\ Doc cac anh tu file.
		int aDataSetRead(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac anh tu file.
		int aDataSetReadNotPose(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);

	};
}