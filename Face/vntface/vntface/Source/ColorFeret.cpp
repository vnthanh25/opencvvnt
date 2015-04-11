/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "../Header/ColorFeret.h"
#include "../Header/Utilities.h"

using namespace vnt;

/********** Constructor **********/
ColorFeret::ColorFeret() : FaceDataSetBase()
{
}
ColorFeret::~ColorFeret()
{
}

/********** public Methods **********/
//\\ Get DVD.
std::string ColorFeret::aGetDVD(const int pIndex)
{
	//\\ pIndex phai tu 0.
	if (pIndex < 0)
		return "";
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	int count = -1;
	while (1)
	{
		count++;
		//\\ Tim dau ',' phan cach cac phan tu.
		end = mDVDs.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mDVDs.length();
			break;
		}
		//\\ Kiem tra thu tu index.
		if (count < pIndex)
		{
			start = end + 1;
		}
		else
			break;
	}
	//\\ pIndex vuot ra khoi danh sach.
	if (count < pIndex)
		return "";
	return mDVDs.substr(start, end - start);
}
//\\ Get Type.
std::string ColorFeret::aGetType(const int pIndex)
{
	//\\ pIndex phai tu 0.
	if (pIndex < 0)
		return "";
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	int count = -1;
	while (1)
	{
		count++;
		//\\ Tim dau ',' phan cach cac phan tu.
		end = mTypes.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mTypes.length();
			break;
		}
		//\\ Kiem tra thu tu index.
		if (count < pIndex)
		{
			start = end + 1;
		}
		else
			break;
	}
	//\\ pIndex vuot ra khoi danh sach.
	if (count < pIndex)
		return "";
	return mTypes.substr(start, end - start);
}
//\\ Get Subject Id.
std::string ColorFeret::aGetId(const int pIndex)
{
	//\\ pIndex phai tu 0.
	if (pIndex < 0)
		return "";
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	int count = -1;
	while (1)
	{
		count++;
		//\\ Tim dau ',' phan cach cac phan tu.
		end = mIds.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mIds.length();
			break;
		}
		//\\ Kiem tra thu tu index.
		if (count < pIndex)
		{
			start = end + 1;
		}
		else
			break;
	}
	//\\ pIndex vuot ra khoi danh sach.
	if (count < pIndex)
		return "";
	return mIds.substr(start, end - start);
}
//\\ Get Date.
std::string ColorFeret::aGetDate(const int pIndex)
{
	//\\ pIndex phai tu 0.
	if (pIndex < 0)
		return "";
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	int count = -1;
	while (1)
	{
		count++;
		//\\ Tim dau ',' phan cach cac phan tu.
		end = mDate.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mDate.length();
			break;
		}
		//\\ Kiem tra thu tu index.
		if (count < pIndex)
		{
			start = end + 1;
		}
		else
			break;
	}
	//\\ pIndex vuot ra khoi danh sach.
	if (count < pIndex)
		return "";
	return mDate.substr(start, end - start);
}
//\\ Get Pose.
std::string ColorFeret::aGetPose(const int pIndex)
{
	//\\ pIndex phai tu 0.
	if (pIndex < 0)
		return "";
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	int count = -1;
	while (1)
	{
		count++;
		//\\ Tim dau ',' phan cach cac phan tu.
		end = mPose.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mPose.length();
			break;
		}
		//\\ Kiem tra thu tu index.
		if (count < pIndex)
		{
			start = end + 1;
		}
		else
			break;
	}
	//\\ pIndex vuot ra khoi danh sach.
	if (count < pIndex)
		return "";
	return mPose.substr(start, end - start);
}
//\\ Get Meta.
std::string ColorFeret::aGetMeta(const int pIndex)
{
	//\\ pIndex phai tu 0.
	if (pIndex < 0)
		return "";
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	int count = -1;
	while (1)
	{
		count++;
		//\\ Tim dau ',' phan cach cac phan tu.
		end = mMeta.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mMeta.length();
			break;
		}
		//\\ Kiem tra thu tu index.
		if (count < pIndex)
		{
			start = end + 1;
		}
		else
			break;
	}
	//\\ pIndex vuot ra khoi danh sach.
	if (count < pIndex)
		return "";
	return mMeta.substr(start, end - start);
}

