/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "../Header/HeadPose.h"
#include "../Header/Utilities.h"

using namespace vnt;

/********** Constructor **********/
HeadPose::HeadPose() : FaceDataSetBase()
{
}
HeadPose::~HeadPose()
{
}

/********** public Methods **********/
//\\ Lay Serie.
std::string HeadPose::aGetSerie()
{
	return mSerie;
}
//\\ Gan Serie.
void HeadPose::aSetSerie(std::string pSerie)
{
	mSerie = pSerie;
}

//\\ Get Subject Id.
std::string HeadPose::aGetId(const int pIndex)
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
//\\ Get Serie.
std::string HeadPose::aGetSerie(const int pIndex)
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
		end = mSerie.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mSerie.length();
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
	return mSerie.substr(start, end - start);
}
//\\ Get Number.
std::string HeadPose::aGetNumber(const int pIndex)
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
		end = mNumber.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mNumber.length();
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
	return mNumber.substr(start, end - start);
}
//\\ Get Tilt.
std::string HeadPose::aGetTilt(const int pIndex)
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
		end = mTilt.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mTilt.length();
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
	return mTilt.substr(start, end - start);
}
//\\ Get Pan.
std::string HeadPose::aGetPan(const int pIndex)
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
		end = mPan.find(',', start);
		//\\ Khong tim thay hoac phan tu cuoi.
		if (end == std::string::npos)
		{
			end = mPan.length();
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
	return mPan.substr(start, end - start);
}

//\\ Lay tat ca Id.
std::vector<std::string> HeadPose::aGetsAllId()
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
//\\ Lay tat ca Serie.
std::vector<std::string> HeadPose::aGetsAllSerie()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetSerie(index);
		if (item == "")
			break;
		//if (item == "2")
		result.push_back(item);
		index++;
	}
	return result;
}
//\\ Lay tat ca Number.
std::vector<std::string> HeadPose::aGetsAllNumber()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetNumber(index);
		if (item == "")
			break;
		result.push_back(item);
		index++;
	}
	return result;
}
//\\ Lay tat ca Tilt.
std::vector<std::string> HeadPose::aGetsAllTilt()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetTilt(index);
		if (item == "")
			break;
		result.push_back(item);
		index++;
	}
	return result;
}
//\\ Lay tat ca Pan.
std::vector<std::string> HeadPose::aGetsAllPan()
{
	std::vector<std::string> result;
	std::string item;
	int index = 0;
	while (1)
	{
		item = aGetPan(index);
		if (item == "")
			break;
		result.push_back(item);
		index++;
	}
	return result;
}

//\\ Lay tat ca Id theo thu tu tang dan.
std::vector<std::string> HeadPose::aGetsAllIds()
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
//\\ Lay tat ca Number theo thu tu tang dan.
std::vector<std::string> HeadPose::aGetsAllNumbers()
{
	std::vector<std::string> result;
	Utilites util;
	std::vector<std::string> index = aGetsAllNumber();
	size_t index_size = index.size();
	for (size_t i = 0; i < index_size; i += 2)
	{
		size_t start = std::atoi(index[i].c_str());
		size_t end = std::atoi(index[i + 1].c_str());
		//\\ Them phan tu dau tien.
		std::string number = index[i];
		result.push_back(number);
		//\\ Them cac phan tu tiep theo cho den phan tu cuoi.
		for (size_t j = start; j < end; j++)
		{
			number = util.increaseNumber(number, 1);
			result.push_back(number);
		}
	}
	return result;
}

