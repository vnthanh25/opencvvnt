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
//\\ Lay danh sach ten file.
std::vector<std::vector<std::string>> FaceDataSet::aGetFileNames()
{
	return mFileNames;
}
//\\ Gan danh sach ten file.
void FaceDataSet::aSetFileNames(std::vector<std::vector<std::string>> pFileNames)
{
	mFileNames = pFileNames;
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
//\\ Lay danh sach TiltPanPose.
std::vector<std::vector<std::string>> FaceDataSet::aGetTiltPanPoses()
{
	return mTiltPanPoses;
}
//\\ Gan danh sach TiltPanPose.
void FaceDataSet::aSetPoses(std::vector<std::vector<std::string>> pTiltPanPoses)
{
	mTiltPanPoses = pTiltPanPoses;
}
//\\ Lay danh sach pose name.
std::vector<std::vector<std::string>> FaceDataSet::aGetPoseNames()
{
	return mPoseNames;
}
//\\ Gan danh sach pose name.
void FaceDataSet::aSetPoseNames(std::vector<std::vector<std::string>> pPoseNames)
{
	mPoseNames = pPoseNames;
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
//\\ Doc tat ca cac anh trong mot thu muc. Giu lai danh sach dac trung va pose tuong ung. Tuy co luu ra file.
void FaceDataSet::aReadsImage1(std::vector<std::string> pAllFileName, std::vector<int> pPoses, const std::string pDataSourcePath, std::string pSavePath, bool pIsSaveToFile)
{
	std::vector<std::string> vFileNames;
	std::vector<cv::Mat> vFaceTrack;
	std::vector<int> vPoses;
	Utilites util;
	size_t vAllFileNameSize = pAllFileName.size();
	int numFilesLength = std::to_string(vAllFileNameSize).length();
	int sumPose = 0;
	for (size_t i = 0; i < vAllFileNameSize; i++)
	{
		cv::Mat face = cv::imread(pDataSourcePath + pAllFileName[i], CV_8UC1);
		if (!face.empty())
		{
			vFileNames.push_back(pAllFileName[i]);
			vFaceTrack.push_back(face);
			vPoses.push_back(pPoses[i]);

			////\\ Ten file co dang: "Feature01.txt", ...
			////\\fNum = util.leftPad(fName, numFilesLength, '0');
			//std::string fNum = std::to_string(i);
			////\\ Ghi anh Mat.
			//util.writeMatBasic(face, pFolderPath + mImageName + fNum + mImageType);
			////\\ Ghi anh goc.
			//std::string vImageTypeRoot = "." + util.subStringAfter(pAllFileName[i], ".");
			//cv::imwrite(pFolderPath + mImageName + fNum + vImageTypeRoot, face);
			////\\ Ghi gia tri pose co kieu Mat ra file.
			//cv::Mat matPose = cv::Mat(1, 1, CV_32SC1, pPoses[i]);
			//util.writeMatBasic(matPose, pFolderPath + mPoseName + fNum + mImageType);

			//\\ Ghi file.
			if (pIsSaveToFile)
			{
				aSaveToFile(face, pAllFileName[i], pSavePath);
				//\\ Ghi anh goc
				util.FileCopy(pDataSourcePath + pAllFileName[i], pSavePath + pAllFileName[i]);
			}
			//\\ Cong them gia tri pose tuong ung vao ten file.
			sumPose += pPoses[i];
		}
	}
	//\\ Ghi gia tri sumpose va thong tin ve anh ra file.
	if (pIsSaveToFile)
	{
		//\\ Ghi thong tin ve ten file anh va pose.
		aSaveToFile1(vFileNames, vPoses, pSavePath);
	}
	//\\ Giu lai danh sach dac trung va pose tuong ung.
	mFileNames.push_back(vFileNames);
	mFaceTracks.push_back(vFaceTrack);
	mPoses.push_back(vPoses);
}
//\\ (Use) Doc tat ca cac anh trong mot thu muc. Giu lai danh sach dac trung va pose tuong ung. Tuy co luu ra file.
void FaceDataSet::aReadsImage2(std::vector<std::string> pAllFileName, std::vector<int> pPoses, std::vector<std::string> pPoseNames, const std::string pDataSourcePath, std::string pSavePath, bool pIsSaveToFile)
{
	std::vector<std::string> vFileNames;
	std::vector<cv::Mat> vFaceTrack;
	std::vector<int> vPoses;
	std::vector<std::string> vPoseNames;
	Utilites util;
	size_t vAllFileNameSize = pAllFileName.size();
	int numFilesLength = std::to_string(vAllFileNameSize).length();
	int sumPose = 0;
	for (size_t i = 0; i < vAllFileNameSize; i++)
	{
		cv::Mat face = cv::imread(pDataSourcePath + pAllFileName[i], CV_8UC1);
		if (!face.empty())
		{
			vFileNames.push_back(pAllFileName[i]);
			vFaceTrack.push_back(face);
			vPoses.push_back(pPoses[i]);
			vPoseNames.push_back(pPoseNames[i]);

			//\\ Ghi file.
			if (pIsSaveToFile)
			{
				aSaveToFile(face, pAllFileName[i], pSavePath);
				//\\ Ghi anh goc
				util.FileCopy(pDataSourcePath + pAllFileName[i], pSavePath + pAllFileName[i]);
			}
			//\\ Cong them gia tri pose tuong ung vao ten file.
			sumPose += pPoses[i];
		}
	}
	//\\ Ghi gia tri sumpose va thong tin ve anh ra file.
	if (pIsSaveToFile)
	{
		//\\ Ghi thong tin ve ten file anh va pose.
		aSaveToFile2(vFileNames, vPoses, vPoseNames, pSavePath);
	}
	//\\ Giu lai danh sach dac trung va pose tuong ung.
	mFileNames.push_back(vFileNames);
	mFaceTracks.push_back(vFaceTrack);
	mPoses.push_back(vPoses);
	mPoseNames.push_back(vPoseNames);
}
//\\ (Use) Doc tat ca cac anh trong mot thu muc. Giu lai danh sach dac trung va pose tuong ung. Tuy co luu ra file.
void FaceDataSet::aReadsImage3(std::vector<std::string> pAllFileName, std::vector<std::string> pPoses, std::vector<std::string> pPoseNames, const std::string pDataSourcePath, std::string pSavePath, bool pIsSaveToFile)
{
	std::vector<std::string> vFileNames;
	std::vector<cv::Mat> vFaceTrack;
	std::vector<std::string> vPoses;
	std::vector<std::string> vPoseNames;
	Utilites util;
	size_t vAllFileNameSize = pAllFileName.size();
	int numFilesLength = std::to_string(vAllFileNameSize).length();
	int sumPose = 0;
	for (size_t i = 0; i < vAllFileNameSize; i++)
	{
		cv::Mat face = cv::imread(pDataSourcePath + pAllFileName[i], CV_8UC1);
		if (!face.empty())
		{
			vFileNames.push_back(pAllFileName[i]);
			vFaceTrack.push_back(face);
			vPoses.push_back(pPoses[i]);
			vPoseNames.push_back(pPoseNames[i]);

			//\\ Ghi file.
			if (pIsSaveToFile)
			{
				aSaveToFile(face, pAllFileName[i], pSavePath);
				//\\ Ghi anh goc
				util.FileCopy(pDataSourcePath + pAllFileName[i], pSavePath + pAllFileName[i]);
			}
		}
	}
	//\\ Ghi thong tin ve anh ra file.
	if (pIsSaveToFile)
	{
		//\\ Ghi thong tin ve ten file anh va pose.
		aSaveToFile3(vFileNames, vPoses, vPoseNames, true, pSavePath);
	}
	//\\ Giu lai danh sach dac trung va pose tuong ung.
	mFileNames.push_back(vFileNames);
	mFaceTracks.push_back(vFaceTrack);
	mTiltPanPoses.push_back(vPoses);
	mPoseNames.push_back(vPoseNames);
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

//\\ (Use) Khoi tao DataSet (chuyen doi anh thanh doi tuong Mat).
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
//\\ Khoi tao DataSet (chuyen doi anh thanh doi tuong Mat). Co ghi csdl ra file.
int FaceDataSet::aDataSetInit(FaceDataSetBase* pFaceDataSetBase, std::string pDataSourcePath, std::string pSavePath, const bool pCheckFile)
{
	int result = -1;
	//mFaceTracks.clear();
	mDataSetBase = pFaceDataSetBase;
	mFolderPath = pSavePath;
	Utilites util;
	std::string vFolderPath = pSavePath;
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
		std::string vSourcePath = pDataSourcePath + mDataSetBase->aGetPath(vId);
		//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
		std::vector<std::string> vAllFileName = mDataSetBase->aGetsAllFileName(vId);
		//\\ Lay tat ca pose tuong ung voi ten file.
		std::vector<int> vAllPose = mDataSetBase->aGetsAllPose1(vId);
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
		//\\std::string fNum = util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string fNum = std::to_string(i);
		//\\ Tao thu muc cho facetrack thu i.
		std::string vFaceTrackPath = mFolderPath + mDataSetFolder + "/" + mFaceTrackName + fNum;
		util.makeDir(util.replaceAll(vFaceTrackPath, "/", "\\"));
		vFaceTrackPath += "/";
		//\\ Doc anh va ghi ra file.
		aReadsImage1(vAllFileName, vAllPose, vSourcePath, vFaceTrackPath);
	}// for i.
	result = mFaceTracks.size();
	return result;
}
//\\ (Use) Chia moi FaceTrack trong DataSet thanh n FaceTrack. Co ghi csdl ra file. Kiem tra file anh co ton tai khong?
int FaceDataSet::aDataSetInitDiv1(FaceDataSetBase* pFaceDataSetBase, const std::string pDataSourcePath, const std::string pSavePath, const int pNum, const bool pCheckFile)
{
	int result = -1;
	//mFaceTracks.clear();
	mDataSetBase = pFaceDataSetBase;
	mFolderPath = pSavePath;
	Utilites util;
	//\\ Lay tat ca Ids co trong nguon anh.
	std::vector<std::string> vAllIds = mDataSetBase->aGetsAllIds();
	size_t vAllIdsSize = vAllIds.size();
	int numlengthFaceTrack = std::to_string(vAllIdsSize * pNum).length();
	int vFaceTrackIndex = 0;
	for (size_t i = 0; i < vAllIdsSize; i++)
	{
		std::string vId = vAllIds[i];
		std::string vSourcePath = pDataSourcePath + mDataSetBase->aGetPath(vId);
		//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
		std::vector<std::string> vAllFileName = mDataSetBase->aGetsAllFileName(vId);
		//\\ Lay tat ca pose tuong ung voi ten file.
		std::vector<int> vAllPose = mDataSetBase->aGetsAllPose1(vId);
		//\\ Lay tat ca pose name tuong ung voi ten file.
		std::vector<std::string> vAllPoseName = mDataSetBase->aGetsAllPoseName(vId);
		if (pCheckFile)
		{
			std::vector<std::string> vAllFileName1;
			std::vector<int> vAllPose1;
			std::vector<std::string> vAllPoseName1;
			for (size_t j = 0; j < vAllFileName.size(); j++)
			{
				cv::Mat face = cv::imread(vSourcePath + vAllFileName[j], CV_8UC1);
				if (!face.empty())
				{
					vAllFileName1.push_back(vAllFileName[j]);
					vAllPose1.push_back(vAllPose[j]);
					vAllPoseName1.push_back(vAllPoseName[j]);
				}
			}
			vAllFileName.clear();
			vAllPose.clear();
			vAllPoseName.clear();
			vAllFileName = vAllFileName1;
			vAllPose = vAllPose1;
			vAllPoseName = vAllPoseName1;
		}
		size_t vAllFileNameSize = vAllFileName.size() / pNum;
		if (vAllFileNameSize == 0)
			continue;
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
			std::vector<std::string> vAllPoseNameDiv;
			for (size_t k = 0; k < vAllFileNameSize; k++)
			{
				vAllFileNameDiv.push_back(vAllFileName[j * vAllFileNameSize + k]);
				vAllPoseDiv.push_back(vAllPose[j * vAllFileNameSize + k]);
				vAllPoseNameDiv.push_back(vAllPoseName[j * vAllFileNameSize + k]);
				//sumAllPose += vAllPose[j * vAllFileNameSize + k];
			}
			//\\ Doc anh va ghi ra file.
			aReadsImage2(vAllFileNameDiv, vAllPoseDiv, vAllPoseNameDiv, vSourcePath, vFaceTrackPath);
		}
	}// for i.
	result = vAllIdsSize;
	return result;
}
//\\ (Use) Chia moi FaceTrack trong DataSet thanh n FaceTrack. Co ghi csdl ra file. Kiem tra file anh co ton tai khong?
int FaceDataSet::aDataSetInitDiv2(FaceDataSetBase* pFaceDataSetBase, const std::string pDataSourcePath, const std::string pSavePath, const int pNum, const int pStart, const bool pCheckFile)
{
	int result = -1;
	//mFaceTracks.clear();
	mDataSetBase = pFaceDataSetBase;
	mFolderPath = pSavePath;
	Utilites util;
	//\\ Lay tat ca Ids co trong nguon anh.
	std::vector<std::string> vAllIds = mDataSetBase->aGetsAllIds();
	size_t vAllIdsSize = vAllIds.size();
	int numlengthFaceTrack = std::to_string(vAllIdsSize * pNum).length();
	int vFaceTrackIndex = 0;
	for (size_t i = 0; i < vAllIdsSize; i++)
	{
		std::string vId = vAllIds[i];
		std::string vSourcePath = pDataSourcePath + mDataSetBase->aGetPath(vId);
		//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
		std::vector<std::string> vAllFileName = mDataSetBase->aGetsAllFileName(vId);
		//\\ Lay tat ca pose tuong ung voi ten file.
		std::vector<std::string> vAllPose = mDataSetBase->aGetsAllPose2(vId);
		//\\ Lay tat ca pose name tuong ung voi ten file.
		std::vector<std::string> vAllPoseName = mDataSetBase->aGetsAllPoseName(vId);
		if (pCheckFile)
		{
			std::vector<std::string> vAllFileName1;
			std::vector<std::string> vAllPose1;
			std::vector<std::string> vAllPoseName1;
			for (size_t j = 0; j < vAllFileName.size(); j++)
			{
				cv::Mat face = cv::imread(vSourcePath + vAllFileName[j], CV_8UC1);
				if (!face.empty())
				{
					vAllFileName1.push_back(vAllFileName[j]);
					vAllPose1.push_back(vAllPose[j]);
					vAllPoseName1.push_back(vAllPoseName[j]);
				}
			}
			vAllFileName.clear();
			vAllPose.clear();
			vAllPoseName.clear();
			vAllFileName = vAllFileName1;
			vAllPose = vAllPose1;
			vAllPoseName = vAllPoseName1;
		}
		size_t vAllFileNameSize = vAllFileName.size() / pNum;
		int numFilesLength = std::to_string(vAllFileNameSize).length();
		//\\ Chia lam n thu muc facetrack con.
		for (size_t j = 0; j < pNum; j++)
		{
			//\\std::string vNumber = util.leftPad(std::to_string(vFaceTrackIndex), numlengthFaceTrack, '0');
			std::string vNumber = std::to_string(vFaceTrackIndex + pStart);
			//\\ Tao thu muc cho facetrack thu j.
			std::string vFaceTrackPath = mFolderPath + mDataSetFolder + "/" + mFaceTrackName + vNumber;
			util.makeDir(util.replaceAll(vFaceTrackPath, "/", "\\"));
			vFaceTrackPath += "/";
			vFaceTrackIndex++;
			//\\ Luu ten file cua cac anh trong facetrack con.
			std::vector<std::string> vAllFileNameDiv;
			std::vector<std::string> vAllPoseDiv;
			std::vector<std::string> vAllPoseNameDiv;
			for (size_t k = 0; k < vAllFileNameSize; k++)
			{
				vAllFileNameDiv.push_back(vAllFileName[j * vAllFileNameSize + k]);
				vAllPoseDiv.push_back(vAllPose[j * vAllFileNameSize + k]);
				vAllPoseNameDiv.push_back(vAllPoseName[j * vAllFileNameSize + k]);
				//sumAllPose += vAllPose[j * vAllFileNameSize + k];
			}

			//\\ Doc anh va ghi ra file.
			aReadsImage3(vAllFileNameDiv, vAllPoseDiv, vAllPoseNameDiv, vSourcePath, vFaceTrackPath);

		}
	}// for i.
	result = vAllIdsSize;
	return result;
}

//\\ Doc cac anh tu file.
int FaceDataSet::aDataSetRead1(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFaceTracks.clear();
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
	result = mFaceTracks.size();
	return result;
}
//\\ Doc cac anh tu file.
int FaceDataSet::aDataSetReadNotPose1(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFaceTracks.clear();
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
int FaceDataSet::aDataSetRead2(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFaceTracks.clear();
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
	result = mFaceTracks.size();
	return result;
}
//\\ Doc cac anh tu file.
int FaceDataSet::aDataSetReadNotPose2(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFaceTracks.clear();
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
//\\ (Use) Doc cac anh  va thong tin tu file.
int FaceDataSet::aDataSetRead3(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath, bool pIsPose)
{
	int result = 0;
	//mFileNames.clear();
	//mFaceTracks.clear();
	//mPoses.clear();
	Utilites util;
	mFolderPath = pSourcePath;
	//\\ Doc tung facetrack.
	for (size_t i = pNumFaceTrackStart; i <= pNumFaceTrackEnd; i++)
	{
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::string vFaceTrackPath = mFolderPath + mDataSetFolder + "/" + vFaceTrackName + "/";
		std::vector<std::string> vFileNames;
		std::vector<cv::Mat> vImageMats;
		std::vector<int> vPoses;
		std::vector<std::string> vPoseNames;
		//\\ Doc ten file anh va pose tuong ung.
		std::ifstream ifImage(vFaceTrackPath + mImageName + mFileType);
		std::ifstream ifPose(vFaceTrackPath + mPoseName + mFileType);
		std::ifstream ifPoseName(vFaceTrackPath + mPoseNameName + mFileType);
		std::string vFileName;
		std::string vPose;
		std::string vPoseName;
		cv::Mat vImageMat;
		while (!ifImage.eof())
		{
			std::getline(ifImage, vFileName);
			std::getline(ifPose, vPose);
			std::getline(ifPoseName, vPoseName);
			vImageMat = util.readMatBasic(vFaceTrackPath + vFileName + mImageType);
			vFileNames.push_back(vFileName);
			vPoses.push_back(std::atoi(vPose.c_str()));
			vPoseNames.push_back(vPoseName);
			vImageMats.push_back(vImageMat);
		}
		ifImage.close();
		ifPose.close();
		ifPoseName.close();

		mFileNames.push_back(vFileNames);
		mFaceTracks.push_back(vImageMats);
		mPoses.push_back(vPoses);
		mPoseNames.push_back(vPoseNames);
	}
	result = mFaceTracks.size();
	return result;
}
//\\ (Use) Doc cac anh  va thong tin tu file.
int FaceDataSet::aDataSetRead4(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath, bool pIsPose)
{
	int result = 0;
	//mFileNames.clear();
	//mFaceTracks.clear();
	//mTiltPanPoses.clear();
	Utilites util;
	mFolderPath = pSourcePath;
	//\\ Doc tung facetrack.
	for (size_t i = pNumFaceTrackStart; i <= pNumFaceTrackEnd; i++)
	{
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::string vFaceTrackPath = mFolderPath + mDataSetFolder + "/" + vFaceTrackName + "/";
		std::vector<std::string> vFileNames;
		std::vector<cv::Mat> vImageMats;
		std::vector<std::string> vTiltPanPoses;
		std::vector<std::string> vPoseNames;
		//\\ Doc ten file anh va pose tuong ung.
		std::ifstream ifImage(vFaceTrackPath + mImageName + mFileType);
		std::ifstream ifPose(vFaceTrackPath + mTiltPanPoseName + mFileType);
		std::ifstream ifPoseName(vFaceTrackPath + mPoseNameName + mFileType);
		std::string vFileName;
		std::string vPose;
		std::string vPoseName;
		cv::Mat vImageMat;
		while (!ifImage.eof())
		{
			std::getline(ifImage, vFileName);
			std::getline(ifPose, vPose);
			std::getline(ifPoseName, vPoseName);
			vImageMat = util.readMatBasic(vFaceTrackPath + vFileName + mImageType);
			vFileNames.push_back(vFileName);
			vTiltPanPoses.push_back(vPose.c_str());
			vPoseNames.push_back(vPoseName);
			vImageMats.push_back(vImageMat);
		}
		ifImage.close();
		ifPose.close();
		ifPoseName.close();

		mFileNames.push_back(vFileNames);
		mFaceTracks.push_back(vImageMats);
		mTiltPanPoses.push_back(vTiltPanPoses);
		mPoseNames.push_back(vPoseNames);
	}
	result = mFaceTracks.size();
	return result;
}


//\\ (Use) Luu ra file: Anh Mat.
void FaceDataSet::aSaveToFile(cv::Mat pFace, std::string pFileName, std::string pSavePath)
{
	Utilites util;
	//\\ Ghi anh Mat.
	std::string vFileName = util.subStringLastBefor(pFileName, ".");
	util.writeMatBasic(pFace, pSavePath + vFileName + mImageType);
	util.writeMatUChar(pFace, pSavePath + vFileName + ".txt");
}

//\\ Luu danh sach ten file anh va pose tuong ung cua tung facetrack ra file. Kich thuoc 2 danh sach phai bang nhau.
void FaceDataSet::aSaveToFile1(std::vector<std::string> pFileNames, std::vector<int> pPoses, std::string pSavePath)
{
	std::ofstream ofImage(pSavePath + mImageName + mFileType);
	std::ofstream ofPose(pSavePath + mPoseName + mFileType);
	std::string vFileName;
	int vIndex;
	size_t pFileNamesSize = pFileNames.size();
	for (size_t i = 0; i < pFileNamesSize - 1; i++)
	{
		//\\ Bo ten file mo rong.
		vFileName = pFileNames[i];
		vIndex = vFileName.find_last_of('.');
		vFileName = vFileName.substr(0, vIndex);
		//\\ Ghi ra file.
		ofImage << vFileName << endl;
		ofPose << pPoses[i] << endl;
	}
	//\\ Ghi phan tu cuoi.
	vFileName = pFileNames[pFileNamesSize - 1];
	vIndex = vFileName.find_last_of('.');
	vFileName = vFileName.substr(0, vIndex);
	ofImage << vFileName;
	ofPose << pPoses[pFileNamesSize - 1];

	ofImage.close();
	ofPose.close();
}
//\\ (Use) Luu danh sach ten file anh va pose tuong ung cua tung facetrack ra file. Kich thuoc 2 danh sach phai bang nhau.
void FaceDataSet::aSaveToFile2(std::vector<std::string> pFileNames, std::vector<int> pPoses, std::vector<std::string> pPoseNames, std::string pSavePath)
{
	//if (pSortPose)
	{
		Utilites util;
		//\\ Ghi anh Mat.
		std::vector<int> vTiltPans;
		//\\ Khoi tao index.
		for (size_t i = 0; i < pPoses.size(); i++)
		{
			//int vTiltPose = std::atoi(util.subStringLastBefor(pPoses[i], ";").c_str());
			//int vPanPose = std::atoi(util.subStringLastAfter(pPoses[i], ";").c_str());
			int vPose = pPoses[i];
			vTiltPans.push_back(vPose);
		}
		//\\ Sap xep thu tu pose giam dan.
		for (size_t i = 0; i < vTiltPans.size() - 1; i++)
		{
			for (size_t j = i + 1; j < vTiltPans.size(); j++)
			{
				if (vTiltPans[i] < vTiltPans[j])//\\ Theo pose.
				{
					int vTemp = vTiltPans[i];
					vTiltPans[i] = vTiltPans[j];
					vTiltPans[j] = vTemp;
					//\\ pPoses.
					int vSTemp = pPoses[i];
					pPoses[i] = pPoses[j];
					pPoses[j] = vSTemp;
					//\\ pPoseNames.
					std::string vSTempName = pPoseNames[i];
					pPoseNames[i] = pPoseNames[j];
					pPoseNames[j] = vSTempName;
					//\\ pFileNames.
					vSTempName = pFileNames[i];
					pFileNames[i] = pFileNames[j];
					pFileNames[j] = vSTempName;
				}
			}// for j.
		}// for i.
	}

	std::ofstream ofImage(pSavePath + mImageName + mFileType);
	std::ofstream ofPose(pSavePath + mPoseName + mFileType);
	std::ofstream ofPoseName(pSavePath + mPoseNameName + mFileType);
	std::string vFileName;
	int vIndex;
	size_t pFileNamesSize = pFileNames.size();
	for (size_t i = 0; i < pFileNamesSize - 1; i++)
	{
		//\\ Bo ten file mo rong.
		vFileName = pFileNames[i];
		vIndex = vFileName.find_last_of('.');
		vFileName = vFileName.substr(0, vIndex);
		//\\ Ghi ra file.
		ofImage << vFileName << endl;
		ofPose << pPoses[i] << endl;
		ofPoseName << pPoseNames[i] << endl;
	}
	//\\ Ghi phan tu cuoi.
	vFileName = pFileNames[pFileNamesSize - 1];
	vIndex = vFileName.find_last_of('.');
	vFileName = vFileName.substr(0, vIndex);
	ofImage << vFileName;
	ofPose << pPoses[pFileNamesSize - 1];
	ofPoseName << pPoseNames[pFileNamesSize - 1];

	ofImage.close();
	ofPose.close();
	ofPoseName.close();
}
//\\ (Use) Luu danh sach ten file anh va pose tuong ung cua tung facetrack ra file. Kich thuoc 2 danh sach phai bang nhau.
void FaceDataSet::aSaveToFile3(std::vector<std::string> pFileNames, std::vector<std::string> pPoses, std::vector<std::string> pPoseNames, bool pSortPose, std::string pSavePath)
{
	if (pSortPose)
	{
		Utilites util;
		//\\ Ghi anh Mat.
		std::vector<int> vTiltPans;
		//\\ Khoi tao index.
		for (size_t i = 0; i < pPoses.size(); i++)
		{
			//int vTiltPose = std::atoi(util.subStringLastBefor(pPoses[i], ";").c_str());
			//int vPanPose = std::atoi(util.subStringLastAfter(pPoses[i], ";").c_str());
			int vPose = std::atoi(pPoses[i].c_str());
			vPose = vPose / 1000 + vPose % 1000;
			vTiltPans.push_back(vPose);
		}
		//\\ Sap xep thu tu pose giam dan.
		for (size_t i = 0; i < vTiltPans.size() - 1; i++)
		{
			for (size_t j = i + 1; j < vTiltPans.size(); j++)
			{
				if (vTiltPans[i] < vTiltPans[j])//\\ Theo pose.
				{
					int vTemp = vTiltPans[i];
					vTiltPans[i] = vTiltPans[j];
					vTiltPans[j] = vTemp;
					//\\ pPoses.
					std::string vSTemp = pPoses[i];
					pPoses[i] = pPoses[j];
					pPoses[j] = vSTemp;
					//\\ pPoseNames.
					vSTemp = pPoseNames[i];
					pPoseNames[i] = pPoseNames[j];
					pPoseNames[j] = vSTemp;
					//\\ pFileNames.
					vSTemp = pFileNames[i];
					pFileNames[i] = pFileNames[j];
					pFileNames[j] = vSTemp;
				}
			}// for j.
		}// for i.
	}



	std::ofstream ofImage(pSavePath + mImageName + mFileType);
	std::ofstream ofPose(pSavePath + mTiltPanPoseName + mFileType);
	std::ofstream ofPoseName(pSavePath + mPoseNameName + mFileType);
	std::string vFileName;
	int vIndex;
	size_t pFileNamesSize = pFileNames.size();
	for (size_t i = 0; i < pFileNamesSize - 1; i++)
	{
		//\\ Bo ten file mo rong.
		vFileName = pFileNames[i];
		vIndex = vFileName.rfind('.');
		vFileName = vFileName.substr(0, vIndex);
		//\\ Ghi ra file.
		ofImage << vFileName << endl;
		ofPose << pPoses[i] << endl;
		ofPoseName << pPoseNames[i] << endl;
	}
	//\\ Ghi phan tu cuoi.
	vFileName = pFileNames[pFileNamesSize - 1];
	vIndex = vFileName.rfind('.');
	vFileName = vFileName.substr(0, vIndex);
	ofImage << vFileName;
	ofPose << pPoses[pFileNamesSize - 1];
	ofPoseName << pPoseNames[pFileNamesSize - 1];

	ofImage.close();
	ofPose.close();
	ofPoseName.close();
}
