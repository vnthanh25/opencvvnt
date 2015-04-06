#include "Header\FeatureLBP.h"

void LBP()
{
	vnt::FeatureLBP lbp;
	vnt::Utilites util;
	//\\ Doc anh.
	cv::Mat image = util.createMatRandom(11, 11);
	std::vector<std::vector<int>> lbpfeature = lbp.LBP(image, 3, 1);
	//\\ Chuyen doi vector 2 chieu thanh Mat.
	cv::Mat lbpFeatureMat = util.convertV2ToMat(lbpfeature, lbpfeature[0].size(), lbpfeature.size());
	//util.writeMatInt(lbpFeatureMat, "Txt/lbpFeatureMat.txt");
	//\\ Hien thi ra man hinh dos cac gia tri dong nhat trong 256 gia tri.
	lbp.showLBPUniValues();

}
// Function main
int main(void)
{
	LBP();

	cv::waitKey();
	return 0;
}
