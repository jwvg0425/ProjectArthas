#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"
#include "GameLayer.h"
#include "UILayer.h"

Arthas::StageManager::StageManager()
	:m_StageData()
{
}

Arthas::StageManager::~StageManager()
{
}

bool Arthas::StageManager::init()
{
	return true;
}


void Arthas::StageManager::getStageData( int stageNum )
{
	//임시 데이터 받는것임
	m_StageData = GET_DATA_MANAGER()->MapTestFunction();
}
