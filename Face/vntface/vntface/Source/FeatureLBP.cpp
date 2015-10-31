#include "..\Header\FeatureLBP.h"

using namespace vnt;

/********** Constructor **********/
FeatureLBP::FeatureLBP()
{
}
FeatureLBP::~FeatureLBP()
{
}

/********** private Methods **********/
//\\ Kiem tra chuoi nhi phan dong nhat (khi so dich chuyen tu 0->1 hoac tu 1->0 la <= 2).
bool FeatureLBP::checkUniformPartern(const std::string pValue)
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
//\\ Khoi tao 58 gia tri dong nhat.
std::vector<int> FeatureLBP::initHisVal()
{
	std::vector<int> result;
	for (int i = 0; i < 256; i++)
	{
		std::string bin = util.leftPad(util.convertUnsignedIntToBinary(i), 8, '0');
		if (checkUniformPartern(bin))
		{
			result.push_back(i);
		}
	}
	return result;
}
//\\ Chia anh thanh n x n vung.
std::vector<cv::Mat> FeatureLBP::divImage(const cv::Mat image, int n)
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
std::vector<cv::Mat> FeatureLBP::divImageDilation(const cv::Mat image, int n, int pad)
{
	std::vector<cv::Mat> result;
	int width = image.cols / n + pad * 2;
	int height = image.rows / n + pad * 2;
	cv::Mat imageDil(image.rows + pad * 2, image.cols + pad * 2, CV_8UC1, cv::Scalar(0));
	image.copyTo(imageDil.colRange(pad, image.cols + pad).rowRange(pad, image.rows + pad));
	cv::Mat region;
	for (int y = 0; y < imageDil.rows - height + 1; y += height - pad * 2)
	{
		for (int x = 0; x < imageDil.cols - width + 1; x += width - pad * 2)
		{
			region = imageDil(cv::Rect(x, y, width, height));
			//util.writeMatUChar(region, "Txt/region" + to_string(y) + "_" + to_string(x) + ".txt");
			result.push_back(region);
		}
	}
	return result;
}
//\\ Chia anh thanh n x n vung. Co cong them bien (pad) de tinh convolution.
//\\ Chieu rong/cao cua anh truyen vao phai lon hon tich chieu rong/cao cua n vung con cong them 2pad.
std::vector<cv::Mat> FeatureLBP::divImageErosion(const cv::Mat image, int n, int pad)
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
			//util.writeMatUChar(region, "Txt/region" + to_string(y) + "_" + to_string(x) + ".txt");
			result.push_back(region);
		}
	}
	return result;
}
//\\ Chia anh thanh n x n vung. Co cong them bien (pad) de tinh convolution.
std::vector<cv::Mat> FeatureLBP::divImage(const cv::Mat image, int n, int pad)
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
std::vector<int> FeatureLBP::hisLBPUni(const cv::Mat region, const std::vector<int> hisTemp)
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
//\\ Tinh LBP cua ma tran co bien. Tra ve ket qua ma tran k co bien. (bien = pad).
cv::Mat FeatureLBP::LBP(const cv::Mat image, int pad)
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

			lbp.at<uchar>(row - pad, col - pad) = center_lbp;
		}
	}
	return lbp;
}
cv::Mat FeatureLBP::LBP(const std::string src_image, int pad)
{
	cv::Mat temp_image = cv::imread(src_image.c_str(), 1);
	cv::Mat Image(temp_image.rows, temp_image.cols, CV_8UC1);
	if (temp_image.channels() == 3)
		cv::cvtColor(temp_image, Image, CV_BGR2GRAY);
	cv::Mat lbp = LBP(Image, pad);
	return lbp;
}

/********** public Methods **********/
//\\ Hien thi ra man hinh dos cac gia tri dong nhat trong 256 gia tri.
void FeatureLBP::showLBPUniValues()
{
	int iCount = 0;
	for (int i = 0; i < 256; i++)
	{
		std::string bin = util.leftPad(util.convertUnsignedIntToBinary(i), 8, '0');
		if (checkUniformPartern(bin))
		{
			iCount++;
			std::cout << std::to_string(iCount) + " : " + bin + " : " + std::to_string(i) << std::endl;
		}
	}
	std::cout << "Total : " + std::to_string(iCount);
}
//\\ Tinh dac trung LBP cho 1 anh xam, chia lam n x n vung va co ban kinh pad.
std::vector<std::vector<int>> FeatureLBP::LBP(const cv::Mat image, int n, int pad)
{
	std::vector<std::vector<int>> result;
	//\\ Khoi tao 58 gia tri dong nhat trong 256 gia tri.
	std::vector<int> hisValues = initHisVal();
	//\\ Chia anh thanh n x n vung. Co mo rong bien voi do lon la pad.
	std::vector<cv::Mat> regions = divImage(image, n, pad);
	//\\ Tinh dac trung LBP voi n x n vung x 59 khoang.
	for (size_t i = 0; i < regions.size(); i++)
	{
		//\\ Tinh LBP cho moi vung.
		cv::Mat lbp = LBP(regions[i], pad);
		//util.writeMatUChar(lbp, "Txt/lbp" + to_string(i) + ".txt");

		//\\ Tinh histogram (59 values) cho LBP with uniform partern.
		std::vector<int> lbphis = hisLBPUni(lbp, hisValues);
		result.push_back(lbphis);
	}
	return result;
}


//\\ Tao Mat voi gia tri.
cv::Mat FeatureLBP::createMat(int width, int height)
{
	cv::Mat result;
	result = cv::Mat(height, width, CV_8UC1, cv::Scalar(0));
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (y % 2 == 1 || x % 2 == 1)
				result.at<uchar>(y, x) = 1;
		}
	}
	return result;
}
