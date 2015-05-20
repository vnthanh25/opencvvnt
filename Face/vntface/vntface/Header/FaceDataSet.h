/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <fstream>
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
		//\\ Danh sach ten file.
		std::vector<std::vector<std::string>> mFileNames;
		//\\ Danh sach facetrack
		std::vector<std::vector<cv::Mat>> mFaceTracks;
		//\\ Danh sach pose cua tung anh trong moi facetrack.
		std::vector<std::vector<int>> mPoses;
		//\\ Tong cac tri pose.
		std::string mFolderPath = "";
		std::string mFaceTrackName = "FaceTrack";//\\ Ex: "FaceTrack01", "FaceTrack02", ...
		std::string mDataSetFolder = "DataSet";//\\ Chua gia tri Mat cua anh.
		std::string mImageType = ".img";
		std::string mImageName = "Image";
		std::string mPoseName = "Pose";
		std::string mFileType = ".txt";
	public:
		/********** Constructor **********/
		FaceDataSet();
		~FaceDataSet();
	
		/********** public Methods **********/
		//\\ Lay nguon anh.
		FaceDataSetBase* aGetDataSetBase();
		//\\ Gan nguon anh.
		void aSetDataSetBase(FaceDataSetBase* pDataSetBase);
		//\\ Lay danh sach ten file.
		std::vector<std::vector<std::string>> aGetFileNames();
		//\\ Gan danh sach ten file.
		void aSetFileNames(std::vector<std::vector<std::string>> pFileNames);
		//\\ Lay danh sach facetrack.
		std::vector<std::vector<cv::Mat>> aGetFaceTraks();
		//\\ Gan danh sach facetrack.
		void aSetFaceTracks(std::vector<std::vector<cv::Mat>> pFaceTracks);
		//\\ Lay danh sach pose.
		std::vector<std::vector<int>> aGetPoses();
		//\\ Gan danh sach pose.
		void aSetPoses(std::vector<std::vector<int>> pPoses);

		//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack.
		std::vector<cv::Mat> aReadsImage(std::vector<std::string> pAllFileName, const std::string pDataSourcePath);
		//\\ (Use) Doc tat ca cac anh trong mot thu muc. Giu lai danh sach dac trung va pose tuong ung. Tuy co luu ra file.
		void aReadsImage(std::vector<std::string> pAllFileName, std::vector<int> pPoses, const std::string pDataSourcePath, std::string pSavePath, bool pIsSaveToFile = true);
		//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack. Co luu ra file.
		std::vector<cv::Mat> aReadsImageNotPose(std::vector<std::string> pAllFileName, const std::string pDataSourcePath, std::string pFolderPath);

		//\\ (Use) Khoi tao DataSet (chuyen doi anh thanh doi tuong Mat).
		int aDataSetInit(FaceDataSetBase* pFaceDataSetBase, std::string pDataSourcePath);
		//\\ (Use) Khoi tao DataSet (chuyen doi anh thanh doi tuong Mat). Co ghi csdl ra file.
		int aDataSetInit(FaceDataSetBase* pFaceDataSetBase, std::string pDataSourcePath, std::string pSavePath, const bool pCheckFile = false);
		//\\ Chia moi FaceTrack trong DataSet thanh n FaceTrack. Co ghi csdl ra file. Kiem tra file anh co ton tai khong?
		int aDataSetInitDiv(FaceDataSetBase* pFaceDataSetBase, const std::string pDataSourcePath, const std::string pSavePath, const int pNum, const bool pCheckFile = false);
	
		//\\ Doc cac anh tu file.
		int aDataSetRead(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac anh tu file.
		int aDataSetReadNotPose(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac anh tu file.
		int aDataSetRead(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac anh tu file.
		int aDataSetReadNotPose(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath);
		//\\ (Use) Doc cac anh  va thong tin tu file.
		int aDataSetRead(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath, bool pIsPose = true);

		//\\ (Use) Luu ra file: Anh Mat, anh goc, gia tri pose. pFileName: co phan mo rong.
		void aSaveToFile(cv::Mat pFace, int pPose, std::string pFileName, std::string pSavePath);
		//\\ (Use) Luu danh sach ten file anh va pose tuong ung cua tung facetrack ra file. Kich thuoc 2 danh sach phai bang nhau.
		void aSaveToFile(std::vector<std::string> pFileNames, std::vector<int> pPoses, std::string pSavePath);
	};
}