#include "pch.h"
#include "AssemblyUILayer.h"
#include "GameManager.h"
#include "StageManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "ButtonLayer.h"
#include "IconLayer.h"
#include "EquipmentHead.h"
#include "EquipmentEngine.h"
#include "EquipmentArmor.h"
#include "EquipmentMelee.h"
#include "EquipmentRange.h"
#include "EquipmentSteamContainer.h"
#include "EquipmentLeg.h"


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
	m_ViewChangeArrow = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ARROW);
	m_DisplayScanBar = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_SCAN_BAR);

	setUIProperties(m_AssemblyBackground, cocos2d::Point::ZERO, cocos2d::Point::ZERO, RESOLUTION, true, 0);
	setUIProperties(m_AssemblyFrame, cocos2d::Point::ZERO, cocos2d::Point::ZERO, RESOLUTION, true, 0);
	setUIProperties(m_ViewChangeArrow, cocos2d::Point(0.5, 0.5), cocos2d::Point(1055, 360), 1.0f, true, 1);
	setUIProperties(m_DisplayScanBar, cocos2d::Point(0.5, 0.5), cocos2d::Point(1055, 200), 1.0f, false, 2);
	equipmentContainerInit();

	assemblyLayerButtonInit();

	displayEquipments();

	m_CurrentAssembly = ASSEMBLY_VIEW;
	m_AssemblyFrame->addChild(m_ViewChangeArrow);	
	m_AssemblyFrame->addChild(m_DisplayScanBar);
	moveScanBar();
	this->addChild(m_AssemblyBackground);
	this->addChild(m_AssemblyFrame);

	return true;
}

void AssemblyUILayer::update(float dTime)
{
	MouseInfo mouseInput = GET_INPUT_MANAGER()->getMouseInfo();
	if (m_CurrentAssembly == ASSEMBLY_VIEW)
	{
		if (mouseInput.m_ScollValue < 0)
		{
			if (m_HeadRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(false, m_HeadContainer, m_HeadRect);
			}
			else if (m_EngineRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(false, m_EngineContainer, m_EngineRect);
			}
			else if (m_ArmorRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(false, m_ArmorContainer, m_ArmorRect);
			}
			else if (m_MeleeRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(false, m_MeleeContainer, m_MeleeRect);
			}
			else if (m_RangeRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(false, m_RangeContainer, m_RangeRect);
			}
			else if (m_SteamRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(false, m_SteamContainer, m_SteamRect);
			}
			else if (m_LegRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(false, m_LegContainer, m_LegRect);
			}
			else
			{
				viewChange(SKILL_VIEW);
			}
		}
		else if (mouseInput.m_ScollValue > 0)
		{
			if (m_HeadRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(true, m_HeadContainer, m_HeadRect);
			}
			else if (m_EngineRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(true, m_EngineContainer, m_EngineRect);
			}
			else if (m_ArmorRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(true, m_ArmorContainer, m_ArmorRect);
			}
			else if (m_MeleeRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(true, m_MeleeContainer, m_MeleeRect);
			}
			else if (m_RangeRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(true, m_RangeContainer, m_RangeRect);
			}
			else if (m_SteamRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(true, m_SteamContainer, m_SteamRect);
			}
			else if (m_LegRect.containsPoint(mouseInput.m_MouseMove))
			{
				moveContainer(true, m_LegContainer, m_LegRect);
			}
		}
		else if (m_viewChangeRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]))
		{
			viewChange(SKILL_VIEW);
		}
		if (m_EquipmentRect.containsPoint(mouseInput.m_MouseMove))
		{
			updateEquipments(dTime);
		}
	}
	else if (m_CurrentAssembly == SKILL_VIEW)
	{
		if (m_viewChangeRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]) || mouseInput.m_ScollValue > 0)
		{
			viewChange(ASSEMBLY_VIEW);
		}
		m_ButtonConfirm->update(dTime);
		m_ButtonCancel->update(dTime);
	}

	if (m_DisplayScanBar->isVisible() && m_DisplayScanBar->getNumberOfRunningActions() == 0)
	{
		m_DisplayScanBar->setVisible(false);
		m_DisplayScanBar->setPosition(cocos2d::Point(1055, 200));
	}
}

