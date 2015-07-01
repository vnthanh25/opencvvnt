/*
VNThanh
- Face Track.
*/

#include "../Header/FaceTrackDB.h"
#include "../Header/FeatureLBP.h"
#include "../Header/Utilities.h"

using namespace vnt;

/********** Constructor **********/
FaceTrackDB::FaceTrackDB()
{
}
FaceTrackDB::~FaceTrackDB()
{
}

/********** public Methods **********/
//\\ Lay danh sach ten file.
std::vector<std::vector<std::string>> FaceTrackDB::aGetFileNames()
{
	return mFileNames;
}
//\\ Gan danh sach ten file.
void FaceTrackDB::aSetFileNames(std::vector<std::vector<std::string>> pFileNames)
{
	mFileNames = pFileNames;
}

//\\ Lay csdl.
std::vector<std::vector<std::vector<std::vector<double>>>> FaceTrackDB::aGetFaceTrackDatabase()
{
	return mFaceTrackDatabase;
}
//\\ Gan csdl.
void FaceTrackDB::aSetFaceTrackDatabase(std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTrackDatabase)
{
	mFaceTrackDatabase = pFaceTrackDatabase;
}

//\\ Lay feature.
std::vector<std::vector<std::vector<std::vector<int>>>> FaceTrackDB::aGetFacetrackFeatures()
{
	return mFacetrackFeatures;
}
//\\ Gan feature.
void FaceTrackDB::aSetFacetrackFeatures(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures)
{
	mFacetrackFeatures = pFacetrackFeatures;
}

//\\ Lay Poses.
std::vector<std::vector<int>> FaceTrackDB::aGetPoses()
{
	return mPoses;
}
//\\ Gan Poses.
void FaceTrackDB::aSetPoses(std::vector<std::vector<int>> pPoses)
{
	mPoses = pPoses;
}

//\\ Lay TiltPanPoses.
std::vector<std::vector<std::string>> FaceTrackDB::aGetTiltPanPoses()
{
	return mTiltPanPoses;
}
//\\ Gan TiltPanPoses.
void FaceTrackDB::aSetTiltPanPoses(std::vector<std::vector<std::string>> pTiltPanPoses)
{
	mTiltPanPoses = pTiltPanPoses;
}

//\\ Lay danh sach pose name.
std::vector<std::vector<std::string>> FaceTrackDB::aGetPoseNames()
{
	return mPoseNames;
}
//\\ Gan danh sach pose name.
void FaceTrackDB::aSetPoseNames(std::vector<std::vector<std::string>> pPoseNames)
{
	mPoseNames = pPoseNames;
}

//\\ Lay danh sach FolderPath.
std::string FaceTrackDB::aGetFolderPath()
{
	return mFolderPath;
}
//\\ Gan danh sach FolderPath.
void FaceTrackDB::aSetFolderPath(std::string pFolderPath)
{
	mFolderPath = pFolderPath;
}



//\\ Doc tat ca file anh vao trong facetrack.
std::vector<cv::Mat> FaceTrackDB::aGestAllImage(std::string pFolderPath, std::vector<std::string> pAllFileName)
{
	std::vector<cv::Mat> result;
	size_t size01 = pAllFileName.size();
	for (size_t i = 0; i < size01; i++)
	{
		cv::Mat face = cv::imread(pFolderPath + pAllFileName[i], CV_8UC1);
		result.push_back(face);
	}
	return result;
}

//\\ (Use) Lay dac trung cua tung face trong facetrack.
std::vector<std::vector<std::vector<int>>> FaceTrackDB::aGetsFeature(const std::vector<cv::Mat> pFaceTrack)
{
	std::vector<std::vector<std::vector<int>>> result;
	//\\ Su dung dac trung LBP.
	FeatureLBP featureLBP;
	for (size_t i = 0; i < pFaceTrack.size(); i++)
	{
		result.push_back(featureLBP.LBP(pFaceTrack[i], 3, 1));
	}

	return result;
}
//\\ (Use) Tinh vector trung binh cho facetrack.
std::vector<std::vector<double>> FaceTrackDB::aAvgFeature1(const std::vector<std::vector<std::vector<int>>> pFeatures, const std::vector<int> pFTPoses)
{
	std::vector<std::vector<double>> result;
	//\\ Tinh vector trung binh cho cac dac trung cua facetrack.
	if (pFeatures.size() > 0)
	{
		//\\ Lap qua 9 vung. (truc y)
		for (size_t i = 0; i < pFeatures[0].size(); i++)
		{
			std::vector<double> lbp;
			//\\ Lap qua 59 dac trung LBP. (truc x)
			for (size_t j = 0; j < pFeatures[0][0].size(); j++)
			{
				double avg = 0;
				int vSumPose = 0;
				//\\ Lap qua danh sach dac trung. (truc z)
				for (size_t k = 0; k < pFeatures.size(); k++)
				{
					//\\ Tich hop pose: moi dac trung nhan voi he so pose.
					avg += 1.0 * pFTPoses[k] * pFeatures[k][i][j];
					////\\ Chua tich hop pose.
					//avg += pFeatures[k][i][j];
					vSumPose += pFTPoses[k];
				}
				//\\ Tich hop pose: gia tri trung binh chia cho tong pose.
				avg = avg / (pFeatures.size() * vSumPose);
				lbp.push_back(avg);
			}
			result.push_back(lbp);
		}
	}
	return result;
}
//\\ (Use) (1,2) Tinh vector trung binh cho facetrack.
std::vector<std::vector<double>> FaceTrackDB::aAvgFeatureNotPose1(const std::vector<std::vector<std::vector<int>>> pFeatures)
{
	std::vector<std::vector<double>> result;
	//\\ Tinh vector trung binh cho cac dac trung cua facetrack.
	if (pFeatures.size() > 0)
	{
		//\\ Lap qua 9 vung. (truc y)
		for (size_t i = 0; i < pFeatures[0].size(); i++)
		{
			std::vector<double> lbp;
			//\\ Lap qua 59 dac trung LBP. (truc x)
			for (size_t j = 0; j < pFeatures[0][0].size(); j++)
			{
				double avg = 0;
				//\\ Lap qua danh sach dac trung. (truc z)
				for (size_t k = 0; k < pFeatures.size(); k++)
				{
					avg += pFeatures[k][i][j];
				}
				avg = avg / pFeatures.size();
				lbp.push_back(avg);
			}
			result.push_back(lbp);
		}
	}
	return result;
}
std::vector<std::vector<double>> FaceTrackDB::aAvgFeature2(const std::vector<cv::Mat> pFaceTrack, const std::vector<int> pFTPoses)
{
	std::vector<std::vector<double>> result;
	//\\ Tinh dac trung LBP cho tat ca face trong facetrack
	std::vector<std::vector<std::vector<int>>> featureLBPs = aGetsFeature(pFaceTrack);
	result = aAvgFeature1(featureLBPs, pFTPoses);
	return result;
}
std::vector<std::vector<double>> FaceTrackDB::aAvgFeatureNotPose2(const std::vector<cv::Mat> pFaceTrack)
{
	std::vector<std::vector<double>> result;
	//\\ Tinh dac trung LBP cho tat ca face trong facetrack
	std::vector<std::vector<std::vector<int>>> featureLBPs = aGetsFeature(pFaceTrack);
	result = aAvgFeatureNotPose1(featureLBPs);
	return result;
}
//\\ (Use) Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
std::vector<std::vector<std::vector<double>>> FaceTrackDB::aAvgFeaturesPose1(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<int>> pFTPoses)
{
	std::vector<std::vector<std::vector<double>>> result;
	//\\ Tinh vector dac trung trung binh cho tung facetrack.
	for (size_t i = 0; i < pFTFeatures.size(); i++)
	{
		std::vector<std::vector<double>> feature = aAvgFeature1(pFTFeatures[i], pFTPoses[i]);
		result.push_back(feature);
	}
	return result;
}
//\\ (Use) (1,2) Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
std::vector<std::vector<std::vector<double>>> FaceTrackDB::aAvgFeaturesNotPose1(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures)
{
	std::vector<std::vector<std::vector<double>>> result;
	//\\ Tinh vector dac trung trung binh cho tung facetrack.
	for (size_t i = 0; i < pFTFeatures.size(); i++)
	{
		std::vector<std::vector<double>> feature = aAvgFeatureNotPose1(pFTFeatures[i]);
		result.push_back(feature);
	}
	return result;
}
//\\ (Use) (2) Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
std::vector<std::vector<std::vector<double>>> FaceTrackDB::aAvgFeaturesPose2(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<std::string>> pTiltPanPoses)
{
	std::vector<std::vector<std::vector<double>>> result;
	//\\ Tinh vector dac trung trung binh cho tung facetrack.
	for (size_t i = 0; i < pFTFeatures.size(); i++)
	{
		std::vector<std::vector<double>> feature = aAvgFeature6(pFTFeatures[i], pTiltPanPoses[i]);
		result.push_back(feature);
	}
	return result;
}
//\\ (Use) Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
std::vector<std::vector<double>> FaceTrackDB::aAvgFeature3(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<int>> pFTPoses)
{
	std::vector<std::vector<double>> result;
	//\\ Tinh vector trung binh cho cac dac trung cua facetrack.
	if (pFTFeatures.size() > 0)
	{
		//\\ Lap qua 9 vung. (truc y)
		for (size_t i = 0; i < pFTFeatures[0][0].size(); i++)
		{
			std::vector<double> lbp;
			//\\ Lap qua 59 dac trung LBP. (truc x)
			for (size_t j = 0; j < pFTFeatures[0][0][0].size(); j++)
			{
				double avg = 0;
				int vSumPose = 0;
				//\\ Lap qua danh sach facetrack. (truc z).
				for (size_t k = 0; k < pFTFeatures.size(); k++)
				{
					//\\ Lap qua danh sach dac trung. (truc t)
					for (size_t l = 0; l < pFTFeatures[k].size(); l++)
					{
						//\\ Tich hop pose: moi dac trung nhan voi he so pose.
						avg += 1.0 * pFTPoses[k][l] * pFTFeatures[k][l][i][j];
						////\\ Chua tich hop pose.
						//avg += pFTFeatures[k][l][i][j];
						vSumPose += pFTPoses[k][l];
					}
				}
				//\\ Tich hop pose: gia tri trung binh chia cho tong pose.
				avg = avg / (pFTFeatures.size() * pFTFeatures[0].size() * vSumPose);
				lbp.push_back(avg);
			}
			result.push_back(lbp);
		}
	}
	return result;
}
//\\ (Use) (1,2) Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
std::vector<std::vector<double>> FaceTrackDB::aAvgFeatureNotPose3(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures)
{
	std::vector<std::vector<double>> result;
	//\\ Tinh vector trung binh cho cac dac trung cua facetrack.
	if (pFTFeatures.size() > 0)
	{
		//\\ Lap qua 9 vung. (truc y)
		for (size_t i = 0; i < pFTFeatures[0][0].size(); i++)
		{
			std::vector<double> lbp;
			//\\ Lap qua 59 dac trung LBP. (truc x)
			for (size_t j = 0; j < pFTFeatures[0][0][0].size(); j++)
			{
				double avg = 0;
				//\\ Lap qua danh sach facetrack. (truc z).
				for (size_t k = 0; k < pFTFeatures.size(); k++)
				{
					//\\ Lap qua danh sach dac trung. (truc t)
					for (size_t l = 0; l < pFTFeatures[k].size(); l++)
					{
						avg += pFTFeatures[k][l][i][j];
					}
				}
				avg = avg / (pFTFeatures.size() * pFTFeatures[0].size());
				lbp.push_back(avg);
			}
			result.push_back(lbp);
		}
	}
	return result;
}
//\\ (Use) Tinh vector trung binh cho tat ca facetrack. Moi facetrack co 1 vector dac trung trung binh.
std::vector<std::vector<double>> FaceTrackDB::aAvgFeature4(const std::vector<std::vector<std::vector<double>>> pFTFeatures)
{
	std::vector<std::vector<double>> result;
	//\\ Tinh vector trung binh cho cac dac trung cua facetrack.
	if (pFTFeatures.size() > 0)
	{
		//\\ Lap qua 9 vung. (truc y)
		for (size_t i = 0; i < pFTFeatures[0].size(); i++)
		{
			std::vector<double> lbp;
			//\\ Lap qua 59 dac trung LBP. (truc x)
			for (size_t j = 0; j < pFTFeatures[0][0].size(); j++)
			{
				double avg = 0;
				//\\ Lap qua danh sach dac trung. (truc z)
				for (size_t k = 0; k < pFTFeatures.size(); k++)
				{
					avg += pFTFeatures[k][i][j];
				}
				avg = avg / pFTFeatures.size();
				lbp.push_back(avg);
			}
			result.push_back(lbp);
		}
	}
	return result;
}
//\\ (Use) (2) Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
std::vector<std::vector<double>> FaceTrackDB::aAvgFeature5(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures, const std::vector<std::vector<std::string>> pTiltPanPoses)
{
	std::vector<std::vector<double>> result;
	Utilites util;
	//\\ Tinh vector trung binh cho cac dac trung cua facetrack.
	if (pFTFeatures.size() > 0)
	{
		//\\ Lay so luong gia tri trong TiltPanPose lam so vong lap.
		std::string vSPose = pTiltPanPoses[0][0];
		//std::vector<std::string> vVTiltPanPose = util.splitString(vSPose, ";");
		//\\ Lap tilt and pan cua pose.
		//for (size_t p = 0; p < vVTiltPanPose.size(); p++)
		int vPose = 0;
		size_t vVTiltPanPoseSize = 1;// 1 pose.
		if (vSPose.length() > 3)// 2 pose.
			vVTiltPanPoseSize = 2;
		for (size_t p = 0; p < vVTiltPanPoseSize; p++)
		{
			//\\ Lap qua 9 vung. (truc y).
			for (size_t i = 0; i < pFTFeatures[0][0].size(); i++)
			{
				std::vector<double> lbp;
				//\\ Lap qua 59 dac trung LBP. (truc x)
				for (size_t j = 0; j < pFTFeatures[0][0][0].size(); j++)
				{
					double avg = 0;
					int vSumPose = 0;
					//\\ Lap qua danh sach facetrack. (truc z).
					for (size_t k = 0; k < pFTFeatures.size(); k++)
					{
						//\\ Lap qua danh sach dac trung. (truc t)
						for (size_t l = 0; l < pFTFeatures[k].size(); l++)
						{
							//vPose = std::atoi(util.splitString(pTiltPanPoses[k][l], ";")[p].c_str());
							vPose = std::atoi(pTiltPanPoses[k][l].c_str());
							if (vVTiltPanPoseSize == 2)
							{
								if (p == 0)// Tilt.
									vPose /= 1000;
								else
									vPose %= 1000;
							}
							//\\ Tich hop pose: moi dac trung nhan voi he so pose.
							avg += 1.0 * vPose * pFTFeatures[k][l][i][j];
							////\\ Chua tich hop pose.
							//avg += pFTFeatures[k][l][i][j];
							vSumPose += vPose;
						}
					}
					//\\ Tich hop pose: gia tri trung binh chia cho tong pose.
					avg = avg / (pFTFeatures.size() * pFTFeatures[0].size() * vSumPose);
					lbp.push_back(avg);
				}// for  Lap qua 59 dac trung LBP. (truc x).
				result.push_back(lbp);
			}// for Lap qua 9 vung. (truc y).
		}// for Lap tilt and pan cua pose.
	}// if
	return result;
}
//\\ (Use) (2) Tinh vector trung binh cho facetrack.
std::vector<std::vector<double>> FaceTrackDB::aAvgFeature6(const std::vector<std::vector<std::vector<int>>> pFeatures, const std::vector<std::string> pTiltPanPoses)
{
	std::vector<std::vector<double>> result;
	Utilites util;
	//\\ Tinh vector trung binh cho cac dac trung cua facetrack.
	if (pFeatures.size() > 0)
	{
		//\\ Lay so luong gia tri trong TiltPanPose lam so vong lap.
		std::string vSPose = pTiltPanPoses[0];
		//std::vector<std::string> vVTiltPanPose = util.splitString(vSPose, ";");
		////\\ Lap tilt and pan cua pose.
		int vPose = 0;
		//for (size_t p = 0; p < vVTiltPanPose.size(); p++)
		size_t vVTiltPanPoseSize = 1;// 1 pose.
		if (vSPose.length() > 3)// 2 pose.
			vVTiltPanPoseSize = 2;
		for (size_t p = 0; p < vVTiltPanPoseSize; p++)
		{
			//\\ Lap qua 9 vung. (truc y).
			for (size_t i = 0; i < pFeatures[0].size(); i++)
			{
				std::vector<double> lbp;
				//\\ Lap qua 59 dac trung LBP. (truc x).
				for (size_t j = 0; j < pFeatures[0][0].size(); j++)
				{
					double avg = 0;
					int vSumPose = 0;
					//\\ Lap qua danh sach dac trung. (truc z)
					for (size_t k = 0; k < pFeatures.size(); k++)
					{
						//vPose = std::atoi(util.splitString(pTiltPanPoses[k], ";")[p].c_str());
						vPose = std::atoi(pTiltPanPoses[k].c_str());
						if (vVTiltPanPoseSize == 2)
						{
							if (p == 0)// Tilt.
								vPose /= 1000;
							else
								vPose %= 1000;
						}
						//\\ Tich hop pose: moi dac trung nhan voi he so pose.
						avg += 1.0 * vPose * pFeatures[k][i][j];
						////\\ Chua tich hop pose.
						//avg += pFeatures[k][i][j];
						vSumPose += vPose;
					}
					//\\ Tich hop pose: gia tri trung binh chia cho tong pose.
					avg = avg / (pFeatures.size() * vSumPose);
					lbp.push_back(avg);
				}// for  Lap qua 59 dac trung LBP. (truc x).
				result.push_back(lbp);
			}// for Lap qua 9 vung. (truc y).
		}// for Lap tilt and pan cua pose.
	}// if
	return result;
}

