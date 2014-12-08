#include "pch.h"
#include "HPLayer.h"
#include "Player.h"
#include "StageManager.h"
#include "ResourceManager.h"

HPLayer::HPLayer()
{
}

HPLayer::~HPLayer()
{
}

bool HPLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_HPSprite = GET_RESOURCE_MANAGER()->createSprite(ST_HP_BAR);
	m_HPBar = cocos2d::ProgressTimer::create(m_HPSprite);
	m_HPBar->setScale(RESOLUTION);
	m_HPBar->setPosition(cocos2d::Point(160 * RESOLUTION, 160 * RESOLUTION));
	m_HPBar->setPercentage(0);
	m_HPBar->setBarChangeRate(cocos2d::Point(0, 1));
	m_HPBar->setType(cocos2d::ProgressTimer::Type::RADIAL);
	this->addChild(m_HPBar);

	return true;
}

void HPLayer::update(float dTime)
{
	auto playerInfo = GET_STAGE_MANAGER()->getPlayer()->getInfo();
	controlHP(playerInfo.m_MaxHp, playerInfo.m_CurrentHp);
}

void HPLayer::controlHP(int maxHP, int currentHP)
{
	if (currentHP <= 0)
	{
		currentHP = 0;
	}
	if (m_PrevHP != currentHP)
	{
		float hpRatio = 50.0f * currentHP / maxHP;
		float duration = hpRatio / 100.0f;
		cocos2d::ProgressTo* act = cocos2d::ProgressTo::create(duration, hpRatio);
		m_HPBar->runAction(act);
		m_PrevHP = currentHP;
	}
}
