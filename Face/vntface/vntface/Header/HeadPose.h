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
	/********** class HeadPose: image format ("subjectid_date_pose_meta.ppm") **********/
	class HeadPose : public FaceDataSetBase
	{
	private:

		/********** private Methods **********/

		//\\ Image format: "person[Id][Serie][Number][Tilt][Pan].jpg".
		const std::string mImageName = "person[Id][Serie][Number][Tilt][Pan].jpg";
		//\\ Id dau tien va Id cuoi cung.
		std::string mIds = "01,15";
		//\\ Chuoi anh: Seri 1 tranning, seri 2 test.
		std::string mSerie = "1,2";//\\= "1,2";
		//\\ So thu tu cua file trong thu muc.
		const std::string mNumber = "00,92";
		//\\ Goc nghien theo chieu dung.
		const std::string mTilt = "-90,-60,-30,-15,+0,+15,+30,+60,+90";
		//\\ Goc nghien theo chieu ngang.
		const std::string mPan = "-90,-75,-60,-45,-30,-15,+0,+15,+30,+45,+60,+75,+90";
		//\\ Goc nghien lon nhat.
		const int mMaxPose = 100;

		///* Test */
		////\\ Id dau tien va Id cuoi cung.
		//const std::string mIds = "01,05";
		////\\ Chuoi anh.
		//const std::string mSerie = "1";
		////\\ So thu tu cua file trong thu muc.
		//const std::string mNumber = "00,05";
		////\\ Goc nghien theo chieu dung.
		//const std::string mTilt = "-90,-60,+90";
		////\\ Goc nghien theo chieu ngang.
		//const std::string mPan = "-90,-75,-60,-45";

	public:
		/********** Constructor **********/
		HeadPose();
		~HeadPose();

		/********** public Methods **********/
		//\\ Lay Ids.
		std::string aGetIds();
		//\\ Gan Ids.
		void aSetIds(std::string pIds);
		//\\ Lay Serie.
		std::string aGetSerie();
		//\\ Gan Serie.
		void aSetSerie(std::string pSerie);

		//\\ Get Subject Id.
		std::string aGetId(const int pIndex);
		//\\ Get Serie.
		std::string aGetSerie(const int pIndex);
		//\\ Get Number.
		std::string aGetNumber(const int pIndex);
		//\\ Get Tilt.
		std::string aGetTilt(const int pIndex);
		//\\ Get Pan.
		std::string aGetPan(const int pIndex);

		//\\ Lay tat ca Id.
		std::vector<std::string> aGetsAllId();
		//\\ Lay tat ca Serie.
		std::vector<std::string> aGetsAllSerie();
		//\\ Lay tat ca Number.
		std::vector<std::string> aGetsAllNumber();
		//\\ Lay tat ca Tilt.
		std::vector<std::string> aGetsAllTilt();
		//\\ Lay tat ca Pan.
		std::vector<std::string> aGetsAllPan();

		//\\ Lay tat ca Id theo thu tu tang dan.
		std::vector<std::string> aGetsAllIds();
		//\\ Lay tat ca Number theo thu tu tang dan.
		std::vector<std::string> aGetsAllNumbers();

		//\\ Lay duong dan thu muc.
		std::string aGetPath(const std::string pId);
		//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm"
		std::vector<std::string> aGetsAllFileName(const std::string pId);
		//\\ Lay to hop cac pose tuong ung voi goc nhin trong ten file.
		std::vector<int> aGetsAllPose1(const std::string pId);
		//\\ Lay to hop cac pose tuong ung voi goc nhin trong ten file.
		std::vector<std::string> aGetsAllPose2(const std::string pId);
		//\\ Lay to hop cac pose tuong ung voi goc nhin trong ten file.
		std::vector<std::string> aGetsAllPoseName(const std::string pId);
		//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm". Co duong dan tuong doi.
		std::vector<std::string> aGetsAllFullFileName(const std::string pId, const std::string pPath);
	};
}