//\\ (Use) (1,2) (double) Tinh tong cua tich cac phan tu tuong ung trong 2 vector. Co so chieu bang nhau.
double FaceTrackDB::aSumMul1(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
{
	double result = 0;
	//\\ Lap qua 9 vung. (truc y)
	for (size_t i = 0; i < pVector1.size(); i++)
	{
		//\\ Lap qua 59 dac trung LBP. (truc x)
		for (size_t j = 0; j < pVector1[0].size(); j++)
		{
			//\\ Cong don cua tich cua cac phan tu.
			result += pVector1[i][j] * pVector2[i][j];
		}
	}
	return result;
}
//\\ (Use) (1,2) (int) Tinh tong cua tich cac phan tu tuong ung trong 2 vector. Co so chieu bang nhau.
double FaceTrackDB::aSumMul2(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2)
{
	double result = 0;
	//\\ Lap qua 9 vung. (truc y)
	for (size_t i = 0; i < pVector1.size(); i++)
	{
		//\\ Lap qua 59 dac trung LBP. (truc x)
		for (size_t j = 0; j < pVector1[0].size(); j++)
		{
			//\\ Cong don cua tich cua cac phan tu.
			result += pVector1[i][j] * pVector2[i][j];
		}
	}
	return result;
}
//\\ (Use) (1,2) (double) Tinh khoang cach cosine cua 2 vector. Co so chieu bang nhau.
double FaceTrackDB::aCosine1(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
{
	double result = 0;

	//\\ Tinh tong tich Ai x Bi.
	double d12 = aSumMul1(pVector1, pVector2);
	//\\ Tinh tong tich Ai x Ai.
	double d11 = aSumMul1(pVector1, pVector1);
	//\\ Tinh tong tich Bi x Bi.
	double d22 = aSumMul1(pVector2, pVector2);

	result = d12 / (sqrt(d11) * sqrt(d22));
	return result;
}
//\\ (Use) (1,2) (int) Tinh khoang cach cosine cua 2 vector. Co so chieu bang nhau.
double FaceTrackDB::aCosine2(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2)
{
	double result = 0;

	//\\ Tinh tong tich Ai x Bi.
	double d12 = aSumMul2(pVector1, pVector2);
	//\\ Tinh tong tich Ai x Ai.
	double d11 = aSumMul2(pVector1, pVector1);
	//\\ Tinh tong tich Bi x Bi.
	double d22 = aSumMul2(pVector2, pVector2);

	result = d12 / (sqrt(d11) * sqrt(d22));
	return result;
}

//\\ Tinh tong cua hieu cua binh phuong cac phan tu tuong ung trong 2 vector. Co so chieu bang nhau.
double FaceTrackDB::aSumSub1(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
{
	double result = 0;
	//\\ Lap qua 9 vung. (truc y)
	for (size_t i = 0; i < pVector1.size(); i++)
	{
		//\\ Lap qua 59 dac trung LBP. (truc x)
		for (size_t j = 0; j < pVector1[0].size(); j++)
		{
			//\\ Cong don cua binh phuong cua hieu cua cac phan tu.
			double sub = pVector1[i][j] - pVector2[i][j];
			result += sub * sub;
		}
	}
	return result;
}
double FaceTrackDB::aSumSub2(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2)
{
	double result = 0;
	//\\ Lap qua 9 vung. (truc y)
	for (size_t i = 0; i < pVector1.size(); i++)
	{
		//\\ Lap qua 59 dac trung LBP. (truc x)
		for (size_t j = 0; j < pVector1[0].size(); j++)
		{
			//\\ Cong don cua binh phuong cua hieu cua cac phan tu.
			double sub = pVector1[i][j] - pVector2[i][j];
			result += sub * sub;
		}
	}
	return result;
}
//\\ Tinh khoang cach hinh hoc cua 2 vector.
double FaceTrackDB::aEuclid11(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
{
	double result = 0;

	//\\ Tinh tong cua hieu cua binh phuong cua cac phan tu.
	double sum = aSumSub1(pVector1, pVector2);
	//\\ Tinh khoang cach hinh hoc.
	result = sqrt(sum);
	return result;
}
double FaceTrackDB::aEuclid21(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2)
{
	double result = 0;

	//\\ Tinh tong cua hieu cua binh phuong cua cac phan tu.
	double sum = aSumSub2(pVector1, pVector2);
	//\\ Tinh khoang cach hinh hoc.
	result = sqrt(sum);
	return result;
}

//\\ Tinh khoang cach hinh hoc cua 2 vector.
double FaceTrackDB::aLp1(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2, int pLevel)
{
	double result = 0;
	//\\ Lap qua 9 vung. (truc y)
	for (size_t i = 0; i < pVector1.size(); i++)
	{
		//\\ Lap qua 59 dac trung LBP. (truc x)
		for (size_t j = 0; j < pVector1[0].size(); j++)
		{
			//\\ Cong don cua binh phuong cua hieu cua cac phan tu.
			double sub = pVector1[i][j] - pVector2[i][j];
			sub = abs(sub);
			//\\ Tinh mu cua hieu.
			for (int p = 1; p < pLevel; p++)
			{
				sub *= sub;
			}
			result += sub;
		}
	}
	//\\ Tinh can.
	double vPow = 1.0 / pLevel;
	result = pow(result, vPow);
	return result;
}
double FaceTrackDB::aLp2(std::vector<std::vector<int>> pVector1, std::vector<std::vector<int>> pVector2, int pLevel)
{
	double result = 0;
	//\\ Lap qua 9 vung. (truc y)
	for (size_t i = 0; i < pVector1.size(); i++)
	{
		//\\ Lap qua 59 dac trung LBP. (truc x)
		for (size_t j = 0; j < pVector1[0].size(); j++)
		{
			//\\ Cong don cua binh phuong cua hieu cua cac phan tu.
			double sub = pVector1[i][j] - pVector2[i][j];
			sub = abs(sub);
			//\\ Tinh mu cua hieu.
			for (int p = 1; p < pLevel; p++)
			{
				sub *= sub;
			}
			result += sub;
		}
	}
	//\\ Tinh can.
	double vPow = 1.0 / pLevel;
	result = pow(result, vPow);
	return result;
}

//\\ (Use) (1,2) (double) Tinh hieu cua 2 vector dac trung.
std::vector<std::vector<double>> FaceTrackDB::aSub(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
{
	std::vector<std::vector<double>> result;
	//\\ Lap qua 9 vung. (truc y)
	for (size_t i = 0; i < pVector1.size(); i++)
	{
		std::vector<double> lbp;
		//\\ Lap qua 59 dac trung LBP. (truc x)
		for (size_t j = 0; j < pVector1[0].size(); j++)
		{
			//\\ Hieu cua cac phan tu.
			lbp.push_back(pVector1[i][j] - pVector2[i][j]);
		}
		result.push_back(lbp);
	}
	return result;
}

//\\ Khoi tao vector dac trung.
int FaceTrackDB::aFeatureInit1(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<int>> pPoses, std::string pFolderPath)
{
	int result = -1;
	//mFacetrackFeatures.clear();
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mFaceTracksFolder);
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	//std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	const size_t vFaceTrackSize = pFaceTracks.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		util.makeDir(vFolderPath + mFaceTracksFolder + "\\" + faceTrackName);
		faceTrackNames.push_back(faceTrackName);
		//\\ Lay danh sach vector dac trung cua mot facetrack.
		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		mFacetrackFeatures.push_back(features);
		//\\ Ghi ra file: cac vector dac trung cua facetrack thu i.
		size_t featuressize = features.size();
		int numlengthFeature = std::to_string((int)featuressize).length();
		int sumPose = 0;
		for (size_t j = 0; j < featuressize; j++)
		{
			//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
			cv::Mat vFeatureFile = util.convertV2IToMat(features[j], features[j][0].size(), features[j].size());
			//\\ Ten file co dang: "Feature01.txt", ...
			//\\std::string vNum = util.leftPad(std::to_string(j), numlengthFeature, '0');
			std::string vNum = std::to_string(j);
			//\\ Ghi gia tri vector dac trung.
			util.writeMatBasic(vFeatureFile, mFolderPath + mFaceTracksFolder + "/" + faceTrackName + "/" + mFeatureName + vNum + mFeatureType);
			//\\ Ghi gia tri pose co kieu Mat ra file.
			cv::Mat matPose = cv::Mat(1, 1, CV_32SC1, pPoses[i][j]);
			util.writeMatBasic(matPose, mFolderPath + mFaceTracksFolder + "/" + faceTrackName + "/" + mPoseName + vNum + mFeatureType);
			//\\ Cong them gia tri pose tuong ung vao ten file.
			sumPose += pPoses[i][j];
		}
	}
	result = mFacetrackFeatures.size();
	return result;
}
//\\ Khoi tao vector dac trung.
int FaceTrackDB::aFeatureInitNotPose1(std::vector<std::vector<cv::Mat>> pFaceTracks, std::string pFolderPath)
{
	int result = -1;
	//mFacetrackFeatures.clear();
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mFaceTracksFolder);
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	//std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	const size_t vFaceTrackSize = pFaceTracks.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		util.makeDir(vFolderPath + mFaceTracksFolder + "\\" + faceTrackName);
		faceTrackNames.push_back(faceTrackName);
		//\\ Lay danh sach vector dac trung cua mot facetrack.
		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		mFacetrackFeatures.push_back(features);
		//\\ Ghi ra file: cac vector dac trung cua facetrack thu i.
		size_t featuressize = features.size();
		int numlengthFeature = std::to_string((int)featuressize).length();
		for (size_t j = 0; j < featuressize; j++)
		{
			//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
			cv::Mat vFeatureFile = util.convertV2IToMat(features[j], features[j][0].size(), features[j].size());
			//\\ Ten file co dang: "Feature01.txt", ...
			//\\std::string vNum = util.leftPad(std::to_string(j), numlengthFeature, '0');
			std::string vNum = std::to_string(j);
			//\\ Ghi gia tri vector dac trung.
			util.writeMatBasic(vFeatureFile, mFolderPath + mFaceTracksFolder + "/" + faceTrackName + "/" + mFeatureName + vNum + mFeatureType);
		}
	}
	result = mFacetrackFeatures.size();
	return result;
}
//\\ Khoi tao vector dac trung.
int FaceTrackDB::aFeatureInit2(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pSavePath, bool pIsSaveToFile)
{
	int result = -1;
	//mFacetrackFeatures.clear();
	mFileNames = pFileNames;
	mPoses = pPoses;
	mFolderPath = pSavePath;
	Utilites util;
	//\\ Tao thu muc.
	std::string vSavePath = mFolderPath + mFaceTracksFolder + "/";
	std::string vFolderPath = util.replaceAll(vSavePath, "/", "\\");
	util.makeDir(vFolderPath);
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	//std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	const size_t vFaceTrackSize = pFaceTracks.size();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		util.makeDir(vFolderPath + "\\" + faceTrackName);
		faceTrackNames.push_back(faceTrackName);
		//\\ Lay danh sach vector dac trung cua mot facetrack.
		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		mFacetrackFeatures.push_back(features);
		//\\ Ghi ra file: cac vector dac trung cua facetrack thu i.
		size_t featuressize = features.size();
		int sumPose = 0;
		for (size_t j = 0; j < featuressize; j++)
		{
			if (pIsSaveToFile)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat vFeatureFile = util.convertV2IToMat(features[j], features[j][0].size(), features[j].size());
				aSaveToFile(vFeatureFile, mFileNames[i][j], vSavePath + faceTrackName + "/");
			}
			//\\ Cong them gia tri pose tuong ung vao ten file.
			sumPose += pPoses[i][j];
		}
		if (pIsSaveToFile)
		{
			//\\ Ghi thong tin ve ten file anh va pose.
			aSaveToFile1(mFileNames[i], mPoses[i], vSavePath + faceTrackName + "/");
		}
	}
	result = mFacetrackFeatures.size();
	return result;
}
//\\ (Use) Khoi tao vector dac trung.
int FaceTrackDB::aFeatureInit3(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::vector<std::vector<std::string>> pPoseNames, std::string pSavePath, bool pIsSaveToFile)
{
	int result = -1;
	//mFacetrackFeatures.clear();
	mFileNames = pFileNames;
	mPoses = pPoses;
	mPoseNames = pPoseNames;
	mFolderPath = pSavePath;
	Utilites util;
	//\\ Tao thu muc.
	std::string vSavePath = mFolderPath + mFaceTracksFolder + "/";
	std::string vFolderPath = util.replaceAll(vSavePath, "/", "\\");
	util.makeDir(vFolderPath);
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	//std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	const size_t vFaceTrackSize = pFaceTracks.size();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		util.makeDir(vFolderPath + "\\" + faceTrackName);
		faceTrackNames.push_back(faceTrackName);
		//\\ Lay danh sach vector dac trung cua mot facetrack.
		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		mFacetrackFeatures.push_back(features);
		//\\ Ghi ra file: cac vector dac trung cua facetrack thu i.
		size_t featuressize = features.size();
		int sumPose = 0;
		for (size_t j = 0; j < featuressize; j++)
		{
			if (pIsSaveToFile)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat vFeatureFile = util.convertV2IToMat(features[j], features[j][0].size(), features[j].size());
				aSaveToFile(vFeatureFile, mFileNames[i][j], vSavePath + faceTrackName + "/");
			}
			//\\ Cong them gia tri pose tuong ung vao ten file.
			sumPose += pPoses[i][j];
		}
		if (pIsSaveToFile)
		{
			//\\ Ghi thong tin ve ten file anh va pose.
			aSaveToFile2(mFileNames[i], mPoses[i], mPoseNames[i], vSavePath + faceTrackName + "/");
		}
	}
	result = mFacetrackFeatures.size();
	return result;
}
//\\ (Use) Khoi tao vector dac trung.
int FaceTrackDB::aFeatureInit4(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, std::vector<std::vector<std::string>> pPoseNames, std::string pSavePath, bool pIsSaveToFile)
{
	int result = -1;
	//mFacetrackFeatures.clear();
	mFileNames = pFileNames;
	mTiltPanPoses = pTiltPanPoses;
	mPoseNames = pPoseNames;
	mFolderPath = pSavePath;
	Utilites util;
	//\\ Tao thu muc.
	std::string vSavePath = mFolderPath + mFaceTracksFolder + "/";
	std::string vFolderPath = util.replaceAll(vSavePath, "/", "\\");
	util.makeDir(vFolderPath);
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	//std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	const size_t vFaceTrackSize = pFaceTracks.size();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		util.makeDir(vFolderPath + "\\" + faceTrackName);
		faceTrackNames.push_back(faceTrackName);
		//\\ Lay danh sach vector dac trung cua mot facetrack.
		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		mFacetrackFeatures.push_back(features);
		//\\ Ghi ra file: cac vector dac trung cua facetrack thu i.
		size_t featuressize = features.size();
		int sumPose = 0;
		for (size_t j = 0; j < featuressize; j++)
		{
			if (pIsSaveToFile)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat vFeatureFile = util.convertV2IToMat(features[j], features[j][0].size(), features[j].size());
				aSaveToFile(vFeatureFile, mFileNames[i][j], vSavePath + faceTrackName + "/");
			}
		}
		if (pIsSaveToFile)
		{
			//\\ Ghi thong tin ve ten file anh va pose.
			aSaveToFile3(mFileNames[i], mTiltPanPoses[i], mPoseNames[i], true, vSavePath + faceTrackName + "/");
		}
	}
	result = mFacetrackFeatures.size();
	return result;
}

