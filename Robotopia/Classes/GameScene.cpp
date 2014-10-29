#include "GameScene.h"
#include "GameLayer.h"
#include "UILayer.h"
#include "GameManager.h"

USING_NS_CC;

GameScene* GameScene::createScene()
{
	GameScene* scene = GameScene::create();
	return scene;
}

bool GameScene::init()
{
	if( !Scene::init() )
	{
		return false;
	}

	m_GameLayer = GameLayer::create();
	m_GameLayer->setAnchorPoint( Point::ZERO );

	m_UILayer = UILayer::create();
	m_UILayer->setPosition( Point::ZERO );

	this->addChild( m_GameLayer , GameScene::ZOrder::GAMELAYER );
	this->addChild( m_UILayer , GameScene::ZOrder::UILAYER);

	return true;
}

void GameScene::onEnter()
{
}

void GameScene::update( float dTime )
{
	m_UILayer->update( dTime );
	m_GameLayer->update( dTime );
}


