#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace vnt
{
	class Rotation
	{
	public:
		vector<Point> findRect(Mat src_gray);
		bool isLeft(vector<Point> vctPoint);
		Mat RotationWithHough(Mat src_gray);

		Rotation();
		~Rotation();

	private:

	};
}