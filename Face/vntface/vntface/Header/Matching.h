#include "Utilities.h"
#include "FaceDetect.h"
#include "HeadPose.h"
#include "FaceDataSet.h"
#include "FaceTrackDB.h"

namespace vnt
{
	/********** class Matching **********/
	class Matching
	{
	public:
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
		void aDatabaseInit_HeadPose_PoseNormalize(int pNumVector);
		//\\ Khoi tao csdl: HeadPose (csdl khong chia) + InDiv (query trong csdl co chia) + Pose (co Pose) + NotNormalize (csdl khong chuan hoa).
		void aDatabaseInit_HeadPose_PoseNotNormalize(int pNumVector);

		//\\ Khoi tao csdl.
		void aDatabaseInit();

		//\\ Khoi tao csdl: tao dataset -> tao facetrack -> tao database.
		void aDatabaseInitFull(std::string pSourcePath);


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

		double aMatchingHeadPoseMAP2(std::string pDatabasePath, std::string pDatabaseFeaturePath, int pCountMax);
		//\\ Tron serie1 va serie2 cua HeadPose de lam csdl va tinh MAP.
		void aMatchingHeadPoseMAP();
	};
}