void AssemblyUILayer::updateEquipments(float dTime)
{
	for (int i = static_cast<int>(HL_START); i < static_cast<int>(HL_END); ++i)
	{
		m_HeadList[i]->update(dTime);
		m_HeadList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
	}
	for (int i = static_cast<int>(EL_START); i < static_cast<int>(EL_END); ++i)
	{
		m_EngineList[i]->update(dTime);
		m_EngineList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_EngineContainer->getBoundingBox().getMinX() * RESOLUTION, m_EngineContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
	}
	for (int i = static_cast<int>(AL_START); i < static_cast<int>(AL_END); ++i)
	{
		m_ArmorList[i]->update(dTime);
		m_ArmorList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_ArmorContainer->getBoundingBox().getMinX() * RESOLUTION, m_ArmorContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
	}
	for (int i = static_cast<int>(ML_START); i < static_cast<int>(ML_END); ++i)
	{
		m_MeleeList[i]->update(dTime);
		m_MeleeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_MeleeContainer->getBoundingBox().getMinX() * RESOLUTION, m_MeleeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
	}
	for (int i = static_cast<int>(RL_START); i < static_cast<int>(RL_END); ++i)
	{
		m_RangeList[i]->update(dTime);
		m_RangeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_RangeContainer->getBoundingBox().getMinX() * RESOLUTION, m_RangeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
	}
	for (int i = static_cast<int>(SCL_START); i < static_cast<int>(SCL_END); ++i)
	{
		m_SteamList[i]->update(dTime);
		m_SteamList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_SteamContainer->getBoundingBox().getMinX() * RESOLUTION, m_SteamContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
	}
	for (int i = static_cast<int>(LL_START); i < static_cast<int>(LL_END); ++i)
	{
		m_LegList[i]->update(dTime);
		m_LegList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_LegContainer->getBoundingBox().getMinX() * RESOLUTION, m_LegContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
	}
}

void AssemblyUILayer::viewChange(AssemblyLayerType moveViewTo)
{
	if (m_AssemblyBackground->getNumberOfRunningActions() == 0)
	{
		cocos2d::ActionInterval* moveAction0;
		cocos2d::ActionInterval* moveAction1;
		if (moveViewTo == SKILL_VIEW)
		{
			moveAction0 = cocos2d::MoveTo::create(1.0f, cocos2d::Point(-830 * RESOLUTION, 0));
			moveAction1 = cocos2d::MoveTo::create(1.2f, cocos2d::Point(-830 * RESOLUTION, 0));
			m_viewChangeRect.setRect(20 * RESOLUTION, 310 * RESOLUTION, 25 * RESOLUTION, 100 * RESOLUTION);
			m_ViewChangeArrow->setRotation(180);
			m_ButtonConfirm->setButtonRect(cocos2d::Point(-830 * RESOLUTION, 0));
			m_ButtonCancel->setButtonRect(cocos2d::Point(-830 * RESOLUTION, 0));
			equipmentContainerVisible(false);
			m_CurrentAssembly = SKILL_VIEW;
		}
		else
		{
			moveAction0 = cocos2d::MoveTo::create(1.0f, cocos2d::Point(0, 0));
			moveAction1 = cocos2d::MoveTo::create(1.2f, cocos2d::Point(0, 0));
			m_viewChangeRect.setRect(1235 * RESOLUTION, 310 * RESOLUTION, 25 * RESOLUTION, 100 * RESOLUTION);
			m_ViewChangeArrow->setRotation(0);
			m_ButtonConfirm->setButtonRect(cocos2d::Point(0 * RESOLUTION, 0));
			m_ButtonCancel->setButtonRect(cocos2d::Point(0 * RESOLUTION, 0));
			equipmentContainerVisible(true);
			m_CurrentAssembly = ASSEMBLY_VIEW;
		}
		cocos2d::Action* action0 = cocos2d::EaseExponentialOut::create(moveAction0);
		cocos2d::Action* action1 = cocos2d::EaseExponentialOut::create(moveAction1);
		m_AssemblyFrame->runAction(action0);
		m_AssemblyBackground->runAction(action1);
	}
	GET_INPUT_MANAGER()->resetMouseInfo();
}

void AssemblyUILayer::confirmAssembly()
{
	if (!m_IsStarted)
	{
		m_IsStarted = true;
		GET_GAME_MANAGER()->changeScene(GET_STAGE_MANAGER()->getGameScene(),GAME_SCENE);
		GET_STAGE_MANAGER()->start();
	}
}

void AssemblyUILayer::toTitleScene()
{
	exit(0);
}

