#include "Utilities.h"
#include "FaceDetect.h"
#include "HeadPose.h"
#include "ColorFeret.h"
#include "FaceDataSet.h"
#include "FaceTrackDB.h"

namespace vnt
{
	/********** class Matching **********/
	class Matching
	{
	public:
		std::string mDataSetFolder = "DataSet";//\\ Chua gia tri Mat cua anh.
		std::string mFaceTrackName = "FaceTrack";//\\ Ex: "FaceTrack01", "FaceTrack02", ...
		std::string mFaceTracksFolder = "FaceTracks";
		std::string mFeatureName = "Feature";//\\ Ex: "Feature01", "Feature02", ...
		std::string mDBFeatureName = "Feature";//\\ Ex: "Feature01", "Feature02", ...
		std::string mDatabaseFolder = "Database";//\\ Chua vector dac trung trung binh.
		std::string mMatchingFolder = "Matching";//\\ Chua vector dac trung trung binh.
		std::string mLBPTitle = "LBP";
		std::string mLBPVLFeatTitle = "LBPVLFeat";

		int mNumPerson = 0;
		int mDiv = 0;
		//\\ Detect HeadPose with serie 1.
		void aHeadPoseFaceDetectSerie1(std::string pCascadeName);
		//\\ Detect HeadPose with serie 2.
		void aHeadPoseFaceDetectSerie2(std::string pCascadeName);
		//\\ Detect HeadPose with serie 1 and 2.
		void aHeadPoseFaceDetect();


		//\\ Khoi tao DataSet: Serie 1 + Not Div
		void aHeadPoseDataSetInitSerie1NotDiv();
		//\\ Khoi tao DataSet: Serie 1 + Div (3).
		void aHeadPoseDataSetInitSerie1Div();
		//\\ Khoi tao DataSet: Serie 2 + Not Div
		void aHeadPoseDataSetInitSerie2NotDiv();
		//\\ Khoi tao DataSet: Serie 2 + Div (3).
		void aHeadPoseDataSetInitSerie2Div();
		//\\ Khoi tao DataSet: facetrack 15-30 ung voi serie2.
		void Matching::aHeadPoseDataSetInitNotDiv();
		//\\ Khoi tao DataSet
		void aHeadPoseDataSetInit();


		//\\ Khoi tao features: Serie1 + Khong chia + co Pose.
		void aFeaturesInitSerie1NotDiv();
		//\\ Khoi tao features: Serie1 + chia + co Pose.
		void aFeaturesInitSerie1Div();
		//\\ Khoi tao features: Serie2 + Khong chia + co Pose.
		void aFeaturesInitSerie2NotDiv();
		//\\ Khoi tao features: Serie2 + chia + co Pose.
		void aFeaturesInitSerie2Div();
		//\\ Khoi tao features: Serie1 + Serie2.
		void aFeaturesInitNotDiv();
		//\\ Khoi tao feature
		void aFeaturesInit();


		//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
		void aDatabaseInit_Serie12_NotDiv_NotPoseNormalize(std::string pTestPath);
		//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
		void aDatabaseInit_Serie12_NotDiv_NotPoseNotNormalize(std::string pTestPath);
		//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
		void aDatabaseInit_Serie12_NotDiv_PoseNormalize(std::string pTestPath);
		//\\ Khoi tao csdl: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
		void aDatabaseInit_Serie12_NotDiv_PoseNotNormalize(std::string pTestPath);

		//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
		void aDatabaseInit_Serie12_Div_NotPoseNormalize(std::string pTestPath);
		//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
		void aDatabaseInit_Serie12_Div_NotPoseNotNormalize(std::string pTestPath);
		//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
		void aDatabaseInit_Serie12_Div_PoseNormalize(std::string pTestPath);
		//\\ Khoi tao csdl: Div (csdl chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
		void aDatabaseInit_Serie12_Div_PoseNotNormalize(std::string pTestPath);

