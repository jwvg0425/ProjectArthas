#include "pch.h"
#include "TitleScene.h"
#include "GameManager.h"
#include "StageManager.h"
#include "UIManager.h"
#include "UILayer.h"
#include "InputManager.h"
#include "AssemblyScene.h"
#include "ButtonLayer.h"
#include "ResourceManager.h"

cocos2d::Scene* TitleScene::createScene()
{
	TitleScene* scene = TitleScene::create();
	return scene;
}

bool TitleScene::init()
{
	auto layer = cocos2d::Layer::create();
	this->addChild( layer );
	m_TitleBackground = GET_RESOURCE_MANAGER()->createSprite(ST_TITLE_SCENE);
	m_TitleBackground->setAnchorPoint(cocos2d::Point(0, 0));
	m_TitleBackground->setScale(RESOLUTION);
	this->addChild(m_TitleBackground);
	titleButtonInit();
	auto button = cocos2d::MenuItemFont::create("Start", CC_CALLBACK_1(TitleScene::menuCallback, this));
	auto menu = cocos2d::Menu::create(button, NULL);
	m_TitleBackground->addChild(menu);
	button->setPosition(cocos2d::Point(125, -108));
	scheduleUpdate();
	return true;
}

void TitleScene::update(float dTime)
{
	m_StartButton->update(dTime);
	m_QuitButton->update(dTime);
}

void TitleScene::menuCallback( cocos2d::Ref* sender )
{
	if(!m_IsStarted)
	{
		m_IsStarted = true;
		GET_GAME_MANAGER()->changeScene(SceneType::ASSEMBLY_SCENE);
	}
}

void TitleScene::onExit()
{
	Scene::onExit();
	m_IsStarted = false;
}

void TitleScene::titleButtonInit()
{
	m_StartButton = ButtonLayer::create();
	m_QuitButton = ButtonLayer::create();

	m_StartButton->setButtonProperties(BUTTON_UPGRADE, cocos2d::Point(0, 0), cocos2d::Point(640, 180), "", 35);
	m_QuitButton->setButtonProperties(BUTTON_UPGRADE, cocos2d::Point(0, 0), cocos2d::Point(640, 110), "Quit Game", 35);

// 	m_StartButton->setButtonFunc(std::bind(&TitleScene::menuCallback, this));
// 	m_QuitButton->setButtonFunc(std::bind(&TitleScene::quitGame, this));

	m_TitleBackground->addChild(m_StartButton);
	m_TitleBackground->addChild(m_QuitButton);
}

void TitleScene::quitGame()
{
	exit(0);
}
