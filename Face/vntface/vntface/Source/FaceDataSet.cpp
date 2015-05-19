/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "../Header/FaceDataSet.h"
#include "../Header/Utilities.h"

using namespace vnt;

/********** Constructor **********/
FaceDataSet::FaceDataSet(){}
FaceDataSet::~FaceDataSet(){}

/********** public Methods **********/
//\\ Lay nguon anh.
FaceDataSetBase* FaceDataSet::aGetDataSetBase()
{
	return mDataSetBase;
}
//\\ Gan nguon anh.
void FaceDataSet::aSetDataSetBase(FaceDataSetBase* pDataSetBase)
{
	mDataSetBase = pDataSetBase;
}
//\\ Lay danh sach facetrack.
std::vector<std::vector<cv::Mat>> FaceDataSet::aGetFaceTraks()
{
	return mFaceTracks;
}
//\\ Gan danh sach facetrack.
void FaceDataSet::aSetFaceTracks(std::vector<std::vector<cv::Mat>> pFaceTracks)
{
	mFaceTracks = pFaceTracks;
}
//\\ Lay danh sach Pose.
std::vector<std::vector<int>> FaceDataSet::aGetPoses()
{
	return mPoses;
}
//\\ Gan danh sach Pose.
void FaceDataSet::aSetPoses(std::vector<std::vector<int>> pPoses)
{
	mPoses = pPoses;
}
//\\ Lay tong pose.
int FaceDataSet::aGetSumPose()
{
	return mSumPose;
}
//\\ Gan tong pose.
void FaceDataSet::aSetSumPose(int pSumPose)
{
	mSumPose = pSumPose;
}


//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack.
std::vector<cv::Mat> FaceDataSet::aReadsImage(std::vector<std::string> pAllFileName, const std::string pDataSourcePath)
{
	std::vector<cv::Mat> result;
	size_t vAllFileNameSize = pAllFileName.size();
	for (size_t i = 0; i < vAllFileNameSize; i++)
	{
		cv::Mat face = cv::imread(pDataSourcePath + pAllFileName[i], CV_8UC1);
		if (!face.empty())
			result.push_back(face);
	}
	return result;
}
//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack. Co luu ra file.
std::vector<cv::Mat> FaceDataSet::aReadsImage(std::vector<std::string> pAllFileName, std::vector<int> pPoses, const std::string pDataSourcePath, std::string pFolderPath)
{
	std::vector<cv::Mat> result;
	Utilites util;
	size_t vAllFileNameSize = pAllFileName.size();
	int numFilesLength = std::to_string(vAllFileNameSize).length();
	int sumPose = 0;
	for (size_t i = 0; i < vAllFileNameSize; i++)
	{
		cv::Mat face = cv::imread(pDataSourcePath + pAllFileName[i], CV_8UC1);
		if (!face.empty())
		{
			result.push_back(face);
			//\\ Ten file co dang: "Feature01.txt", ...
			//\\fName = util.leftPad(fName, numFilesLength, '0');
			std::string fName = std::to_string(i);
			//\\ Ghi anh Mat.
			util.writeMatBasic(face, pFolderPath + mImageName + fName + mImageType);
			//\\ Ghi anh goc.
			std::string vImageTypeRoot = "." + util.subStringAfter(pAllFileName[i], ".");
			cv::imwrite(pFolderPath + mImageName + fName + vImageTypeRoot, face);
			//\\ Ghi gia tri pose co kieu Mat ra file.
			cv::Mat matPose = cv::Mat(1, 1, CV_32SC1, pPoses[i]);
			util.writeMatBasic(matPose, pFolderPath + mPoseName + fName + mImageType);
			//\\ Cong them gia tri pose tuong ung vao ten file.
			sumPose += pPoses[i];
		}
	}
	//\\ Luu tong pose cua tat ca cac anh trong facetrack. sumPose = 3350;
	cv::Mat matSumPose = cv::Mat(1, 1, CV_32SC1, sumPose);
	//\\ Ghi gia tri sumpose ra file.
	util.writeMatBasic(matSumPose, pFolderPath + mSumPoseName + mImageType);

	return result;
}
//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack. Co luu ra file.
std::vector<cv::Mat> FaceDataSet::aReadsImageNotPose(std::vector<std::string> pAllFileName, const std::string pDataSourcePath, std::string pFolderPath)
{
	std::vector<cv::Mat> result;
	Utilites util;
	size_t vAllFileNameSize = pAllFileName.size();
	int numFilesLength = std::to_string(vAllFileNameSize).length();
	for (size_t i = 0; i < vAllFileNameSize; i++)
	{
		cv::Mat face = cv::imread(pDataSourcePath + pAllFileName[i], CV_8UC1);
		if (!face.empty())
		{
			result.push_back(face);
			//\\ Ten file co dang: "Feature01.txt", ...
			//\\std::string fNum = util.leftPad(std::to_string(i), numFilesLength, '0');
			std::string fNum = std::to_string(i);
			//\\ Ghi anh Mat.
			util.writeMatBasic(face, pFolderPath + mImageName + fNum + mImageType);
			//\\ Ghi anh goc.
			cv::imwrite(pFolderPath + mImageName + fNum + ".jpg", face);
		}
	}
	return result;
}

