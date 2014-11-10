#include "pch.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "GameManager.h"
#include "UIManager.h"

cocos2d::Scene* Arthas::GameScene::createScene()
{
	cocos2d::Scene* scene = cocos2d::Scene::createWithPhysics();
	cocos2d::Vect gravity = cocos2d::Vect( 0.0f, -980.0f );

#ifdef _DEBUG
	scene->getPhysicsWorld()->setDebugDrawMask( cocos2d::PhysicsWorld::DEBUGDRAW_ALL );
#endif

	scene->getPhysicsWorld()->setGravity( gravity );
	
	Arthas::GameScene* layer = Arthas::GameScene::create();
	//layer->setPhysicsWorld( scene->getPhysicsWorld() );
	scene->addChild( layer, NULL, GAME_SCENE_TAG );

// 	Arthas::GameScene* scene = Arthas::GameScene::create();
// 	scene->initWithPhysics();
// 	cocos2d::Vect gravity = cocos2d::Vect( 0.0f, -980.0f );
// 	scene->getPhysicsWorld()->setDebugDrawMask( cocos2d::PhysicsWorld::DEBUGDRAW_ALL );
// 	scene->getPhysicsWorld()->setGravity( gravity );
// 	scene->getGameLayer()->setPhysicsWorld( scene->getPhysicsWorld() );

	return scene;
}

bool Arthas::GameScene::init()
{
	if(!cocos2d::Layer::init())
	{
		return false;
	}

	m_GameLayer = Arthas::GameLayer::create();
	m_GameLayer->setAnchorPoint(cocos2d::Point::ZERO);
	m_GameLayer->setPhysicsWorld(m_PhysicsWorld);

	m_UILayer = GET_UI_MANAGER()->getUILayer(GAME_SCENE);
	m_UILayer->setAnchorPoint(cocos2d::Point::ZERO);

	this->addChild(m_GameLayer, Arthas::GameScene::ZOrder::GAMELAYER);
	this->addChild(m_UILayer, Arthas::GameScene::ZOrder::UILAYER);

	scheduleUpdate();
	return true;
}


void Arthas::GameScene::update(float dTime)
{
	m_UILayer->update(dTime);
	m_GameLayer->update(dTime);
}

Arthas::GameLayer* Arthas::GameScene::getGameLayer()
{
	return m_GameLayer;
}

Arthas::UILayer* Arthas::GameScene::getUILayer()
{
	return m_UILayer;
}

void Arthas::GameScene::setPhysicsWorld( cocos2d::PhysicsWorld* physicsWorld )
{
	m_PhysicsWorld = physicsWorld;
}


