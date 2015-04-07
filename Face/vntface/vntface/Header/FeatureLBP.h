/*
VNThanh
- Rut trich dac trung.
*/
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>
#include <string>

#include "Utilities.h"

namespace vnt
{
	class FeatureLBP
	{
	private:
		/********** private Members **********/
		vnt::Utilites util;

		/********** private Methods **********/
		//\\ Kiem tra chuoi nhi phan dong nhat (khi so dich chuyen tu 0->1 hoac tu 1->0 la <= 2).
		bool checkUniformPartern(const std::string pValue);
		//\\ Khoi tao 58 gia tri dong nhat.
		std::vector<int> initHisVal();
		//\\ Chia anh thanh n x n vung.
		std::vector<cv::Mat> divImage(const cv::Mat image, int n);
		//\\ Chia anh thanh n x n vung. Co cong them bien (pad) de tinh convolution.
		//\\ Chieu rong/cao cua anh truyen vao phai nho hon tich chieu rong/cao cua n vung con cong them 2pad.
		std::vector<cv::Mat> divImageDilation(const cv::Mat image, int n, int pad);
		//\\ Chia anh thanh n x n vung. Co cong them bien (pad) de tinh convolution.
		//\\ Chieu rong/cao cua anh truyen vao phai lon hon tich chieu rong/cao cua n vung con cong them 2pad.
		std::vector<cv::Mat> divImageErosion(const cv::Mat image, int n, int pad);
		//\\ Chia anh thanh n x n vung. Co cong them bien (pad) de tinh convolution.
		std::vector<cv::Mat> divImage(const cv::Mat image, int n, int pad);
		//\\ Tinh histogram cho cac gia tri dong nhat.
		std::vector<int> hisLBPUni(const cv::Mat region, const std::vector<int> hisTemp);
		//\\ Tinh LBP cua ma tran co bien. Tra ve ket qua ma tran k co bien. (bien = pad).
		cv::Mat LBP(const cv::Mat image, int pad);
		cv::Mat LBP(const std::string src_image, int pad);

	public:
		/********** Constructor **********/
		FeatureLBP();
		~FeatureLBP();
		/********** public Methods **********/
		//\\ Hien thi ra man hinh dos cac gia tri dong nhat trong 256 gia tri.
		void showLBPUniValues();
		//\\ Tinh dac trung LBP cho 1 anh xam, chia lam n x n vung va co ban kinh pad.
		std::vector<std::vector<int>> LBP(const cv::Mat image, int n, int pad);

		//\\ Tao Mat voi gia tri.
		cv::Mat createMat(int width, int height);

	};
}