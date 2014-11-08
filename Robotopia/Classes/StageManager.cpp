#include "pch.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "UILayer.h"

Arthas::StageManager::StageManager()
{
	m_GameScene = nullptr;
	m_CurrentStageNum = -1;
}

Arthas::StageManager::~StageManager()
{
}

bool Arthas::StageManager::init()
{
	auto scene = GameScene::createScene();
	GET_GAME_MANAGER()->changeScene(scene, Arthas::SceneType::GAME_SCENE);
	m_GameScene = (Arthas::GameScene*)(scene->getChildByTag( GAME_SCENE_TAG ));
	m_GameScene->scheduleUpdate();
	return true;
}

void Arthas::StageManager::initStage( int stageNum )
{
	m_CurrentStageNum = stageNum;
	StageData stageData = GET_DATA_MANAGER()->getStageData( stageNum );
	m_GameScene->getGameLayer()->initGameLayer( stageData );
}

const Arthas::Player* Arthas::StageManager::getPlayer()
{
	return m_GameScene->getGameLayer()->getPlayer();
}

int Arthas::StageManager::getStageNum()
{
	return m_CurrentStageNum;
}