//\\ Doc cac vector dac trung tu file va dua vao csdl.
int FaceTrackDB::aFeatureRead1(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFacetrackFeatures.clear();
	//mPoses.clear();
	Utilites util;
	mFolderPath = pFolderPath;
	int facetrackLength = pNumFaceTrackEnd.length();
	int featueLength = pNumFeatureEnd.length();
	//\\ Doc tung facetrack.
	size_t vNumFaceTrackStart = std::atoi(pNumFaceTrackStart.c_str());
	size_t vNumFaceTrackEnd = std::atoi(pNumFaceTrackEnd.c_str());
	for (size_t i = vNumFaceTrackStart; i <= vNumFaceTrackEnd; i++)
	{
		std::vector<int> vPose;
		//\\ Doc tung vector dac trung (trung binh) cua facetrack.
		//std::string vFaceTrackPath = mFolderPath + mFaceTracksFolder + "/";
		//\\std::string vFaceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), facetrackLength, '0');
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::vector<std::vector<std::vector<int>>> facetrack;
		size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = vNumFeatureStart; j <= vNumFeatureEnd; j++)
		{
			//std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string featureNum = util.leftPad(std::to_string(j), featueLength, '0');
			std::string featureNum = std::to_string(j);
			cv::Mat featureMat = util.readMatBasic(mFolderPath + mFaceTracksFolder + "/" + vFaceTrackName + "/" + mDBFeatureName + featureNum + mFeatureType);
			if (!featureMat.empty())
			{
				std::vector<std::vector<int>> feature = util.convertMatToV2I(featureMat);
				facetrack.push_back(feature);
				//\\ Doc pose tu file.
				cv::Mat poseMat = util.readMatBasic(mFolderPath + mFaceTracksFolder + "/" + vFaceTrackName + "/" + mPoseName + featureNum + mFeatureType);
				int pose = poseMat.at<int>(0, 0);
				vPose.push_back(pose);
			}
		}
		mFacetrackFeatures.push_back(facetrack);
		facetrack.clear();
		mPoses.push_back(vPose);
	}
	result = mFacetrackFeatures.size();
	return result;
}
//\\ Doc cac vector dac trung tu file va dua vao csdl.
int FaceTrackDB::aFeatureReadNotPose1(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFacetrackFeatures.clear();
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
		std::vector<std::vector<std::vector<int>>> facetrack;
		size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = vNumFeatureStart; j <= vNumFeatureEnd; j++)
		{
			//std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string featureNum = mDBFeatureName + util.leftPad(std::to_string(j), featueLength, '0');
			std::string featureNum = mDBFeatureName + std::to_string(j);
			cv::Mat featureMat = util.readMatBasic(mFolderPath + mFaceTracksFolder + "/" + vFaceTrackName + "/" + featureNum + mFeatureType);
			if (!featureMat.empty())
			{
				std::vector<std::vector<int>> feature = util.convertMatToV2I(featureMat);
				facetrack.push_back(feature);
			}
		}
		mFacetrackFeatures.push_back(facetrack);
		facetrack.clear();
	}
	result = mFacetrackFeatures.size();
	return result;
}
//\\ Doc cac vector dac trung tu file va dua vao csdl.
int FaceTrackDB::aFeatureRead2(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFacetrackFeatures.clear();
	//mPoses.clear();
	Utilites util;
	mFolderPath = pFolderPath;
	//int facetrackLength = pNumFaceTrackEnd.length();
	//int featueLength = pNumFeatureEnd.length();
	//\\ Doc tung facetrack.
	//size_t vNumFaceTrackStart = std::atoi(pNumFaceTrackStart.c_str());
	//size_t vNumFaceTrackEnd = std::atoi(pNumFaceTrackEnd.c_str());
	for (size_t i = pNumFaceTrackStart; i <= pNumFaceTrackEnd; i++)
	{
		std::vector<int> vPose;
		//\\ Doc tung vector dac trung (trung binh) cua facetrack.
		//std::string vFaceTrackPath = mFolderPath + mFaceTracksFolder + "/";
		//\\std::string vFaceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), facetrackLength, '0');
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::vector<std::vector<std::vector<int>>> facetrack;
		//size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		//size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = pNumFeatureStart; j <= pNumFeatureEnd; j++)
		{
			//std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string featureNum = util.leftPad(std::to_string(j), featueLength, '0');
			std::string featureNum = std::to_string(j);
			cv::Mat featureMat = util.readMatBasic(mFolderPath + mFaceTracksFolder + "/" + vFaceTrackName + "/" + mDBFeatureName + featureNum + mFeatureType);
			if (!featureMat.empty())
			{
				std::vector<std::vector<int>> feature = util.convertMatToV2I(featureMat);
				facetrack.push_back(feature);
				//\\ Doc pose tu file.
				cv::Mat poseMat = util.readMatBasic(mFolderPath + mFaceTracksFolder + "/" + vFaceTrackName + "/" + mPoseName + featureNum + mFeatureType);
				int pose = poseMat.at<int>(0, 0);
				vPose.push_back(pose);
			}
		}
		mFacetrackFeatures.push_back(facetrack);
		facetrack.clear();
		mPoses.push_back(vPose);
	}
	result = mFacetrackFeatures.size();
	return result;
}
//\\ Doc cac vector dac trung tu file va dua vao csdl.
int FaceTrackDB::aFeatureReadNotPose2(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFacetrackFeatures.clear();
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
		//\\std::string vFaceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), facetrackLength, '0');
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::vector<std::vector<std::vector<int>>> facetrack;
		//size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		//size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = pNumFeatureStart; j <= pNumFeatureEnd; j++)
		{
			//std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string featureNum = mDBFeatureName + util.leftPad(std::to_string(j), featueLength, '0');
			std::string featureNum = mDBFeatureName + std::to_string(j);
			cv::Mat featureMat = util.readMatBasic(mFolderPath + mFaceTracksFolder + "/" + vFaceTrackName + "/" + featureNum + mFeatureType);
			if (!featureMat.empty())
			{
				std::vector<std::vector<int>> feature = util.convertMatToV2I(featureMat);
				facetrack.push_back(feature);
			}
		}
		mFacetrackFeatures.push_back(facetrack);
		facetrack.clear();
	}
	result = mFacetrackFeatures.size();
	return result;
}
//\\ (Use) (1) Doc cac anh  va thong tin tu file.
int FaceTrackDB::aFeatureRead3(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath)
{
	int result = 0;
	//mFileNames.clear();
	//mFacetrackFeatures.clear();
	//mPoses.clear();
	Utilites util;
	mFolderPath = pSourcePath;
	//\\ Doc tung facetrack.
	for (size_t i = pNumFaceTrackStart; i <= pNumFaceTrackEnd; i++)
	{
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::string vFaceTrackPath = mFolderPath + mFaceTracksFolder + "/" + vFaceTrackName + "/";
		std::vector<std::string> vFileNames;
		std::vector<std::vector<std::vector<int>>> vFacetrackFeatures;
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
			vImageMat = util.readMatBasic(vFaceTrackPath + vFileName + mFeatureType);
			vFileNames.push_back(vFileName);
			vPoses.push_back(std::atoi(vPose.c_str()));
			vPoseNames.push_back(vPoseName);
			vFacetrackFeatures.push_back(util.convertMatToV2I(vImageMat));
		}
		ifImage.close();
		ifPose.close();
		ifPoseName.close();

		mFileNames.push_back(vFileNames);
		mFacetrackFeatures.push_back(vFacetrackFeatures);
		mPoses.push_back(vPoses);
		mPoseNames.push_back(vPoseNames);
	}
	result = mFacetrackFeatures.size();
	return result;
}
//\\ (Use) (2) Doc cac anh  va thong tin tu file.
int FaceTrackDB::aFeatureRead4(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath)
{
	int result = 0;
	//mFileNames.clear();
	//mFacetrackFeatures.clear();
	//mTiltPanPoses.clear();
	Utilites util;
	mFolderPath = pSourcePath;
	//\\ Doc tung facetrack.
	for (size_t i = pNumFaceTrackStart; i <= pNumFaceTrackEnd; i++)
	{
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::string vFaceTrackPath = mFolderPath + mFaceTracksFolder + "/" + vFaceTrackName + "/";
		std::vector<std::string> vFileNames;
		std::vector<std::vector<std::vector<int>>> vFacetrackFeatures;
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
			vImageMat = util.readMatBasic(vFaceTrackPath + vFileName + mFeatureType);
			vFileNames.push_back(vFileName);
			vTiltPanPoses.push_back(vPose.c_str());
			vPoseNames.push_back(vPoseName);
			vFacetrackFeatures.push_back(util.convertMatToV2I(vImageMat));
		}
		ifImage.close();
		ifPose.close();
		ifPoseName.close();

		mFileNames.push_back(vFileNames);
		mFacetrackFeatures.push_back(vFacetrackFeatures);
		mTiltPanPoses.push_back(vTiltPanPoses);
		mPoseNames.push_back(vPoseNames);
	}
	result = mFacetrackFeatures.size();
	return result;
}

