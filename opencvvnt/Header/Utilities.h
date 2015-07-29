#pragma once //\\ File header duoc include nhieu nhat 1 lan.
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace vnt
{
	class Utilites
	{
	public:
		/********** Constructor **********/
		Utilites();
		~Utilites();


		RNG rng;

		double angle(Point pt1, Point pt2, Point pt0);
		void setLabel(Mat& im, const string label, vector<Point>& contour);

		//\\ Bo sung ky tu "c" ve ben trai chuoi ky tu.
		string leftPad(string s, int len, char c);
		//\\ Ghi Mat ra file.
		void writeMatUChar(Mat img, string fname);
		void writeMatInt(Mat img, string fname);
		void writeMatBasic(Mat img, string fname);
		void readMatBasic(Mat img, string fname);

		Mat convolutionInt(Mat img, Mat tmp);

		//\\ Chuyen doi so thanh chuoi nhi phan.
		std::string convertUnsignedIntToBinary(int pValue);

		//\\ Chuyen vector<vector<int>> thanh Mat.
		cv::Mat convertV2IToMat(std::vector<std::vector<int>> lbpFeature, int width, int height);
		//\\ Chuyen Mat thanh vector<vector<int>>.
		std::vector<std::vector<int>> convertMatToV2I(cv::Mat image);
		//\\ Chuyen vector<vector<double>> thanh Mat.
		cv::Mat convertV2DToMat(std::vector<std::vector<double>> lbpFeature, int width, int height);
		//\\ Chuyen Mat thanh vector<vector<double>>.
		std::vector<std::vector<double>> convertMatToV2D(cv::Mat image);

		//\\ Lay so tiep theo tu chuoi so truyen vao.
		std::string increaseNumber(const std::string pNumber, const int pIncrease);
		//\\ Get current date/time, format is YYYY-MM-DD.HH:mm:ss
		std::string currentDateTime();
		//\\ Tao thu muc.
		int makeDir(std::string folderName);

		Mat detectsimpleshape(Mat src);


	};
}
