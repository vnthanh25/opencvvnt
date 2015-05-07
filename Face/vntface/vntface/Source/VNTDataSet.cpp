/*
VNThanh
- Du lieu anh ve mat nguoi.
*/

#include "../Header/VNTDataSet.h"
#include "../Header/Utilities.h"

using namespace vnt;

/********** Constructor **********/
VNTDataSet::VNTDataSet() : FaceDataSetBase()
{
}
VNTDataSet::~VNTDataSet()
{
}

/********** public Methods **********/
//\\ Get Subject Id.
std::string VNTDataSet::aGetId(const int pIndex)
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
//\\ Get Number.
std::string VNTDataSet::aGetNumber(const int pIndex)
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

//\\ Lay tat ca Id.
std::vector<std::string> VNTDataSet::aGetsAllId()
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
//\\ Lay tat ca Number.
std::vector<std::string> VNTDataSet::aGetsAllNumber()
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

//\\ Lay tat ca Id theo thu tu tang dan.
std::vector<std::string> VNTDataSet::aGetsAllIds()
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
std::vector<std::string> VNTDataSet::aGetsAllNumbers()
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
std::string VNTDataSet::aGetPath(const std::string pId)
{
	std::string result = "FaceTrack" + pId + "/";
	return result;
}
//\\ Lay to hop tat ca cac ten anh mat nguoi co trong thu muc. Format: "Image[Number].jpg"
std::vector<std::string> VNTDataSet::aGetsAllFileName(const std::string pId)
{
	std::vector<std::string> result;
	std::string fName = mImageName;
	//\\ Lay tat ca Number theo thu tu tang dan.
	std::vector<std::string> number = aGetsAllNumbers();

	//\\ Ghep chuoi de tao ten file.
	std::string imageName;
	int len = 0;
	size_t number_size = number.size();
	for (size_t i = 0; i < number_size; i++)
	{
		imageName = "Image" + number[i] + ".jpg";
		result.push_back(imageName);
	}// serie
	return result;
}
//\\ Lay to hop cac pose tuong ung voi goc nhin trong ten file.
std::vector<int> VNTDataSet::aGetsAllPose(const std::string pId)
{
	std::vector<int> result;
	std::string fName = mImageName;
	//\\ Lay tat ca Number theo thu tu tang dan.
	std::vector<std::string> number = aGetsAllNumbers();

	//\\ Ghep chuoi de tao ten file.
	int pose;
	int len = 0;
	size_t number_size = number.size();
	for (size_t i = 0; i < number_size; i++)
	{
		pose = 0;//\\ Chua tinh
		result.push_back(pose);
	}// serie
	return result;
}
//\\ Lay tat ca cac ten anh mat nguoi co trong thu muc. Format: "Image[Number].jpg". Co duong dan tuong doi.
std::vector<std::string> VNTDataSet::aGetsAllFullFileName(const std::string pId, const std::string pPath)
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


//\\ Chia moi FaceTrack trong DataSet thanh n FaceTrack. 
int VNTDataSet::aVNTDataSetInit(FaceDataSetBase* pFaceDataSetBase, const std::string pDataSourcePath, const std::string pFolderPath, const int n)
{
	int result = -1;
	Utilites util;
	std::string vFaceTrackName = "FaceTrack";
	//\\ Lay tat ca Ids co trong nguon anh.
	std::vector<std::string> vAllIds = pFaceDataSetBase->aGetsAllIds();
	size_t vAllIdsSize = vAllIds.size();
	int numlengthFaceTrack = std::to_string(vAllIdsSize * n).length();
	int vFaceTrackIndex = 0;
	for (size_t i = 0; i < vAllIdsSize; i++)
	{
		std::string vId = vAllIds[i];
		//\\ Load facetrack. Lay tat ca ten file anh cua 1 nguoi.
		std::vector<std::string> vAllFileName = pFaceDataSetBase->aGetsAllFileName(vId);
		size_t vAllFileNameSize = vAllFileName.size() / n;
		int numFilesLength = std::to_string(vAllFileNameSize).length();
		//\\ Chia lam n thu muc facetrack con.
		for (size_t j = 0; j < n; j++)
		{
			std::string vFaceTrackPath = pFolderPath + vFaceTrackName + util.leftPad(std::to_string(vFaceTrackIndex), numlengthFaceTrack, '0');
			util.makeDir(util.replaceAll(vFaceTrackPath, "/", "\\"));
			vFaceTrackPath += "/";
			vFaceTrackIndex++;
			for (size_t k = 0; k < vAllFileNameSize; k++)
			{
				cv::Mat face = cv::imread(pDataSourcePath + pFaceDataSetBase->aGetPath(vId) + vAllFileName[j * n + k], CV_8UC1);
				if (!face.empty())
				{
					//\\ Ten file co dang: "Image01.txt", ...
					std::string fName = std::to_string(k);
					fName = mImageName + util.leftPad(fName, numFilesLength, '0');
					//\\ Ghi anh Mat.
					util.writeMatBasic(face, vFaceTrackPath + fName + mImageType);
					//\\ Ghi anh goc.
					cv::imwrite(vFaceTrackPath + fName + ".jpg", face);
				}
			}
		}
	}// for i.
	result = vAllIdsSize;
	return result;
}