//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
int FaceTrackDB::aDatabaseInit(std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<int>> pPoses)
{
	int result = -1;
	//mFaceTrackDatabase.clear();
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	const size_t vFaceTrackSize = pFaceTracks.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		facetrackfeatures.push_back(features);
	}
	//\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	std::vector<std::vector<double>> avgFeature = aAvgFeature3(facetrackfeatures, pPoses);
	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesPose1(facetrackfeatures, pPoses);
	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);
		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
int FaceTrackDB::aDatabaseInitNotPose(std::vector<std::vector<cv::Mat>> pFaceTracks)
{
	int result = -1;
	//mFaceTrackDatabase.clear();
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	const size_t vFaceTrackSize = pFaceTracks.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		facetrackfeatures.push_back(features);
	}
	//\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	std::vector<std::vector<double>> avgFeature = aAvgFeatureNotPose3(facetrackfeatures);
	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesNotPose1(facetrackfeatures);
	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);
		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
	}
	result = mFaceTrackDatabase.size();
	return result;
}

//\\ TiltPanPose = Tilt + Pan.
int FaceTrackDB::aSumTiltPanPose()
{
	Utilites util;
	for (size_t i = 0; i < mTiltPanPoses.size(); i++)
	{
		for (size_t j = 0; j < mTiltPanPoses[i].size(); j++)
		{
			//std::vector<std::string> vTiltPan = util.splitString(mTiltPanPoses[i][j], ";");
			//int vTilt = std::atoi(vTiltPan[0].c_str());
			//int vPan = std::atoi(vTiltPan[1].c_str());
			int vPose = std::atoi(mTiltPanPoses[i][j].c_str());
			vPose = vPose / 1000 + vPose % 1000;
			mTiltPanPoses[i][j] = std::to_string(vPose);
		}
	}
	return 0;
}

//\\ (Use) Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceTrackDB::aDatabaseInitPoseNormalize1(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile)
{
	int result = -1;
	//mFaceTrackDatabase.clear();
	mFileNames = pFileNames;
	mPoses = pPoses;
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mDBFeatureFolder);

	const size_t vFaceTrackSize = pFacetrackFeatures.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		faceTrackNames.push_back(faceTrackName);
	}

	//\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	std::vector<std::vector<double>> avgFeature = aAvgFeature3(pFacetrackFeatures, pPoses);

	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesPose1(pFacetrackFeatures, pPoses);

	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack. Va ghi ra csdl.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		util.makeDir(vFolderPath + "\\" + mDBFeatureFolder + "\\" + faceTrackNames[i]);
		//\\ Chuan hoa cac vector dac trung trung binh.
		dbfeatures.clear();

		std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);

		////\\ Test. Khong chuan hoa cho u (vector dac trung trung binh toan bo anh).
		//std::vector<std::vector<double>> featureSub = facetrackfeature[i];

		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
		//\\ Ghi ra file: cac vector dac trung da duoc chuan hoa (dac trung trung binh) cua facetrack thu i.
		if (pIsSaveToFile)
		{
			//\\ Tinh tong pose cho trung facetrac.
			int vSumPose = 0;
			for (size_t j = 0; j < pPoses[i].size(); j++)
			{
				vSumPose += pPoses[i][j];
			}
			std::string vSaveFTPath = mFolderPath + mDBFeatureFolder + "/" + faceTrackNames[i] + "/";
			std::ofstream ofImage(vSaveFTPath + mImageName + mFileType);
			std::ofstream ofPose(vSaveFTPath + mPoseName + mFileType);
			size_t featuressize = dbfeatures.size();
			for (size_t j = 0; j < featuressize; j++)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat face = util.convertV2DToMat(dbfeatures[j], (int)dbfeatures[j][0].size(), (int)dbfeatures[j].size());
				std::string vDBname = mDBFeatureName + std::to_string(j);
				//\\ Ghi vector trung binh.
				util.writeMatBasic(face, vSaveFTPath + vDBname + mDBFeatureType);
				//\\ Ghi ten vector trung binh.
				ofImage << vDBname;
				ofPose << vSumPose;
				//\\ Ghi file text.
				util.writeMatDouble(face, vSaveFTPath + vDBname + ".txt");
			}
			ofImage.close();
			ofPose.close();
		}
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ (Use) Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceTrackDB::aDatabaseInitNotPose1(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile)
{
	int result = -1;
	//mFaceTrackDatabase.clear();
	mFileNames = pFileNames;
	mPoses = pPoses;
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mDBFeatureFolder);

	const size_t vFaceTrackSize = pFacetrackFeatures.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		faceTrackNames.push_back(faceTrackName);
	}

	//\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	std::vector<std::vector<double>> avgFeature = aAvgFeatureNotPose3(pFacetrackFeatures);
	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesNotPose1(pFacetrackFeatures);
	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		util.makeDir(vFolderPath + "\\" + mDBFeatureFolder + "\\" + faceTrackNames[i]);
		//\\ Chuan hoa cac vector dac trung trung binh.
		dbfeatures.clear();
		std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);
		
		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
		//\\ Ghi ra file: cac vector dac trung da duoc chuan hoa (dac trung trung binh) cua facetrack thu i.
		if (pIsSaveToFile)
		{
			//\\ Tinh tong pose cho trung facetrac.
			int vSumPose = 0;
			for (size_t j = 0; j < pPoses[i].size(); j++)
			{
				vSumPose += pPoses[i][j];
			}
			std::string vSaveFTPath = mFolderPath + mDBFeatureFolder + "/" + faceTrackNames[i] + "/";
			std::ofstream ofImage(vSaveFTPath + mImageName + mFileType);
			std::ofstream ofPose(vSaveFTPath + mPoseName + mFileType);
			size_t featuressize = dbfeatures.size();
			for (size_t j = 0; j < featuressize; j++)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat face = util.convertV2DToMat(dbfeatures[j], (int)dbfeatures[j][0].size(), (int)dbfeatures[j].size());
				std::string vDBname = mDBFeatureName + std::to_string(j);
				//\\ Ghi vector trung binh.
				util.writeMatBasic(face, vSaveFTPath + vDBname + mDBFeatureType);
				//\\ Ghi ten vector trung binh.
				ofImage << vDBname;
				ofPose << vSumPose;
				//\\ Ghi file text.
				util.writeMatDouble(face, vSaveFTPath + vDBname + ".txt");
			}
			ofImage.close();
			ofPose.close();
		}
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ (Use) Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceTrackDB::aDatabaseInitNotNormalize1(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile)
{
	int result = -1;
	//mFaceTrackDatabase.clear();
	mFileNames = pFileNames;
	mPoses = pPoses;
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mDBFeatureFolder);

	const size_t vFaceTrackSize = pFacetrackFeatures.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		faceTrackNames.push_back(faceTrackName);
	}

	////\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	//std::vector<std::vector<double>> avgFeature = aAvgFeature(pFacetrackFeatures, pPoses, pSumPose);

	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesPose1(pFacetrackFeatures, pPoses);

	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack. Va ghi ra csdl.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		util.makeDir(vFolderPath + "\\" + mDBFeatureFolder + "\\" + faceTrackNames[i]);
		//\\ Chuan hoa cac vector dac trung trung binh.
		dbfeatures.clear();

		//std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);

		//\\ Test. Khong chuan hoa cho u (vector dac trung trung binh toan bo anh).
		std::vector<std::vector<double>> featureSub = facetrackfeature[i];

		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
		//\\ Ghi ra file: cac vector dac trung da duoc chuan hoa (dac trung trung binh) cua facetrack thu i.
		if (pIsSaveToFile)
		{
			//\\ Tinh tong pose cho trung facetrac.
			int vSumPose = 0;
			for (size_t j = 0; j < pPoses[i].size(); j++)
			{
				vSumPose += pPoses[i][j];
			}
			std::string vSaveFTPath = mFolderPath + mDBFeatureFolder + "/" + faceTrackNames[i] + "/";
			std::ofstream ofImage(vSaveFTPath + mImageName + mFileType);
			std::ofstream ofPose(vSaveFTPath + mPoseName + mFileType);
			size_t featuressize = dbfeatures.size();
			for (size_t j = 0; j < featuressize; j++)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat face = util.convertV2DToMat(dbfeatures[j], (int)dbfeatures[j][0].size(), (int)dbfeatures[j].size());
				std::string vDBname = mDBFeatureName + std::to_string(j);
				//\\ Ghi vector trung binh.
				util.writeMatBasic(face, vSaveFTPath + vDBname + mDBFeatureType);
				//\\ Ghi ten vector trung binh.
				ofImage << vDBname;
				ofPose << vSumPose;
				//\\ Ghi file text.
				util.writeMatDouble(face, vSaveFTPath + vDBname + ".txt");
			}
			ofImage.close();
			ofPose.close();
		}
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ (Use) Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceTrackDB::aDatabaseInitNotPoseNotNormalize1(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<int>> pPoses, std::string pFolderPath, bool pIsSaveToFile)
{
	int result = -1;
	//mFaceTrackDatabase.clear();
	mFileNames = pFileNames;
	mPoses = pPoses;
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mDBFeatureFolder);

	const size_t vFaceTrackSize = pFacetrackFeatures.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		faceTrackNames.push_back(faceTrackName);
	}

	////\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	//std::vector<std::vector<double>> avgFeature = aAvgFeatureNotPose(pFacetrackFeatures);

	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesNotPose1(pFacetrackFeatures);
	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		util.makeDir(vFolderPath + "\\" + mDBFeatureFolder + "\\" + faceTrackNames[i]);
		//\\ Chuan hoa cac vector dac trung trung binh.
		dbfeatures.clear();

		//std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);

		//\\ Test. Khong chuan hoa cho u (vector dac trung trung binh toan bo anh).
		std::vector<std::vector<double>>featureSub = facetrackfeature[i];

		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
		//\\ Ghi ra file: cac vector dac trung da duoc chuan hoa (dac trung trung binh) cua facetrack thu i.
		if (pIsSaveToFile)
		{
			//\\ Tinh tong pose cho trung facetrac.
			int vSumPose = 0;
			for (size_t j = 0; j < pPoses[i].size(); j++)
			{
				vSumPose += pPoses[i][j];
			}
			std::string vSaveFTPath = mFolderPath + mDBFeatureFolder + "/" + faceTrackNames[i] + "/";
			std::ofstream ofImage(vSaveFTPath + mImageName + mFileType);
			std::ofstream ofPose(vSaveFTPath + mPoseName + mFileType);
			size_t featuressize = dbfeatures.size();
			for (size_t j = 0; j < featuressize; j++)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat face = util.convertV2DToMat(dbfeatures[j], (int)dbfeatures[j][0].size(), (int)dbfeatures[j].size());
				std::string vDBname = mDBFeatureName + std::to_string(j);
				//\\ Ghi vector trung binh.
				util.writeMatBasic(face, vSaveFTPath + vDBname + mDBFeatureType);
				//\\ Ghi ten vector trung binh.
				ofImage << vDBname;
				ofPose << vSumPose;
				//\\ Ghi file text.
				util.writeMatDouble(face, vSaveFTPath + vDBname + ".txt");
			}
			ofImage.close();
			ofPose.close();
		}
	}
	result = mFaceTrackDatabase.size();
	return result;
}