//\\ Lay duong dan thu muc.
std::string HeadPose::aGetPath(const std::string pId)
{
	std::string result = "Person" + pId + "/";
	return result;
}
//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "person[Id][Serie][Number][Tilt][Pan].jpg"
std::vector<std::string> HeadPose::aGetsAllFileName(const std::string pId)
{
	std::vector<std::string> result;
	std::string fName = mImageName;
	//\\ Lay tat ca Serie.
	std::vector<std::string> serie = aGetsAllSerie();
	//\\ Lay tat ca Number theo thu tu tang dan.
	std::vector<std::string> number = aGetsAllNumbers();
	//\\ Lay tat ca Tilt.
	std::vector<std::string> tilt = aGetsAllTilt();
	//\\ Lay tat ca Pan.
	std::vector<std::string> pan = aGetsAllPan();

	//\\ Ghep chuoi de tao ten file.
	std::string imageName;
	int len = 0;
	size_t serie_size = serie.size();
	size_t tilt_size = tilt.size();
	size_t pan_size = pan.size();
	//\\ Co 2 serie.
	for (size_t i = 0; i < serie_size; i++)
	{
		imageName = "person" + pId + serie[i] + number[0] + "-90+0.jpg";
		result.push_back(imageName);
		int num = 1;
		for (size_t j = 1; j < tilt_size - 1; j++) // Bo gia tri dau (-90) va gia tri cuoi (+90).
		{
			for (size_t k = 0; k < pan_size; k++)
			{
				imageName = mImageName;
				len = 0;
				//\\ Thay doi id.
				imageName = imageName.replace(6, 4, pId);
				len += pId.length() - 4;
				//\\ Thay doi serie.
				imageName = imageName.replace(10 + len, 7, serie[i]);
				len += serie[i].length() - 7;
				//\\ Thay doi number.
				imageName = imageName.replace(17 + len, 8, number[num]);
				len += number[num].length() - 8;
				//\\ Thay doi tilt.
				imageName = imageName.replace(25 + len, 6, tilt[j]);
				len += tilt[j].length() - 6;
				//\\ Thay doi pan.
				imageName = imageName.replace(31 + len, 5, pan[k]);
				result.push_back(imageName);
				num++;
			}// pan
		}// tilt
		imageName = "person" + pId + serie[i] + number[num] + "+90+0.jpg";
		result.push_back(imageName);
	}// serie
	return result;
}
//\\ Lay to hop cac pose tuong ung voi goc nhin trong ten file.
std::vector<int> HeadPose::aGetsAllPose(const std::string pId)
{
	std::vector<int> result;
	std::string fName = mImageName;
	//\\ Lay tat ca Serie.
	std::vector<std::string> serie = aGetsAllSerie();
	//\\ Lay tat ca Number theo thu tu tang dan.
	std::vector<std::string> number = aGetsAllNumbers();
	//\\ Lay tat ca Tilt.
	std::vector<std::string> tilt = aGetsAllTilt();
	//\\ Lay tat ca Pan.
	std::vector<std::string> pan = aGetsAllPan();

	Utilites util;
	//\\ Ghep chuoi de tao ten file.
	int pose;
	int len = 0;
	size_t serie_size = serie.size();
	size_t tilt_size = tilt.size();
	size_t pan_size = pan.size();
	//\\ Co 2 serie.
	for (size_t i = 0; i < serie_size; i++)
	{
		//\\ File anh "...-90+0.jpg" => pose = (100 - 90) + (100 - 0) = 110.
		pose = 110;
		result.push_back(pose);
		for (size_t j = 1; j < tilt_size - 1; j++) //\\ Bo gia tri dau (-90) va gia tri cuoi (+90).
		{
			for (size_t k = 0; k < pan_size; k++)
			{
				int itilt = std::atoi(tilt[j].c_str());//\\ Vertical.
				int ipan = std::atoi(pan[k].c_str());//\\ Horizontal.
				pose = (mMaxPose - abs(itilt)) + (mMaxPose - abs(ipan));

				result.push_back(pose);
			}// pan
		}// tilt
		//\\ File anh "...-90+0.jpg" => pose = (100 - 90) + (100 - 0) = 110.
		pose = 110;
		result.push_back(pose);
	}// serie
	return result;
}
//\\ Lay tat ca cac ten anh mat nguoi co trong thu muc. Format: "person[Id][Serie][Number][Tilt][Pan].jpg". Co duong dan tuong doi.
std::vector<std::string> HeadPose::aGetsAllFullFileName(const std::string pId, const std::string pPath)
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

