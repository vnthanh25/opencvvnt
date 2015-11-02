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
	enum TypeFunction { Not, Linear, Gaussian, Threshold, Filter };

	class FaceTrackDB
	{
	private:
		//\\ Danh sach ten file.
		std::vector<std::vector<std::string>> mFileNames;
		std::vector<std::vector<std::vector<std::vector<double>>>> mFaceTrackDatabase;
		std::vector<std::vector<std::vector<std::vector<int>>>> mFacetrackFeatures;
		std::vector<std::vector<int>> mPoses;
		//\\ Danh sach pose cua tung anh trong moi facetrack. format: "tilt;pan".
		std::vector<std::vector<std::string>> mTiltPanPoses;
		//\\ Danh sach pose cua tung anh trong moi facetrack.
		std::vector<std::vector<std::string>> mPoseNames;
		std::string mFolderPath = "";
		std::string mDataSetFolder = "DataSet";//\\ Chua gia tri Mat cua anh.
		std::string mImageType = ".img";
		std::string mFaceTrackName = "FaceTrack";//\\ Ex: "FaceTrack01", "FaceTrack02", ...
		std::string mFaceTracksFolder = "FaceTracks";
		std::string mFeatureName = "Feature";//\\ Ex: "Feature01", "Feature02", ...
		std::string mDBFeatureName = "Feature";//\\ Ex: "Feature01", "Feature02", ...
		std::string mDBFeatureFolder = "Database";//\\ Chua vector dac trung trung binh.
		std::string mFeatureType = ".fea";
		std::string mDBFeatureType = ".dbf";
		std::string mImageName = "Image";
		std::string mPoseName = "Pose";
		std::string mTiltPanPoseName = "TiltPanPoses";
		std::string mPoseNameName = "PoseNames";
		std::string mFileType = ".txt";
		const int mMaxPose = 100;
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

		//\\ Lay TiltPanPoses.
		std::vector<std::vector<std::string>> aGetTiltPanPoses();
		//\\ Gan TiltPanPoses.
		void aSetTiltPanPoses(std::vector<std::vector<std::string>> pTiltPanPoses);

		//\\ Lay danh sach pose name.
		std::vector<std::vector<std::string>> aGetPoseNames();
		//\\ Gan danh sach pose name.
		void aSetPoseNames(std::vector<std::vector<std::string>> pPoseNames);

		//\\ Lay danh sach FolderPath.
		std::string aGetFolderPath();
		//\\ Gan danh sach FolderPath.
		void aSetFolderPath(std::string pFolderPath);



		//\\ Doc tat ca file anh vao trong facetrack.
		std::vector<cv::Mat> aGestAllImage(std::string pFolderPath, std::vector<std::string> pAllFileName);

		//\\ Lay dac trung cua tung face trong facetrack.
		std::vector<std::vector<std::vector<int>>> aGetsFeature(const std::vector<cv::Mat> pFaceTrack);
		//\\ Tinh vector trung binh cho facetrack.
		std::vector<std::vector<double>> aAvgFeature1(const std::vector<std::vector<std::vector<int>>> pFeatures, const std::vector<int> pFTPoses);
		//\\ Tinh vector trung binh cho facetrack.
		std::vector<std::vector<double>> aAvgFeatureNotPose1(const std::vector<std::vector<std::vector<int>>> pFeatures);
		std::vector<std::vector<double>> aAvgFeature2(const std::vector<cv::Mat> pFaceTrack, const std::vector<int> pFTPoses);
		std::vector<std::vector<double>> aAvgFeatureNotPose2(const std::vector<cv::Mat> pFaceTrack);
		//\\ Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<std::vector<double>>> aAvgFeaturesPose1(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<int>> pFTPoses);
		//\\ Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<std::vector<double>>> aAvgFeaturesNotPose1(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures);
		//\\ Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<std::vector<double>>> aAvgFeaturesPose2(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<std::string>> pTiltPanPoses, int pMinPose, int pMaxPose);
		//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<double>> aAvgFeature3(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<int>> pFTPoses);
		//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<double>> aAvgFeatureNotPose3(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures);
		//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co 1 vector dac trung trung binh.
		std::vector<std::vector<double>> aAvgFeature4(const std::vector<std::vector<std::vector<double>>> pFTFeatures);
		//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<double>> aAvgFeature5(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<std::string>> pTiltPanPoses);
		//\\ Tinh vector trung binh cho facetrack.
		std::vector<std::vector<double>> aAvgFeature6(const std::vector<std::vector<std::vector<int>>> pFeatures, const std::vector<std::string> pTiltPanPoses, int pMinPose, int pMaxPose);

		//\\ Tinh tong cua tich cac phan tu tuong ung trong 2 vector. Co so chieu bang nhau.
		double aSumMul1(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);
		double aSumMul2(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2);
		//\\ Tinh khoang cach cosine cua 2 vector. Co so chieu bang nhau.
		double aCosine1(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);
		double aCosine2(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2);

		//\\ Tinh tong cua hieu cua binh phuong cac phan tu tuong ung trong 2 vector. Co so chieu bang nhau.
		double aSumSub1(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);
		double aSumSub2(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2);
		//\\ Tinh khoang cach hinh hoc cua 2 vector.
		double aEuclid11(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);
		double aEuclid21(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2);
		//\\ Tinh khoang cach hinh hoc cua 2 vector.
		double aLp1(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2, int pLevel);
		double aLp2(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2, int pLevel);

		//\\ Tinh hieu cua 2 vector dac trung.
		std::vector<std::vector<double>> aSub(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2);
		//\\ Tinh tong cua 2 vector dac trung.
		std::vector<std::vector<double>> aSum(std::vector<std::vector<double>> pVector1, std::vector<std::vector<int>> pVector2);
		//\\ (Use) (1,2) (double) Tinh tong sau khi nhan cua 2 vector dac trung.
		std::vector<std::vector<double>> aSumAfterMul(std::vector<std::vector<double>> pVector1, std::vector<std::vector<int>> pVector2, int pPose);
		//\\ (Use) (1,2) (double) Tinh tong sau khi nhan cua 2 vector dac trung.
		std::vector<std::vector<double>> aSumAfterGaussian(std::vector<std::vector<double>> pVector1, std::vector<std::vector<int>> pVector2, int pPose);
		//\\ Tinh tong cua 2 vector dac trung.
		std::vector<std::vector<double>> aSumFloat(std::vector<std::vector<double>> pVector1, std::vector<std::vector<float>> pVector2);
		//\\ (Use) (1,2) (double) Tinh tong sau khi nhan cua 2 vector dac trung.
		std::vector<std::vector<double>> aSumAfterMulFloat(std::vector<std::vector<double>> pVector1, std::vector<std::vector<float>> pVector2, int pPose);
		//\\ (Use) (1,2) (double) Tinh tong sau khi nhan cua 2 vector dac trung.
		std::vector<std::vector<double>> aSumAfterGaussianFloat(std::vector<std::vector<double>> pVector1, std::vector<std::vector<float>> pVector2, int pPose);

		//\\ Chia vector dac trung cho mot so
		std::vector<std::vector<double>> aDiv(std::vector<std::vector<double>> pVector, int pDiv);
		//\\ Khoi tao vector dac trung
		std::vector<std::vector<double>> aInitFeature(double pValue, int pRows, int pCols);

		//\\ Khoi tao vector dac trung.
		int aFeatureInit1(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<int>> pPoses, std::string pFolderPath);
		//\\ Khoi tao vector dac trung.
		int aFeatureInitNotPose1(std::vector<std::vector<cv::Mat>> pFaceTracks, std::string pFolderPath);
		//\\ Khoi tao vector dac trung.
		int aFeatureInit2(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pSavePath, bool pIsSaveToFile = true);
		//\\ (Use) Khoi tao vector dac trung.
		int aFeatureInit3(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::vector<std::vector<std::string>> pPoseNames, std::string pSavePath, bool pIsSaveToFile = true);
		//\\ (Use) Khoi tao vector dac trung.
		int aFeatureInit4(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, std::vector<std::vector<std::string>> pPoseNames, std::string pSavePath, bool pIsSaveToFile = true);
		//\\ (Use) Khoi tao vector dac trung.
		int aFeatureInit5(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSavePath, bool pIsSaveToFile = true);
		//\\ (Use) Khoi tao vector dac trung.
		int aFeatureInit(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pDataSetPath, std::string pSavePath, bool pIsSaveToFile = true);
		//\\ (Use) Khoi tao vector dac trung.
		int aFeatureInitFloat(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pDataSetPath, std::string pSavePath, int pElementType, bool pIsSaveToFile = true);

		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aFeatureRead1(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aFeatureReadNotPose1(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aFeatureRead2(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac vector dac trung tu file va dua vao csdl.
		int aFeatureReadNotPose2(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath);
		//\\ (Use) (1) Doc cac anh  va thong tin tu file.
		int aFeatureRead3(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath);
		//\\ (Use) (2) Doc cac anh  va thong tin tu file.
		int aFeatureRead4(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath);

		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
		int aDatabaseInit(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<int>> pPoses);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
		int aDatabaseInitNotPose(std::vector<std::vector<cv::Mat>> pFaceTracks);

		//\\ TiltPanPose = Tilt + Pan.
		int aSumTiltPanPose();

		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitPoseNormalize1(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitNotPose1(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitNotNormalize1(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitNotPoseNotNormalize1(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitPoseNormalize2(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, int pMinPose, int pMaxPose, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ (Use) (2) Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitNotPose2(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitNotNormalize2(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, int pMinPose, int pMaxPose, std::string pFolderPath, bool pIsSaveToFile = true);
		//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
		int aDatabaseInitNotPoseNotNormalize2(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, std::string pFolderPath, bool pIsSaveToFile = true);

		//\\ (Use) Khoi tao database.
		int aDatabaseInitNotPose5(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSavePath, bool pIsSaveToFile = true);
		//\\ (Use) Khoi tao database.
		int aDatabaseInitPose5(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSavePath, int pMinPose, int pMaxPose, TypeFunction pTypeFunction = Not, bool pIsSaveToFile = true);
		//\\ (Use) Khoi tao database.
		int aDatabaseInit(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pDataSetPath, std::string pFeaturePath, std::string pSavePath, int pMinPose, int pMaxPose, TypeFunction pTypeFunction = Not, bool pIsSaveToFile = true);
		//\\ (Use) Khoi tao database.
		int aDatabaseInitFloat(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pDataSetPath, std::string pFeaturePath, std::string pSavePath, int pMinPose, int pMaxPose, TypeFunction pTypeFunction = Not, bool pIsSaveToFile = true);


		//\\ Doc cac vector dac trung trung binh tu file va dua vao csdl.
		int aDatabaseRead1(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath);
		//\\ Doc cac vector dac trung trung binh tu file va dua vao csdl.
		int aDatabaseRead2(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath);
		//\\ (Use) Doc cac vector dac trung trung binh tu file va dua vao csdl.
		int aDatabaseRead3(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath);
		//\\ (Use) Doc cac vector dac trung trung binh va doc tat ca feature tuong ung tu file va dua vao csdl.
		int aDatabaseAndFeatureRead(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath, std::string pFeaturePath);
		//\\ (Use) Doc cac vector dac trung trung binh va doc tat ca feature tuong ung tu file va dua vao csdl.
		int aDatabaseAndFeatureRead5(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath, std::string pFeaturePath);
		//\\ (Use) Doc cac vector dac trung trung binh va doc tat ca feature tuong ung tu file va dua vao csdl.
		int aDatabaseRead(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath, int pFeatureCount);

		//\\ Sap xep danh sach facetrack theo facetrack truy van. Moi facetrack duoc dai dien bang 1 vector dac trung trung binh.
		std::vector<std::vector<std::vector<std::vector<double>>>> aMeanCosMatching(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks);
		std::vector<int> aMeanCosMatchingIndex1(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks);
		//\\ Sap xep danh sach vector dac trung trung binh.
		std::vector<int> FaceTrackDB::aMeanCosMatchingIndex2(std::vector<std::vector<double>> pFeature, std::vector<std::vector<std::vector<double>>> pFeatures);
		std::vector<int> aMeanCosMatchingIndex3(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks, std::vector<std::vector<std::vector<int>>> pFeatureFaceTrack, std::vector<std::vector<std::vector<std::vector<int>>>> pFeatureFaceTracks, std::vector<std::string> pPoseName, std::vector<std::vector<std::string>> pPoseNames, int pCountMax);
		std::vector<int> aMeanCosMatchingIndex(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks, std::string pLogPath);
		//\\ Thuat toan mean-cos: input (facetrack truy van, DS facetrack); output (DS facetrack duoc sap xep theo facetrack truy van).
		std::vector<std::vector<cv::Mat>> aMeanCos(std::vector<cv::Mat> pFaceTrack, std::vector<int> pPose, std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<int>> pPoses);
		//\\ Thuat toan mean-cos: input (facetrack truy van, DS facetrack); output (DS facetrack duoc sap xep theo facetrack truy van).
		std::vector<std::vector<cv::Mat>> aMeanCosNotPose(std::vector<cv::Mat> pFaceTrack, std::vector<std::vector<cv::Mat>> pFaceTracks);
		//\\ Sap xep danh sach vector dac trung trung binh. Theo Level (level = 2 la Euclidian).
		std::vector<int> aLpMatchingIndex1(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks, std::vector<std::vector<std::vector<int>>> pFeatureFaceTrack, std::vector<std::vector<std::vector<std::vector<int>>>> pFeatureFaceTracks, std::vector<std::string> pPoseName, std::vector<std::vector<std::string>> pPoseNames, int pCountMax, int pLevel);

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

		//\\ (Use) Luu ra file: vector dac trung
		void aSaveToFile(cv::Mat pFace, std::string pFileName, std::string pSavePath);
		//\\ (Use) Luu ra file: vector dac trung
		void aSaveToFileFloat(cv::Mat pFace, std::string pFileName, std::string pSavePath, int pElementType);
		//\\ Luu danh sach ten file anh va pose tuong ung cua tung facetrack ra file. Kich thuoc 2 danh sach phai bang nhau.
		void aSaveToFile1(std::vector<std::string> pFileNames, std::vector<int> pPoses, std::string pSavePath);
		//\\ (Use) Luu danh sach ten file anh va pose tuong ung cua tung facetrack ra file. Kich thuoc 2 danh sach phai bang nhau.
		void aSaveToFile2(std::vector<std::string> pFileNames, std::vector<int> pPoses, std::vector<std::string> pPoseNames, std::string pSavePath);
		//\\ (Use) Luu danh sach ten file anh va pose tuong ung cua tung facetrack ra file. Kich thuoc 2 danh sach phai bang nhau.
		void aSaveToFile3(std::vector<std::string> pFileNames, std::vector<std::string > pPoses, std::vector<std::string> pPoseNames, bool pSortPose, std::string pSavePath);
	};

}