#include "pch.h"
#include "AssemblyUILayer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "ButtonLayer.h"

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

	m_currentAssembly = true;

	setUIProperties(m_AssemblyBackground, cocos2d::Point::ZERO, cocos2d::Point::ZERO, RESOLUTION, true, 0);
	setUIProperties(m_AssemblyFrame, cocos2d::Point::ZERO, cocos2d::Point::ZERO, RESOLUTION, true, 0);
	setUIProperties(m_viewChangeArrow, cocos2d::Point(0.5, 0.5), cocos2d::Point(1055, 360), 1.0f, true, 1);

	m_ButtonConfirm->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1670, 90), "Confirm", 1);
	m_ButtonCancel->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1900, 90), "Cancel", 2);

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
	if (m_viewChangeRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]))
	{
		viewChange();
	}
	m_ButtonConfirm->update(dTime);
	m_ButtonCancel->update(dTime);
}

void AssemblyUILayer::viewChange()
{
	cocos2d::ActionInterval* moveAction;
	if (m_currentAssembly)
	{
		moveAction = cocos2d::MoveTo::create(1.0f, cocos2d::Point(-830 * RESOLUTION, 0));
		m_viewChangeRect.setRect(20 * RESOLUTION, 310 * RESOLUTION, 25 * RESOLUTION, 100 * RESOLUTION);
		m_currentAssembly = false;
		m_viewChangeArrow->setRotation(180);
		m_ButtonConfirm->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(-830 * RESOLUTION, 0), cocos2d::Point(1670, 90), "Confirm", 1);
		m_ButtonCancel->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(-830 * RESOLUTION, 0), cocos2d::Point(1900, 90), "Cancel", 2);
	}
	else
	{
		moveAction = cocos2d::MoveTo::create(1.0f, cocos2d::Point(0, 0));
		m_viewChangeRect.setRect(1235 * RESOLUTION, 310 * RESOLUTION, 25 * RESOLUTION, 100 * RESOLUTION);
		m_currentAssembly = true;
		m_viewChangeArrow->setRotation(0);
		m_ButtonConfirm->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1670, 90), "Confirm", 1);
		m_ButtonCancel->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1900, 90), "Cancel", 2);
	}
	cocos2d::Action* act = cocos2d::EaseExponentialOut::create(moveAction);
	m_AssemblyFrame->runAction(act);
	GET_INPUT_MANAGER()->resetMouseInfo();
}
