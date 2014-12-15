#include "pch.h"
#include "SkillLineLayer.h"
#include "IconLayer.h"
#include "ResourceManager.h"
#include "DataManager.h"

bool SkillLineLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	initSkillContainer();
	displaySkills();
	return true;
}

void SkillLineLayer::initSkillContainer()
{
	m_BearContainer = cocos2d::Node::create();
	m_MonkeyContainer = cocos2d::Node::create();
	m_EagleContainer = cocos2d::Node::create();
	m_CommonContainer = cocos2d::Node::create();

	m_BearContainer->setPosition(cocos2d::Point(85, 550));
	m_MonkeyContainer->setPosition(cocos2d::Point(85, 465));
	m_EagleContainer->setPosition(cocos2d::Point(85, 380));
	m_CommonContainer->setPosition(cocos2d::Point(85, 295));

	this->addChild(m_BearContainer);
	this->addChild(m_MonkeyContainer);
	this->addChild(m_EagleContainer);
	this->addChild(m_CommonContainer);

	m_BearRect.setRect(535 * RESOLUTION, 550 * RESOLUTION, 320 * RESOLUTION, 70 * RESOLUTION);
	m_MonkeyRect.setRect(535 * RESOLUTION, 465 * RESOLUTION, 320 * RESOLUTION, 70 * RESOLUTION);
	m_EagleRect.setRect(535 * RESOLUTION, 380 * RESOLUTION, 320 * RESOLUTION, 70 * RESOLUTION);
	m_CommonRect.setRect(535 * RESOLUTION, 295 * RESOLUTION, 320 * RESOLUTION, 70 * RESOLUTION);
}

void SkillLineLayer::displaySkills()
{
	int count = 0;
	for (int i = static_cast<int>(BEAR_START)+1; i < static_cast<int>(BEAR_END); ++i)
	{
		auto info = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, i);
		IconLayer* skillIcon = IconLayer::create();
		m_BearList.push_back(skillIcon);
		if (info->m_IsLock)
		{
			m_BearList[i]->changeIconState(ICON_LOCKED);
		}
		else
		{
			m_BearList[i]->setIconContent(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_CONTENT_DEFAULT));
		}
		m_BearList[i]->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_BearList[i]->createIconLabel(cocos2d::Point(m_BearContainer->getBoundingBox().getMinX() * RESOLUTION, m_BearContainer->getBoundingBox().getMinY() * RESOLUTION), info->m_IsLock);
		m_BearContainer->addChild(m_BearList[i]);
		count++;
	}
	m_BearContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(MONKEY_START)+1; i < static_cast<int>(MONKEY_END); ++i)
	{
		auto info = GET_DATA_MANAGER()->getSkillInfo(SKILL_MONKEY, i);
		IconLayer* skillIcon = IconLayer::create();
		m_MonkeyList.push_back(skillIcon);
		if (info->m_IsLock)
		{
			m_MonkeyList[i]->changeIconState(ICON_LOCKED);
		}
		else
		{
			m_MonkeyList[i]->setIconContent(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_CONTENT_DEFAULT));
		}
		m_MonkeyList[i]->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_MonkeyList[i]->createIconLabel(cocos2d::Point(m_MonkeyContainer->getBoundingBox().getMinX() * RESOLUTION, m_MonkeyContainer->getBoundingBox().getMinY() * RESOLUTION), info->m_IsLock);
		m_MonkeyContainer->addChild(m_MonkeyList[i]);
		count++;
	}
	m_MonkeyContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(EAGLE_START)+1; i < static_cast<int>(EAGLE_END); ++i)
	{
		auto info = GET_DATA_MANAGER()->getSkillInfo(SKILL_EAGLE, i);
		IconLayer* skillIcon = IconLayer::create();
		m_EagleList.push_back(skillIcon);
		if (info->m_IsLock)
		{
			m_EagleList[i]->changeIconState(ICON_LOCKED);
		}
		else
		{
			m_EagleList[i]->setIconContent(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_CONTENT_DEFAULT));
		}
		m_EagleList[i]->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_EagleList[i]->createIconLabel(cocos2d::Point(m_EagleContainer->getBoundingBox().getMinX() * RESOLUTION, m_EagleContainer->getBoundingBox().getMinY() * RESOLUTION), info->m_IsLock);
		m_EagleContainer->addChild(m_EagleList[i]);
		count++;
	}
	m_EagleContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(COMMON_START)+1; i < static_cast<int>(COMMON_END); ++i)
	{
		auto info = GET_DATA_MANAGER()->getSkillInfo(SKILL_COMMON, i);
		IconLayer* skillIcon = IconLayer::create();
		m_CommonList.push_back(skillIcon);
		if (info->m_IsLock)
		{
			m_CommonList[i]->changeIconState(ICON_LOCKED);
		}
		else
		{
			m_CommonList[i]->setIconContent(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_CONTENT_DEFAULT));
		}
		m_CommonList[i]->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_CommonList[i]->createIconLabel(cocos2d::Point(m_CommonContainer->getBoundingBox().getMinX() * RESOLUTION, m_CommonContainer->getBoundingBox().getMinY() * RESOLUTION), info->m_IsLock);
		m_CommonContainer->addChild(m_CommonList[i]);
		count++;
	}
	m_CommonContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
}

