#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "UILayer.h"

Arthas::StageManager::StageManager()
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

void Arthas::StageManager::initStage( int stageNum )
{
	StageData stageData = GET_DATA_MANAGER()->getStageData( stageNum );
	m_GameScene->getGameLayer()->initGameLayer( stageData );
}
