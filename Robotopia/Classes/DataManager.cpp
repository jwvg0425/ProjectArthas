#include "DataManager.h"
#include "cocos2d.h"
#include "json/json.h"

Arthas::DataManager::DataManager()
{

}

Arthas::DataManager::~DataManager()
{

}

bool Arthas::DataManager::init()
{
	for (int dirType = 0; dirType < DIR_MAX; dirType++)
	{
		m_ModuleDatas[dirType].reserve(40);
	}

	return true;
}

bool Arthas::DataManager::loadModuleData()
{
	//data 불러오기
	ssize_t bufferSize = 0;
	unsigned char* fileData = cocos2d::FileUtils::getInstance()->getFileData(MODULE_FILE_NAME, "rb", &bufferSize);
	std::string clearData((const char*)fileData, bufferSize);

	Json::Value root;
	Json::Reader reader;
	char key[BUF_SIZE] = {};
	bool isParsingSuccess = reader.parse(clearData, root);

	if (!isParsingSuccess)
	{
		cocos2d::log("parser failed : \n %s", MODULE_FILE_NAME);
		return false;
	}

	for (int dirType = 0; dirType < DIR_MAX; dirType++)
	{
		int size;

		m_ModuleDatas[dirType].clear();

		ModuleData data;

		//size 불러오기
		getModuleKey(dirType, "size", key);
		size = root.get(key, 0).asInt();

		if (size > 0)
		{

			for (int idx = 0; idx < size; idx++)
			{
				int width, height;

				//너비 높이 불러오기
				getModuleKey(dirType, idx, "width", key);
				width = root.get(key, 0).asInt();
				getModuleKey(dirType, idx, "height", key);
				height = root.get(key, 0).asInt();

				data.width = width;
				data.height = height;

				//ComponentType 배열 불러오기
				getModuleKey(dirType, idx, "data", key);
				Json::Value array = root[key];

				for (int i = 0; i < width * height; i++)
				{
					ComponentType type;

					type = (ComponentType)array[i].asInt();

					data.data.push_back(type);
				}
			}
			m_ModuleDatas[dirType].push_back(data);
		}
	}

	return true;
}


bool Arthas::DataManager::saveModuleData()
{
	Json::Value moduleData;
	char buffer[BUF_SIZE] = {};

	for (int dirType = 0; dirType < DIR_MAX; dirType++)
	{
		//현재 타입의 모듈 사이즈 삽입
		getModuleKey(dirType, "size", buffer);
		moduleData[buffer] = m_ModuleDatas[dirType].size();

		for (int idx = 0; idx < m_ModuleDatas[dirType].size(); idx++)
		{
			int width, height;

			width = m_ModuleDatas[dirType][idx].width;
			height = m_ModuleDatas[dirType][idx].height;

			//너비, 높이 삽입
			getModuleKey(dirType, idx, "width", buffer);
			moduleData[buffer] = width;
			getModuleKey(dirType, idx, "height", buffer);
			moduleData[buffer] = height;

			Json::Value data;

			//세부 데이터(오브젝트 타입들) 삽입
			for (int i = 0; i < width * height; i++)
			{
				data.append(m_ModuleDatas[dirType][idx].data[i]);
			}
			getModuleKey(dirType, idx, "data", buffer);
			moduleData[buffer] = data;
		}
	}

	Json::StyledWriter writer;
	std::string strJSON = writer.write(moduleData);

	saveData(MODULE_FILE_NAME, strJSON.c_str());

	return true;
}

bool Arthas::DataManager::saveData(std::string fileName, const char* pData)
{
	FILE *fp = fopen(fileName.c_str(), "wb");

	if (!fp)
	{
		cocos2d::log("can not create file %s", fileName);
		return false;
	}


	fputs(pData, fp);

	fclose(fp);

	return true;
}

bool Arthas::DataManager::getModuleKey(int type, int idx, char* category, OUT char* key)
{
	if (key == nullptr || category == nullptr)
		return false;

	sprintf(key, "%d_%d_%s", type, idx, category);

	return true;
}

bool Arthas::DataManager::getModuleKey(int type, char* category, OUT char* key)
{
	if (key == nullptr || category == nullptr)
		return false;

	sprintf(key, "%d_%s", type, category);

	return true;
}
