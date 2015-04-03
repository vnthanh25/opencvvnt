/*
VNThanh
- LBP feature.
*/

#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>
#include <string>

//\\ Chuyen doi so thanh chuoi nhi phan.
std::string convertUnsignedIntToBinary(unsigned int pValue)
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
	if (pValue.length() < 2)
		return false;
	int iCount = 0;
	char pre = pValue[0];
	for (int i = 1; i < pValue.length(); i++)
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
std::vector<unsigned int> initHisVal()
{
	std::vector<unsigned int> result;
	for (unsigned int i = 0; i < 256; i++)
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
	for (unsigned int i = 0; i < 256; i++)
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
	cv::Mat lbp(image.rows - pad * 2, image.cols - pad * 2, CV_8UC1, cv::Scalar(255));
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
//\\ Chia anh thanh n x n vung. Co cong them bien pad.
std::vector<cv::Mat> divImageEx(const cv::Mat image, int n, int pad)
{
	std::vector<cv::Mat> result;
	cv::Mat imageEx(image.cols + pad * 2, image.rows + pad * 2, CV_8UC1, cv::Scalar(255));
	image.copyTo(imageEx.colRange(pad, image.cols + pad).rowRange(pad, image.rows + pad));
	int width = image.cols / n + pad * 2;
	int height = image.rows / n + pad * 2;
	cv::Mat region;
	for (int y = 0; y < imageEx.rows - height; y += height - pad * 2)
	{
		for (int x = 0; x < imageEx.cols - width; x += width - pad * 2)
		{
			region = imageEx(cv::Rect(x, y, width, height));
			result.push_back(region);
		}
	}
	return result;
}
//\\ Tinh histogram cho cac gia tri dong nhat.
std::vector<int> hisLBPUni(const cv::Mat region, const std::vector<unsigned int> hisTemp)
{
	int len = hisTemp.size();//  58 muc gia tri.
	std::vector<int> result(len + 1);// 59 muc gia tri.
	for (int y = 0; y < region.rows; y++)
	{
		for (int x = 0; x < region.cols; x++)
		{
			unsigned int value = (unsigned int)region.at<uchar>(y, x);
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
//\\ Ham chinh.
int main(int argc, const char *argv[]) {
	//\\ Doc anh.
	cv::Mat image = cv::imread("images/lena.png", CV_8UC1);
	//\\ Khoi tao cac gia tri dong nhat.
	std::vector<unsigned int> hisValues = initHisVal();
	//\\ Ban kinh diem lan can pad = 1;
	int pad = 1;
	//\\ Chia anh thanh 3 x 3 vung. Co mo rong bien voi do lon la pad.
	std::vector<cv::Mat> regions = divImageEx(image, 3, pad);
	//\\ Tinh dac trung LBP voi 9 vung x 59 khoang.
	std::vector<std::vector<int>> lbpFeature;
	for (int i = 0; i < regions.size(); i++)
	{
		//\\ Tinh LBP cho moi vung.
		cv::Mat lbp = LBP(regions[i], pad);
		//\\ Tinh histogram (59 values) cho LBP with uniform partern.
		std::vector<int> lbphis = hisLBPUni(lbp, hisValues);
		lbpFeature.push_back(lbphis);
	}
	cv::waitKey(0);
	//\\cv::destroyAllWindows();
	return 0;
}