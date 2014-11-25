#include "pch.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "GameManager.h"
#include "UIManager.h"

cocos2d::Scene* GameScene::createScene()
{
	cocos2d::Scene* scene = cocos2d::Scene::createWithPhysics();
	cocos2d::Vect gravity = cocos2d::Vect( 0.0f, -980.0f );

#ifdef _DEBUG
	scene->getPhysicsWorld()->setDebugDrawMask( cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
#endif
	scene->getPhysicsWorld()->setGravity( gravity );
	GameScene* layer = GameScene::create();
	scene->addChild( layer, NULL, GAME_SCENE_TAG );
	return scene;
}

bool GameScene::init()
{
	if(!cocos2d::Layer::init())
	{
		return false;
	}

	m_GameLayer = GameLayer::create();
	m_GameLayer->setAnchorPoint(cocos2d::Point::ZERO);
	m_GameLayer->setPhysicsWorld(m_PhysicsWorld);

	m_UILayer = GET_UI_MANAGER()->getUILayer(GAME_SCENE);
	m_UILayer->setAnchorPoint(cocos2d::Point::ZERO);

	this->addChild(m_GameLayer, GameScene::ZOrder::GAMELAYER);
	this->addChild(m_UILayer, GameScene::ZOrder::UILAYER);

	scheduleUpdate();
	return true;
}


void GameScene::update(float dTime)
{
	m_UILayer->update(dTime);
	m_GameLayer->update(dTime);
}

GameLayer* GameScene::getGameLayer()
{
	return m_GameLayer;
}

UILayer* GameScene::getUILayer()
{
	return m_UILayer;
}

void GameScene::setPhysicsWorld( cocos2d::PhysicsWorld* physicsWorld )
{
	m_PhysicsWorld = physicsWorld;
}


