#include "pch.h"
#include "TitleScene.h"
#include "GameManager.h"
#include "StageManager.h"
#include "UIManager.h"
#include "UILayer.h"
#include "InputManager.h"
#include "AssemblyScene.h"
cocos2d::Scene* TitleScene::createScene()
{
	TitleScene* scene = TitleScene::create();
	return scene;
}

bool TitleScene::init()
{
	auto layer = cocos2d::Layer::create();
	this->addChild( layer );
	auto button = cocos2d::MenuItemFont::create("Start", CC_CALLBACK_1(TitleScene::menuCallback, this));
	auto menu = cocos2d::Menu::create(button, NULL);
	layer->addChild(menu);
	scheduleUpdate();
	return true;
}

void TitleScene::update(float dTime)
{
}

void TitleScene::menuCallback( cocos2d::Ref* sender )
{
	if(!m_IsStarted)
	{
		m_IsStarted = true;
		GET_GAME_MANAGER()->changeScene(AssemblyScene::create(), SceneType::ASSEMBLY_SCENE);
	}
}