//\\ Lay tat ca DVD.
std::vector<std::string> ColorFeret::aGetsAllDVD()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetDVD(index);
		if (item == "")
			break;
		result.push_back(item);
		index++;
	}
	return result;
}
//\\ Lay tat ca Type.
std::vector<std::string> ColorFeret::aGetsAllType()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetType(index);
		if (item == "")
			break;
		result.push_back(item);
		index++;
	}
	return result;
}
//\\ Lay tat ca Id.
std::vector<std::string> ColorFeret::aGetsAllId()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetId(index);
		if (item == "")
			break;
		result.push_back(item);
		index++;
	}
	return result;
}
//\\ Lay tat ca date.
std::vector<std::string> ColorFeret::aGetsAllDate()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetDate(index);
		if (item == "")
			break;
		result.push_back(item);
		index++;
	}
	return result;
}
//\\ Lay tat ca Pose.
std::vector<std::string> ColorFeret::aGetsAllPose()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetPose(index);
		if (item == "")
			break;
		result.push_back(item);
		index++;
	}
	return result;
}
//\\ Lay tat ca Meta.
std::vector<std::string> ColorFeret::aGetsAllMeta()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetMeta(index);
		if (item == "")
			break;
		result.push_back(item);
		index++;
	}
	return result;
}


//\\ Lay tat ca Id theo thu tu tang dan.
std::vector<std::string> ColorFeret::aGetsAllIds()
{
	std::vector<std::string> result;
	Utilites util;
	std::vector<std::string> index = aGetsAllId();
	size_t index_size = index.size();
	for (size_t i = 0; i < index_size; i += 2)
	{
		size_t start = std::atoi(index[i].c_str());
		size_t end = std::atoi(index[i + 1].c_str());
		//\\ Them phan tu dau tien.
		std::string id = index[i];
		result.push_back(id);
		//\\ Them cac phan tu tiep theo cho den phan tu cuoi.
		for (size_t j = start; j < end; j++)
		{
			id = util.increaseNumber(id, 1);
			result.push_back(id);
		}
	}
	return result;
}

//\\ Lay duong dan thu muc.
std::string ColorFeret::aGetPath(const std::string pId)
{
	std::string result = mPath;
	std::string s;
	int len = 0;
	//\\ Thay doi dvd.
	s = aGetDVD(0);
	result = result.replace(0, 3, s);
	len = s.length() - 3;
	//\\ Thay doi type.
	s = aGetType(0);
	result = result.replace(9 + len, 4, s);
	len += s.length() - 4;
	//\\ Thay doi Id.
	s = pId;
	result = result.replace(14 + len, 2, s);

	return result;
}
//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm"
std::vector<std::string> ColorFeret::aGetsAllFileName(const std::string pId)
{
	std::vector<std::string> result;
	std::string fName = mImageName;
	//\\ Lay tat ca Date.
	std::vector<std::string> dates = aGetsAllDate();
	//\\ Lay tat ca Pose.
	std::vector<std::string> poses = aGetsAllPose();
	//\\ Lay tat ca Meta. Them phan tu rong.
	std::vector<std::string> metas = aGetsAllMeta();
	metas.push_back("");
	//\\ Ghep chuoi de tao ten file.
	std::string imageName;
	int len = 0;
	for (size_t i = 0; i < dates.size(); i++)
	{
		for (size_t j = 0; j < poses.size(); j++)
		{
			for (size_t k = 0; k < metas.size(); k++)
			{
				imageName = mImageName;
				len = 0;
				//\\ Thay doi id.
				imageName = imageName.replace(0, 2, pId);
				len += pId.length() - 2;
				//\\ Thay doi date.
				imageName = imageName.replace(3 + len, 4, dates[i]);
				len += dates[i].length() - 4;
				//\\ Thay doi pose.
				imageName = imageName.replace(8 + len, 4, poses[j]);
				len += poses[j].length() - 4;
				//\\ Thay doi meta.
				if (metas[k] == "")
					imageName = imageName.replace(13 + len - 1, 5, metas[k]);
				else
					imageName = imageName.replace(13 + len, 4, metas[k]);
				result.push_back(imageName);
			}
		}
	}
	return result;
}
//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "id_date_pose_meta.ppm". Co duong dan tuong doi.
std::vector<std::string> ColorFeret::aGetsAllFullFileName(const std::string pId, const std::string pPath)
{
	std::vector<std::string> result;
	//\\ Lay duong dan thu muc.
	std::string path = pPath + aGetPath(pId);
	//\\ Lay tat ca ten file anh co the co.
	std::vector<std::string> fileNames = aGetsAllFileName(pId);
	//\\ Tra ve anh dau tien duoc tim thay trong thu muc.
	cv::Mat face;
	for (size_t i = 0; i < fileNames.size(); i++)
	{
		path += fileNames[i];
		result.push_back(path);
	}
	return result;
}
