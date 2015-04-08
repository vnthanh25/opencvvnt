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
	/********** class ColorFeret: image format ("subjectid_date_pose_meta.ppm") **********/
	class ColorFeret : public FaceDataSetBase
	{
	private:

		/********** private Methods **********/

	public:
		/********** public Members **********/

		//\\ Duong dan den file anh (co chua cac token: mFeretDVDs,mFeretImageTypes,subjectid).
		const std::string mPath = "dvd/data/type/id/";
		//\\
						//\\ Do kich thuoc lon nen chia ra lam nhieu thu muc.
		const std::string mDVDs = "dvd1,dvd2";
		//\\ Co nhieu loai kich thuoc khac nhau.
		const std::string mTypes = "images,smaller,thumbnails";
		//\\ Image format: "subjectid_date_pose_meta.ppm".
		const std::string mImageName = "id_date_pose_meta.ppm";
		//\\ Id dau tien va Id cuoi cung cua moi dvd.
		const std::string mIds = "00001,00739,00740,01208";
		//\\ 14 capture dates .
		const std::string mDate = "930831,931230,940128,940307,940422,940519,940928,941031,941121,941201,941205,960530,960620,960627";
		//\\ Goc nghien cua mat nguoi.
		/*
		fa	regular frontal image
		fb	alternative frontal image, taken shortly after the
		corresponding fa image
		pl	profile left
		hl	half left - head turned about 67.5 degrees left
		ql	quarter left - head turned about 22.5 degrees left
		pr	profile right
		hr	half right - head turned about 67.5 degrees right
		qr	quarter right - head turned about 22.5 degrees right
		ra	random image - head turned about 45 degree left
		rb	random image - head turned about 15 degree left
		rc	random image - head turned about 15 degree right
		rd	random image - head turned about 45 degree right
		re	random image - head turned about 75 degree right
		*/
		/*
		Pose Angle   Images Subjects
		fa       0     1364      994
		fb       0     1358      993
		hl   +67.5     1267      917
		hr   -67.5     1320      953
		pl     +90     1312      960
		pr     -90     1363      994
		ql   +22.5      761      501
		qr   -22.5      761      501
		ra     +45      321      261
		rb     +15      321      261
		rc     -15      610      423
		rd     -45      290      236
		re     -75      290      236
		*/
		const std::string mPose = "fa,fb,pl,hl,ql,pr,hr,qr,ra,rb,rc,rd,re";
		//\\ Thong tin them
		/*
		a	subject is wearing glasses
		b	subject changed his or her hairstyle for the
		image and is not wearing glasses
		c	subject changed his or her hairstyle for the
		image and is wearing glasses
		*/
		const std::string mMeta = "a,b,c";

		/********** Constructor **********/
		ColorFeret();
		~ColorFeret();

		/********** public Methods **********/
		//\\ Get DVD.
		std::string aGetDVD(const int pIndex);
		//\\ Get Type.
		std::string aGetType(const int pIndex);
		//\\ Get Subject Id.
		std::string aGetId(const int pIndex);
		//\\ Get Date.
		std::string aGetDate(const int pIndex);
		//\\ Get Pose.
		std::string aGetPose(const int pIndex);
		//\\ Get Meta.
		std::string aGetMeta(const int pIndex);

		//\\ Lay tat ca DVD.
		std::vector<std::string> aGetsAllDVD();
		//\\ Lay tat ca Type.
		std::vector<std::string> aGetsAllType();
		//\\ Lay tat ca Id.
		std::vector<std::string> aGetsAllId();
		//\\ Lay tat ca date.
		std::vector<std::string> aGetsAllDate();
		//\\ Lay tat ca Pose.
		std::vector<std::string> aGetsAllPose();
		//\\ Lay tat ca Meta.
		std::vector<std::string> aGetsAllMeta();

		//\\ Lay duong dan thu muc.
		std::string aGetPath(const std::string pId);
		//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm"
		std::vector<std::string> aGetsAllFileName(const std::string pId);
		//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm". Co duong dan tuong doi.
		std::vector<std::string> aGetsAllFullFileName(const std::string pId, const std::string pPath);
	};
}