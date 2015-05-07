/*
VNThanh
- Du lieu anh ve mat nguoi.
*/
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

//#ifndef _FaceDataSetBase_
//#define _FaceDataSetBase_
//#include "FaceDataSetBase.h"
//#endif
#include "FaceDataSetBase.h"

namespace vnt
{
	/********** class VNTDataSet: image format ("subjectid_date_pose_meta.ppm") **********/
	class VNTDataSet : public FaceDataSetBase
	{
	private:

		/********** private Methods **********/

	public:
		/********** public Members **********/

		//\\ Image format: "Image[Number].jpg".
		const std::string mImageName = "Image";
		//\\ Id dau tien va Id cuoi cung.
		const std::string mIds = "00,14";
		//\\ So thu tu cua file trong thu muc.
		const std::string mNumber = "000,092";//\\ Tu 93 den 185 la seri 2 dung de test.
		std::string mImageType = ".img";

		/********** Constructor **********/
		VNTDataSet();
		~VNTDataSet();

		/********** public Methods **********/
		//\\ Get Subject Id.
		std::string aGetId(const int pIndex);
		//\\ Get Number.
		std::string aGetNumber(const int pIndex);

		//\\ Lay tat ca Id.
		std::vector<std::string> aGetsAllId();
		//\\ Lay tat ca Number.
		std::vector<std::string> aGetsAllNumber();

		//\\ Lay tat ca Id theo thu tu tang dan.
		std::vector<std::string> aGetsAllIds();
		//\\ Lay tat ca Number theo thu tu tang dan.
		std::vector<std::string> aGetsAllNumbers();

		//\\ Lay duong dan thu muc.
		std::string aGetPath(const std::string pId);
		//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm"
		std::vector<std::string> aGetsAllFileName(const std::string pId);
		//\\ Lay to hop cac pose tuong ung voi goc nhin trong ten file.
		std::vector<int> aGetsAllPose(const std::string pId);
		//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm". Co duong dan tuong doi.
		std::vector<std::string> aGetsAllFullFileName(const std::string pId, const std::string pPath);
	

		//\\ Chia moi FaceTrack lam n FaceTrack va luu ra file.
		int aVNTDataSetInit(FaceDataSetBase* pFaceDataSetBase, const std::string pDataSourcePath, const std::string pFolderPath, const int n);
	};
}