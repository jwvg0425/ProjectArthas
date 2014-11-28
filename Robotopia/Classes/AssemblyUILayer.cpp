#include "pch.h"
#include "AssemblyUILayer.h"
#include "GameManager.h"
#include "StageManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "ButtonLayer.h"
#include "IconLayer.h"

AssemblyUILayer::AssemblyUILayer()
{
	m_viewChangeRect.setRect(1235 * RESOLUTION, 310 * RESOLUTION, 25 * RESOLUTION, 100 * RESOLUTION);
}

AssemblyUILayer::~AssemblyUILayer()
{
}

bool AssemblyUILayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_IsStarted = false;

	m_AssemblyBackground = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_BACKGROUND);
	m_AssemblyFrame = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_FRAME);
	m_viewChangeArrow = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ARROW);
	
	m_ButtonConfirm = ButtonLayer::create();
	m_ButtonCancel = ButtonLayer::create();

	m_HeadContainer = cocos2d::Node::create();
	m_EngineContainer = cocos2d::Node::create();
	m_ArmorContainer = cocos2d::Node::create();
	m_MeleeContainer = cocos2d::Node::create();
	m_RangeContainer = cocos2d::Node::create();
	m_SteamContainer = cocos2d::Node::create();
	m_LegContainer = cocos2d::Node::create();

	m_CurrentAssembly = ASSEMBLY_VIEW;

	setUIProperties(m_AssemblyBackground, cocos2d::Point::ZERO, cocos2d::Point::ZERO, RESOLUTION, true, 0);
	setUIProperties(m_AssemblyFrame, cocos2d::Point::ZERO, cocos2d::Point::ZERO, RESOLUTION, true, 0);
	setUIProperties(m_viewChangeArrow, cocos2d::Point(0.5, 0.5), cocos2d::Point(1055, 360), 1.0f, true, 1);

	m_ButtonConfirm->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1670, 90), "Confirm");
	m_ButtonCancel->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1900, 90), "Cancel");
	
	m_ButtonConfirm->setButtonFunc(std::bind(&AssemblyUILayer::confirmAssembly, this));
	m_ButtonCancel->setButtonFunc(std::bind(&AssemblyUILayer::toTitleScene, this));
	m_HeadContainer->setPosition(cocos2d::Point(190, 550));
	m_EngineContainer->setPosition(cocos2d::Point(190, 465));
	m_ArmorContainer->setPosition(cocos2d::Point(190, 380));
	m_MeleeContainer->setPosition(cocos2d::Point(190, 295));
	m_RangeContainer->setPosition(cocos2d::Point(190, 210));
	m_SteamContainer->setPosition(cocos2d::Point(190, 125));
	m_LegContainer->setPosition(cocos2d::Point(190, 40));

	auto sp = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_DEFAULT);

	auto test1 = IconLayer::create();
	auto test2 = IconLayer::create();
	auto test3 = IconLayer::create();
	auto test4 = IconLayer::create();
	auto test5 = IconLayer::create();
	auto test6 = IconLayer::create();

	m_HeadList.push_back(test1);
	m_HeadList.push_back(test2);
	m_HeadList.push_back(test3);
	m_HeadList.push_back(test4);
	m_HeadList.push_back(test5);
	m_HeadList.push_back(test6);

	for (int i = 0; i < 6; ++i)
	{
		m_HeadList[i]->setIconProperties(ASSEMBLY_ICON, sp, cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_HeadList[i]->setAnchorPoint(cocos2d::Point::ZERO);
		m_HeadContainer->addChild(m_HeadList[i]);
	}

	m_AssemblyBackground->addChild(m_HeadContainer);
	m_AssemblyBackground->addChild(m_EngineContainer);
	m_AssemblyBackground->addChild(m_ArmorContainer);
	m_AssemblyBackground->addChild(m_MeleeContainer);
	m_AssemblyBackground->addChild(m_RangeContainer);
	m_AssemblyBackground->addChild(m_SteamContainer);
	m_AssemblyBackground->addChild(m_LegContainer);

	m_AssemblyFrame->addChild(m_ButtonConfirm);
	m_AssemblyFrame->addChild(m_ButtonCancel);
	m_AssemblyFrame->addChild(m_viewChangeArrow);
	
	this->addChild(m_AssemblyBackground);
	this->addChild(m_AssemblyFrame);

	return true;
}

