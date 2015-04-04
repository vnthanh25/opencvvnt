#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace vnt
{
	class DataMat
	{
	public:
		static Mat src, gray, filter, edge, dst;
	};

	class Utilites
	{
	public:

		
		RNG rng;
		
		double angle(Point pt1, Point pt2, Point pt0);
		void setLabel(Mat& im, const string label, vector<Point>& contour);
		Mat detectsimpleshape(Mat src);

		string leftPad(string s, int len, char c);
		void writeMatUChar(Mat img, string fname);
		void writeMatInt(Mat img, string fname);
		void writeMatBasic(Mat img, string fname);
		void readMatBasic(Mat img, string fname);

		Mat convolutionInt(Mat img, Mat tmp);

		Utilites();
		~Utilites();

	private:

	};
}
