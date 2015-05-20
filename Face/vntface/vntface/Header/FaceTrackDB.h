/*
VNThanh
- Face Track.
*/

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <fstream>
#include <stdio.h>

namespace vnt
{
	class FaceTrackDB
	{
	private:
		//\\ Danh sach ten file.
		std::vector<std::vector<std::string>> mFileNames;
		std::vector<std::vector<std::vector<std::vector<double>>>> mFaceTrackDatabase;
		std::vector<std::vector<std::vector<std::vector<int>>>> mFacetrackFeatures;
		std::vector<std::vector<int>> mPoses;
		std::string mFolderPath = "";
		std::string mFaceTrackName = "FaceTrack";//\\ Ex: "FaceTrack01", "FaceTrack02", ...
		std::string mFaceTracksFolder = "FaceTracks";
		std::string mFeatureName = "Feature";//\\ Ex: "Feature01", "Feature02", ...
		std::string mDBFeatureName = "Feature";//\\ Ex: "Feature01", "Feature02", ...
		std::string mDBFeatureFolder = "Database";//\\ Chua vector dac trung trung binh.
		std::string mFeatureType = ".fea";
		std::string mDBFeatureType = ".dbf";
		std::string mImageName = "Image";
		std::string mPoseName = "Pose";
		std::string mFileType = ".txt";
	public:
		/********** Constructor **********/
		FaceTrackDB();
		~FaceTrackDB();

		/********** public Methods **********/
		//\\ Lay danh sach ten file.
		std::vector<std::vector<std::string>> aGetFileNames();
		//\\ Gan danh sach ten file.
		void aSetFileNames(std::vector<std::vector<std::string>> pFileNames);

		//\\ Lay csdl.
		std::vector<std::vector<std::vector<std::vector<double>>>> aGetFaceTrackDatabase();
		//\\ Gan csdl.
		void aSetFaceTrackDatabase(std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTrackDatabase);

		//\\ Lay feature.
		std::vector<std::vector<std::vector<std::vector<int>>>> aGetFacetrackFeatures();
		//\\ Gan feature.
		void aSetFacetrackFeatures(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures);

		//\\ Lay Poses.
		std::vector<std::vector<int>> aGetPoses();
		//\\ Gan Poses.
		void aSetPoses(std::vector<std::vector<int>> pPoses);

		//\\ Doc tat ca file anh vao trong facetrack.
		std::vector<cv::Mat> aGestAllImage(std::string pFolderPath, std::vector<std::string> pAllFileName);

		//\\ Lay dac trung cua tung face trong facetrack.
		std::vector<std::vector<std::vector<int>>> aGetsFeature(const std::vector<cv::Mat> pFaceTrack);
		//\\ Tinh vector trung binh cho facetrack.
		std::vector<std::vector<double>> aAvgFeature(const std::vector<std::vector<std::vector<int>>> pFeatures, const std::vector<int> pFTPoses);
		//\\ Tinh vector trung binh cho facetrack.
		std::vector<std::vector<double>> aAvgFeatureNotPose(const std::vector<std::vector<std::vector<int>>> pFeatures);
		std::vector<std::vector<double>> aAvgFeature(const std::vector<cv::Mat> pFaceTrack, const std::vector<int> pFTPoses);
		std::vector<std::vector<double>> aAvgFeatureNotPose(const std::vector<cv::Mat> pFaceTrack);
		//\\ Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<std::vector<double>>> aAvgFeatures(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<int>> pFTPoses);
		//\\ Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<std::vector<double>>> aAvgFeaturesNotPose(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures);
		//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<double>> aAvgFeature(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<int>> pFTPoses);
		//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<double>> aAvgFeatureNotPose(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures);
		//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co 1 vector dac trung trung binh.
		std::vector<std::vector<double>> aAvgFeature(const std::vector<std::vector<std::vector<double>>> pFTFeatures);

		//\\ Tinh tong cua tich cac phan tu tuong ung trong 2 vector. Co so chieu bang nhau.
		double aSumMul(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);
		//\\ Tinh khoang cach cosine cua 2 vector. Co so chieu bang nhau.
		double aCosine(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);

