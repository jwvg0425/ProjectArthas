#include "pch.h"
#include "TitleScene.h"
#include "GameManager.h"
#include "StageManager.h"
#include "UIManager.h"
#include "UILayer.h"
#include "InputManager.h"
cocos2d::Scene* TitleScene::createScene()
{
	TitleScene* scene = TitleScene::create();
	return scene;
}

bool TitleScene::init()
{
	auto layer = cocos2d::Layer::create();
	this->addChild( layer );
// 	auto playButton = cocos2d::MenuItemFont::create("PLAY", CC_CALLBACK_1( TitleScene::menuCallback , this ) );
// 	auto menu = cocos2d::Menu::create( playButton , NULL );
	
	GET_INPUT_MANAGER()->receiveKeyboardData(layer);
	GET_INPUT_MANAGER()->receiveMouseData(layer);

	m_UILayer = GET_UI_MANAGER()->getUILayer(ASSEMBLY_SCENE);
	m_UILayer->setAnchorPoint(cocos2d::Point::ZERO);
	layer->addChild(m_UILayer);
// 
// 	layer->addChild(menu);
	scheduleUpdate();
	return true;
}

void TitleScene::update(float dTime)
{
	m_UILayer->update(dTime);
}

void TitleScene::menuCallback( cocos2d::Ref* sender )
{
	if(!m_IsStarted)
	{
		m_IsStarted = true;
		GET_STAGE_MANAGER()->initStage(0);
	}
}


