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
std::vector<cv::Mat> FaceDataSet::aReadsImage(std::vector<std::string> pAllFileName, const std::string pDataSourcePath, std::string pFolderPath)
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
			std::string fName = std::to_string(i);
			fName = mImageName + util.leftPad(fName, numFilesLength, '0');
			//\\ Ghi gia tri vector dac trung.
			util.writeMatBasic(face, pFolderPath + fName + mImageType);
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
	//\\ * Load tat ca anh vao FaceDataSet.
	//\\ Lay tat ca Ids co trong nguon anh.
	std::vector<std::string> vAllIds = mDataSetBase->aGetsAllIds();
	size_t vAllIdsSize = vAllIds.size();
	int numlengthFaceTrack = std::to_string(vAllIdsSize).length();
	for (size_t i = 0; i < vAllIdsSize; i++)
	{
		std::string vId = vAllIds[i];
		//\\ Tao thu muc cho facetrack thu i.
		std::string vFaceTrackPath = mFolderPath + mDataSetFolder + "/" + mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
		std::vector<std::string> vAllFileName = mDataSetBase->aGetsAllFileName(vId);
		//\\ Tao thu muc facetrack thu i.
		util.makeDir(util.replaceAll(vFaceTrackPath, "/", "\\"));
		vFaceTrackPath += "/";
		//\\ Doc anh va ghi ra file.
		std::vector<cv::Mat> vFaceTrack = aReadsImage(vAllFileName, pDataSourcePath + mDataSetBase->aGetPath(vId), vFaceTrackPath);
		mFaceTracks.push_back(vFaceTrack);
	}// for i.
	result = mFaceTracks.size();
	return result;
}
//\\ Doc cac anh tu file va dua vao csdl.
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
		std::string vFaceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), facetrackLength, '0');
		std::vector<cv::Mat> facetrack;
		size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = vNumFeatureStart; j <= vNumFeatureEnd; j++)
		{
			//std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			std::string vImageName = mImageName + util.leftPad(std::to_string(j), featueLength, '0');
			cv::Mat vImageMat = util.readMatBasic(mFolderPath + mDataSetFolder + "/" + vFaceTrackName + "/" + vImageName + mImageType);
			facetrack.push_back(vImageMat);
		}
		mFaceTracks.push_back(facetrack);
		facetrack.clear();
	}
	result = mFaceTracks.size();
	return result;
}