//\\ (Use) (2) Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceTrackDB::aDatabaseInitPoseNormalize2(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, std::string pFolderPath, bool pIsSaveToFile)
{
	int result = -1;
	mFaceTrackDatabase.clear();
	mFileNames = pFileNames;
	mTiltPanPoses = pTiltPanPoses;
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mDBFeatureFolder);

	const size_t vFaceTrackSize = pFacetrackFeatures.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		faceTrackNames.push_back(faceTrackName);
	}

	//\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	std::vector<std::vector<double>> avgFeature = aAvgFeature5(pFacetrackFeatures, mTiltPanPoses);

	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesPose2(pFacetrackFeatures, mTiltPanPoses);

	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack. Va ghi ra csdl.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		util.makeDir(vFolderPath + "\\" + mDBFeatureFolder + "\\" + faceTrackNames[i]);
		//\\ Chuan hoa cac vector dac trung trung binh.
		dbfeatures.clear();

		std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);

		////\\ Test. Khong chuan hoa cho u (vector dac trung trung binh toan bo anh).
		//std::vector<std::vector<double>> featureSub = facetrackfeature[i];

		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
		//\\ Ghi ra file: cac vector dac trung da duoc chuan hoa (dac trung trung binh) cua facetrack thu i.
		if (pIsSaveToFile)
		{
			//\\ Tinh tong pose cho trung facetrac.
			int vSumPose = 0;
			for (size_t j = 0; j < mTiltPanPoses[i].size(); j++)
			{
				//std::vector<std::string> vSPose = util.splitString(mTiltPanPoses[i][j], ";");
				//for (size_t p = 0; p < vSPose.size(); p++)
				//{
				//	vSumPose += std::atoi(vSPose[p].c_str());
				//}
				int vPose = std::atoi(mTiltPanPoses[i][j].c_str());
				vSumPose += vPose / 1000 + vPose % 1000;
			}
			std::string vSaveFTPath = mFolderPath + mDBFeatureFolder + "/" + faceTrackNames[i] + "/";
			std::ofstream ofImage(vSaveFTPath + mImageName + mFileType);
			std::ofstream ofPose(vSaveFTPath + mTiltPanPoseName + mFileType);
			size_t featuressize = dbfeatures.size();
			for (size_t j = 0; j < featuressize; j++)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat face = util.convertV2DToMat(dbfeatures[j], (int)dbfeatures[j][0].size(), (int)dbfeatures[j].size());
				std::string vDBname = mDBFeatureName + std::to_string(j);
				//\\ Ghi vector trung binh.
				util.writeMatBasic(face, vSaveFTPath + vDBname + mDBFeatureType);
				//\\ Ghi ten vector trung binh.
				ofImage << vDBname;
				ofPose << vSumPose;
				//\\ Ghi file text.
				util.writeMatDouble(face, vSaveFTPath + vDBname + ".txt");
			}
			ofImage.close();
			ofPose.close();
		}
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ (Use) (2) Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceTrackDB::aDatabaseInitNotPose2(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, std::string pFolderPath, bool pIsSaveToFile)
{
	int result = -1;
	mFaceTrackDatabase.clear();
	mFileNames = pFileNames;
	mTiltPanPoses = pTiltPanPoses;
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mDBFeatureFolder);

	const size_t vFaceTrackSize = pFacetrackFeatures.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		faceTrackNames.push_back(faceTrackName);
	}

	//\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	std::vector<std::vector<double>> avgFeature = aAvgFeatureNotPose3(pFacetrackFeatures);
	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesNotPose1(pFacetrackFeatures);
	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		util.makeDir(vFolderPath + "\\" + mDBFeatureFolder + "\\" + faceTrackNames[i]);
		//\\ Chuan hoa cac vector dac trung trung binh.
		dbfeatures.clear();
		std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);

		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
		//\\ Ghi ra file: cac vector dac trung da duoc chuan hoa (dac trung trung binh) cua facetrack thu i.
		if (pIsSaveToFile)
		{
			//\\ Tinh tong pose cho trung facetrac.
			int vSumPose = 0;
			for (size_t j = 0; j < mTiltPanPoses[i].size(); j++)
			{
				//std::vector<std::string> vSPose = util.splitString(mTiltPanPoses[i][j], ";");
				//vSumPose += std::atoi(vSPose[0].c_str()) + std::atoi(vSPose[1].c_str());
				int vPose = std::atoi(mTiltPanPoses[i][j].c_str());
				vSumPose += vPose / 1000 + vPose % 1000;
			}
			std::string vSaveFTPath = mFolderPath + mDBFeatureFolder + "/" + faceTrackNames[i] + "/";
			std::ofstream ofImage(vSaveFTPath + mImageName + mFileType);
			std::ofstream ofPose(vSaveFTPath + mTiltPanPoseName + mFileType);
			size_t featuressize = dbfeatures.size();
			for (size_t j = 0; j < featuressize; j++)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat face = util.convertV2DToMat(dbfeatures[j], (int)dbfeatures[j][0].size(), (int)dbfeatures[j].size());
				std::string vDBname = mDBFeatureName + std::to_string(j);
				//\\ Ghi vector trung binh.
				util.writeMatBasic(face, vSaveFTPath + vDBname + mDBFeatureType);
				//\\ Ghi ten vector trung binh.
				ofImage << vDBname;
				ofPose << vSumPose;
				//\\ Ghi file text.
				util.writeMatDouble(face, vSaveFTPath + vDBname + ".txt");
			}
			ofImage.close();
			ofPose.close();
		}
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ (Use) (2) Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceTrackDB::aDatabaseInitNotNormalize2(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, std::string pFolderPath, bool pIsSaveToFile)
{
	int result = -1;
	mFaceTrackDatabase.clear();
	mFileNames = pFileNames;
	mTiltPanPoses = pTiltPanPoses;
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mDBFeatureFolder);

	const size_t vFaceTrackSize = pFacetrackFeatures.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		faceTrackNames.push_back(faceTrackName);
	}

	////\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	//std::vector<std::vector<double>> avgFeature = aAvgFeature5(pFacetrackFeatures, mTiltPanPoses, pSumPose);

	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesPose2(pFacetrackFeatures, mTiltPanPoses);

	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack. Va ghi ra csdl.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		util.makeDir(vFolderPath + "\\" + mDBFeatureFolder + "\\" + faceTrackNames[i]);
		//\\ Chuan hoa cac vector dac trung trung binh.
		dbfeatures.clear();

		//std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);

		//\\ Test. Khong chuan hoa cho u (vector dac trung trung binh toan bo anh).
		std::vector<std::vector<double>> featureSub = facetrackfeature[i];

		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
		//\\ Ghi ra file: cac vector dac trung da duoc chuan hoa (dac trung trung binh) cua facetrack thu i.
		if (pIsSaveToFile)
		{
			//\\ Tinh tong pose cho trung facetrac.
			int vSumPose = 0;
			for (size_t j = 0; j < mTiltPanPoses[i].size(); j++)
			{
				//std::vector<std::string> vSPose = util.splitString(mTiltPanPoses[i][j], ";");
				//for (size_t p = 0; p < vSPose.size(); p++)
				//{
				//	vSumPose += std::atoi(vSPose[p].c_str());
				//}
				int vPose = std::atoi(mTiltPanPoses[i][j].c_str());
				vSumPose += vPose / 1000 + vPose % 1000;
			}
			std::string vSaveFTPath = mFolderPath + mDBFeatureFolder + "/" + faceTrackNames[i] + "/";
			std::ofstream ofImage(vSaveFTPath + mImageName + mFileType);
			std::ofstream ofPose(vSaveFTPath + mPoseName + mFileType);
			size_t featuressize = dbfeatures.size();
			for (size_t j = 0; j < featuressize; j++)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat face = util.convertV2DToMat(dbfeatures[j], (int)dbfeatures[j][0].size(), (int)dbfeatures[j].size());
				std::string vDBname = mDBFeatureName + std::to_string(j);
				//\\ Ghi vector trung binh.
				util.writeMatBasic(face, vSaveFTPath + vDBname + mDBFeatureType);
				//\\ Ghi ten vector trung binh.
				ofImage << vDBname;
				ofPose << vSumPose;
				//\\ Ghi file text.
				util.writeMatDouble(face, vSaveFTPath + vDBname + ".txt");
			}
			ofImage.close();
			ofPose.close();
		}
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ (Use) (2) Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceTrackDB::aDatabaseInitNotPoseNotNormalize2(std::vector<std::vector<std::vector<std::vector<int>>>> pFacetrackFeatures, std::vector<std::vector<std::string>> pFileNames, std::vector<std::vector<std::string>> pTiltPanPoses, std::string pFolderPath, bool pIsSaveToFile)
{
	int result = -1;
	mFaceTrackDatabase.clear();
	mFileNames = pFileNames;
	mTiltPanPoses = pTiltPanPoses;
	Utilites util;
	//\\ Tao thu muc.
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mDBFeatureFolder);

	const size_t vFaceTrackSize = pFacetrackFeatures.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		//\\std::string faceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), numlengthFaceTrack, '0');
		std::string faceTrackName = mFaceTrackName + std::to_string(i);
		faceTrackNames.push_back(faceTrackName);
	}

	////\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	//std::vector<std::vector<double>> avgFeature = aAvgFeatureNotPose(pFacetrackFeatures);

	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeaturesNotPose1(pFacetrackFeatures);
	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack.
	std::vector<std::vector<std::vector<double>>> dbfeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		util.makeDir(vFolderPath + "\\" + mDBFeatureFolder + "\\" + faceTrackNames[i]);
		//\\ Chuan hoa cac vector dac trung trung binh.
		dbfeatures.clear();

		//std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);

		//\\ Test. Khong chuan hoa cho u (vector dac trung trung binh toan bo anh).
		std::vector<std::vector<double>>featureSub = facetrackfeature[i];

		dbfeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(dbfeatures);
		//\\ Ghi ra file: cac vector dac trung da duoc chuan hoa (dac trung trung binh) cua facetrack thu i.
		if (pIsSaveToFile)
		{
			//\\ Tinh tong pose cho trung facetrac.
			int vSumPose = 0;
			for (size_t j = 0; j < mTiltPanPoses[i].size(); j++)
			{
				//std::vector<std::string> vSPose = util.splitString(mTiltPanPoses[i][j], ";");
				//vSumPose += std::atoi(vSPose[0].c_str()) + std::atoi(vSPose[1].c_str());
				int vPose = std::atoi(mTiltPanPoses[i][j].c_str());
				vSumPose += vPose / 1000 + vPose % 1000;
			}
			std::string vSaveFTPath = mFolderPath + mDBFeatureFolder + "/" + faceTrackNames[i] + "/";
			std::ofstream ofImage(vSaveFTPath + mImageName + mFileType);
			std::ofstream ofPose(vSaveFTPath + mPoseName + mFileType);
			size_t featuressize = dbfeatures.size();
			for (size_t j = 0; j < featuressize; j++)
			{
				//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
				cv::Mat face = util.convertV2DToMat(dbfeatures[j], (int)dbfeatures[j][0].size(), (int)dbfeatures[j].size());
				std::string vDBname = mDBFeatureName + std::to_string(j);
				//\\ Ghi vector trung binh.
				util.writeMatBasic(face, vSaveFTPath + vDBname + mDBFeatureType);
				//\\ Ghi ten vector trung binh.
				ofImage << vDBname;
				ofPose << vSumPose;
				//\\ Ghi file text.
				util.writeMatDouble(face, vSaveFTPath + vDBname + ".txt");
			}
			ofImage.close();
			ofPose.close();
		}
	}
	result = mFaceTrackDatabase.size();
	return result;
}

