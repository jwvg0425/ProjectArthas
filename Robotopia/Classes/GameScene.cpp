#include "pch.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "UIManager.h"

cocos2d::Scene* GameScene::createScene()
{
	cocos2d::Scene* scene = cocos2d::Scene::createWithPhysics();
	cocos2d::Vect gravity = cocos2d::Vect( 0.0f, GRAVITY );
#ifdef _DEBUG
	scene->getPhysicsWorld()->setDebugDrawMask( cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
#endif
	scene->getPhysicsWorld()->setGravity( gravity );
	GameScene* layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild( layer, NULL, GAME_SCENE_TAG );
	layer->enter();
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

	m_UILayer = GET_UI_MANAGER()->getUILayer(GAME_SCENE);
	m_UILayer->setAnchorPoint(cocos2d::Point::ZERO);

	this->addChild(m_GameLayer, GameScene::ZOrder::GAMELAYER);
	this->addChild(m_UILayer, GameScene::ZOrder::UILAYER);

	m_LoadingSprite = GET_RESOURCE_MANAGER()->createSprite( ST_LOADING );
	m_LoadingSprite->retain();
	addChild( m_LoadingSprite );
	m_LoadingSprite->setAnchorPoint( cocos2d::Point::ZERO );
	cocos2d::Point loadingStartPos( 0 , WINSIZE_HEIGHT );
	m_LoadingSprite->setPosition( loadingStartPos );
	m_LoadingSprite->setVisible(false);
	m_LoadingSprite->setZOrder( 100 );

	scheduleUpdate();
	return true;
}


void GameScene::update(float dTime)
{
	m_UILayer->update(dTime);
	m_GameLayer->update(dTime);
}

void GameScene::enter()
{
	m_GameLayer->setPhysicsWorld(m_PhysicsWorld);
}

void GameScene::exit()
{

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

void GameScene::startLoading()
{
	auto startSeting = cocos2d::CallFuncN::create( CC_CALLBACK_1( GameScene::enterLoading , this ) );
	auto downAction = cocos2d::MoveTo::create( 1.0f , cocos2d::Point( 0 , 0 ) );
	auto downEase = cocos2d::EaseIn::create( downAction , 3.0f );
	auto delay = cocos2d::DelayTime::create( 3.f );
	auto sequence = cocos2d::Sequence::create( startSeting, downEase , delay, nullptr );
	m_LoadingSprite->runAction( sequence );
}

void GameScene::endLoading()
{
	auto delay = cocos2d::DelayTime::create( 3.f );
	auto upAction = cocos2d::MoveTo::create( 1.0f , cocos2d::Point( 0 , WINSIZE_HEIGHT ) );
	auto upEase = cocos2d::EaseIn::create( upAction , 3.0f );
	auto endUp = cocos2d::CallFuncN::create( CC_CALLBACK_1( GameScene::exitLoading , this ) );
	auto sequence = cocos2d::Sequence::create( delay , upEase , endUp , nullptr );
	m_LoadingSprite->runAction( sequence );
}


void GameScene::enterLoading( cocos2d::Node* ref )
{
	m_LoadingSprite->setPosition( cocos2d::Point( 0 , WINSIZE_HEIGHT ) );
	m_LoadingSprite->setVisible( true );
}

void GameScene::exitLoading( cocos2d::Node* ref )
{
	m_LoadingSprite->setVisible(false);
	m_LoadingSprite->stopAllActions();
}

