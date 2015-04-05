#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace vnt
{
	class DataMat
	{
	public:
		DataMat();
		~DataMat();
		static Mat src, gray, filter, edge, dst;
	};
}
