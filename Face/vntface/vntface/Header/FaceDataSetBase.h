/*
VNThanh
- Lop co so cho cac lop DataSet.
*/
#pragma once //\\ File header duoc include nhieu nhat 1 lan.
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

namespace vnt
{
	/********** class FaceDataSetBase **********/
	class FaceDataSetBase
	{
	private:
	public:
		FaceDataSetBase();
		~FaceDataSetBase();

		//\\ Lay tat ca Id theo thu tu tang dan.
		virtual std::vector<std::string> aGetsAllIds() = 0;

		//\\ Lay duong dan thu muc.
		virtual std::string aGetPath(const std::string pId) = 0;
		//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm"
		virtual std::vector<std::string> aGetsAllFileName(const std::string pId) = 0;
		//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm". Co duong dan tuong doi.
		virtual std::vector<std::string> aGetsAllFullFileName(const std::string pId, const std::string pPath) = 0;
	};
}