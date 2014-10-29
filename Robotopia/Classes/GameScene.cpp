#include "GameScene.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "GameManager.h"


Arthas::GameScene* Arthas::GameScene::createScene()
{
	Arthas::GameScene* scene = Arthas::GameScene::create();
	return scene;
}

bool Arthas::GameScene::init()
{
	if( !cocos2d::Scene::init() )
	{
		return false;
	}

	m_GameLayer = Arthas::GameLayer::create();
	m_GameLayer->setAnchorPoint( cocos2d::Point::ZERO );

	m_UILayer = Arthas::UILayer::create();
	m_UILayer->setPosition( cocos2d::Point::ZERO );

	this->addChild( m_GameLayer , Arthas::GameScene::ZOrder::GAMELAYER );
	this->addChild( m_UILayer , Arthas::GameScene::ZOrder::UILAYER );

	return true;
}

void Arthas::GameScene::onEnter()
{
}

void Arthas::GameScene::update( float dTime )
{
	m_UILayer->update( dTime );
	m_GameLayer->update( dTime );
}