		//\\ Khoi tao csdl: HeadPose (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + Normalize (csdl co chuan hoa).
		void aDatabaseInit_HeadPose_NotPoseNormalize();
		//\\ Khoi tao csdl: HeadPose (csdl khong chia) + InDiv (query trong csdl co chia) + NotPose (khong co Pose) + NotNormalize (csdl khong chuan hoa).
		void aDatabaseInit_HeadPose_NotPoseNotNormalize();
		//\\ Khoi tao csdl: HeadPose (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + Normalize (csdl co chuan hoa).
		void aDatabaseInit_HeadPose_PoseNormalize(int pNumVector, int pMinPose, int pMaxPose);
		//\\ Khoi tao csdl: HeadPose (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
		void aDatabaseInit_HeadPose_PoseNotNormalize(int pNumVector, int pMinPose, int pMaxPose);

		//\\ Detect face.
		void aDetectFace(std::string pCascadeName, std::string pSourcePath, std::string pSavePath, std::string pPrefixFaceTrackName, std::string pSuffixFaceTrackName, std::string pStartIndex, std::string pEndIndex, FaceDataSetBase* pFaceDataSetBase);
		//\\ Khoi tao csdl.
		void aDatabaseInitHeadPose();
		void aDatabaseInit(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pDataSetPath, std::string pFeaturePath, std::string pSavePath, int pElementType, TypeFunction pTypeFunction);

		//\\ Khoi tao csdl: tao dataset -> tao facetrack -> tao database.
		void aDatabaseInitFull(std::string pSourcePath);
		void aDatabaseInitFull1(std::string pSourcePath);

		std::vector<int> aMatching(FaceTrackDB pFaceTrackDB, FaceTrackDB pFaceTrackDBQuery, int pNum);
		//\\ So khop: NotDiv (csdl khong chia) + InDiv (query trong csdl co chia).
		std::vector<int> aMatchingHeadPose_NotDiv_Div(std::string pDatabasePath, std::string pQueryPath, std::string pDatabaseFeaturePath, std::string pQueryFeaturePath, int pNum);
		//\\ So khop:
		void aMatchingHeadPose();


		//\\ Tinh vector dac trung trung binh.
		std::vector<std::vector<double>> aFeatureAvg(std::string pSourcePath, bool pIsPose);
		void aMatchingHeadPoseCheck(bool pIsPose);
		void aMatchingHeadPoseCheck();



		double aMatchingHeadPoseMAP1(std::string pDatabasePath);

		double aMatchingMAP2(std::string pDatabasePath, std::string pDatabaseFeaturePath, int pCountMax, int pNumPerson, int pDiv);
		double aMatchingMAP(std::string pDatabasePath, int pNumFaceTrackStart, int pNumFaceTrackEnd, int pMul, int pDiv, std::string pLogPath);
		//\\ Tron serie1 va serie2 cua HeadPose de lam csdl va tinh MAP.
		void aMatchingHeadPoseMAP();
		void aMatchingColorFeretMAP();


		std::string aGetFaceTrackPath(std::string pSavePath, int pLBPType);
		std::string aDatabasePath(std::string pSavePath, int pLBPType, int pFunctionType);
		std::string aMatchingPath(std::string pSavePath, int pLBPType, int pFunctionType);
		void aDataSetInit(FaceDataSetBase* pFaceDataSetBase, int pPersonStart, int pPersonEnd, std::string pSourePath, std::string pSavePath, int pMul, int pDiv);
		void aFeatureInit(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourePath, std::string pSavePath, int pLBPType);
		void aDatabaseInitFunctionType(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pDataSetPath, std::string pFeaturePath, std::string pSavePath, int pLBPType);
		void aMatchingFunctionType(std::string pDatabasePath, int pNumFaceTrackStart, int pNumFaceTrackEnd, int pMul, int pDiv, std::string pLogPath, int pLBPType);
		
		void aMatchingHeadPoseFull(std::string pSourePath, std::string pSavePath, int pPersonStart, int pPersonEnd, int pMul, int pDiv, int pLBPType = 0);
		void aMatchingColorFeretFull(std::string pSourePath, std::string pSavePath, int pPersonStart, int pPersonEnd, int pMul, int pDiv, int pLBPType = 0);
		// Color Feret:pDataSetType = 1 (HeadPose); pDataSetType = 2 (ColorFeret). pElementType = 1 (LBP); pElementType = 2 (LBPVLFeat).
		void aMatchingFull();
	};
}
