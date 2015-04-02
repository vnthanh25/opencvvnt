/*
VNThanh
- LBP feature.
*/

#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>
#include <string>

#include "Utilities.h"
vnt::Utilites util;

//\\ Chuyen doi so thanh chuoi nhi phan.
std::string convertUnsignedIntToBinary(int pValue)
{
	std::string result = "";
	while (pValue > 0)
	{
		result = std::to_string(pValue % 2) + result;
		pValue = pValue / 2;
	}
	return result;
}

//\\ Kiem tra chuoi nhi phan dong nhat (khi so dich chuyen tu 0->1 hoac tu 1->0 la <= 2).
bool checkUniformPartern(const std::string pValue)
{
	int len = pValue.length();
	if (len < 2)
		return false;
	int iCount = 0;
	char pre = pValue[0];
	for (int i = 1; i < len; i++)
	{
		if (pValue[i] != pre)
		{
			if (iCount > 1)
				return false;
			iCount++;
		}
		pre = pValue[i];
	}
	return true;
}

//\\ Bo sung ky tu "c" ve ben trai chuoi ky tu.
std::string leftPad(const std::string s, int len, char c)
{
	std::string result = s;
	for (int i = s.length(); i < len; i++)
	{
		result = c + result;
	}
	return result;
}

//\\ Khoi tao 58 gia tri dong nhat.
std::vector<int> initHisVal()
{
	std::vector<int> result;
	for (int i = 0; i < 256; i++)
	{
		std::string bin = leftPad(convertUnsignedIntToBinary(i), 8, '0');
		if (checkUniformPartern(bin))
		{
			result.push_back(i);
		}
	}
	return result;
}

//\\ Hien thi ra man hinh dos cac gia tri dong nhat trong 256 gia tri.
void showLBPUniValues()
{
	int iCount = 0;
	for (int i = 0; i < 256; i++)
	{
		std::string bin = leftPad(convertUnsignedIntToBinary(i), 8, '0');
		if (checkUniformPartern(bin))
		{
			iCount++;
			std::cout << std::to_string(iCount) + " : " + bin + " : " + std::to_string(i) << std::endl;
		}
	}
	std::cout << "Total : " + std::to_string(iCount);
}

//\\ Tinh LBP cua ma tran co bien. Tra ve ket qua ma tran k co bien. (bien = pad).
cv::Mat LBP(const cv::Mat image, int pad)
{
	cv::Mat lbp(image.rows - pad * 2, image.cols - pad * 2, CV_8UC1, cv::Scalar(0));
	int center = 0;
	int center_lbp = 0;

	for (int row = pad; row < image.rows - pad; row++)
	{
		for (int col = pad; col < image.cols - pad; col++)
		{
			center = (int)image.at<uchar>(row, col);
			center_lbp = 0;

			if (center <= (int)image.at<uchar>(row - pad, col - pad))
				center_lbp += 1;

			if (center <= (int)image.at<uchar>(row - pad, col))
				center_lbp += 2;

			if (center <= (int)image.at<uchar>(row - pad, col + pad))
				center_lbp += 4;

			if (center <= (int)image.at<uchar>(row, col + pad))
				center_lbp += 8;

			if (center <= (int)image.at<uchar>(row + pad, col + pad))
				center_lbp += 16;

			if (center <= (int)image.at<uchar>(row + pad, col))
				center_lbp += 32;

			if (center <= (int)image.at<uchar>(row + pad, col - pad))
				center_lbp += 64;

			if (center <= (int)image.at<uchar>(row, col - pad))
				center_lbp += 128;

			lbp.at<uchar>(row - 1, col - 1) = center_lbp;
		}
	}
	return lbp;
}

cv::Mat LBP(const std::string src_image, int pad)
{
	cv::Mat temp_image = cv::imread(src_image.c_str(), 1);
	cv::Mat Image(temp_image.rows, temp_image.cols, CV_8UC1);
	if (temp_image.channels() == 3)
		cv::cvtColor(temp_image, Image, CV_BGR2GRAY);
	cv::Mat lbp = LBP(Image, pad);
	return lbp;
}

//\\ Chia anh thanh n x n vung.
std::vector<cv::Mat> divImage(const cv::Mat image, int n)
{
	std::vector<cv::Mat> result;
	int width = image.cols / n;
	int height = image.rows / n;
	cv::Mat region;
	for (int y = 0; y < image.rows - height; y += height)
	{
		for (int x = 0; x < image.cols - width; x += width)
		{
			region = image(cv::Rect(x, y, width, height));
			result.push_back(region);
		}
	}
	return result;
}

//\\ Chia anh thanh n x n vung. Co cong them bien (pad) de tinh convolution.
//\\ Chieu rong/cao cua anh truyen vao phai nho hon tich chieu rong/cao cua n vung con cong them 2pad.
std::vector<cv::Mat> divImageDilation(const cv::Mat image, int n, int pad)
{
	std::vector<cv::Mat> result;
	int width = image.cols / n + pad * 2;
	int height = image.rows / n + pad * 2;
	cv::Mat imageDil(image.cols + pad * 2, image.rows + pad * 2, CV_8UC1, cv::Scalar(0));
	image.copyTo(imageDil.colRange(pad, image.cols + pad).rowRange(pad, image.rows + pad));
	cv::Mat region;
	for (int y = 0; y < imageDil.rows - height + 1; y += height - pad * 2)
	{
		for (int x = 0; x < imageDil.cols - width + 1; x += width - pad * 2)
		{
			region = imageDil(cv::Rect(x, y, width, height));
			util.writeMatUChar(region, "Txt/region" + to_string(y) + "_" + to_string(x) + ".txt");
			result.push_back(region);
		}
	}
	return result;
}

