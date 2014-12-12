#include "pch.h"
#include "SkillLineLayer.h"
#include "IconLayer.h"
#include "ResourceManager.h"

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

	m_BearRect.setRect(85 * RESOLUTION, 550 * RESOLUTION, 320 * RESOLUTION, 70 * RESOLUTION);
	m_MonkeyRect.setRect(85 * RESOLUTION, 465 * RESOLUTION, 320 * RESOLUTION, 70 * RESOLUTION);
	m_EagleRect.setRect(85 * RESOLUTION, 380 * RESOLUTION, 320 * RESOLUTION, 70 * RESOLUTION);
	m_CommonRect.setRect(85 * RESOLUTION, 295 * RESOLUTION, 320 * RESOLUTION, 70 * RESOLUTION);
}

void SkillLineLayer::displaySkills()
{
	int count = 0;
	for (int i = static_cast<int>(BEAR_START)+1; i < static_cast<int>(BEAR_END); ++i)
	{
		//SkillInfo info = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, i);
		IconLayer* skillIcon = IconLayer::create();
		m_BearList.push_back(skillIcon);
		m_BearList[i]->setIconContent(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_CONTENT_DEFAULT));
		m_BearList[i]->setIconRect(cocos2d::Point(m_BearContainer->getBoundingBox().getMinX() * RESOLUTION, m_BearContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_BearList[i]->createIconLabel(cocos2d::Point(m_BearContainer->getBoundingBox().getMinX() * RESOLUTION, m_BearContainer->getBoundingBox().getMinY() * RESOLUTION), false);
		m_BearContainer->addChild(m_BearList[i]);
		count++;
	}
	m_BearContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(MONKEY_START)+1; i < static_cast<int>(MONKEY_END); ++i)
	{
		//SkillInfo info = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, i);
		IconLayer* skillIcon = IconLayer::create();
		m_MonkeyList.push_back(skillIcon);
		m_MonkeyList[i]->setIconContent(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_CONTENT_DEFAULT));
		m_MonkeyList[i]->setIconRect(cocos2d::Point(m_MonkeyContainer->getBoundingBox().getMinX() * RESOLUTION, m_MonkeyContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_MonkeyList[i]->createIconLabel(cocos2d::Point(m_MonkeyContainer->getBoundingBox().getMinX() * RESOLUTION, m_MonkeyContainer->getBoundingBox().getMinY() * RESOLUTION), false);
		m_MonkeyContainer->addChild(m_MonkeyList[i]);
		count++;
	}
	m_MonkeyContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(EAGLE_START)+1; i < static_cast<int>(EAGLE_END); ++i)
	{
		//SkillInfo info = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, i);
		IconLayer* skillIcon = IconLayer::create();
		m_EagleList.push_back(skillIcon);
		m_EagleList[i]->setIconContent(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_CONTENT_DEFAULT));
		m_EagleList[i]->setIconRect(cocos2d::Point(m_EagleContainer->getBoundingBox().getMinX() * RESOLUTION, m_EagleContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_EagleList[i]->createIconLabel(cocos2d::Point(m_EagleContainer->getBoundingBox().getMinX() * RESOLUTION, m_EagleContainer->getBoundingBox().getMinY() * RESOLUTION), false);
		m_EagleContainer->addChild(m_EagleList[i]);
		count++;
	}
	m_EagleContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(EAGLE_START)+1; i < static_cast<int>(EAGLE_END); ++i)
	{
		//SkillInfo info = GET_DATA_MANAGER()->getSkillInfo(SKILL_BEAR, i);
		IconLayer* skillIcon = IconLayer::create();
		m_CommonList.push_back(skillIcon);
		m_CommonList[i]->setIconContent(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_CONTENT_DEFAULT));
		m_CommonList[i]->setIconRect(cocos2d::Point(m_CommonContainer->getBoundingBox().getMinX() * RESOLUTION, m_CommonContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_CommonList[i]->createIconLabel(cocos2d::Point(m_CommonContainer->getBoundingBox().getMinX() * RESOLUTION, m_CommonContainer->getBoundingBox().getMinY() * RESOLUTION), true);
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

}


void SkillLineLayer::updateSkills(float dTime)
{

}

void SkillLineLayer::updateDoubleClickSkill(cocos2d::Point clickPoint)
{

}

void SkillLineLayer::setSkillSet(cocos2d::Point clickPoint)
{

}

void SkillLineLayer::containerScroll(float scrollValue, cocos2d::Point clickPoint)
{

}

SkillSet SkillLineLayer::getSkillSet()
{
	return m_SkillSet;
}

