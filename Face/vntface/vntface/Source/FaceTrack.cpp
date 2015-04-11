/*
VNThanh
- Face Track.
*/

#include "../Header/FaceTrack.h"
#include "../Header/FeatureLBP.h"
#include "../Header/Utilities.h"

using namespace vnt;

/********** Constructor **********/
FaceTrack::FaceTrack()
{
}
FaceTrack::~FaceTrack()
{
}

/********** public Methods **********/
//\\ Lay csdl.
std::vector<std::vector<std::vector<std::vector<double>>>> FaceTrack::aGetFaceTrackDatabase()
{
	return mFaceTrackDatabase;
}
//\\ Gan csdl.
void FaceTrack::aSetFaceTrackDatabase(std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTrackDatabase)
{
	mFaceTrackDatabase = pFaceTrackDatabase;
}

//\\ Doc tat ca file anh vao trong facetrack.
std::vector<cv::Mat> FaceTrack::aGestAllImage(std::string pFolderPath, std::vector<std::string> pAllFileName)
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

//\\ Lay dac trung cua tung face trong facetrack.
std::vector<std::vector<std::vector<int>>> FaceTrack::aGetsFeature(const std::vector<cv::Mat> pFaceTrack)
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
//\\ Tinh vector trung binh cho facetrack.
std::vector<std::vector<double>> FaceTrack::aAvgFeature(const std::vector<std::vector<std::vector<int>>> pFeatures)
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
std::vector<std::vector<double>> FaceTrack::aAvgFeature(const std::vector<cv::Mat> pFaceTrack)
{
	std::vector<std::vector<double>> result;
	//\\ Tinh dac trung LBP cho tat ca face trong facetrack
	std::vector<std::vector<std::vector<int>>> featureLBPs = aGetsFeature(pFaceTrack);
	result = aAvgFeature(featureLBPs);
	return result;
}
//\\ Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
std::vector<std::vector<std::vector<double>>> FaceTrack::aAvgFeatures(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures)
{
	std::vector<std::vector<std::vector<double>>> result;
	//\\ Tinh vector dac trung trung binh cho tung facetrack.
	for (size_t i = 0; i < pFTFeatures.size(); i++)
	{
		std::vector<std::vector<double>> feature = aAvgFeature(pFTFeatures[i]);
		result.push_back(feature);
	}
	return result;
}
//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
std::vector<std::vector<double>> FaceTrack::aAvgFeature(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures)
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
					for (size_t l = 0; l < pFTFeatures[0].size(); l++)
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
//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co 1 vector dac trung trung binh.
std::vector<std::vector<double>> FaceTrack::aAvgFeature(const std::vector<std::vector<std::vector<double>>> pFTFeatures)
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

