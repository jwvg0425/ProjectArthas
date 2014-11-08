#include "pch.h"
#include "UIManager.h"
#include "UILayer.h"
#include "TitleSceneUILayer.h"
#include "LodingSceneUILayer.h"
#include "GameSceneUILayer.h"

bool Arthas::UILayer::init()
{
	//m_CurrentScene; ³ªÁß¿¡ get stage manager
	m_TitleUILayer = (TitleSceneUILayer*) GET_UI_MANAGER()->getUILayer(TITLE_SCENE);
	m_LodingUILayer = (LoadingSceneUILayer*) GET_UI_MANAGER()->getUILayer(LOADING_SCENE);
	m_GameUILayer = (GameSceneUILayer*) GET_UI_MANAGER()->getUILayer(GAME_SCENE);
	return true;
}


void Arthas::UILayer::update( float dTime )
{
	m_TitleUILayer->update(dTime);
	m_LodingUILayer->update(dTime);
	m_GameUILayer->update(dTime);
}

void Arthas::UILayer::setUIProperties(OUT cocos2d::Sprite* sprite, cocos2d::Point anchorPoint, cocos2d::Point positionPoint, float scale, bool visible, int zOrder)
{
	sprite->setAnchorPoint(anchorPoint);
	sprite->setPosition(positionPoint);
	sprite->setScale(scale);
	sprite->setVisible(visible);
}
