#include "pch.h"
#include "AssemblyScene.h"
#include "GameManager.h"
#include "StageManager.h"
#include "UIManager.h"
#include "UILayer.h"
#include "InputManager.h"

cocos2d::Scene* AssemblyScene::createScene()
{
	AssemblyScene* scene = AssemblyScene::create();
	return scene;
}

bool AssemblyScene::init()
{
	auto layer = cocos2d::Layer::create();
	this->addChild(layer);

	GET_INPUT_MANAGER()->receiveMouseData(layer);

	m_UILayer = GET_UI_MANAGER()->getUILayer(ASSEMBLY_SCENE);
	m_UILayer->setAnchorPoint(cocos2d::Point::ZERO);
	layer->addChild(m_UILayer);
	scheduleUpdate();
	return true;
}

void AssemblyScene::update(float dTime)
{
	m_UILayer->update(dTime);
}

void AssemblyScene::onExit()
{
	m_I
}

