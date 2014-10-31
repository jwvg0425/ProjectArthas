#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"
#include "GameScene.h"
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
	m_GameScene = GameScene::createScene();
	cocos2d::Director::getInstance()->replaceScene( m_GameScene );
	m_GameScene->scheduleUpdate();
	return true;
}


void Arthas::StageManager::getStageData( int stageNum )
{
	//임시 데이터 받는것임
	m_StageData = GET_DATA_MANAGER()->MapTestFunction();
}

void Arthas::StageManager::initStage( int stageNum )
{
	getStageData(stageNum);
	m_GameScene->getGameLayer()->initGameLayer( m_StageData );
}
