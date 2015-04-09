/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

#ifndef _FaceDataSetBase_
#define _FaceDataSetBase_
#include "FaceDataSetBase.h"
#endif

namespace vnt
{
	/********** FaceDataSet: Data player **********/
	class FaceDataSet
	{
	private:
		FaceDataSetBase* mDataSetBase;
		//\\ Danh sach facetrack
		std::vector<std::vector<cv::Mat>> mFaceTracks;
	public:
		/********** Constructor **********/
		FaceDataSet();
		~FaceDataSet();
	
		/********** public Methods **********/
		////\\ Lay nguon anh.
		//FaceDataSetBase aGetDataSetBase();
		////\\ Gan nguon anh.
		//void aSetDataSetBase(FaceDataSetBase pDataSetBase);
		////\\ Lay danh sach facetrack.
		//std::vector<std::vector<cv::Mat>> aGetFaceTraks();
		////\\ Gan danh sach facetrack.
		//void aSetFaceTracks(std::vector<std::vector<cv::Mat>> pFaceTracks);
	
		//\\ Doc tat ca cac anh. Roi gan vao danh sach facetrack.
		std::vector<cv::Mat> aReadsImage(std::vector<std::string> pAllFileName, const std::string pPath = "");

	};
}