//\\ Doc cac vector dac trung tu file va dua vao csdl.
int FaceTrackDB::aDatabaseRead1(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFaceTrackDatabase.clear();
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
		std::vector<std::vector<std::vector<double>>> facetrack;
		size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = vNumFeatureStart; j <= vNumFeatureEnd; j++)
		{
			//std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string fNum = util.leftPad(std::to_string(j), featueLength, '0');
			std::string fNum = std::to_string(j);
			cv::Mat featureMat = util.readMatBasic(mFolderPath + mDBFeatureFolder + "/" + vFaceTrackName + "/" + mDBFeatureName + fNum + mDBFeatureType);
			std::vector<std::vector<double>> feature = util.convertMatToV2D(featureMat);
			facetrack.push_back(feature);
		}
		mFaceTrackDatabase.push_back(facetrack);
		facetrack.clear();
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ Doc cac vector dac trung tu file va dua vao csdl.
int FaceTrackDB::aDatabaseRead2(int pNumFaceTrackStart, int pNumFaceTrackEnd, int pNumFeatureStart, int pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	//mFaceTrackDatabase.clear();
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
		//\\std::string vFaceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), facetrackLength, '0');
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::vector<std::vector<std::vector<double>>> facetrack;
		//size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		//size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = pNumFeatureStart; j <= pNumFeatureEnd; j++)
		{
			//std::string vFeaturePath = vFaceTrackPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
			//\\std::string fNum = util.leftPad(std::to_string(j), featueLength, '0');
			std::string fNum = std::to_string(j);
			cv::Mat featureMat = util.readMatBasic(mFolderPath + mDBFeatureFolder + "/" + vFaceTrackName + "/" + mDBFeatureName + fNum + mDBFeatureType);
			std::vector<std::vector<double>> feature = util.convertMatToV2D(featureMat);
			facetrack.push_back(feature);
		}
		mFaceTrackDatabase.push_back(facetrack);
		facetrack.clear();
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ (Use) Doc cac vector dac trung tu file va dua vao csdl.
int FaceTrackDB::aDatabaseRead3(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath)
{
	int result = 0;
	//mFileNames.clear();
	//mFaceTrackDatabase.clear();
	Utilites util;
	mFolderPath = pSourcePath;
	//\\ Doc tung facetrack.
	for (size_t i = pNumFaceTrackStart; i <= pNumFaceTrackEnd; i++)
	{
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::string vDBFeaturePath = mFolderPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
		std::vector<std::string> vFileNames;
		std::vector<std::vector<std::vector<double>>> vFaceTrackDatabases;
		std::vector<int> vPoses;
		//\\ Doc ten file anh va pose tuong ung.
		std::ifstream ifImage(vDBFeaturePath + mImageName + mFileType);
		std::ifstream ifPose(vDBFeaturePath + mPoseName + mFileType);
		std::string vFileName;
		std::string vPose;
		cv::Mat vImageMat;
		while (!ifImage.eof())
		{
			std::getline(ifImage, vFileName);
			std::getline(ifPose, vPose);
			vImageMat = util.readMatBasic(vDBFeaturePath + vFileName + mDBFeatureType);
			vFaceTrackDatabases.push_back(util.convertMatToV2D(vImageMat));
			vFileNames.push_back(vFileName);
			vPoses.push_back(std::atoi(vPose.c_str()));
		}
		ifImage.close();

		mFileNames.push_back(vFileNames);
		mFaceTrackDatabase.push_back(vFaceTrackDatabases);
		mPoses.push_back(vPoses);
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ (Use) Doc cac vector dac trung trung binh va doc tat ca feature tuong ung tu file va dua vao csdl.
int FaceTrackDB::aDatabaseAndFeatureRead(int pNumFaceTrackStart, int pNumFaceTrackEnd, std::string pSourcePath, std::string pFeaturePath)
{
	int result = 0;
	//mFileNames.clear();
	//mFaceTrackDatabase.clear();
	Utilites util;
	mFolderPath = pSourcePath;
	//\\ Doc tung facetrack.
	for (size_t i = pNumFaceTrackStart; i <= pNumFaceTrackEnd; i++)
	{
		std::string vFaceTrackName = mFaceTrackName + std::to_string(i);
		std::string vDBFeaturePath = mFolderPath + mDBFeatureFolder + "/" + vFaceTrackName + "/";
		std::vector<std::string> vFileNames;
		std::vector<std::vector<std::vector<double>>> vFaceTrackDatabases;
		std::vector<int> vPoses;
		std::vector<std::string> vPoseNames;
		std::ifstream ifImage(vDBFeaturePath + mImageName + mFileType);
		//std::ifstream ifPose(vDBFeaturePath + mPoseName + mFileType);
		std::string vFileName;
		std::string vPose;
		std::string vPoseName;
		cv::Mat vImageMat;
		while (!ifImage.eof())
		{
			std::getline(ifImage, vFileName);
			//Bo\\
			//std::getline(ifPose, vPose);
			////\\ Doc ten file anh va pose tuong ung cua csdl.
			//vFileNames.push_back(vFileName);
			//vPoses.push_back(std::atoi(vPose.c_str()));
			vImageMat = util.readMatBasic(vDBFeaturePath + vFileName + mDBFeatureType);
			vFaceTrackDatabases.push_back(util.convertMatToV2D(vImageMat));
		}
		ifImage.close();
		//ifPose.close();
		
		//\\ Doc tat ca dac trung tuong ung vao database.
		std::vector<std::vector<std::vector<int>>> vFacetrackFeatures;
		std::string vFeaturePath = pFeaturePath + mFaceTracksFolder + "/" + vFaceTrackName + "/";
		ifImage = std::ifstream(vFeaturePath + mImageName + mFileType);
		std::ifstream ifPose = std::ifstream(vFeaturePath + mPoseName + mFileType);
		std::ifstream ifPoseName(vFeaturePath + mPoseNameName + mFileType);
		while (!ifImage.eof())
		{
			std::getline(ifImage, vFileName);
			std::getline(ifPose, vPose);
			std::getline(ifPoseName, vPoseName);
			//\\ Doc ten file anh va pose tuong ung cua feature.
			vFileNames.push_back(vFileName);
			vPoses.push_back(std::atoi(vPose.c_str()));
			vPoseNames.push_back(vPoseName);
			vImageMat = util.readMatBasic(vFeaturePath + vFileName + mFeatureType);
			vFacetrackFeatures.push_back(util.convertMatToV2I(vImageMat));
		}
		ifImage.close();
		ifPose.close();
		ifPoseName.close();
		//\\ Sap xep cac vector dac trung theo pose giam dan.
		size_t vPosesSize = vPoses.size();
		for (size_t j = 0; j < vPosesSize - 1; j++)
		{
			for (size_t k = j + 1; k < vPosesSize; k++)
			{
				if (vPoses[j] < vPoses[k])
				{
					int tempPose = vPoses[j];
					vPoses[j] = vPoses[k];
					vPoses[k] = tempPose;

					std::string tempName = vFileNames[j];
					vFileNames[j] = vFileNames[k];
					vFileNames[k] = tempName;

					std::string tempPoseName = vPoseNames[j];
					vPoseNames[j] = vPoseNames[k];
					vPoseNames[k] = tempPoseName;

					std::vector<std::vector<int>> tempMat = vFacetrackFeatures[j];
					vFacetrackFeatures[j] = vFacetrackFeatures[k];
					vFacetrackFeatures[k] = tempMat;
				}
			}
		}
		mFileNames.push_back(vFileNames);
		mPoses.push_back(vPoses);
		mPoseNames.push_back(vPoseNames);
		mFaceTrackDatabase.push_back(vFaceTrackDatabases);
		mFacetrackFeatures.push_back(vFacetrackFeatures);
	}

	result = mFaceTrackDatabase.size();
	return result;
}

//\\ Sap xep danh sach facetrack theo facetrack truy van. Moi facetrack duoc dai dien bang 1 vector dac trung trung binh.
std::vector<std::vector<std::vector<std::vector<double>>>> FaceTrackDB::aMeanCosMatching(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks)
{
	std::vector<std::vector<std::vector<std::vector<double>>>> result;
	std::vector<double> resultmeancos;
	//\\ Tinh khoang cach mean-cos giua 2 vector dac trung trung binh.
	double meancos = 0;
	//\\ Lap qua trung facetrack de tinh khoang cach.
	size_t facetracksize = pFaceTracks.size();
	for (size_t i = 0; i < facetracksize; i++)
	{
		meancos = aCosine1(pFaceTrack[0], pFaceTracks[i][0]);
		std::vector<double> resultmeancostemp;
		std::vector<std::vector<std::vector<std::vector<double>>>> resulttemp;

		size_t j = 0;
		bool find = true;
		//\\ Chen gia tri menacos vua tinh vao danh sach temp.
		while (j < resultmeancos.size())
		{
			if (find && meancos < resultmeancos[j])
			{
				resultmeancostemp.push_back(meancos);
				resulttemp.push_back(pFaceTracks[i]);
				find = false;
			}
			resultmeancostemp.push_back(resultmeancos[j]);
			resulttemp.push_back(result[j]);
			j++;
		}
		//\\ Khong tim thay cai nao lon hon meancos.
		if (find)
		{
			resultmeancostemp.push_back(meancos);
			resulttemp.push_back(pFaceTracks[i]);
		}
		//\\ Gan danh sach temp cho danh sach ket qua.
		resultmeancos = resultmeancostemp;
		resultmeancostemp.clear();
		result = resulttemp;
		resulttemp.clear();
	}
	return result;
}
//\\ Sap xep danh sach facetrack theo facetrack truy van. Moi facetrack duoc dai dien bang 1 vector dac trung trung binh.
std::vector<int> FaceTrackDB::aMeanCosMatchingIndex1(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks)
{
	std::vector<int> result;
	if (pFaceTracks.size() == 0)
		return result;

	std::vector<double> resultmeancos;
	//\\ Tinh khoang cach mean-cos giua 2 vector dac trung trung binh.
	double meancos;
	//\\ Lap qua trung facetrack de tinh khoang cach.
	size_t facetracksize = pFaceTracks.size();

	ofstream of("Doc/Matching.txt", std::ofstream::app);
	of << "aCosine: ";

	//\\ Lap qua tung vector dac trung.
	for (size_t j = 0; j < pFaceTrack.size(); j++)
	{
		//\\ Lap qua tung face trac.
		for (size_t i = 0; i < facetracksize; i++)
		{
			//\\ Neu so luong vector dac trung cua query lon hon facetrac thu i thi bo qua.
			if (j >= pFaceTracks[i].size())
				continue;

			meancos = aCosine1(pFaceTrack[j], pFaceTracks[i][j]);

			//of << std::to_string(i) + "(" << std::to_string(meancos) << ") ";

			std::vector<double> resultmeancostemp;
			std::vector<int> resulttemp;
			size_t j = 0;
			bool find = true;
			//\\ Chen gia tri menacos vua tinh vao danh sach temp.
			while (j < resultmeancos.size())
			{
				if (find && meancos > resultmeancos[j])
				{
					resultmeancostemp.push_back(meancos);
					resulttemp.push_back(i);
					find = false;
				}
				resultmeancostemp.push_back(resultmeancos[j]);
				resulttemp.push_back(result[j]);
				j++;
			}
			//\\ Khong tim thay cai nao lon hon meancos.
			if (find)
			{
				resultmeancostemp.push_back(meancos);
				resulttemp.push_back(i);
			}
			//\\ Gan danh sach temp cho danh sach ket qua.
			resultmeancos = resultmeancostemp;
			resultmeancostemp.clear();
			result = resulttemp;
			resulttemp.clear();
		}

		//\\ Cach kiem tra: Giu lai thu tu so khop cua facetrack.
		for (size_t k = 0; k < result.size(); k++)
		{
			int vFaceTrackIndex = result[k];
			of << std::to_string(vFaceTrackIndex) + "(" + std::to_string(resultmeancos[k]) + ") ";
		}
		//\\ End. Cach kiem tra.

		of << std::endl;
	}
	of << endl;
	of.close();

	return result;
}
//\\ Sap xep danh sach vector dac trung trung binh.
std::vector<int> FaceTrackDB::aMeanCosMatchingIndex2(std::vector<std::vector<double>> pFeature, std::vector<std::vector<std::vector<double>>> pFeatures)
{
	std::vector<int> result;
	if (pFeatures.size() == 0)
		return result;
	std::vector<double> resultmeancos;
	//\\ Tinh khoang cach mean-cos giua 2 vector dac trung trung binh.
	double meancos;
	//\\ Lap qua trung facetrack de tinh khoang cach.
	size_t vFeatureSize = pFeatures.size();

	ofstream of("Doc/Matching.txt", std::ofstream::app);
	of << "aCosine: ";

	for (size_t i = 0; i < vFeatureSize; i++)
	{
		meancos = aCosine1(pFeature, pFeatures[i]);

		of << std::to_string(i) + "(" << std::to_string(meancos) << ") ";

		std::vector<double> resultmeancostemp;
		std::vector<int> resulttemp;
		size_t j = 0;
		bool find = true;
		//\\ Chen gia tri menacos vua tinh vao danh sach temp.
		while (j < resultmeancos.size())
		{
			if (find && meancos > resultmeancos[j])
			{
				resultmeancostemp.push_back(meancos);
				resulttemp.push_back(i);
				find = false;
			}
			resultmeancostemp.push_back(resultmeancos[j]);
			resulttemp.push_back(result[j]);
			j++;
		}
		//\\ Khong tim thay cai nao lon hon meancos.
		if (find)
		{
			resultmeancostemp.push_back(meancos);
			resulttemp.push_back(i);
		}
		//\\ Gan danh sach temp cho danh sach ket qua.
		resultmeancos = resultmeancostemp;
		resultmeancostemp.clear();
		result = resulttemp;
		resulttemp.clear();
	}

	of << endl;
	of.close();

	return result;
}
//\\ (Use) (1,2) Sap xep danh sach facetrack theo facetrack truy van.
std::vector<int> FaceTrackDB::aMeanCosMatchingIndex3(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks, std::vector<std::vector<std::vector<int>>> pFeatureFaceTrack, std::vector<std::vector<std::vector<std::vector<int>>>> pFeatureFaceTracks, std::vector<std::string> pPoseName, std::vector<std::vector<std::string>> pPoseNames, int pCountMax)
{
	std::vector<int> result;
	if (pFaceTracks.size() == 0)
		return result;

	Utilites util;
	size_t facetracksize = pFaceTracks.size();
	//std::vector<int> vFaceTrackMatch(facetracksize);
	std::vector<double> vFaceTrackMatch(facetracksize);
	std::vector<int> vFaceTrack(facetracksize);
	std::vector<double> resultmeancos;
	std::vector<int> resultDB;
	//\\ Tinh khoang cach mean-cos giua 2 vector dac trung trung binh.
	double meancos;
	//\\ Lap qua trung facetrack de tinh khoang cach.

	int vFolderPathIndex = mFolderPath.rfind("/Pose/");
	if (vFolderPathIndex == -1)
	{
		vFolderPathIndex = mFolderPath.rfind("/NotPose/");
	}
	std::string vSPose = mFolderPath.substr(vFolderPathIndex);
	vSPose = util.replaceAll(vSPose, "/", "");
	std::string vFacetrackPath = mFolderPath.substr(0, vFolderPathIndex + 1);
	//vFacetrackPath = mFolderPath.substr(vFolderPathIndex);
	//vFacetrackPath = mFolderPath.substr(vFolderPathIndex) + vFacetrackPath;
	ofstream of(vFacetrackPath + "Matching.txt", std::ofstream::app);
	ofstream ofDb(vFacetrackPath + "Matching" + vSPose + ".txt", std::ofstream::app);
	of << "aCosine: ";
	ofDb << "aCosine: ";

	//\\ Lap qua tung vector dac trung trung binh.
	for (size_t f = 0; f < pFaceTrack.size(); f++)
	{
		result.clear();
		resultmeancos.clear();
		//\\ Lap qua tung face track.
		for (size_t i = 0; i < facetracksize; i++)
		{
			//\\ Neu so luong vector dac trung cua query lon hon facetrac thu i thi bo qua.
			if (f >= pFeatureFaceTracks[i].size())
				continue;

			meancos = aCosine1(pFaceTrack[f], pFaceTracks[i][f]);
			//meancos = aEuclid(pFaceTrack[f], pFaceTracks[i][f]);
			//\\ Khoi tao thu tu facetrack.aEuclid
			vFaceTrack[i] = i;

			////\\ Cach chinh:
			////\\ Giu lai gia tri so khop cua facetrack.
			//vFaceTrackMatch[i] += meancos;
			//of << std::to_string(i) + "(" << std::to_string(meancos) << ") ";
			//\\ End. Cach chinh.

			std::vector<double> resultmeancostemp;
			std::vector<int> resulttemp;
			size_t j = 0;
			bool find = true;
			//\\ Chen gia tri menacos vua tinh vao danh sach temp.
			while (j < resultmeancos.size())
			{
				if (find && meancos > resultmeancos[j])
				{
					resultmeancostemp.push_back(meancos);
					resulttemp.push_back(i);
					find = false;
				}
				resultmeancostemp.push_back(resultmeancos[j]);
				resulttemp.push_back(result[j]);
				j++;
			}
			//\\ Khong tim thay cai nao lon hon meancos.
			if (find)
			{
				resultmeancostemp.push_back(meancos);
				resulttemp.push_back(i);
			}
			//\\ Gan danh sach temp cho danh sach ket qua.
			resultmeancos = resultmeancostemp;
			resultmeancostemp.clear();
			result = resulttemp;
			resulttemp.clear();
		}// for i (facetrack)



		//\\ Cach kiem tra: Giu lai thu tu so khop cua facetrack.
		for (size_t k = 0; k < result.size(); k++)
		{
			int vFaceTrackIndex = result[k];
			//vFaceTrackMatch[vFaceTrackIndex] += k;//\\ Theo thu tu.
			vFaceTrackMatch[vFaceTrackIndex] += resultmeancos[k];//\\ Theo meancos.
			of << std::to_string(k) + ":" + std::to_string(vFaceTrackIndex) + "(" + std::to_string(resultmeancos[k]) + ")\t";
			ofDb << std::to_string(k) + ":" + std::to_string(vFaceTrackIndex) + "(" + std::to_string(resultmeancos[k]) + ")\t";
		}
		//\\ End. Cach kiem tra.



		resultDB = result;
		of << std::endl;
		ofDb << std::endl;
	}// for f (feature).


	//\\ So khop tung dac trung.

	int vTopFaceTracksize = facetracksize;// / 2; //\\ chi so sanh 1/2 facetrack dau.
	int vCount = 0;
	//\\ So lan dac trung toi da.
	int vCountMax = pFeatureFaceTrack.size();
	if (vCountMax > pCountMax)
		vCountMax = pCountMax;
	//\\ Lap qua tung vector dac trung trung binh.
	for (size_t f = 0; f < pFeatureFaceTrack.size(); f++)
	{
		//\\ Chi qua mot so dac trung co pose lon
		if (vCount == vCountMax)
			break;
		result.clear();
		resultmeancos.clear();
		bool vFound = false;
		//\\ Lap qua mot so face track dau tien sau khi so khop trong csdl.
		for (size_t t = 0; t < vTopFaceTracksize; t++)
		{
			int i = resultDB[t];
			//\\ Neu khong co vector dac trung cua query trong csdl thi bo qua.
			vFound = false;
			size_t k = 0;
			for (k = 0; k < pPoseNames[i].size(); k++)
			{
				if (pPoseName[f] == pPoseNames[i][k])
				{
					vFound = true;
					break;
				}
			}
			if (!vFound)
				break;

			meancos = aCosine2(pFeatureFaceTrack[f], pFeatureFaceTracks[i][k]);

			////\\ Cach chinh:
			//result.push_back(i);
			//resultmeancos.push_back(meancos);
			////\\ End. Cach chinh.



			//\\ Cach kiem tra: Sep xep result de xem log.
			std::vector<double> resultmeancostemp;
			std::vector<int> resulttemp;
			size_t j = 0;
			bool find = true;
			//\\ Chen gia tri menacos vua tinh vao danh sach temp.
			while (j < resultmeancos.size())
			{
				if (find && meancos > resultmeancos[j])
				{
					resultmeancostemp.push_back(meancos);
					resulttemp.push_back(i);
					find = false;
				}
				resultmeancostemp.push_back(resultmeancos[j]);
				resulttemp.push_back(result[j]);
				j++;
			}
			//\\ Khong tim thay cai nao lon hon meancos.
			if (find)
			{
				resultmeancostemp.push_back(meancos);
				resulttemp.push_back(i);
			}
			//\\ Gan danh sach temp cho danh sach ket qua.
			resultmeancos = resultmeancostemp;
			resultmeancostemp.clear();
			result = resulttemp;
			resulttemp.clear();
			//\\ End. Cach kiem tra.



		}// for t (facetrack)
		//\\ Neu tat ca facetrack deu co anh cung goc nhin voi query.
		if (vFound)
		{
			of << pPoseName[f] + ": ";
			ofDb << pPoseName[f] + ": ";
			vCount++;
			//\\ Giu lai thu tu so khop cua facetrack.
			for (size_t k = 0; k < result.size(); k++)
			{
				int vFaceTrackIndex = result[k];
				//vFaceTrackMatch[vFaceTrackIndex] += k;//\\ Theo thu tu.
				vFaceTrackMatch[vFaceTrackIndex] += resultmeancos[k];//\\ Theo meancos.
				of << std::to_string(k) + ":" + std::to_string(vFaceTrackIndex) + "(" + std::to_string(resultmeancos[k]) + ")\t";
				ofDb << std::to_string(k) + ":" + std::to_string(vFaceTrackIndex) + "(" + std::to_string(resultmeancos[k]) + ")\t";
			}
		}
		of << std::endl;
		ofDb << std::endl;
	}// for f (feature).

	//\\ Sap xep thu tu facetrack giam dan.
	for (size_t i = 0; i < facetracksize - 1; i++)
	{
		for (size_t j = i + 1; j < facetracksize; j++)
		{
			//if (vFaceTrackMatch[i] > vFaceTrackMatch[j])//\\ Theo thu tu.
			if (vFaceTrackMatch[i] < vFaceTrackMatch[j])//\\ Theo meancos.
			{
				double vTemp = vFaceTrackMatch[i];
				vFaceTrackMatch[i] = vFaceTrackMatch[j];
				vFaceTrackMatch[j] = vTemp;

				vTemp = vFaceTrack[i];
				vFaceTrack[i] = vFaceTrack[j];
				vFaceTrack[j] = vTemp;
			}
		}// for j.
	}// for i.
	of.close();
	ofDb.close();

	return vFaceTrack;
}
//\\ Thuat toan mean-cos: input (facetrack truy van, DS facetrack); output (DS facetrack duoc sap xep theo facetrack truy van).
std::vector<std::vector<cv::Mat>> FaceTrackDB::aMeanCos(std::vector<cv::Mat> pQueryFaceTrack, std::vector<int> pPose, std::vector<std::vector<cv::Mat>> pFaceTracks, std::vector<std::vector<int>> pPoses)
{
	std::vector<std::vector<cv::Mat>> result;
	//\\ Facetrack truy van.
	std::vector<std::vector<std::vector<double>>> queryfacetrack;
	//\\ Rut trich vector dac trung cho facetrack truy van.
	std::vector<std::vector<double>> queryfeature = aAvgFeature2(pQueryFaceTrack, pPose);
	queryfacetrack.push_back(queryfeature);
	//\\ Khoi tao csdl.
	aDatabaseInit(pFaceTracks, pPoses);
	//\\ Sap xep danh sach facetrack theo facetrack truy van. Tra ve danh sach index cua facetrack.

	//\\ Kiem tra lai
	std::vector<int> resultIndex = aMeanCosMatchingIndex1(queryfacetrack, mFaceTrackDatabase);


	for (size_t i = 0; i < resultIndex.size(); i++)
	{
		int index = resultIndex[i];
		result.push_back(pFaceTracks[index]);
	}
	return result;
}
//\\ Thuat toan mean-cos: input (facetrack truy van, DS facetrack); output (DS facetrack duoc sap xep theo facetrack truy van).
std::vector<std::vector<cv::Mat>> FaceTrackDB::aMeanCosNotPose(std::vector<cv::Mat> pQueryFaceTrack, std::vector<std::vector<cv::Mat>> pFaceTracks)
{
	std::vector<std::vector<cv::Mat>> result;
	//\\ Facetrack truy van.
	std::vector<std::vector<std::vector<double>>> queryfacetrack;
	//\\ Rut trich vector dac trung cho facetrack truy van.

	//\\ Kiem tra lai
	std::vector<std::vector<double>> queryfeature = aAvgFeatureNotPose2(pQueryFaceTrack);


	queryfacetrack.push_back(queryfeature);
	//\\ Khoi tao csdl.
	aDatabaseInitNotPose(pFaceTracks);
	//\\ Sap xep danh sach facetrack theo facetrack truy van. Tra ve danh sach index cua facetrack.
	std::vector<int> resultIndex = aMeanCosMatchingIndex1(queryfacetrack, mFaceTrackDatabase);
	for (size_t i = 0; i < resultIndex.size(); i++)
	{
		int index = resultIndex[i];
		result.push_back(pFaceTracks[index]);
	}
	return result;
}
//\\ Sap xep danh sach vector dac trung trung binh. Theo Level (level = 2 la Euclidian).
std::vector<int> FaceTrackDB::aLpMatchingIndex1(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks, std::vector<std::vector<std::vector<int>>> pFeatureFaceTrack, std::vector<std::vector<std::vector<std::vector<int>>>> pFeatureFaceTracks, std::vector<std::string> pPoseName, std::vector<std::vector<std::string>> pPoseNames, int pCountMax, int pLevel)
{
	std::vector<int> result;
	if (pFaceTracks.size() == 0)
		return result;

	Utilites util;
	size_t facetracksize = pFaceTracks.size();
	//std::vector<int> vFaceTrackMatch(facetracksize);
	std::vector<double> vFaceTrackMatch(facetracksize);
	std::vector<int> vFaceTrack(facetracksize);
	std::vector<double> resultmeancos;
	std::vector<int> resultDB;
	//\\ Tinh khoang cach mean-cos giua 2 vector dac trung trung binh.
	double meancos;
	//\\ Lap qua trung facetrack de tinh khoang cach.

	int vFolderPathIndex = mFolderPath.rfind("/Pose/");
	if (vFolderPathIndex == -1)
	{
		vFolderPathIndex = mFolderPath.rfind("/NotPose/");
	}
	std::string vSPose = mFolderPath.substr(vFolderPathIndex);
	vSPose = util.replaceAll(vSPose, "/", "");
	std::string vFacetrackPath = mFolderPath.substr(0, vFolderPathIndex + 1);
	//vFacetrackPath = mFolderPath.substr(vFolderPathIndex);
	//vFacetrackPath = mFolderPath.substr(vFolderPathIndex) + vFacetrackPath;
	ofstream of(vFacetrackPath + "Matching.txt", std::ofstream::app);
	ofstream ofDb(vFacetrackPath + "Matching" + vSPose + ".txt", std::ofstream::app);
	of << "aCosine: ";
	ofDb << "aCosine: ";

	//\\ Lap qua tung vector dac trung trung binh.
	for (size_t f = 0; f < pFaceTrack.size(); f++)
	{
		result.clear();
		resultmeancos.clear();
		//\\ Lap qua tung face track.
		for (size_t i = 0; i < facetracksize; i++)
		{
			//\\ Neu so luong vector dac trung cua query lon hon facetrac thu i thi bo qua.
			if (f >= pFeatureFaceTracks[i].size())
				continue;

			//meancos = aCosine1(pFaceTrack[f], pFaceTracks[i][f]);
			//meancos = aEuclid1(pFaceTrack[f], pFaceTracks[i][f]);
			meancos = aLp1(pFaceTrack[f], pFaceTracks[i][f], pLevel);
			//\\ Khoi tao thu tu facetrack.aEuclid
			vFaceTrack[i] = i;

			////\\ Cach chinh:
			////\\ Giu lai gia tri so khop cua facetrack.
			//vFaceTrackMatch[i] += meancos;
			//of << std::to_string(i) + "(" << std::to_string(meancos) << ") ";
			//\\ End. Cach chinh.

			std::vector<double> resultmeancostemp;
			std::vector<int> resulttemp;
			size_t j = 0;
			bool find = true;
			//\\ Chen gia tri menacos vua tinh vao danh sach temp.
			while (j < resultmeancos.size())
			{
				//if (find && meancos > resultmeancos[j]) // Theo Cosine.
				if (find && meancos < resultmeancos[j]) // Theo Euclid.
				{
					resultmeancostemp.push_back(meancos);
					resulttemp.push_back(i);
					find = false;
				}
				resultmeancostemp.push_back(resultmeancos[j]);
				resulttemp.push_back(result[j]);
				j++;
			}
			//\\ Khong tim thay cai nao lon hon meancos.
			if (find)
			{
				resultmeancostemp.push_back(meancos);
				resulttemp.push_back(i);
			}
			//\\ Gan danh sach temp cho danh sach ket qua.
			resultmeancos = resultmeancostemp;
			resultmeancostemp.clear();
			result = resulttemp;
			resulttemp.clear();
		}// for i (facetrack)



		//\\ Cach kiem tra: Giu lai thu tu so khop cua facetrack.
		for (size_t k = 0; k < result.size(); k++)
		{
			int vFaceTrackIndex = result[k];
			//vFaceTrackMatch[vFaceTrackIndex] += k;//\\ Theo thu tu.
			vFaceTrackMatch[vFaceTrackIndex] += resultmeancos[k];//\\ Theo meancos.
			of << std::to_string(k) + ":" + std::to_string(vFaceTrackIndex) + "(" + std::to_string(resultmeancos[k]) + ")\t";
			ofDb << std::to_string(k) + ":" + std::to_string(vFaceTrackIndex) + "(" + std::to_string(resultmeancos[k]) + ")\t";
		}
		//\\ End. Cach kiem tra.



		resultDB = result;
		of << std::endl;
		ofDb << std::endl;
	}// for f (feature).


	//\\ So khop tung dac trung.

	int vTopFaceTracksize = facetracksize;// / 2; //\\ chi so sanh 1/2 facetrack dau.
	int vCount = 0;
	//\\ So lan dac trung toi da.
	int vCountMax = pFeatureFaceTrack.size();
	if (vCountMax > pCountMax)
		vCountMax = pCountMax;
	//\\ Lap qua tung vector dac trung trung binh.
	for (size_t f = 0; f < pFeatureFaceTrack.size(); f++)
	{
		//\\ Chi qua mot so dac trung co pose lon
		if (vCount == vCountMax)
			break;
		result.clear();
		resultmeancos.clear();
		bool vFound = false;
		//\\ Lap qua mot so face track dau tien sau khi so khop trong csdl.
		for (size_t t = 0; t < vTopFaceTracksize; t++)
		{
			int i = resultDB[t];
			//\\ Neu khong co vector dac trung cua query trong csdl thi bo qua.
			vFound = false;
			size_t k = 0;
			for (k = 0; k < pPoseNames[i].size(); k++)
			{
				if (pPoseName[f] == pPoseNames[i][k])
				{
					vFound = true;
					break;
				}
			}
			if (!vFound)
				break;

			//meancos = aCosine2(pFeatureFaceTrack[f], pFeatureFaceTracks[i][k]);
			//meancos = aEuclid2(pFeatureFaceTrack[f], pFeatureFaceTracks[i][k]);
			meancos = aLp2(pFeatureFaceTrack[f], pFeatureFaceTracks[i][k], pLevel);

			////\\ Cach chinh:
			//result.push_back(i);
			//resultmeancos.push_back(meancos);
			////\\ End. Cach chinh.



			//\\ Cach kiem tra: Sep xep result de xem log.
			std::vector<double> resultmeancostemp;
			std::vector<int> resulttemp;
			size_t j = 0;
			bool find = true;
			//\\ Chen gia tri menacos vua tinh vao danh sach temp.
			while (j < resultmeancos.size())
			{
				//if (find && meancos > resultmeancos[j])
				if (find && meancos < resultmeancos[j])
				{
					resultmeancostemp.push_back(meancos);
					resulttemp.push_back(i);
					find = false;
				}
				resultmeancostemp.push_back(resultmeancos[j]);
				resulttemp.push_back(result[j]);
				j++;
			}
			//\\ Khong tim thay cai nao lon hon meancos.
			if (find)
			{
				resultmeancostemp.push_back(meancos);
				resulttemp.push_back(i);
			}
			//\\ Gan danh sach temp cho danh sach ket qua.
			resultmeancos = resultmeancostemp;
			resultmeancostemp.clear();
			result = resulttemp;
			resulttemp.clear();
			//\\ End. Cach kiem tra.



		}// for t (facetrack)
		//\\ Neu tat ca facetrack deu co anh cung goc nhin voi query.
		if (vFound)
		{
			of << pPoseName[f] + ": ";
			ofDb << pPoseName[f] + ": ";
			vCount++;
			//\\ Giu lai thu tu so khop cua facetrack.
			for (size_t k = 0; k < result.size(); k++)
			{
				int vFaceTrackIndex = result[k];
				//vFaceTrackMatch[vFaceTrackIndex] += k;//\\ Theo thu tu.
				vFaceTrackMatch[vFaceTrackIndex] += resultmeancos[k];//\\ Theo meancos.
				of << std::to_string(k) + ":" + std::to_string(vFaceTrackIndex) + "(" + std::to_string(resultmeancos[k]) + ")\t";
				ofDb << std::to_string(k) + ":" + std::to_string(vFaceTrackIndex) + "(" + std::to_string(resultmeancos[k]) + ")\t";
			}
		}
		of << std::endl;
		ofDb << std::endl;
	}// for f (feature).

	//\\ Sap xep thu tu facetrack giam dan.
	for (size_t i = 0; i < facetracksize - 1; i++)
	{
		for (size_t j = i + 1; j < facetracksize; j++)
		{
			//if (vFaceTrackMatch[i] > vFaceTrackMatch[j])//\\ Theo thu tu.
			//if (vFaceTrackMatch[i] < vFaceTrackMatch[j])//\\ Theo meancos.
			if (vFaceTrackMatch[i] > vFaceTrackMatch[j])//\\ Theo Euclid.
			{
				double vTemp = vFaceTrackMatch[i];
				vFaceTrackMatch[i] = vFaceTrackMatch[j];
				vFaceTrackMatch[j] = vTemp;

				vTemp = vFaceTrack[i];
				vFaceTrack[i] = vFaceTrack[j];
				vFaceTrack[j] = vTemp;
			}
		}// for j.
	}// for i.
	of.close();
	ofDb.close();

	return vFaceTrack;
}

/******************** Gia lap ********************/
//\\ Gia lap danh sach vector dac trung cua facetrack. 1 facetrack co nhieu vector dac trung.
std::vector<std::vector<std::vector<int>>> FaceTrackDB::aGetsFeatureFake(size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue)
{
	std::vector<std::vector<std::vector<int>>> result;
	//size_t numLists = 3;
	//size_t numRows = 3;
	//size_t numCols = 3;
	for (size_t i = 0; i < pNumList; i++)
	{
		std::vector<std::vector<int>> row;
		for (size_t j = 0; j < pNumRows; j++)
		{
			std::vector<int> col;
			for (size_t k = 0; k < pNumCols; k++)
			{
				//\\ Tao vector co gia tri theo thu tu list. "012..."; "123..."; "234..."; ...
				if (pValue == -1)
					col.push_back(i + j * pNumCols + k);
				else
					col.push_back(pValue);
			}
			row.push_back(col);
		}
		result.push_back(row);
	}
	return result;
}
//\\ Gia lap danh sach vector dac trung trung binh cua tat ca facetrack. Moi facetrack co 1 vector dac trung trung binh.
std::vector<std::vector<std::vector<double>>> FaceTrackDB::aGetsAvgFeatureFake(size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue)
{
	std::vector<std::vector<std::vector<double>>> result;
	//size_t numLists = 3;
	//size_t numRows = 3;
	//size_t numCols = 3;
	for (size_t i = 0; i < pNumList; i++)
	{
		std::vector<std::vector<double>> row;
		for (size_t j = 0; j < pNumRows; j++)
		{
			std::vector<double> col;
			for (size_t k = 0; k < pNumCols; k++)
			{
				//\\ Tao vector co gia tri theo thu tu list. "012..."; "123..."; "234..."; ...
				if (pValue == -1)
					col.push_back(i + j * pNumCols + k);
				else
					col.push_back(pValue);
			}
			row.push_back(col);
		}
		result.push_back(row);
	}
	return result;
}
//\\ Gia lap danh sach cua danh sach vector dac trung cua facetrack. Moi  facetrack co nhieu vector dac trung.
std::vector<std::vector<std::vector<std::vector<int>>>> FaceTrackDB::aGetsFeaturesFake(size_t pNumLists, size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue)
{
	std::vector<std::vector<std::vector<std::vector<int>>>> result;
	//size_t numLists = 3;
	for (size_t i = 0; i < pNumLists; i++)
	{
		//\\ Gia lap danh sach vector dac trung cua facetrack. 1 facetrack co nhieu vector dac trung.
		result.push_back(aGetsFeatureFake(pNumList, pNumRows, pNumCols, pValue));
	}
	return result;
}
//\\ Gia lap vector dac trung trung binh.
std::vector<std::vector<double>> FaceTrackDB::aAvgFetureFake(size_t pNumRows, size_t pNumCols, double pValue)
{
	std::vector<std::vector<double>> result;
	//size_t numRows = 1;
	//size_t numCols = 3;
	for (size_t i = 0; i < pNumRows; i++)
	{
		std::vector<double> col;
		for (size_t j = 0; j < pNumCols; j++)
		{
			//\\ Tao vector co gia tri tang dan. "012...".
			if (pValue == -1)
				col.push_back(i * pNumCols + j);
			else
				col.push_back(pValue);
		}
		result.push_back(col);
	}
	return result;
}
//\\ Gia lap facetrack.
std::vector<cv::Mat> FaceTrackDB::aFaceTrackFake(size_t numList, int pNumRows, int pNumCols, uchar pValue)
{
	std::vector<cv::Mat> result;
	//size_t numList = 3;
	//int rows = 3;
	//int cols = 3;
	for (size_t i = 0; i < numList; i++)
	{
		cv::Mat face;
		if (pValue == -1)
			face = cv::Mat(pNumRows, pNumCols, CV_8UC1, cv::Scalar(i));
		else
			face = cv::Mat(pNumRows, pNumCols, CV_8UC1, cv::Scalar(pValue));
		result.push_back(face);
	}
	return result;
}

//\\ (Use) Luu ra file: vector dac trung
void FaceTrackDB::aSaveToFile(cv::Mat pFace, std::string pFileName, std::string pSavePath)
{
	Utilites util;
	//\\ Ghi anh Mat.
	std::string vFileName = util.subStringLastBefor(pFileName, ".");
	util.writeMatBasic(pFace, pSavePath + vFileName + mFeatureType);
	util.writeMatInt(pFace, pSavePath + vFileName + ".txt");
}

//\\ Luu danh sach ten file anh va pose tuong ung cua tung facetrack ra file. Kich thuoc 2 danh sach phai bang nhau.
void FaceTrackDB::aSaveToFile1(std::vector<std::string> pFileNames, std::vector<int> pPoses, std::string pSavePath)
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
void FaceTrackDB::aSaveToFile2(std::vector<std::string> pFileNames, std::vector<int> pPoses, std::vector<std::string> pPoseNames, std::string pSavePath)
{
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
void FaceTrackDB::aSaveToFile3(std::vector<std::string> pFileNames, std::vector<std::string> pPoses, std::vector<std::string> pPoseNames, bool pSortPose, std::string pSavePath)
{
	//if (pSortPose)
	//{
	//	Utilites util;
	//	//\\ Ghi anh Mat.
	//	int vTiltPose = 0;
	//	int vPanPose = 0;
	//	//\\ Khoi tao index.
	//	std::vector<int> vTiltPans;
	//	std::vector<int> vPoseIndex;
	//	for (size_t i = 0; i < pPoses.size(); i++)
	//	{
	//		vTiltPose = std::atoi(util.subStringLastBefor(pPoses[i], ";").c_str());
	//		vPanPose = std::atoi(util.subStringLastAfter(pPoses[i], ";").c_str());
	//		vTiltPans.push_back(vTiltPose + vPanPose);
	//		vPoseIndex.push_back(i);
	//	}
	//	//\\ Sap xep thu tu pose giam dan.
	//	for (size_t i = 0; i < vTiltPans.size() - 1; i++)
	//	{
	//		for (size_t j = i + 1; j < vTiltPans.size(); j++)
	//		{
	//			if (vTiltPans[i] < vTiltPans[j])//\\ Theo pose.
	//			{
	//				int vTemp = vTiltPans[i];
	//				vTiltPans[i] = vTiltPans[j];
	//				vTiltPans[j] = vTemp;

	//				std::string vSTemp = pPoses[i];
	//				pPoses[i] = pPoses[j];
	//				pPoses[j] = vSTemp;

	//				vSTemp = pPoseNames[i];
	//				pPoseNames[i] = pPoseNames[j];
	//				pPoseNames[j] = vSTemp;
	//			}
	//		}// for j.
	//	}// for i.
	//}



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