//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
int FaceDataSet::aDataSetInit(FaceDataSetBase* pFaceDataSetBase, std::string pDataSourcePath)
{
	int result = -1;
	mDataSetBase = pFaceDataSetBase;
	Utilites util;
	//\\ * Load tat ca anh vao FaceDataSet.
	//\\ Lay tat ca Ids co trong nguon anh.
	std::vector<std::string> vAllIds = mDataSetBase->aGetsAllIds();
	size_t vAllIdsSize = vAllIds.size();
	for (size_t i = 0; i < vAllIdsSize; i++)
	{
		std::string vId = vAllIds[i];
		//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
		std::vector<std::string> vAllFileName = mDataSetBase->aGetsAllFileName(vId);
		std::vector<cv::Mat> vFaceTrack = aReadsImage(vAllFileName, pDataSourcePath + mDataSetBase->aGetPath(vId));
		mFaceTracks.push_back(vFaceTrack);
	}// for i.
	result = mFaceTracks.size();
	return result;
}
//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceDataSet::aDataSetInit(FaceDataSetBase* pFaceDataSetBase, std::string pDataSourcePath, std::string pFolderPath)
{
	int result = -1;
	mDataSetBase = pFaceDataSetBase;
	mFolderPath = pFolderPath;
	Utilites util;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(vFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mDataSetFolder);
	//\\ Lay tat ca Ids co trong nguon anh.
	std::vector<std::string> vAllIds = mDataSetBase->aGetsAllIds();
	size_t vAllIdsSize = vAllIds.size();
	int numlengthFaceTrack = std::to_string(vAllIdsSize).length();
	for (size_t i = 0; i < vAllIdsSize; i++)
	{
		std::string vId = vAllIds[i];
		//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
		std::vector<std::string> vAllFileName = mDataSetBase->aGetsAllFileName(vId);
		//\\ Lay tat ca pose tuong ung voi ten file.
		std::vector<int> vAllPose = mDataSetBase->aGetsAllPose(vId);
		//\\std::string fNum = util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string fNum = std::to_string(i);
		//\\ Tao thu muc cho facetrack thu i.
		std::string vFaceTrackPath = mFolderPath + mDataSetFolder + "/" + mFaceTrackName + fNum;
		util.makeDir(util.replaceAll(vFaceTrackPath, "/", "\\"));
		vFaceTrackPath += "/";
		//\\ Doc anh va ghi ra file.
		std::vector<cv::Mat> vFaceTrack = aReadsImage(vAllFileName, vAllPose, pDataSourcePath + mDataSetBase->aGetPath(vId), vFaceTrackPath);
		mFaceTracks.push_back(vFaceTrack);
	}// for i.
	result = mFaceTracks.size();
	return result;
}
//\\ Chia moi FaceTrack trong DataSet thanh n FaceTrack. Co ghi csdl ra file. Kiem tra file anh co ton tai khong?
int FaceDataSet::aDataSetInitDiv(FaceDataSetBase* pFaceDataSetBase, const std::string pDataSourcePath, const std::string pFolderPath, const int pNum, const bool pCheckFile)
{
	int result = -1;
	mDataSetBase = pFaceDataSetBase;
	mFolderPath = pFolderPath;
	Utilites util;
	//\\ Lay tat ca Ids co trong nguon anh.
	std::vector<std::string> vAllIds = pFaceDataSetBase->aGetsAllIds();
	size_t vAllIdsSize = vAllIds.size();
	int numlengthFaceTrack = std::to_string(vAllIdsSize * pNum).length();
	int vFaceTrackIndex = 0;
	int sumAllPose = 0;
	for (size_t i = 0; i < vAllIdsSize; i++)
	{
		std::string vId = vAllIds[i];
		std::string vSourcePath = pDataSourcePath + mDataSetBase->aGetPath(vId);
		//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
		std::vector<std::string> vAllFileName = pFaceDataSetBase->aGetsAllFileName(vId);
		//\\ Lay tat ca pose tuong ung voi ten file.
		std::vector<int> vAllPose = mDataSetBase->aGetsAllPose(vId);
		if (pCheckFile)
		{
			std::vector<std::string> vAllFileName1;
			std::vector<int> vAllPose1;
			for (size_t j = 0; j < vAllFileName.size(); j++)
			{
				cv::Mat face = cv::imread(vSourcePath + vAllFileName[j], CV_8UC1);
				if (!face.empty())
				{
					vAllFileName1.push_back(vAllFileName[j]);
					vAllPose1.push_back(vAllPose[j]);
				}
			}
			vAllFileName.clear();
			vAllFileName = vAllFileName1;
			vAllPose.clear();
			vAllPose = vAllPose1;
		}
		size_t vAllFileNameSize = vAllFileName.size() / pNum;
		int numFilesLength = std::to_string(vAllFileNameSize).length();
		//\\ Chia lam n thu muc facetrack con.
		for (size_t j = 0; j < pNum; j++)
		{
			//\\std::string vNumber = util.leftPad(std::to_string(vFaceTrackIndex), numlengthFaceTrack, '0');
			std::string vNumber = std::to_string(vFaceTrackIndex);
			//\\ Tao thu muc cho facetrack thu j.
			std::string vFaceTrackPath = mFolderPath + mDataSetFolder + "/" + mFaceTrackName + vNumber;
			util.makeDir(util.replaceAll(vFaceTrackPath, "/", "\\"));
			vFaceTrackPath += "/";
			vFaceTrackIndex++;
			//\\ Luu ten file cua cac anh trong facetrack con.
			std::vector<std::string> vAllFileNameDiv;
			std::vector<int> vAllPoseDiv;
			for (size_t k = 0; k < vAllFileNameSize; k++)
			{
				vAllFileNameDiv.push_back(vAllFileName[j * vAllFileNameSize + k]);
				vAllPoseDiv.push_back(vAllPose[j * vAllFileNameSize + k]);
				sumAllPose += vAllPose[j * vAllFileNameSize + k];
			}
			//\\ Doc anh va ghi ra file.
			std::vector<cv::Mat> vFaceTrack = aReadsImage(vAllFileNameDiv, vAllPoseDiv, vSourcePath, vFaceTrackPath);
			mFaceTracks.push_back(vFaceTrack);
		}
	}// for i.
	sumAllPose /= vAllIdsSize;
	//\\ Luu tong pose cua tat ca cac anh trong facetrack. sumPose = 11280.
	cv::Mat matSumPose = cv::Mat(1, 1, CV_32SC1, sumAllPose);
	//\\ Ghi gia tri sumpose ra file.
	util.writeMatBasic(matSumPose, mFolderPath + mDataSetFolder + "/" + mSumPoseName + mImageType);
	result = vAllIdsSize;
	return result;
}