		//\\ Tinh tong cua hieu cua binh phuong cac phan tu tuong ung trong 2 vector. Co so chieu bang nhau.
		double aSumSub(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);
		//\\ Tinh khoang cach hinh hoc cua 2 vector.
		double aEuclid(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);

		//\\ Tinh hieu cua 2 vector dac trung.
		std::vector<std::vector<double>> aSub(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);
		
		//\\ Khoi tao vector dac trung.
		int aFeatureInit(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<int>> pPoses, std::string pFolderPath);
		//\\ Khoi tao vector dac trung.
		int aFeatureInitNotPose(std::vector<std::vector<cv::Mat>> pFaceTracks, std::string pFolderPath);
		//\\ (Use) Khoi tao vector dac trung.
		int aFeatureInit(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pSavePath, bool pIsSaveToFile = true);

		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aFeatureRead(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aFeatureReadNotPose(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aFeatureRead(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aFeatureReadNotPose(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath);
		//\\ (Use) Doc cac anh  va thong tin tu file.
		int aFeatureRead(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath);

		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
		int aDatabaseInit(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<int>> pPoses);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
		int aDatabaseInitNotPose(std::vector<std::vector<cv::Mat>> pFaceTracks);

		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInit(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitNotPose(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitNotNormalize(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitNotPoseNotNormalize(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile = true);
		
		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aDatabaseRead(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aDatabaseRead(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath);

		//\\ Sap xep danh sach facetrack theo facetrack truy van. Moi facetrack duoc dai dien bang 1 vector dac trung trung binh.
		std::vector<std::vector<std::vector<std::vector<double>>>> aMeanCosMatching(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks);
		std::vector<int> aMeanCosMatchingIndex(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks);
		//\\ Thuat toan mean-cos: input (facetrack truy van, DS facetrack); output (DS facetrack duoc sap xep theo facetrack truy van).
		std::vector<std::vector<cv::Mat>> aMeanCos(std::vector<cv::Mat> pFaceTrack, std::vector<int> pPose, std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<int>> pPoses);
		//\\ Thuat toan mean-cos: input (facetrack truy van, DS facetrack); output (DS facetrack duoc sap xep theo facetrack truy van).
		std::vector<std::vector<cv::Mat>> aMeanCosNotPose(std::vector<cv::Mat> pFaceTrack, std::vector<std::vector<cv::Mat>> pFaceTracks);


		/******************** Gia lap ********************/
		//\\ Gia lap danh sach vector dac trung cua facetrack. 1 facetrack co nhieu vector dac trung.
		std::vector<std::vector<std::vector<int>>> aGetsFeatureFake(size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue = -1);
		//\\ Gia lap danh sach vector dac trung trung binh cua tat ca facetrack. Moi facetrack co 1 vector dac trung trung binh.
		std::vector<std::vector<std::vector<double>>> aGetsAvgFeatureFake(size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue = -1);
		//\\ Gia lap danh sach cua danh sach vector dac trung cua facetrack. Moi  facetrack co nhieu vector dac trung.
		std::vector<std::vector<std::vector<std::vector<int>>>> aGetsFeaturesFake(size_t pNumLists, size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue = -1);
		//\\ Gia lap vector dac trung trung binh.
		std::vector<std::vector<double>> aAvgFetureFake(size_t pNumRows, size_t pNumCols, double pValue = -1);
		//\\ Gia lap facetrack.
		std::vector<cv::Mat> aFaceTrackFake(size_t numList, int pNumRows, int pNumCols, uchar pValue = -1);

		//\\ (Use) Luu ra file: Anh Mat, anh goc, gia tri pose. pFileName: co phan mo rong.
		void aSaveToFile(cv::Mat pFace, int pPose, std::string pFileName, std::string pSavePath);
		//\\ (Use) Luu danh sach ten file anh va pose tuong ung cua tung facetrack ra file. Kich thuoc 2 danh sach phai bang nhau.
		void aSaveToFile(std::vector<std::string> pFileNames, std::vector<int> pPoses, std::string pSavePath);
	};

}