void AssemblyUILayer::equipmentContainerInit()
{
	m_HeadContainer = cocos2d::Node::create();
	m_EngineContainer = cocos2d::Node::create();
	m_ArmorContainer = cocos2d::Node::create();
	m_MeleeContainer = cocos2d::Node::create();
	m_RangeContainer = cocos2d::Node::create();
	m_SteamContainer = cocos2d::Node::create();
	m_LegContainer = cocos2d::Node::create();

	m_HeadContainer->setPosition(cocos2d::Point(190, 550));
	m_EngineContainer->setPosition(cocos2d::Point(190, 465));
	m_ArmorContainer->setPosition(cocos2d::Point(190, 380));
	m_MeleeContainer->setPosition(cocos2d::Point(190, 295));
	m_RangeContainer->setPosition(cocos2d::Point(190, 210));
	m_SteamContainer->setPosition(cocos2d::Point(190, 125));
	m_LegContainer->setPosition(cocos2d::Point(190, 40));
	
	m_AssemblyBackground->addChild(m_HeadContainer);
	m_AssemblyBackground->addChild(m_EngineContainer);
	m_AssemblyBackground->addChild(m_ArmorContainer);
	m_AssemblyBackground->addChild(m_MeleeContainer);
	m_AssemblyBackground->addChild(m_RangeContainer);
	m_AssemblyBackground->addChild(m_SteamContainer);
	m_AssemblyBackground->addChild(m_LegContainer);

	m_EquipmentRect.setRect(190 * RESOLUTION, 40 * RESOLUTION, 390 * RESOLUTION, 580 * RESOLUTION);
	m_HeadRect.setRect(190 * RESOLUTION, 550 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_EngineRect.setRect(190 * RESOLUTION, 465 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_ArmorRect.setRect(190 * RESOLUTION, 380 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_MeleeRect.setRect(190 * RESOLUTION, 295 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_RangeRect.setRect(190 * RESOLUTION, 210 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_SteamRect.setRect(190 * RESOLUTION, 125 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_LegRect.setRect(190 * RESOLUTION, 40 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);

	setContainerSize();
}

void AssemblyUILayer::assemblyLayerButtonInit()
{
	m_ButtonConfirm = ButtonLayer::create();
	m_ButtonCancel = ButtonLayer::create();
	
	m_ButtonConfirm->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1670, 90), "Confirm");
	m_ButtonCancel->setButtonProperties(ASSEMBLY_BUTTON, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1900, 90), "Cancel");
	
	m_ButtonConfirm->setButtonFunc(std::bind(&AssemblyUILayer::confirmAssembly, this));
	m_ButtonCancel->setButtonFunc(std::bind(&AssemblyUILayer::toTitleScene, this));
	
	m_AssemblyFrame->addChild(m_ButtonConfirm);
	m_AssemblyFrame->addChild(m_ButtonCancel);
}

void AssemblyUILayer::displayEquipments()
{
	listUpEquipment(static_cast<int>(HL_START), static_cast<int>(HL_END), m_HeadContainer, &m_HeadList);
	listUpEquipment(static_cast<int>(EL_START), static_cast<int>(EL_END), m_EngineContainer, &m_EngineList);
	listUpEquipment(static_cast<int>(AL_START), static_cast<int>(AL_END), m_ArmorContainer, &m_ArmorList);
	listUpEquipment(static_cast<int>(ML_START), static_cast<int>(ML_END), m_MeleeContainer, &m_MeleeList);
	listUpEquipment(static_cast<int>(RL_START), static_cast<int>(RL_END), m_RangeContainer, &m_RangeList);
	listUpEquipment(static_cast<int>(SCL_START), static_cast<int>(SCL_END), m_SteamContainer, &m_SteamList);
	listUpEquipment(static_cast<int>(LL_START), static_cast<int>(LL_END), m_LegContainer, &m_LegList);
}

void AssemblyUILayer::equipmentContainerVisible(bool visible)
{
	m_HeadContainer->setVisible(visible);
	m_EngineContainer->setVisible(visible);
	m_ArmorContainer->setVisible(visible);
	m_MeleeContainer->setVisible(visible);
	m_RangeContainer->setVisible(visible);
	m_SteamContainer->setVisible(visible);
	m_LegContainer->setVisible(visible);
}

void AssemblyUILayer::setContainerSize()
{
	int count = 0;
	for (int i = static_cast<int>(HL_START); i < static_cast<int>(HL_END); ++i)
	{
		count++;
	}
	m_HeadContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(EL_START); i < static_cast<int>(EL_END); ++i)
	{
		count++;
	}
	m_EngineContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(AL_START); i < static_cast<int>(AL_END); ++i)
	{
		count++;
	}
	m_ArmorContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(ML_START); i < static_cast<int>(ML_END); ++i)
	{
		count++;
	}
	m_MeleeContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(RL_START); i < static_cast<int>(RL_END); ++i)
	{
		count++;
	}
	m_RangeContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(SCL_START); i < static_cast<int>(SCL_END); ++i)
	{
		count++;
	}
	m_SteamContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(LL_START); i < static_cast<int>(LL_END); ++i)
	{
		count++;
	}
	m_LegContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
}

void AssemblyUILayer::moveScanBar()
{
	m_DisplayScanBar->setVisible(true);
	auto moveAction = cocos2d::MoveTo::create(1.0f, cocos2d::Point(1055, 650));
	m_DisplayScanBar->runAction(moveAction);
}

void AssemblyUILayer::moveContainer(bool moveLeft, cocos2d::Node* container, cocos2d::Rect containerRect)
{
	if (moveLeft)
	{
		if (container->getBoundingBox().getMaxX() - 110 > containerRect.getMaxX())
		{//액션으로 만들 수도?
			container->setPosition(cocos2d::Point(container->getPosition().x - 15, container->getPosition().y));
		}
		GET_INPUT_MANAGER()->resetMouseInfo();
	}
	else
	{
		if (container->getBoundingBox().getMinX() * RESOLUTION - 15 < containerRect.getMinX())
		{
			container->setPosition(cocos2d::Point(container->getPosition().x + 15, container->getPosition().y));
		}
		GET_INPUT_MANAGER()->resetMouseInfo();
	}
}
