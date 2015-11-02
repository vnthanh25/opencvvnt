extern "C" {
#include <vl/generic.h>
#include <vl/lbp.h>
}

#include "Header\Matching.h"
#include "Header\FeatureLBP.h"
#include <fstream>


std::vector<std::vector<int>> LBP()
{
	vnt::FeatureLBP lbp;
	vnt::Utilites util;
	//\\ Doc anh.
	//cv::Mat img = lbp.createMat(11, 11);
	cv::Mat img = imread("images/lena.png", CV_LOAD_IMAGE_GRAYSCALE);
	int n = 8;
	std::vector<std::vector<int>> lbpfeature = lbp.LBP(img, n, 1);
	////\\ Chuyen doi vector 2 chieu thanh Mat.
	//cv::Mat lbpFeatureMat = util.convertV2IToMat(lbpfeature, lbpfeature[0].size(), lbpfeature.size());
	////util.writeMatInt(lbpFeatureMat, "Txt/lbpFeatureMat.txt");
	////\\ Hien thi ra man hinh dos cac gia tri dong nhat trong 256 gia tri.
	//lbp.showLBPUniValues();

	return lbpfeature;
}

std::vector<std::vector<float>> vlfeat(int convert)
{
	cv::Mat img = imread("images/lena.png", CV_LOAD_IMAGE_GRAYSCALE);
	// Convert value from uchar to float.
	float* data = new float[];
	cv::Mat imgf;
	switch (convert)
	{
	case 1:
		data = new float[img.rows * img.cols];
		for (size_t i = 0; i < img.rows; i++)
		{
			for (size_t j = 0; j < img.cols; j++)
			{
				uchar c = img.at<uchar>(i, j);
				float f = (float)c;
				data[i*j + j] = f;
			}
		}
		break;
	case 2:
		img.convertTo(imgf, CV_32FC1);
		data = imgf.ptr<float>();
		break;
	default:
		break;
	}

	VlLbp* lbp = vl_lbp_new(VlLbpMappingType::VlLbpUniform, false);
	vl_size cellSize = vl_lbp_get_dimension(lbp);
	vl_size width = img.cols;
	vl_size height = img.rows;
	const int numColumns = floor(width / cellSize);
	const int numRows = floor(height / cellSize);
	const int featureSize = numColumns * numRows * cellSize;

	float* features = new float[featureSize];
	vl_lbp_process(lbp, features, data, width, height, cellSize);
	//delete data;

	std::vector<std::vector<float>> fVL;
	for (size_t i = 0; i < numRows * numColumns; i++)
	{
		std::vector<float> fVL1;
		for (size_t j = 0; j < cellSize; j++)
		{
			fVL1.push_back(features[i*j + j]);
		}
		fVL.push_back(fVL1);
	}

	return fVL;
}

// Function main
int main(void)
{
	vnt::Utilites util;
	vnt::Matching vMatching;
	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath() + "\\";
	std::string vPath = util.replaceAll(vExePath, "\\", "/");
	VL_PRINT("Starting ...");
	cout << endl;
	cout << vExePath << endl;
	cout << vPath << endl;

	//\\ ColorFeret.
	vMatching.Feret(1);
	vMatching.Feret(2);

	cv::waitKey();
	cout << vExePath << endl;
	cout << vPath << endl;
	cout << "End." << endl;
	std::string end;
	cin >> end;
	return 0;
}