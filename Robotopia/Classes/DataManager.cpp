#include "DataManager.h"
#include "cocos2d.h"




USING_NS_CC;

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}

bool DataManager::init()
{
	for (int dirType = 0; dirType < DIR_MAX; dirType++)
	{
		m_ModuleDatas[dirType].reserve(40);
	}
	ModuleData data;

	data.width = 20;
	m_ModuleDatas[0].push_back(data);

	saveModuleData();
	return true;
}

bool DataManager::loadModuleData()
{
	return true;
}


bool DataManager::saveModuleData()
{
}

