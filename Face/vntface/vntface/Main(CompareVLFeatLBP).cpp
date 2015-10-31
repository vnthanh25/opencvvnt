extern "C" {
#include <vl/generic.h>
#include <vl/lbp.h>
}

#include "Header\FeatureLBP.h"
#include <fstream>


std::vector<std::vector<int>> LBP()
{
	vnt::FeatureLBP lbp;
	vnt::Utilites util;
	//\\ Doc anh.
	//cv::Mat img = lbp.createMat(11, 11);
	cv::Mat img = imread("images/lena1.png", CV_8UC1);
	int n = 8;
	std::vector<std::vector<int>> lbpfeature = lbp.LBP(img, n, 1);
	////\\ Chuyen doi vector 2 chieu thanh Mat.
	//cv::Mat lbpFeatureMat = util.convertV2IToMat(lbpfeature, lbpfeature[0].size(), lbpfeature.size());
	////util.writeMatInt(lbpFeatureMat, "Txt/lbpFeatureMat.txt");
	////\\ Hien thi ra man hinh dos cac gia tri dong nhat trong 256 gia tri.
	//lbp.showLBPUniValues();

	return lbpfeature;
}

std::vector<std::vector<float>> vlfeat()
{
	cv::Mat img = imread("images/lena.png", CV_8UC1);
	// Convert value from uchar to float.
	//C1:
	//cv::Mat imgf;
	//img.convertTo(imgf, CV_32FC1);
	//float* data = imgf.ptr<float>();
	//C2:
	float* data = new float[img.rows * img.cols];
	for (size_t i = 0; i < img.rows; i++)
	{
		for (size_t j = 0; j < img.cols; j++)
		{
			uchar c = img.at<uchar>(i, j);
			float f = (float)c;
			data[i*j + j] = f;
		}
	}

	VlLbp* lbp = vl_lbp_new(VlLbpMappingType::VlLbpUniform, false);
	vl_size cellSize = vl_lbp_get_dimension(lbp);
	vl_size width = img.cols;
	vl_size height = img.rows;
	const int numColumns = floor(width / cellSize);
	const int numRows = floor(height / cellSize);
	int featureSize = numColumns * numRows * cellSize;
	//float* features = new float[];
	float features[3712] = {};
	vl_lbp_process(lbp, features, data, width, height, cellSize);

	std::vector<std::vector<float>> fVL;
	for (size_t i = 0; i < 64; i++)
	{
		std::vector<float> fVL1;
		for (size_t j = 0; j < 58; j++)
		{
			fVL1.push_back(features[i*j + j]);
		}
		fVL.push_back(fVL1);
	}


	//vnt::FeatureLBP lbpf;
	//int n = 8;
	//std::vector<std::vector<int>> lbpfeature = lbpf.LBP(img, n, 1);

	return fVL;
}

void writeFile(std::string fileName)
{
}
// Function main
int main(void)
{
	VL_PRINT("Starting ...");
	vnt::Utilites util;
	//\\ Duong dan den nguon du lieu.
	std::string vExePath = util.GetExePath() + "\\";
	std::string vPath = util.replaceAll(vExePath, "\\", "/");

	// VLFeat.
	std::vector<std::vector<float>> vllbp = vlfeat();
	std::vector<float> vllbpvector;
	std::ofstream ofvllbp(vPath + "lbp(vlfeat).txt");
	for (size_t i = 0; i < 64; i++)
	{
		for (size_t j = 0; j < 58; j++)
		{
			float value = (float)vllbp[i][j];
			vllbpvector.push_back(value);
			ofvllbp << value << std::endl;
		}
	}
	ofvllbp.close();
	// LBP.
	std::vector<std::vector<int>> lbp = LBP();
	std::vector<float> lbpvector;
	std::ofstream oflbp(vPath + "lbp.txt");
	for (size_t i = 0; i < 64; i++)
	{
		for (size_t j = 0; j < 58; j++)
		{
			float value = (float)lbp[i][j];
			lbpvector.push_back(lbp[i][j]);
			oflbp << value << std::endl;
		}
	}
	oflbp.close();

	cv::waitKey();
	return 0;
}