#include "..\Header\Utilities.h"
#include <ctime>

using namespace vnt;

/********** Constructor **********/
Utilites::Utilites()
{
}
Utilites::~Utilites()
{
}

//\\ Bo sung ky tu "c" ve ben trai chuoi ky tu.
string Utilites::leftPad(string s, int len, char c)
{
	std::string result = s;
	for (int i = s.length(); i < len; i++)
	{
		result = c + result;
	}
	return result;
}
//\\ Ghi Mat ra file.
void Utilites::writeMatUChar(Mat img, string fname)
{
	FileStorage file(fname, FileStorage::WRITE);
	//file << "mat" << img;
	file << "mat" << "[:";
	string sValue = "";
	for (int x = 0; x < img.cols; x++)
	{
		stringstream out;
		out << x;
		string value = out.str();
		sValue += leftPad(value, 3, ' ') + " ";
	}
	file << "{" << "x" << sValue + "-1" << "}";
	for (int y = 0; y < img.rows; y++)
	{
		sValue = "";
		for (int x = 0; x < img.cols; x++)
		{
			int iv = (int)img.at<uchar>(Point(x, y));
			stringstream out;
			out << iv;
			string value = out.str();
			sValue += leftPad(value, 3, ' ') + " ";
		}
		stringstream out;
		out << y;
		file << "{" << "y" << sValue + out.str() << "}";
	}
	file << "]";
	file.release();
}
void Utilites::writeMatInt(Mat img, string fname)
{
	FileStorage file(fname, FileStorage::WRITE);
	//file << "mat" << img;
	file << "mat" << "[:";
	string sValue = "";
	for (int x = 0; x < img.cols; x++)
	{
		stringstream out;
		out << x;
		string value = out.str();
		sValue += leftPad(value, 3, ' ') + " ";
	}
	file << "{" << "x" << sValue + "-1" << "}";
	for (int y = 0; y < img.rows; y++)
	{
		sValue = "";
		for (int x = 0; x < img.cols; x++)
		{
			int iv = img.at<int>(Point(x, y));
			stringstream out;
			out << iv;
			string value = out.str();
			sValue += leftPad(value, 3, ' ') + " ";
		}
		stringstream out;
		out << y;
		file << "{" << "y" << sValue + out.str() << "}";
	}
	file << "]";
	file.release();
}
void Utilites::writeMatBasic(Mat img, string fname)
{
	FileStorage storage(fname, cv::FileStorage::WRITE);
	storage << "image" << img;
	storage.release();
}
Mat Utilites::readMatBasic(string fname)
{
	Mat result;
	FileStorage storage(fname, cv::FileStorage::READ);
	if (storage.isOpened())
	{
		storage["image"] >> result;
		storage.release();
	}
	return result;
}
Mat Utilites::convolutionInt(Mat img, Mat tmp)
{
	Mat src = Mat::zeros(img.rows + tmp.rows - 1, img.cols + tmp.cols - 1, CV_32SC1);
	img.copyTo(src.rowRange(0, img.rows).colRange(0, img.cols));
	Mat dst = Mat::zeros(img.size(), CV_32SC1);
	// Step by step of the source image.
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			int sum = 0;
			// Step by step of the template.
			for (int m = 0; m < tmp.rows; m++)
			{
				for (int n = 0; n < tmp.cols; n++)
				{
					int isrc = src.at<int>(y + m, x + n);
					int itmp = tmp.at<int>(m, n);
					sum += src.at<int>(y + m, x + n) * tmp.at<int>(m, n);
				}
			}
			dst.at<int>(y, x) = sum;
		}
	}
	return dst;
}


//\\ Chuyen doi so thanh chuoi nhi phan.
std::string Utilites::convertUnsignedIntToBinary(int pValue)
{
	std::string result = "";
	while (pValue > 0)
	{
		result = std::to_string(pValue % 2) + result;
		pValue = pValue / 2;
	}
	return result;
}

//\\ Chuyen vector<vector<int>> thanh Mat.
cv::Mat Utilites::convertV2IToMat(std::vector<std::vector<int>> lbpFeature, int width, int height)
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
//\\ Chuyen Mat thanh vector<vector<int>>.
std::vector<std::vector<int>> Utilites::convertMatToV2I(cv::Mat image)
{
	std::vector<std::vector<int>> result;
	size_t rows = image.rows;
	size_t cols = image.cols;
	for (size_t y = 0; y < rows; y++)
	{
		std::vector<int> col;
		for (size_t x = 0; x < cols; x++)
		{
			col.push_back(image.at<int>(y, x));
		}
		result.push_back(col);
	}
	return result;
}
//\\ Chuyen vector<vector<double>> thanh Mat.
cv::Mat Utilites::convertV2DToMat(std::vector<std::vector<double>> lbpFeature, int width, int height)
{
	cv::Mat result = cv::Mat::zeros(height, width, CV_64FC1);
	for (size_t y = 0; y < lbpFeature.size(); y++)
	{
		for (size_t x = 0; x < lbpFeature[y].size(); x++)
		{
			result.at<double>(y, x) = lbpFeature[y][x];
		}
	}
	return result;
}
//\\ Chuyen Mat thanh vector<vector<double>>.
std::vector<std::vector<double>> Utilites::convertMatToV2D(cv::Mat image)
{
	std::vector<std::vector<double>> result;
	size_t rows = image.rows;
	size_t cols = image.cols;
	for (size_t y = 0; y < rows; y++)
	{
		std::vector<double> col;
		for (size_t x = 0; x < cols; x++)
		{
			col.push_back(image.at<double>(y, x));
		}
		result.push_back(col);
	}
	return result;
}

//\\ Lay so tiep theo tu chuoi so truyen vao.
std::string Utilites::increaseNumber(const std::string pNumber, const int pIncrease)
{
	std::string result;
	int len = pNumber.length();
	int number = std::stoi(pNumber) + pIncrease;
	result = std::to_string(number);
	result = leftPad(result, len, '0');
	return result;
}

//\\ Get current date/time, format is YYYY-MM-DD.HH:mm:ss
std::string Utilites::currentDateTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

//\\ Tao thu muc.
int Utilites::makeDir(std::string folderName)
{
	std::string folderCreateCommand = "mkdir " + folderName;
	system(folderCreateCommand.c_str());
	return 1;
}

//\\ Thay the chuoi
std::string Utilites::replace(const std::string str, const std::string from, const std::string to)
{
	std::string result = str;
	size_t start_pos = result.find(from);
	if (start_pos == std::string::npos)
		return result;
	result.replace(start_pos, from.length(), to);
	return result;
}
//\\ Thay the tat ca trong chuoi.
std::string Utilites::replaceAll(const std::string str, const std::string from, const std::string to)
{
	std::string result = str;
	if (from.empty())
		return result;
	size_t start_pos = 0;
	while ((start_pos = result.find(from, start_pos)) != std::string::npos) {
		result.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return result;
}