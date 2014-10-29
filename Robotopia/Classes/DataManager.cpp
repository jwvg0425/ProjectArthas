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
	Arthas::ModuleData data;

	data.width = 20;
	m_ModuleDatas[0].push_back(data);

	saveModuleData();
	return true;
}

bool Arthas::DataManager::loadModuleData()
{
	return true;
}


bool Arthas::DataManager::saveModuleData()
{
	Json::Value root;

	root["Name"] = "HongGildong";
	root["Age"] = 26;

	Json::Value friends;

	friends.append("Im kkeokjung");
	friends.append("Elisabeth");
	root["Friend"] = friends;
	root["Sex"] = "male";

	Json::StyledWriter writer;
	std::string strJSON = writer.write(root);

	cocos2d::log("JSON WriteTest : %s", strJSON.c_str());

	//Json::writeFileData("testJSON.json", strJSON.c_str());

	return true;
}

