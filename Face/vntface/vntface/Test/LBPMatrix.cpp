/*
VNThanh
- LBP feature.
*/

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include <iostream>
#include <string>


cv::Mat LBP(std::string src_image)
{
	cv::Mat temp_image = cv::imread(src_image.c_str(), 1);
	cv::Mat Image(temp_image.rows, temp_image.cols, CV_8UC1);
	cv::Mat lbp(temp_image.rows, temp_image.cols, CV_8UC1);

	if (temp_image.channels() == 3)
		cv::cvtColor(temp_image, Image, CV_BGR2GRAY);

	cv::imshow("src_image", Image);

	int center = 0;
	int center_lbp = 0;

	for (int row = 1; row < Image.rows - 1; row++)
	{
		for (int col = 1; col < Image.cols - 1; col++)
		{
			center = (int)Image.at<uchar>(row, col);
			center_lbp = 0;

			if (center <= (int)Image.at<uchar>(row - 1, col - 1))
				center_lbp += 1;

			if (center <= (int)Image.at<uchar>(row - 1, col))
				center_lbp += 2;

			if (center <= (int)Image.at<uchar>(row - 1, col + 1))
				center_lbp += 4;

			if (center <= (int)Image.at<uchar>(row, col - 1))
				center_lbp += 8;

			if (center <= (int)Image.at<uchar>(row, col + 1))
				center_lbp += 16;

			if (center <= (int)Image.at<uchar>(row + 1, col - 1))
				center_lbp += 32;

			if (center <= (int)Image.at<uchar>(row + 1, col))
				center_lbp += 64;

			if (center <= (int)Image.at<uchar>(row + 1, col + 1))
				center_lbp += 128;

			std::cout << "center lbp value: " << center_lbp << std::endl;
			lbp.at<uchar>(row, col) = center_lbp;
		}
	}

	cv::imshow("lbp_image", lbp);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return lbp;
}

int main(int argc, const char *argv[]) {
	LBP("images/lena.png");
	return 0;
}