//\\ Tinh tong cua tich cac phan tu tuong ung trong 2 vector. Co so chieu bang nhau.
double FaceTrack::aSumMul(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
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
//\\ Tinh khoang cach cosine cua 2 vector. Co so chieu bang nhau.
double FaceTrack::aCosine(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
{
	double result = 0;

	//\\ Tinh tong tich Ai x Bi.
	double d12 = aSumMul(pVector1, pVector2);
	//\\ Tinh tong tich Ai x Ai.
	double d11 = aSumMul(pVector1, pVector1);
	//\\ Tinh tong tich Bi x Bi.
	double d22 = aSumMul(pVector2, pVector2);

	result = d12 / (sqrt(d11) * sqrt(d22));
	return result;
}

//\\ Tinh tong cua hieu cua binh phuong cac phan tu tuong ung trong 2 vector. Co so chieu bang nhau.
double FaceTrack::aSumSub(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
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
double FaceTrack::aEuclid(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
{
	double result = 0;

	//\\ Tinh tong cua hieu cua binh phuong cua cac phan tu.
	double sum = aSumSub(pVector1, pVector2);
	//\\ Tinh khoang cach hinh hoc.
	result = sqrt(sum);
	return result;
}

//\\ Tinh hieu cua 2 vector dac trung.
std::vector<std::vector<double>> FaceTrack::aSub(std::vector<std::vector<double>> pVector1, std::vector<std::vector<double>> pVector2)
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

//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack).
int FaceTrack::aDatabaseInit(std::vector<std::vector<cv::Mat>> pFaceTracks)
{
	int result = -1;
	mFaceTrackDatabase.clear();
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	const size_t vFaceTrackSize = pFaceTracks.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		facetrackfeatures.push_back(features);
	}
	//\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	std::vector<std::vector<double>> avgFeature = aAvgFeature(facetrackfeatures);
	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeatures(facetrackfeatures);
	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack.
	std::vector<std::vector<std::vector<double>>> normalizefeatures;
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);
		normalizefeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(normalizefeatures);
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ Khoi tao csdl (danh sach vector dac trung trung binh cho cac facetrack). Co ghi csdl ra file.
int FaceTrack::aDatabaseInit(std::vector<std::vector<cv::Mat>> pFaceTracks, std::string pFolderPath)
{
	int result = -1;
	mFaceTrackDatabase.clear();
	Utilites util;
	mFolderPath = pFolderPath;
	std::string vFolderPath = pFolderPath;
	if (vFolderPath.length() > 0)
		vFolderPath = util.replaceAll(pFolderPath, "/", "\\");
	util.makeDir(vFolderPath + mFaceTracksFolder);
	util.makeDir(vFolderPath + mFaceTracksFolder + "\\" + mDataSetFolder);
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	const size_t vFaceTrackSize = pFaceTracks.size();
	int numlengthFaceTrack = std::to_string((int)vFaceTrackSize).length();
	std::vector<std::string> faceTrackNames;
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		std::string faceTrackName = std::to_string(i);
		faceTrackName = mFaceTrackName + util.leftPad(faceTrackName, numlengthFaceTrack, '0');
		util.makeDir(vFolderPath + mFaceTracksFolder + "\\" + faceTrackName);
		util.makeDir(vFolderPath + mFaceTracksFolder + "\\" + mDataSetFolder + "\\" + faceTrackName);
		faceTrackNames.push_back(faceTrackName);

		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		facetrackfeatures.push_back(features);
		//\\ Ghi ra file: cac vector dac trung cua facetrack thu i.
		size_t featuressize = features.size();
		int numlengthFeature = std::to_string((int)featuressize).length();
		for (size_t j = 0; j < featuressize; j++)
		{
			//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
			cv::Mat vFeatureFile = util.convertV2IToMat(features[j], features[j][0].size(), features[j].size());
			//\\ Ten file co dang: "Feature01.txt", ...
			std::string fName = std::to_string(j);
			fName = mFeatureName + util.leftPad(fName, numlengthFeature, '0');
			//\\ Ghi gia tri vector dac trung.
			util.writeMatBasic(vFeatureFile, mFolderPath + mFaceTracksFolder + "/" + faceTrackName + "/" + fName + mFeatureType);
			//\\ Ghi tri Mat cua anh.
			util.writeMatBasic(vFeatureFile, mFolderPath + mFaceTracksFolder + "/" + mDataSetFolder + "/" + faceTrackName + "/" + fName + mImageType);
		}
	}
	//\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	std::vector<std::vector<double>> avgFeature = aAvgFeature(facetrackfeatures);
	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeatures(facetrackfeatures);
	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack.
	std::vector<std::vector<std::vector<double>>> normalizefeatures;
	//\\ Tao thu muc "Normalize".
	util.makeDir(vFolderPath + mFaceTracksFolder + "\\" + mNormalizeFeatureFolder);
	//size_t facetrackfeaturesize = facetrackfeature.size();
	for (size_t i = 0; i < vFaceTrackSize; i++)
	{
		//\\ Tao thu muc cho facetrack thu i.
		util.makeDir(vFolderPath + mFaceTracksFolder + "\\" + mNormalizeFeatureFolder + "\\" + faceTrackNames[i]);
		//\\ Chuan hoa cac vector dac trung trung binh.
		normalizefeatures.clear();
		std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);
		normalizefeatures.push_back(featureSub);
		mFaceTrackDatabase.push_back(normalizefeatures);
		//\\ Ghi ra file: cac vector dac trung da duoc chuan hoa (dac trung trung binh) cua facetrack thu i.
		size_t featuressize = normalizefeatures.size();
		int numlengthFeature = std::to_string((int)featuressize).length();
		for (size_t j = 0; j < featuressize; j++)
		{
			//\\ Chuyen doi vector 2 chieu thanh doi tuong Mat.
			cv::Mat file = util.convertV2DToMat(normalizefeatures[j], (int)normalizefeatures[j][0].size(), (int)normalizefeatures[j].size());
			//\\ Ten file co dang: "Feature01.txt", ...
			std::string fName = std::to_string(j);
			fName = mFeatureName + util.leftPad(fName, numlengthFeature, '0');
			util.writeMatBasic(file, mFolderPath + mFaceTracksFolder + "/" + mNormalizeFeatureFolder + "/" + faceTrackNames[i] + "/" + fName + mFeatureType);
			//
			////\\ Ten file co dang: "Normalize/Feature01", ...
			//std::string fName = std::to_string(j);
			//fName = mNormalizeFeatureName + util.leftPad(fName, numlengthFeature, '0');
			//util.writeMatBasic(file, mFolderPath + fName);
		}
	}
	result = mFaceTrackDatabase.size();
	return result;
}
//\\ Doc cac vector dac trung tu file va dua vao csdl.
int FaceTrack::aDatabaseRead(std::string pNumFaceTrackStart, std::string pNumFaceTrackEnd, std::string pNumFeatureStart, std::string pNumFeatureEnd, std::string pFolderPath)
{
	int result = 0;
	mFaceTrackDatabase.clear();
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
		std::string vFaceTrackPath = mFolderPath + mFaceTracksFolder + "/";
		std::string vFaceTrackName = mFaceTrackName + util.leftPad(std::to_string(i), facetrackLength, '0');
		std::vector<std::vector<std::vector<double>>> facetrack;
		size_t vNumFeatureStart = std::atoi(pNumFeatureStart.c_str());
		size_t vNumFeatureEnd = std::atoi(pNumFeatureEnd.c_str());
		for (size_t j = vNumFeatureStart; j <= vNumFeatureEnd; j++)
		{
			std::string vFeaturePath = vFaceTrackPath + mNormalizeFeatureFolder + "/" + vFaceTrackName + "/";
			std::string featureName = mNormalizeFeatureName + util.leftPad(std::to_string(j), featueLength, '0');
			cv::Mat featureMat = util.readMatBasic(vFeaturePath + featureName + mFeatureType);
			std::vector<std::vector<double>> feature = util.convertMatToV2D(featureMat);
			facetrack.push_back(feature);
		}
		mFaceTrackDatabase.push_back(facetrack);
		facetrack.clear();
	}
	result = mFaceTrackDatabase.size();
	return result;
}

