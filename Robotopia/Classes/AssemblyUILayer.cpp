#include "pch.h"
#include "AssemblyUILayer.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"
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
	this->addChild(m_AssemblyBackground);
	this->addChild(m_AssemblyFrame);

	return true;
}

void AssemblyUILayer::update(float dTime)
{
	MouseInfo mouseInput = GET_INPUT_MANAGER()->getMouseInfo();
	if (mouseInput.m_DoubleClick)
	{
		cocos2d::log("D?D?D?D??D?D??");
	}
	if (mouseInput.m_DragOn)
	{
		cocos2d::log("On?????????????");
	}
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
			else
			{
				GET_INPUT_MANAGER()->resetMouseWheel();
			}
		}
		else if (m_viewChangeRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]))
		{
			viewChange(SKILL_VIEW);
		}

		if (m_EquipmentRect.containsPoint(mouseInput.m_MouseMove))
		{
			updateEquipments(dTime);

			if (mouseInput.m_DoubleClick)
			{
				cocos2d::log("hey!");
				setConfirmSet();
				moveScanBar();
				GET_INPUT_MANAGER()->resetMouseDoubleClick();
			}
		}
		else
		{
			if (mouseInput.m_DoubleClick)
			{
				GET_INPUT_MANAGER()->resetMouseDoubleClick();
			}
		}

		if (m_DisplayScanBar->getPosition().y == 650)
		{
			m_DisplayScanBar->setVisible(false);
			m_DisplayScanBar->setPosition(cocos2d::Point(1055, 200));
		}
	}
	else if (m_CurrentAssembly == SKILL_VIEW)
	{
		if (mouseInput.m_ScollValue > 0)
		{
			viewChange(ASSEMBLY_VIEW);
		}
		else if (mouseInput.m_ScollValue < 0)
		{
			GET_INPUT_MANAGER()->resetMouseWheel();
		}
		else if (m_viewChangeRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]))
		{
			viewChange(ASSEMBLY_VIEW);
		}
		m_ButtonConfirm->update(dTime);
		m_ButtonCancel->update(dTime);
	}
}