//\\ Doc cac anh tu file.
int FaceDataSet::aDataSetRead(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	mFaceTracks.clear();
	Utilites util;
	mFolderPath = pFolderPath;
	int facetrackLength = pNumFaceTrackEnd.length();
	int featueLength = pNumFeatureEnd.length();
	//\\ Doc tung facetrack.
	size_t vNumFaceTrackStart = std::atoi(pNumFaceTrackStart.c_str());
	size_t vNumFaceTrackEnd = std::atoi(pNumFaceTrackEnd.c_str());
	for (size_t i = vNumFaceTrackStart; i <= vNumFaceTrackEnd; i++)
	{
		//\\ Doc tung vector dac trung (trung binh) cua facetrack.
		//std::string vFaceTrackPath = mFolderPath + mFaceTracksFolder + "/";
		//\\std::string vFaceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), facetrackLength, '0');
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::vector<cv::Mat> facetrack;
		std::vector<int> poses;
		size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = vNumFeatureStart; j <= vNumFeatureEnd; j++)
		{
			//\\std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string vNumber = util.leftPad(std::to_string(j), featueLength, '0');
			std::string vNumber = std::to_string(j);
			cv::Mat vImageMat = util.readMatBasic(mFolderPath + mDataSetFolder + "/" + vFaceTrackName + "/" + mImageName + vNumber + mImageType);
			if (!vImageMat.empty())
			{
				facetrack.push_back(vImageMat);
				//\\ Doc file pose ung voi tung anh trong facetrack.
				cv::Mat vPoseMat = util.readMatBasic(mFolderPath + mDataSetFolder + "/" + vFaceTrackName + "/" + mPoseName + vNumber + mImageType);
				int pose = vPoseMat.at<int>(0, 0);
				poses.push_back(pose);
			}
		}
		mFaceTracks.push_back(facetrack);
		facetrack.clear();
		mPoses.push_back(poses);
		poses.clear();
	}
	//\\ Doc file sumpose.
	cv::Mat vSumPoseMat = util.readMatBasic(mFolderPath + mDataSetFolder + "/" + mSumPoseName + mImageType);
	mSumPose = vSumPoseMat.at<int>(0, 0);
	result = mFaceTracks.size();
	return result;
}
//\\ Doc cac anh tu file.
int FaceDataSet::aDataSetReadNotPose(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	mFaceTracks.clear();
	Utilites util;
	mFolderPath = pFolderPath;
	int facetrackLength = pNumFaceTrackEnd.length();
	int featueLength = pNumFeatureEnd.length();
	//\\ Doc tung facetrack.
	size_t vNumFaceTrackStart = std::atoi(pNumFaceTrackStart.c_str());
	size_t vNumFaceTrackEnd = std::atoi(pNumFaceTrackEnd.c_str());
	for (size_t i = vNumFaceTrackStart; i <= vNumFaceTrackEnd; i++)
	{
		//\\ Doc tung vector dac trung (trung binh) cua facetrack.
		//std::string vFaceTrackPath = mFolderPath + mFaceTracksFolder + "/";
		//\\std::string vFaceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), facetrackLength, '0');
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::vector<cv::Mat> facetrack;
		size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = vNumFeatureStart; j <= vNumFeatureEnd; j++)
		{
			//std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string vNumber = util.leftPad(std::to_string(j), featueLength, '0');
			std::string vNumber = std::to_string(j);
			cv::Mat vImageMat = util.readMatBasic(mFolderPath + mDataSetFolder + "/" + vFaceTrackName + "/" + mImageName + vNumber + mImageType);
			facetrack.push_back(vImageMat);
		}
		mFaceTracks.push_back(facetrack);
		facetrack.clear();
	}
	result = mFaceTracks.size();
	return result;
}
//\\ Doc cac anh tu file.
int FaceDataSet::aDataSetRead(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	mFaceTracks.clear();
	Utilites util;
	mFolderPath = pFolderPath;
	//int facetrackLength = pNumFaceTrackEnd.length();
	//int featueLength = pNumFeatureEnd.length();
	//\\ Doc tung facetrack.
	//size_t vNumFaceTrackStart = std::atoi(pNumFaceTrackStart.c_str());
	//size_t vNumFaceTrackEnd = std::atoi(pNumFaceTrackEnd.c_str());
	for (size_t i = pNumFaceTrackStart; i <= pNumFaceTrackEnd; i++)
	{
		//\\ Doc tung vector dac trung (trung binh) cua facetrack.
		//std::string vFaceTrackPath = mFolderPath + mFaceTracksFolder + "/";
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::vector<cv::Mat> facetrack;
		std::vector<int> poses;
		//size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		//size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = pNumFeatureStart; j <= pNumFeatureEnd; j++)
		{
			//\\std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string vNumber = util.leftPad(std::to_string(j), featueLength, '0');
			std::string vNumber = std::to_string(j);
			cv::Mat vImageMat = util.readMatBasic(mFolderPath + mDataSetFolder + "/" + vFaceTrackName + "/" + mImageName + vNumber + mImageType);
			if (!vImageMat.empty())
			{
				facetrack.push_back(vImageMat);
				//\\ Doc file pose ung voi tung anh trong facetrack.
				cv::Mat vPoseMat = util.readMatBasic(mFolderPath + mDataSetFolder + "/" + vFaceTrackName + "/" + mPoseName + vNumber + mImageType);
				int pose = vPoseMat.at<int>(0, 0);
				poses.push_back(pose);
			}
		}
		mFaceTracks.push_back(facetrack);
		facetrack.clear();
		mPoses.push_back(poses);
		poses.clear();
	}
	//\\ Doc file sumpose.
	cv::Mat vSumPoseMat = util.readMatBasic(mFolderPath + mDataSetFolder + "/" + mSumPoseName + mImageType);
	mSumPose = vSumPoseMat.at<int>(0, 0);
	result = mFaceTracks.size();
	return result;
}
//\\ Doc cac anh tu file.
int FaceDataSet::aDataSetReadNotPose(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	mFaceTracks.clear();
	Utilites util;
	mFolderPath = pFolderPath;
	//int facetrackLength = pNumFaceTrackEnd.length();
	//int featueLength = pNumFeatureEnd.length();
	//\\ Doc tung facetrack.
	//size_t vNumFaceTrackStart = std::atoi(pNumFaceTrackStart.c_str());
	//size_t vNumFaceTrackEnd = std::atoi(pNumFaceTrackEnd.c_str());
	for (size_t i = pNumFaceTrackStart; i <= pNumFaceTrackEnd; i++)
	{
		//\\ Doc tung vector dac trung (trung binh) cua facetrack.
		//std::string vFaceTrackPath = mFolderPath + mFaceTracksFolder + "/";
		//std::string vFaceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), facetrackLength, '0');
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::vector<cv::Mat> facetrack;
		//size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		//size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = pNumFeatureStart; j <= pNumFeatureEnd; j++)
		{
			//std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string vNumber = util.leftPad(std::to_string(j), featueLength, '0');
			std::string vNumber = std::to_string(j);
			cv::Mat vImageMat = util.readMatBasic(mFolderPath + mDataSetFolder + "/" + vFaceTrackName + "/" + mImageName + vNumber + mImageType);
			facetrack.push_back(vImageMat);
		}
		mFaceTracks.push_back(facetrack);
		facetrack.clear();
	}
	result = mFaceTracks.size();
	return result;
}


