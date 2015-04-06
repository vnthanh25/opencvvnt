/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#include "../Header/ColorFeret.h"

namespace vnt
{
	/********** FaceDataSet: Data player **********/
	class FaceDataSet
	{
	private:
		FaceDataSetBase* mDataSet;
	public:
		/********** Constructor **********/
		FaceDataSet();
		~FaceDataSet();
	
		/********** public Methods **********/
		//\\ Lay 1 anh cua 1 nguoi. Mac dinh la lay anh dau tien neu co nhieu anh.
		cv::Mat aGetFace(const std::string pId, const std::string pPath = "");
		//\\ Lay 1 facetrack cua 1 nguoi.
		std::vector<cv::Mat> aGetsAllFace(const std::string pId, const std::string pPath = "");
	};
}