void SkillLineLayer::update(float dTime)
{
}

void SkillLineLayer::hideLabelLayer()
{
	for (int i = static_cast<int>(BEAR_START)+1; i < static_cast<int>(BEAR_END); ++i)
	{
		m_BearList[i]->hideLabel();
	}
	for (int i = static_cast<int>(MONKEY_START)+1; i < static_cast<int>(MONKEY_END); ++i)
	{
		m_MonkeyList[i]->hideLabel();
	}
	for (int i = static_cast<int>(EAGLE_START)+1; i < static_cast<int>(EAGLE_END); ++i)
	{
		m_EagleList[i]->hideLabel();
	}
	for (int i = static_cast<int>(COMMON_START)+1; i < static_cast<int>(COMMON_END); ++i)
	{
		m_CommonList[i]->hideLabel();
	}
}

void SkillLineLayer::updateSkills(float dTime)
{
	for (int i = static_cast<int>(BEAR_START)+1; i < static_cast<int>(BEAR_END); ++i)
	{
		m_BearList[i]->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_BearList[i]->update(dTime);
	}
	for (int i = static_cast<int>(MONKEY_START)+1; i < static_cast<int>(MONKEY_END); ++i)
	{
		m_MonkeyList[i]->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_MonkeyList[i]->update(dTime);
	}
	for (int i = static_cast<int>(EAGLE_START)+1; i < static_cast<int>(EAGLE_END); ++i)
	{
		m_EagleList[i]->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_EagleList[i]->update(dTime);
	}
	for (int i = static_cast<int>(COMMON_START)+1; i < static_cast<int>(COMMON_END); ++i)
	{
		m_CommonList[i]->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_CommonList[i]->update(dTime);
	}
}

void SkillLineLayer::updateDoubleClickSkill(cocos2d::Point clickPoint)
{
	for (int i = static_cast<int>(BEAR_START)+1; i < static_cast<int>(BEAR_END); ++i)
	{
		m_BearList[i]->doubleClickCheck(clickPoint);
	}
	for (int i = static_cast<int>(MONKEY_START)+1; i < static_cast<int>(MONKEY_END); ++i)
	{
		m_MonkeyList[i]->doubleClickCheck(clickPoint);
	}
	for (int i = static_cast<int>(EAGLE_START)+1; i < static_cast<int>(EAGLE_END); ++i)
	{
		m_EagleList[i]->doubleClickCheck(clickPoint);
	}
	for (int i = static_cast<int>(COMMON_START)+1; i < static_cast<int>(COMMON_END); ++i)
	{
		m_CommonList[i]->doubleClickCheck(clickPoint);
	}
}