void AssemblyUILayer::update(float dTime)
{
	MouseInfo mouseInput = GET_INPUT_MANAGER()->getMouseInfo();
	if (m_CurrentAssembly == ASSEMBLY_VIEW)
	{
		if (m_viewChangeRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]) || mouseInput.m_ScollValue < 0)
		{
			viewChange(SKILL_VIEW);
		}
	}
	else
	{
		if (m_viewChangeRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]) || mouseInput.m_ScollValue > 0)
		{
			viewChange(ASSEMBLY_VIEW);
		}
	}
	
	m_ButtonConfirm->update(dTime);
	m_ButtonCancel->update(dTime);
	for (int i = 0; i < 6; ++i)
	{
		m_HeadList[i]->update(dTime);
	}
}

void AssemblyUILayer::viewChange(AssemblyLayerType moveViewTo)
{
	cocos2d::ActionInterval* moveAction0;
	cocos2d::ActionInterval* moveAction1;
	if (moveViewTo == SKILL_VIEW)
	{
		moveAction0 = cocos2d::MoveTo::create(1.0f, cocos2d::Point(-830 * RESOLUTION, 0));
		moveAction1 = cocos2d::MoveTo::create(1.5f, cocos2d::Point(-830 * RESOLUTION, 0));
		m_viewChangeRect.setRect(20 * RESOLUTION, 310 * RESOLUTION, 25 * RESOLUTION, 100 * RESOLUTION);
		m_viewChangeArrow->setRotation(180);
		m_ButtonConfirm->setButtonRect(cocos2d::Point(-830 * RESOLUTION, 0));
		m_ButtonCancel->setButtonRect(cocos2d::Point(-830 * RESOLUTION, 0));
		m_HeadContainer->setVisible(false);
		m_EngineContainer->setVisible(false);
		m_ArmorContainer->setVisible(false);
		m_MeleeContainer->setVisible(false);
		m_RangeContainer->setVisible(false);
		m_SteamContainer->setVisible(false);
		m_LegContainer->setVisible(false);
		m_CurrentAssembly = SKILL_VIEW;
	}
	else
	{
		moveAction0 = cocos2d::MoveTo::create(1.0f, cocos2d::Point(0, 0));
		moveAction1 = cocos2d::MoveTo::create(1.5f, cocos2d::Point(0, 0));
		m_viewChangeRect.setRect(1235 * RESOLUTION, 310 * RESOLUTION, 25 * RESOLUTION, 100 * RESOLUTION);
		m_viewChangeArrow->setRotation(0);
		m_ButtonConfirm->setButtonRect(cocos2d::Point(0 * RESOLUTION, 0));
		m_ButtonCancel->setButtonRect(cocos2d::Point(0 * RESOLUTION, 0));
		m_HeadContainer->setVisible(true);
		m_EngineContainer->setVisible(true);
		m_ArmorContainer->setVisible(true);
		m_MeleeContainer->setVisible(true);
		m_RangeContainer->setVisible(true);
		m_SteamContainer->setVisible(true);
		m_LegContainer->setVisible(true);
		m_CurrentAssembly = ASSEMBLY_VIEW;
	}
	cocos2d::Action* action0 = cocos2d::EaseExponentialOut::create(moveAction0);
	cocos2d::Action* action1 = cocos2d::EaseExponentialOut::create(moveAction1);
	m_AssemblyFrame->runAction(action0);
	m_AssemblyBackground->runAction(action1);
	GET_INPUT_MANAGER()->resetMouseInfo();
}

void AssemblyUILayer::confirmAssembly()
{
	if (!m_IsStarted)
	{
		m_IsStarted = true;
		GET_STAGE_MANAGER()->initStage(0);
	}
}

void AssemblyUILayer::toTitleScene()
{
	exit(0);
}
