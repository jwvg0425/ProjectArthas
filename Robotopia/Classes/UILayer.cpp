#include "pch.h"
#include "UIManager.h"
#include "UILayer.h"
#include "TitleSceneUILayer.h"
#include "LodingSceneUILayer.h"
#include "AssemblyUILayer.h"
#include "GameSceneUILayer.h"

UILayer::UILayer()
{
}

UILayer::~UILayer()
{
}

bool UILayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	//m_CurrentScene; 나중에 get stage manager
	m_TitleUILayer = static_cast<TitleSceneUILayer*> (GET_UI_MANAGER()->getUILayer(TITLE_SCENE));
	m_LodingUILayer = static_cast<LoadingSceneUILayer*> (GET_UI_MANAGER()->getUILayer(LOADING_SCENE));
	m_AssemblyUILayer = static_cast<AssemblyUILayer*> (GET_UI_MANAGER()->getUILayer(ASSEMBLY_SCENE));
	m_GameUILayer = static_cast<GameSceneUILayer*> (GET_UI_MANAGER()->getUILayer(GAME_SCENE));
	return true;
}

void UILayer::update( float dTime )
{
	m_TitleUILayer->update(dTime);
	m_LodingUILayer->update(dTime);
	m_AssemblyUILayer->update(dTime);
	m_GameUILayer->update(dTime);
}

void UILayer::setUIProperties(OUT cocos2d::Sprite* sprite, cocos2d::Point anchorPoint, cocos2d::Point positionPoint, float scale, bool visible, int zOrder)
{
	sprite->setAnchorPoint(anchorPoint);
	sprite->setPosition(positionPoint);
	sprite->setScale(scale);
	sprite->setVisible(visible);
}

void UILayer::rotateSpriteForever(cocos2d::Sprite* sprite, float velocity, bool clockwise)
{
	cocos2d::RotateBy* act;
	if (clockwise)
		act = cocos2d::RotateBy::create(velocity, 180);
	else
		act = cocos2d::RotateBy::create(velocity, -180);
	auto spin = cocos2d::RepeatForever::create(act);
	sprite->runAction(spin);
}