//성능을 위해서 업데이트에서 범위 바꾼 후 템플릿으로 전환 가능
void AssemblyUILayer::setConfirmSet()
{
	auto headTemp = m_ConfirmSet.m_Head;
	for (int i = static_cast<int>(HL_START); i < static_cast<int>(HL_END); ++i)
	{
		if (m_HeadList[i]->getEquipmentIcon()->getSelected())
		{
			if (m_ConfirmSet.m_Head == HL_END)
			{
				m_ConfirmSet.m_Head = m_HeadList[i]->getEquipmentInfo().m_HeadType;
			}
			else if (headTemp != m_HeadList[i]->getEquipmentInfo().m_HeadType)
			{
				m_ConfirmSet.m_Head = m_HeadList[i]->getEquipmentInfo().m_HeadType;
				m_HeadList[i]->setEquipmentIcon(ICON_SELECTED);
			}
			else if (headTemp == m_HeadList[i]->getEquipmentInfo().m_HeadType)
			{
				m_HeadList[i]->setEquipmentIcon(ICON_DEFAULT);
			}
		}
	}
	auto engineTemp = m_ConfirmSet.m_Engine;
	for (int i = static_cast<int>(EL_START); i < static_cast<int>(EL_END); ++i)
	{
		if (m_EngineList[i]->getEquipmentIcon()->getSelected())
		{
			if (m_ConfirmSet.m_Engine == EL_END)
			{
				m_ConfirmSet.m_Engine = m_EngineList[i]->getEquipmentInfo().m_EngineType;
			}
			else if (engineTemp != m_EngineList[i]->getEquipmentInfo().m_EngineType)
			{
				m_ConfirmSet.m_Engine = m_EngineList[i]->getEquipmentInfo().m_EngineType;
				m_EngineList[i]->setEquipmentIcon(ICON_SELECTED);
			}
			else if (engineTemp == m_EngineList[i]->getEquipmentInfo().m_EngineType)
			{
				m_EngineList[i]->setEquipmentIcon(ICON_DEFAULT);
			}
		}
	}
	auto armorTemp = m_ConfirmSet.m_Armor;
	for (int i = static_cast<int>(AL_START); i < static_cast<int>(AL_END); ++i)
	{
		if (m_ArmorList[i]->getEquipmentIcon()->getSelected())
		{
			if (m_ConfirmSet.m_Armor == AL_END)
			{
				m_ConfirmSet.m_Armor = m_ArmorList[i]->getEquipmentInfo().m_ArmorType;
			}
			else if (armorTemp != m_ArmorList[i]->getEquipmentInfo().m_ArmorType)
			{
				m_ConfirmSet.m_Armor = m_ArmorList[i]->getEquipmentInfo().m_ArmorType;
				m_ArmorList[i]->setEquipmentIcon(ICON_SELECTED);
			}
			else if (armorTemp == m_ArmorList[i]->getEquipmentInfo().m_ArmorType)
			{
				m_EngineList[i]->setEquipmentIcon(ICON_DEFAULT);
			}
		}
	}
	auto meleeTemp = m_ConfirmSet.m_Melee;
	for (int i = static_cast<int>(ML_START); i < static_cast<int>(ML_END); ++i)
	{
		if (m_MeleeList[i]->getEquipmentIcon()->getSelected())
		{
			if (m_ConfirmSet.m_Melee == ML_END)
			{
				m_ConfirmSet.m_Melee = m_MeleeList[i]->getEquipmentInfo().m_MeleeType;
			}
			else if (meleeTemp != m_MeleeList[i]->getEquipmentInfo().m_MeleeType)
			{
				m_ConfirmSet.m_Melee = m_MeleeList[i]->getEquipmentInfo().m_MeleeType;
				m_MeleeList[i]->setEquipmentIcon(ICON_SELECTED);
			}
			else if (meleeTemp == m_MeleeList[i]->getEquipmentInfo().m_MeleeType)
			{
				m_MeleeList[i]->setEquipmentIcon(ICON_DEFAULT);
			}
		}
	}
	auto rangeTemp = m_ConfirmSet.m_Range;
	for (int i = static_cast<int>(RL_START); i < static_cast<int>(RL_END); ++i)
	{
		if (m_RangeList[i]->getEquipmentIcon()->getSelected())
		{
			if (m_ConfirmSet.m_Range == RL_END)
			{
				m_ConfirmSet.m_Range = m_RangeList[i]->getEquipmentInfo().m_RangeType;
			}
			else if (rangeTemp != m_RangeList[i]->getEquipmentInfo().m_RangeType)
			{
				m_ConfirmSet.m_Range = m_RangeList[i]->getEquipmentInfo().m_RangeType;
				m_RangeList[i]->setEquipmentIcon(ICON_SELECTED);
			}
			else if (rangeTemp == m_RangeList[i]->getEquipmentInfo().m_RangeType)
			{
				m_RangeList[i]->setEquipmentIcon(ICON_DEFAULT);
			}
		}
	}
	auto steamTemp = m_ConfirmSet.m_Steam;
	for (int i = static_cast<int>(SCL_START); i < static_cast<int>(SCL_END); ++i)
	{
		if (m_SteamList[i]->getEquipmentIcon()->getSelected())
		{
			if (m_ConfirmSet.m_Steam == SCL_END)
			{
				m_ConfirmSet.m_Steam = m_SteamList[i]->getEquipmentInfo().m_SteamContainerType;
			}
			else if (steamTemp != m_SteamList[i]->getEquipmentInfo().m_SteamContainerType)
			{
				m_ConfirmSet.m_Steam = m_SteamList[i]->getEquipmentInfo().m_SteamContainerType;
				m_SteamList[i]->setEquipmentIcon(ICON_SELECTED);
			}
			else if (steamTemp == m_SteamList[i]->getEquipmentInfo().m_SteamContainerType)
			{
				m_SteamList[i]->setEquipmentIcon(ICON_DEFAULT);
			}
		}
	}
	auto legTemp = m_ConfirmSet.m_Leg;
	for (int i = static_cast<int>(LL_START); i < static_cast<int>(LL_END); ++i)
	{
		if (m_LegList[i]->getEquipmentIcon()->getSelected())
		{
			if (m_ConfirmSet.m_Leg == LL_END)
			{
				m_ConfirmSet.m_Leg = m_LegList[i]->getEquipmentInfo().m_LegType;
			}
			else if (legTemp != m_LegList[i]->getEquipmentInfo().m_LegType)
			{
				m_ConfirmSet.m_Leg = m_LegList[i]->getEquipmentInfo().m_LegType;
				m_LegList[i]->setEquipmentIcon(ICON_SELECTED);
			}
			else if (legTemp == m_LegList[i]->getEquipmentInfo().m_LegType)
			{
				m_LegList[i]->setEquipmentIcon(ICON_DEFAULT);
			}
		}
	}
}
//template 변환 가능
void AssemblyUILayer::updateEquipments(float dTime)
{
	for (int i = static_cast<int>(HL_START); i < static_cast<int>(HL_END); ++i)
	{
		m_HeadList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_HeadList[i]->update(dTime);
	}
	for (int i = static_cast<int>(EL_START); i < static_cast<int>(EL_END); ++i)
	{
		m_EngineList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_EngineContainer->getBoundingBox().getMinX() * RESOLUTION, m_EngineContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_EngineList[i]->update(dTime);
	}
	for (int i = static_cast<int>(AL_START); i < static_cast<int>(AL_END); ++i)
	{
		m_ArmorList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_ArmorContainer->getBoundingBox().getMinX() * RESOLUTION, m_ArmorContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_ArmorList[i]->update(dTime);
	}
	for (int i = static_cast<int>(ML_START); i < static_cast<int>(ML_END); ++i)
	{
		m_MeleeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_MeleeContainer->getBoundingBox().getMinX() * RESOLUTION, m_MeleeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_MeleeList[i]->update(dTime);
	}
	for (int i = static_cast<int>(RL_START); i < static_cast<int>(RL_END); ++i)
	{
		m_RangeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_RangeContainer->getBoundingBox().getMinX() * RESOLUTION, m_RangeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_RangeList[i]->update(dTime);
	}
	for (int i = static_cast<int>(SCL_START); i < static_cast<int>(SCL_END); ++i)
	{
		m_SteamList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_SteamContainer->getBoundingBox().getMinX() * RESOLUTION, m_SteamContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_SteamList[i]->update(dTime);
	}
	for (int i = static_cast<int>(LL_START); i < static_cast<int>(LL_END); ++i)
	{
		m_LegList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_LegContainer->getBoundingBox().getMinX() * RESOLUTION, m_LegContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_LegList[i]->update(dTime);
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
	GET_INPUT_MANAGER()->resetMousePoints();
	GET_INPUT_MANAGER()->resetMouseWheel();
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
}

void AssemblyUILayer::assemblyLayerButtonInit()
{
	m_ButtonConfirm = ButtonLayer::create();
	m_ButtonCancel = ButtonLayer::create();
	
	m_ButtonConfirm->setButtonProperties(BUTTON_ASSEMBLY, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1670, 90), "Confirm");
	m_ButtonCancel->setButtonProperties(BUTTON_ASSEMBLY, cocos2d::Point(0 * RESOLUTION, 0), cocos2d::Point(1900, 90), "Cancel");
	
	m_ButtonConfirm->setButtonFunc(std::bind(&AssemblyUILayer::confirmAssembly, this));
	m_ButtonCancel->setButtonFunc(std::bind(&AssemblyUILayer::toTitleScene, this));
	
	m_AssemblyFrame->addChild(m_ButtonConfirm);
	m_AssemblyFrame->addChild(m_ButtonCancel);
}