void SkillLineLayer::setSkillSet(cocos2d::Point clickPoint)
{
	if (m_BearRect.containsPoint(clickPoint))
	{
		BearSkill prev = m_SkillSet.m_BearSkill;
		BearSkill temp = BEAR_START;
		BearSkill bear = BEAR_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(BEAR_START)+1; i < static_cast<int>(BEAR_END); ++i)
		{
			iconState = m_BearList[i]->getIconState();
			if (iconState == ICON_SELECTED)
			{
				bear = static_cast<BearSkill>(i);
				if (bear == prev)
				{
					m_BearList[i]->changeIconState(ICON_DEFAULT);
				}
				else if (bear != prev)
				{
					temp = bear;
				}
			}
		}
		m_SkillSet.m_BearSkill = temp;
	}
	else if (m_MonkeyRect.containsPoint(clickPoint))
	{
		MonkeySkill prev = m_SkillSet.m_MonkeySkill;
		MonkeySkill temp = MONKEY_START;
		MonkeySkill monkey = MONKEY_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(MONKEY_START)+1; i < static_cast<int>(MONKEY_END); ++i)
		{
			iconState = m_MonkeyList[i]->getIconState();
			if (iconState == ICON_SELECTED)
			{
				monkey = static_cast<MonkeySkill>(i);
				if (monkey == prev)
				{
					m_MonkeyList[i]->changeIconState(ICON_DEFAULT);
				}
				else if (monkey != prev)
				{
					temp = monkey;
				}
			}
		}
		m_SkillSet.m_MonkeySkill = temp;
	}
	else if (m_EagleRect.containsPoint(clickPoint))
	{
		EagleSkill prev = m_SkillSet.m_EagleSkill;
		EagleSkill temp = EAGLE_START;
		EagleSkill eagle = EAGLE_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(EAGLE_START)+1; i < static_cast<int>(EAGLE_END); ++i)
		{
			iconState = m_EagleList[i]->getIconState();
			if (iconState == ICON_SELECTED)
			{
				eagle = static_cast<EagleSkill>(i);
				if (eagle == prev)
				{
					m_EagleList[i]->changeIconState(ICON_DEFAULT);
				}
				else if (eagle != prev)
				{
					temp = eagle;
				}
			}
		}
		m_SkillSet.m_EagleSkill = temp;
	}
	else if (m_CommonRect.containsPoint(clickPoint))
	{
		CommonSkill prev = m_SkillSet.m_CommonSkill;
		CommonSkill temp = COMMON_START;
		CommonSkill common = COMMON_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(COMMON_START)+1; i < static_cast<int>(COMMON_END); ++i)
		{
			iconState = m_CommonList[i]->getIconState();
			if (iconState == ICON_SELECTED)
			{
				common = static_cast<CommonSkill>(i);
				if (common == prev)
				{
					m_CommonList[i]->changeIconState(ICON_DEFAULT);
				}
				else if (common != prev)
				{
					temp = common;
				}
			}
		}
		m_SkillSet.m_CommonSkill = temp;
	}
}

void SkillLineLayer::containerScroll(float scrollValue, cocos2d::Point clickPoint)
{
	if (scrollValue != 0)
	{
		bool moveLeft = false;
		if (scrollValue < 0)
		{
			moveLeft = false;
		}
		else if (scrollValue > 0)
		{
			moveLeft = true;
		}

		if (m_BearRect.containsPoint(clickPoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_BearContainer->getPosition()).x, m_BearContainer, m_BearRect);
		}
		else if (m_MonkeyRect.containsPoint(clickPoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_MonkeyContainer->getPosition()).x, m_MonkeyContainer, m_MonkeyRect);
		}
		else if (m_EagleRect.containsPoint(clickPoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_EagleContainer->getPosition()).x, m_EagleContainer, m_EagleRect);
		}
		else if (m_CommonRect.containsPoint(clickPoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_CommonContainer->getPosition()).x, m_CommonContainer, m_CommonRect);
		}
	}
}

SkillSet SkillLineLayer::getSkillSet()
{
	return m_SkillSet;
}