//\\ Sap xep danh sach facetrack theo facetrack truy van. Moi facetrack duoc dai dien bang 1 vector dac trung trung binh.
std::vector<std::vector<std::vector<std::vector<double>>>> FaceTrack::aMeanCosMatching(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks)
{
	std::vector<std::vector<std::vector<std::vector<double>>>> result;
	std::vector<double> resultmeancos;
	//\\ Tinh khoang cach mean-cos giua 2 vector dac trung trung binh.
	double meancos = 0;
	//\\ Lap qua trung facetrack de tinh khoang cach.
	size_t facetracksize = pFaceTracks.size();
	for (size_t i = 0; i < facetracksize; i++)
	{
		meancos = aCosine(pFaceTrack[0], pFaceTracks[i][0]);
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
std::vector<int> FaceTrack::aMeanCosMatchingIndex(std::vector<std::vector<std::vector<double>>> pFaceTrack, std::vector<std::vector<std::vector<std::vector<double>>>> pFaceTracks)
{
	std::vector<int> result;
	if (pFaceTracks.size() == 0)
		return result;
	std::vector<double> resultmeancos;
	//\\ Tinh khoang cach mean-cos giua 2 vector dac trung trung binh.
	double meancos;
	//\\ Lap qua trung facetrack de tinh khoang cach.
	size_t facetracksize = pFaceTracks.size();
	for (size_t i = 0; i < facetracksize; i++)
	{
		meancos = aCosine(pFaceTrack[0], pFaceTracks[i][0]);
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
	return result;
}
//\\ Thuat toan mean-cos: input (facetrack truy van, DS facetrack); output (DS facetrack duoc sap xep theo facetrack truy van).
std::vector<std::vector<cv::Mat>> FaceTrack::aMeanCos(std::vector<cv::Mat> pQueryFaceTrack, std::vector<std::vector<cv::Mat>> pFaceTracks)
{
	std::vector<std::vector<cv::Mat>> result;
	//\\ Facetrack truy van.
	std::vector<std::vector<std::vector<double>>> queryfacetrack;
	//\\ Rut trich vector dac trung cho facetrack truy van.
	std::vector<std::vector<double>> queryfeature = aAvgFeature(pQueryFaceTrack);
	queryfacetrack.push_back(queryfeature);
	//\\ Khoi tao csdl.
	aDatabaseInit(pFaceTracks);
	//\\ Sap xep danh sach facetrack theo facetrack truy van. Tra ve danh sach index cua facetrack.
	std::vector<int> resultIndex = aMeanCosMatchingIndex(queryfacetrack, mFaceTrackDatabase);
	for (size_t i = 0; i < resultIndex.size(); i++)
	{
		int index = resultIndex[i];
		result.push_back(pFaceTracks[index]);
	}
	return result;
}


/******************** Gia lap ********************/
//\\ Gia lap danh sach vector dac trung cua facetrack. 1 facetrack co nhieu vector dac trung.
std::vector<std::vector<std::vector<int>>> FaceTrack::aGetsFeatureFake(size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue)
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
std::vector<std::vector<std::vector<double>>> FaceTrack::aGetsAvgFeatureFake(size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue)
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
std::vector<std::vector<std::vector<std::vector<int>>>> FaceTrack::aGetsFeaturesFake(size_t pNumLists, size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue)
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
std::vector<std::vector<double>> FaceTrack::aAvgFetureFake(size_t pNumRows, size_t pNumCols, double pValue)
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
std::vector<cv::Mat> FaceTrack::aFaceTrackFake(size_t numList, int pNumRows, int pNumCols, uchar pValue)
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