void AssemblyUILayer::displayEquipments()
{
	auto testSp = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_DEFAULT);
	int count = 0;
	for (int i = static_cast<int>(HL_START); i < static_cast<int>(HL_END); ++i)
	{
		EquipmentHead* head = EquipmentHead::create();
		m_HeadList.push_back(head);
		bool lockTest = static_cast<bool>(rand() % 2);
		m_HeadList[i]->setEquipment(EMT_HEAD, static_cast<HeadList>(i), i, i * 10, 20, lockTest, i * 10, i * 100);
		m_HeadList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_HeadList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), lockTest);
		m_HeadContainer->addChild(m_HeadList[i]);
		count++;
	}
	m_HeadContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(EL_START); i < static_cast<int>(EL_END); ++i)
	{
		EquipmentEngine* engine = EquipmentEngine::create();
		m_EngineList.push_back(engine);
		bool lockTest = static_cast<bool>(rand() % 2);
		m_EngineList[i]->setEquipment(EMT_ENGINE, static_cast<EngineList>(i), i, i * 10, 20, static_cast<bool>(rand() % 2), i * 10, i * 100);
		m_EngineList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_EngineContainer->getBoundingBox().getMinX() * RESOLUTION, m_EngineContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_EngineList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), lockTest);
		m_EngineContainer->addChild(m_EngineList[i]);
		count++;
	}
	m_EngineContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(AL_START); i < static_cast<int>(AL_END); ++i)
	{
		EquipmentArmor* armor = EquipmentArmor::create();
		m_ArmorList.push_back(armor);
		bool lockTest = static_cast<bool>(rand() % 2);
		m_ArmorList[i]->setEquipment(EMT_ENGINE, static_cast<ArmorList>(i), i, i * 10, 20, static_cast<bool>(rand() % 2), i * 10, i * 100);
		m_ArmorList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_ArmorContainer->getBoundingBox().getMinX() * RESOLUTION, m_ArmorContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_ArmorList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), lockTest);
		m_ArmorContainer->addChild(m_ArmorList[i]);
		count++;
	}
	m_ArmorContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(ML_START); i < static_cast<int>(ML_END); ++i)
	{
		EquipmentMelee* melee = EquipmentMelee::create();
		m_MeleeList.push_back(melee);
		bool lockTest = static_cast<bool>(rand() % 2);
		m_MeleeList[i]->setEquipment(EMT_ENGINE, static_cast<MeleeList>(i), i, i * 10, 20, static_cast<bool>(rand() % 2), i * 10, i * 100);
		m_MeleeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_MeleeContainer->getBoundingBox().getMinX() * RESOLUTION, m_MeleeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_MeleeList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), lockTest);
		m_MeleeContainer->addChild(m_MeleeList[i]);
		count++;
	}
	m_MeleeContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(RL_START); i < static_cast<int>(RL_END); ++i)
	{
		EquipmentRange* range = EquipmentRange::create();
		m_RangeList.push_back(range);
		bool lockTest = static_cast<bool>(rand() % 2);
		m_RangeList[i]->setEquipment(EMT_ENGINE, static_cast<RangeList>(i), i, i * 10, 20, static_cast<bool>(rand() % 2), i * 10, i * 100, i * 2);
		m_RangeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_RangeContainer->getBoundingBox().getMinX() * RESOLUTION, m_RangeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_RangeList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), lockTest);
		m_RangeContainer->addChild(m_RangeList[i]);
		count++;
	}
	m_RangeContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(SCL_START); i < static_cast<int>(SCL_END); ++i)
	{
		EquipmentSteamContainer* steam = EquipmentSteamContainer::create();
		m_SteamList.push_back(steam);
		bool lockTest = static_cast<bool>(rand() % 2);
		m_SteamList[i]->setEquipment(EMT_ENGINE, static_cast<SteamContainerList>(i), i, i * 10, 20, static_cast<bool>(rand() % 2), i * 10, i * 100);
		m_SteamList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_SteamContainer->getBoundingBox().getMinX() * RESOLUTION, m_SteamContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_SteamList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), lockTest);
		m_SteamContainer->addChild(m_SteamList[i]);
		count++;
	}
	m_SteamContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(LL_START); i < static_cast<int>(LL_END); ++i)
	{
		EquipmentLeg* leg = EquipmentLeg::create();
		m_LegList.push_back(leg);
		bool lockTest = static_cast<bool>(rand() % 2);
		m_LegList[i]->setEquipment(EMT_ENGINE, static_cast<LegList>(i), i, i * 10, 20, static_cast<bool>(rand() % 2), i * 10, i * 100);
		m_LegList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_LegContainer->getBoundingBox().getMinX() * RESOLUTION, m_LegContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_LegList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), lockTest);
		m_LegContainer->addChild(m_LegList[i]);
		count++;
	}
	m_LegContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));

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

void AssemblyUILayer::moveScanBar()
{
	m_DisplayScanBar->setPosition(cocos2d::Point(1055, 200));
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
		GET_INPUT_MANAGER()->resetMouseWheel();
	}
	else
	{
		if (container->getBoundingBox().getMinX() * RESOLUTION - 15 < containerRect.getMinX())
		{
			container->setPosition(cocos2d::Point(container->getPosition().x + 15, container->getPosition().y));
		}
		GET_INPUT_MANAGER()->resetMouseWheel();
	}
}

void AssemblyUILayer::confirmAssembly()
{
	if (!m_IsStarted)
	{
		m_IsStarted = true;
		GET_DATA_MANAGER()->initWorldData();
		GET_INPUT_MANAGER()->resetMouseInfo();
		GET_GAME_MANAGER()->changeScene(GET_STAGE_MANAGER()->getGameScene(), GAME_SCENE);
		GET_STAGE_MANAGER()->start();
	}
}

void AssemblyUILayer::toTitleScene()
{
	exit(0);
}
