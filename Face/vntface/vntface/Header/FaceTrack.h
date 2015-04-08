/*
VNThanh
- Face Track.
*/

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

namespace vnt
{
	class FaceTrack
	{
	private:

	public:
		/********** Constructor **********/
		FaceTrack();
		~FaceTrack();

		/********** public Methods **********/
		//\\ Lay dac trung cua tung face trong facetrack.
		std::vector<std::vector<std::vector<int>>> aGetsFeature(const std::vector<cv::Mat> pFaceTrack);
		//\\ Tinh vector trung binh cho facetrack.
		std::vector<std::vector<double>> aAvgFeature(const std::vector<std::vector<std::vector<int>>> pFeatures);
		std::vector<std::vector<double>> aAvgFeature(const std::vector<cv::Mat> pFaceTrack);
		//\\ Tinh vector trung binh cho tung facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<std::vector<double>>> aAvgFeatures(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures);
		//\\ Tinh vector trung binh cho tat ca facetrack. Moi facetrack co danh sach vector dac trung.
		std::vector<std::vector<double>> aAvgFeature(const std::vector<std::vector<std::vector<std::vector<int>>>> pFTFeatures);
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
		
		//\\ Khoi tao csdl mean-cos (danh sach vector dac trung trung binh cho cac facetrack).
		std::vector<std::vector<std::vector<double>>> aMeanCosInit(std::vector<std::vector<cv::Mat>> pFaceTracks);
		//\\ Sap xep danh sach facetrack theo facetrack yeu cau. Moi facetrack duoc dai dien bang 1 vector dac trung trung binh.
		std::vector<std::vector<std::vector<double>>> aMeanCosMatching(std::vector<std::vector<double>> pFaceTrack, std::vector<std::vector<std::vector<double>>> pFaceTracks);
		std::vector<int> aMeanCosMatchingIndex(std::vector<std::vector<double>> pFaceTrack, std::vector<std::vector<std::vector<double>>> pFaceTracks);
		//\\ Thuat toan mean-cos: input (facetrack yeu cau, DS facetrack); output (DS facetrack duoc sap xep theo facetrack yeu cau).
		std::vector<std::vector<cv::Mat>> aMeanCos(std::vector<cv::Mat> pFaceTrack, std::vector<std::vector<cv::Mat>> pFaceTracks);


		/******************** Gia lap ********************/
		//\\ Gia lap danh sach vector dac trung cua facetrack. 1 facetrack co nhieu vector dac trung.
		std::vector<std::vector<std::vector<int>>> aGetsFeatureFake(size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue = -1);
		//\\ Gia lap danh sach vector dac trung trung binh cua tat ca facetrack. Moi facetrack co 1 vector dac trung trung binh.
		std::vector<std::vector<std::vector<double>>> FaceTrack::aGetsAvgFeatureFake(size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue = -1);
		//\\ Gia lap danh sach cua danh sach vector dac trung cua facetrack. Moi  facetrack co nhieu vector dac trung.
		std::vector<std::vector<std::vector<std::vector<int>>>> aGetsFeaturesFake(size_t pNumLists, size_t pNumList, size_t pNumRows, size_t pNumCols, int pValue = -1);
		//\\ Gia lap vector dac trung trung binh.
		std::vector<std::vector<double>> aAvgFetureFake(size_t pNumRows, size_t pNumCols, double pValue = -1);
		//\\ Gia lap facetrack.
		std::vector<cv::Mat> aFaceTrackFake(size_t numList, int pNumRows, int pNumCols, uchar pValue = -1);
	};

}