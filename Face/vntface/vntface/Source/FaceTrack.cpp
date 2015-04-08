/*
VNThanh
- Face Track.
*/

#include "../Header/FaceTrack.h"
#include "../Header/FeatureLBP.h"

using namespace vnt;

/********** Constructor **********/
FaceTrack::FaceTrack()
{
}
FaceTrack::~FaceTrack()
{
}

/********** public Methods **********/
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
				for (size_t k = 0; k < pFTFeatures[0].size(); k++)
				{
					//\\ Lap qua danh sach dac trung. (truc t)
					for (size_t l = 0; l < pFTFeatures.size(); l++)
					{
						avg += pFTFeatures[k][l][i][j];
					}
				}
				avg = avg / (pFTFeatures[0].size() * pFTFeatures.size());
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

//\\ Khoi tao csdl mean-cos (danh sach vector dac trung trung binh cho cac facetrack).
std::vector<std::vector<std::vector<double>>> FaceTrack::aMeanCosInit(std::vector<std::vector<cv::Mat>> pFaceTracks)
{
	std::vector<std::vector<std::vector<double>>> result;
	//\\ Rut trich vector dac trung cho danh sach facetrack.
	std::vector<std::vector<std::vector<std::vector<int>>>> facetrackfeatures;
	for (size_t i = 0; i < pFaceTracks.size(); i++)
	{
		std::vector<std::vector<std::vector<int>>> features = aGetsFeature(pFaceTracks[i]);
		facetrackfeatures.push_back(features);
	}
	//\\ B1: Tinh vector dac trung trung binh cho toan bo anh trong danh sach facetrack.
	std::vector<std::vector<double>> avgFeature = aAvgFeature(facetrackfeatures);
	//\\ B2: Tinh vector dac trung trung binh cho moi facetrack. (mean)
	std::vector<std::vector<std::vector<double>>> facetrackfeature = aAvgFeatures(facetrackfeatures);
	//\\ B3: Chuan hoa vector dac trung trung binh cua moi facetrack.
	for (size_t i = 0; i < facetrackfeature.size(); i++)
	{
		std::vector<std::vector<double>> featureSub = aSub(facetrackfeature[i], avgFeature);
		result.push_back(featureSub);
	}
	return result;
}
//\\ Sap xep danh sach facetrack theo facetrack yeu cau. Moi facetrack duoc dai dien bang 1 vector dac trung trung binh.
std::vector<std::vector<std::vector<double>>> FaceTrack::aMeanCosMatching(std::vector<std::vector<double>> pFaceTrack, std::vector<std::vector<std::vector<double>>> pFaceTracks)
{
	std::vector<std::vector<std::vector<double>>> result;
	std::vector<double> resultmeancos;
	//\\ Tinh khoang cach mean-cos giua 2 vector dac trung trung binh.
	double meancos = 0;
	//\\ Lap qua trung facetrack de tinh khoang cach.
	for (size_t i = 0; i < pFaceTracks.size(); i++)
	{
		meancos = aCosine(pFaceTrack, pFaceTracks[i]);
		std::vector<double> resultmeancostemp;
		std::vector<std::vector<std::vector<double>>> resulttemp;
		size_t j = 0;
		//\\ Chen gia tri menacos vua tinh vao danh sach temp.
		while (true)
		{
			if (meancos < resultmeancos[j])
			{
				resultmeancostemp.push_back(meancos);
				resultmeancostemp.push_back(resultmeancos[j]);
				resulttemp.push_back(pFaceTracks[i]);
				resulttemp.push_back(result[j]);
				break;
			}
			j++;
		}
		while (j < resultmeancos.size())
		{
			resultmeancostemp.push_back(resultmeancos[j]);
			resulttemp.push_back(result[j]);
			j++;
		}
		//\\ Gan danh sach temp cho danh sach ket qua.
		resultmeancos = resultmeancostemp;
		result = resulttemp;
	}
	return result;
}
std::vector<int> FaceTrack::aMeanCosMatchingIndex(std::vector<std::vector<double>> pFaceTrack, std::vector<std::vector<std::vector<double>>> pFaceTracks)
{
	std::vector<int> result;
	std::vector<double> resultmeancos;
	//\\ Tinh khoang cach mean-cos giua 2 vector dac trung trung binh.
	double meancos = 0;
	//\\ Lap qua trung facetrack de tinh khoang cach.
	for (size_t i = 0; i < pFaceTracks.size(); i++)
	{
		meancos = aCosine(pFaceTrack, pFaceTracks[i]);
		std::vector<double> resultmeancostemp;
		std::vector<int> resulttemp;
		size_t j = 0;
		//\\ Chen gia tri menacos vua tinh vao danh sach temp.
		while (true)
		{
			if (meancos < resultmeancos[j])
			{
				resultmeancostemp.push_back(meancos);
				resultmeancostemp.push_back(resultmeancos[j]);
				resulttemp.push_back(i);
				resulttemp.push_back(result[j]);
				break;
			}
			j++;
		}
		while (j < resultmeancos.size())
		{
			resultmeancostemp.push_back(resultmeancos[j]);
			resulttemp.push_back(result[j]);
			j++;
		}
		//\\ Gan danh sach temp cho danh sach ket qua.
		resultmeancos = resultmeancostemp;
		result = resulttemp;
	}
	return result;
}
//\\ Thuat toan mean-cos: input (facetrack yeu cau, DS facetrack); output (DS facetrack duoc sap xep theo facetrack yeu cau).
std::vector<std::vector<cv::Mat>> FaceTrack::aMeanCos(std::vector<cv::Mat> pQueryFaceTrack, std::vector<std::vector<cv::Mat>> pFaceTracks)
{
	std::vector<std::vector<cv::Mat>> result;
	//\\ Rut trich vector dac trung cho facetrack truy van.
	std::vector<std::vector<double>> queryfeature = aAvgFeature(pQueryFaceTrack);
	//\\ Khoi tao csdl.
	std::vector<std::vector<std::vector<double>>> csdl = aMeanCosInit(pFaceTracks);
	//\\ Sap xep danh sach facetrack theo facetrack yeu cau. Tra ve danh sach index cua facetrack.
	std::vector<int> resultIndex = aMeanCosMatchingIndex(queryfeature, csdl);
	for (size_t i = 0; i < resultIndex.size(); i++)
	{
		result.push_back(pFaceTracks[i]);
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