//\\ Chia anh thanh n x n vung. Co cong them bien (pad) de tinh convolution.
//\\ Chieu rong/cao cua anh truyen vao phai lon hon tich chieu rong/cao cua n vung con cong them 2pad.
std::vector<cv::Mat> divImageErosion(const cv::Mat image, int n, int pad)
{
	std::vector<cv::Mat> result;
	//\\ Tinh chieu rong va cao cua vung can tinh.
	int width = image.cols / n;
	int height = image.rows / n;
	int widthmod = image.cols - (width * n + pad * 2);
	int heightmod = image.rows - (height * n + pad * 2);
	cv::Mat imageEro = image(cv::Rect(widthmod / 2, heightmod / 2, width * n + pad * 2, height * n + pad * 2));
	width += pad * 2;
	height += pad * 2;
	cv::Mat region;
	for (int y = 0; y < imageEro.rows - height + 1; y += height - pad * 2)
	{
		for (int x = 0; x < imageEro.cols - width + 1; x += width - pad * 2)
		{
			region = imageEro(cv::Rect(x, y, width, height));
			util.writeMatUChar(region, "Txt/region" + to_string(y) + "_" + to_string(x) + ".txt");
			result.push_back(region);
		}
	}
	return result;
}

//\\ Chia anh thanh n x n vung. Co cong them bien (pad) de tinh convolution.
std::vector<cv::Mat> divImage(const cv::Mat image, int n, int pad)
{
	std::vector<cv::Mat> result;
	//\\ Tinh chieu rong va cao cua vung can tinh.
	int width = image.cols / n;
	int height = image.rows / n;
	int widthmod = image.cols - (width * n + pad * 2);
	int heightmod = image.rows - (height * n + pad * 2);
	if (widthmod < 0 || heightmod < 0)
		result = divImageDilation(image, n, pad);
	else
		result = divImageErosion(image, n, pad);

	return result;
}

//\\ Tinh histogram cho cac gia tri dong nhat.
std::vector<int> hisLBPUni(const cv::Mat region, const std::vector<int> hisTemp)
{
	int len = hisTemp.size();//  58 muc gia tri.
	std::vector<int> result(len + 1);// 59 muc gia tri.
	for (int y = 0; y < region.rows; y++)
	{
		for (int x = 0; x < region.cols; x++)
		{
			int value = (int)region.at<uchar>(y, x);
			//\\ Tim trong 58 gia tri.
			bool isFound = false;
			for (int n = 0; n < len; n++)
			{
				if (value == hisTemp[n])
				{
					result[n] += 1;
					isFound = true;
					break;
				}
			}// for count of his value.
			//\\ Neu k co trong 58 gia tri thi cho vao gia tri thu 59.
			if (!isFound)
				result[len] += 1;
		}// for cols
	}// for rows
	return result;
}

cv::Mat createMat()
{
	cv::Mat result;
	size_t width = 11;
	size_t height = 11;
	result = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (y % 2 == 1 || x % 2 == 1)
				result.at<uchar>(y, x) = 1;
		}
	}
	return result;
}

//\\ Chuyen vector<vector<in>> thanh Mat.
cv::Mat convertV2ToMat(std::vector<std::vector<int>> lbpFeature, int width, int height)
{
	cv::Mat result = cv::Mat::zeros(height, width, CV_32FC1);
	for (size_t y = 0; y < lbpFeature.size(); y++)
	{
		for (size_t x = 0; x < lbpFeature[y].size(); x++)
		{
			result.at<int>(y, x) = lbpFeature[y][x];
		}
	}
	return result;
}

//\\ Ham chinh.
int main(int argc, const char *argv[]) {
	//\\ Doc anh.
	////cv::Mat image = createMat();
	cv::Mat image = cv::imread("images/lena.png", CV_8UC1);
	util.writeMatUChar(image, "Txt/image.txt");
	//\\ Khoi tao 58 gia tri dong nhat trong 256 gia tri.
	std::vector<int> hisValues = initHisVal();
	//\\ Ban kinh diem lan can pad = 1;
	int pad = 1;
	//\\ Chia anh thanh 3 x 3 vung. Co mo rong bien voi do lon la pad.
	std::vector<cv::Mat> regions = divImage(image, 3, pad);
	//\\ Tinh dac trung LBP voi 9 vung x 59 khoang.
	std::vector<std::vector<int>> lbpFeature;
	for (int i = 0; i < regions.size(); i++)
	{
		//\\ Tinh LBP cho moi vung.
		cv::Mat lbp = LBP(regions[i], pad);
		util.writeMatUChar(lbp, "Txt/lbp" + to_string(i) + ".txt");
		//\\ Tinh histogram (59 values) cho LBP with uniform partern.
		std::vector<int> lbphis = hisLBPUni(lbp, hisValues);
		lbpFeature.push_back(lbphis);
	}
	//\\ Chuyen doi vector 2 chieu thanh Mat.
	cv::Mat lbpFeatureMat = convertV2ToMat(lbpFeature, hisValues.size() + 1, regions.size());
	util.writeMatInt(lbpFeatureMat, "Txt/lbpFeatureMat.txt");

	showLBPUniValues();
	cv::waitKey(0);
	//\\cv::destroyAllWindows();
	return 0;
}
