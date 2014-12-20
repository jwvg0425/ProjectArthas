#include "pch.h"
#include "SkillUseLayer.h"
#include "Player.h"
#include "DataManager.h"
#include "StageManager.h"
#include "ResourceManager.h"

bool SkillUseLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_GearSkillFrame = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT);
	m_CommonSkillFrame = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT);
	m_SkillSet = GET_DATA_MANAGER()->getSkillSet();

	if (m_SkillSet.m_BearSkill != BEAR_START)
	{
		auto bearSkill = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, m_SkillSet.m_BearSkill);
		m_BearSkill = GET_RESOURCE_MANAGER()->createSprite(bearSkill->m_IconSprite);
	}
	else
	{
		m_BearSkill = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT);
	}

	if (m_SkillSet.m_MonkeySkill != MONKEY_START)
	{
		auto monkeySkill = GET_DATA_MANAGER()->getSkillInfo(SKILL_MONKEY, m_SkillSet.m_MonkeySkill);
		m_MonkeySkill = GET_RESOURCE_MANAGER()->createSprite(monkeySkill->m_IconSprite);
	}
	else
	{
		m_MonkeySkill = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT);
	}

	if (m_SkillSet.m_EagleSkill != EAGLE_START)
	{
		auto eagleSkill = GET_DATA_MANAGER()->getSkillInfo(SKILL_EAGLE, m_SkillSet.m_EagleSkill);
		m_EagleSkill = GET_RESOURCE_MANAGER()->createSprite(eagleSkill->m_IconSprite);
	}
	else
	{
		m_EagleSkill = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT);
	}

	if (m_SkillSet.m_CommonSkill != COMMON_START)
	{
		auto commonSkill = GET_DATA_MANAGER()->getSkillInfo(SKILL_COMMON, m_SkillSet.m_CommonSkill);
		m_CommonSkill = GET_RESOURCE_MANAGER()->createSprite(commonSkill->m_IconSprite);
	}
	else
	{
		m_CommonSkill = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT);
	}

	setUIProperties(m_GearSkillFrame, cocos2d::Point(0.5, 0.5), cocos2d::Point(310 * RESOLUTION, 60 * RESOLUTION), RESOLUTION, true, 5);
	setUIProperties(m_CommonSkillFrame, cocos2d::Point(0.5, 0.5), cocos2d::Point(m_WinWidth - 280 * RESOLUTION, 60 * RESOLUTION), RESOLUTION, true, 5);
	setUIProperties(m_BearSkill, cocos2d::Point(0, 0), cocos2d::Point(0, 0), 1.0f, true, 6);
	setUIProperties(m_MonkeySkill, cocos2d::Point(0, 0), cocos2d::Point(0, 0), 1.0f, false, 6);
	setUIProperties(m_EagleSkill, cocos2d::Point(0, 0), cocos2d::Point(0, 0), 1.0f, false, 6);
	setUIProperties(m_CommonSkill, cocos2d::Point(0, 0), cocos2d::Point(0, 0), 1.0f, true, 6);

	this->addChild(m_GearSkillFrame);
	this->addChild(m_CommonSkillFrame);
	m_GearSkillFrame->addChild(m_BearSkill);
	m_GearSkillFrame->addChild(m_MonkeySkill);
	m_GearSkillFrame->addChild(m_EagleSkill);
	m_CommonSkillFrame->addChild(m_CommonSkill);

	//CoolDown Image 추가하기!
	return true;
}

void SkillUseLayer::update(float dTime)
{
	const PlayerInfo player = GET_STAGE_MANAGER()->getPlayer()->getInfo();
	GearType currentGear = player.m_Gear;
	if (m_PrevGear != currentGear)
	{
		changeSkillByGear(currentGear);
		m_PrevGear = currentGear;
	}
}

void SkillUseLayer::changeSkillByGear(GearType newGear)
{
	switch (newGear)
	{
	case GEAR_BEAR:
		m_BearSkill->setVisible(true);
		m_MonkeySkill->setVisible(false);
		m_EagleSkill->setVisible(false);
		break;
	case GEAR_MONKEY:
		m_BearSkill->setVisible(false);
		m_MonkeySkill->setVisible(true);
		m_EagleSkill->setVisible(false);
		break;
	case GEAR_EAGLE:
		m_BearSkill->setVisible(false);
		m_MonkeySkill->setVisible(false);
		m_EagleSkill->setVisible(true);
		break;
	}
}
