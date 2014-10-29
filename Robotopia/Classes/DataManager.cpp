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
	return true;
}

bool DataManager::loadModuleData()
{
	return true;
}


bool DataManager::saveModuleData()
{


	for (int dirType = 0; dirType < DIR_MAX; dirType++)
	{
		for (int idx = 0; idx < m_ModuleDatas[dirType].size(); idx++)
		{

		}
	}
	return true;
}