#include "pch.h"
#include "TitleScene.h"
#include "GameManager.h"
#include "StageManager.h"

cocos2d::Scene* TitleScene::createScene()
{
	TitleScene* scene = TitleScene::create();
	return scene;
}

bool TitleScene::init()
{
	auto layer = cocos2d::Layer::create();
	this->addChild( layer );
	auto playButton = cocos2d::MenuItemFont::create("PLAY", CC_CALLBACK_1( TitleScene::menuCallback , this ) );
	auto menu = cocos2d::Menu::create( playButton , NULL );
	layer->addChild( menu );
	return true;
}

void TitleScene::menuCallback( cocos2d::Ref* sender )
{
	if(!m_IsStarted)
	{
		m_IsStarted = true;
		GET_STAGE_MANAGER()->initStage(0);
	}
}

