#include "pch.h"
#include "AssemblyLineLayer.h"
#include "DataManager.h"
#include "EquipmentAbstract.h"
#include "EquipmentHead.h"
#include "EquipmentEngine.h"
#include "EquipmentArmor.h"
#include "EquipmentMelee.h"
#include "EquipmentRange.h"
#include "EquipmentSteamContainer.h"
#include "EquipmentLeg.h"
#include "EquipmentAbstract.h"
#include "IconLayer.h"

bool AssemblyLineLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	initEquipmentContainer();
	return true;
}

void AssemblyLineLayer::update(float dTime)
{
	/*
	MouseInfo mouseInput = GET_INPUT_MANAGER()->getMouseInfo();
	if (m_CurrentAssembly == ASSEMBLY_VIEW)
	{
		if (mouseInput.m_ScollValue < 0)
		{
			containerScroll(false, mouseInput.m_MouseMove);
			if (!m_EquipmentRect.containsPoint(mouseInput.m_MouseMove))
			{
				viewChange(SKILL_VIEW);
			}
		}
		else if (mouseInput.m_ScollValue > 0)
		{
			containerScroll(true, mouseInput.m_MouseMove);
			if (!m_EquipmentRect.containsPoint(mouseInput.m_MouseMove))
			{
				GET_INPUT_MANAGER()->resetMouseWheel();
			}
		}

		if (m_viewChangeRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]))
		{
			viewChange(SKILL_VIEW);
		}

		if (m_EquipmentRect.containsPoint(mouseInput.m_MouseMove))
		{
			updateEquipments(dTime);

			if (mouseInput.m_DoubleClick)
			{
				updateDoubleClickIcon(mouseInput.m_MouseMove);
				setConfirmSet(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]);
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

		if (m_viewChangeRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]))
		{
			viewChange(ASSEMBLY_VIEW);
		}
	}*/
}

void AssemblyLineLayer::initEquipmentContainer()
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

	this->addChild(m_HeadContainer);
	this->addChild(m_EngineContainer);
	this->addChild(m_ArmorContainer);
	this->addChild(m_MeleeContainer);
	this->addChild(m_RangeContainer);
	this->addChild(m_SteamContainer);
	this->addChild(m_LegContainer);

	m_HeadRect.setRect(190 * RESOLUTION, 550 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_EngineRect.setRect(190 * RESOLUTION, 465 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_ArmorRect.setRect(190 * RESOLUTION, 380 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_MeleeRect.setRect(190 * RESOLUTION, 295 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_RangeRect.setRect(190 * RESOLUTION, 210 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_SteamRect.setRect(190 * RESOLUTION, 125 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_LegRect.setRect(190 * RESOLUTION, 40 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
}

void AssemblyLineLayer::displayEquipments()
{
	int count = 0;
	for (int i = static_cast<int>(HL_START)+1; i < static_cast<int>(HL_END); ++i)
	{
		auto info = static_cast<const HeadInfo*>(GET_DATA_MANAGER()->getEquipmentInfo(EMT_HEAD, i));
		EquipmentHead* head = EquipmentHead::create();
		m_HeadList.push_back(head);
		m_HeadList[i]->setEquipment(*info);
		m_HeadList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_HeadList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
		m_HeadContainer->addChild(m_HeadList[i]);
		count++;
	}
	m_HeadContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(EL_START)+1; i < static_cast<int>(EL_END); ++i)
	{
		auto info = static_cast<const EngineInfo*>(GET_DATA_MANAGER()->getEquipmentInfo(EMT_ENGINE, i));
		EquipmentEngine* engine = EquipmentEngine::create();
		m_EngineList.push_back(engine);
		m_EngineList[i]->setEquipment(*info);
		m_EngineList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_EngineContainer->getBoundingBox().getMinX() * RESOLUTION, m_EngineContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_EngineList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
		m_EngineContainer->addChild(m_EngineList[i]);
		count++;
	}
	m_EngineContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(AL_START)+1; i < static_cast<int>(AL_END); ++i)
	{
		auto info = static_cast<const ArmorInfo*>(GET_DATA_MANAGER()->getEquipmentInfo(EMT_ARMOR, i));
		EquipmentArmor* armor = EquipmentArmor::create();
		m_ArmorList.push_back(armor);
		m_ArmorList[i]->setEquipment(*info);
		m_ArmorList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_ArmorContainer->getBoundingBox().getMinX() * RESOLUTION, m_ArmorContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_ArmorList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
		m_ArmorContainer->addChild(m_ArmorList[i]);
		count++;
	}
	m_ArmorContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(ML_START)+1; i < static_cast<int>(ML_END); ++i)
	{
		auto info = static_cast<const MeleeInfo*>(GET_DATA_MANAGER()->getEquipmentInfo(EMT_MELEE, i));
		EquipmentMelee* melee = EquipmentMelee::create();
		m_MeleeList.push_back(melee);
		m_MeleeList[i]->setEquipment(*info);
		m_MeleeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_MeleeContainer->getBoundingBox().getMinX() * RESOLUTION, m_MeleeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_MeleeList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
		m_MeleeContainer->addChild(m_MeleeList[i]);
		count++;
	}
	m_MeleeContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(RL_START)+1; i < static_cast<int>(RL_END); ++i)
	{
		auto info = static_cast<const RangeInfo*>(GET_DATA_MANAGER()->getEquipmentInfo(EMT_RANGE, i));
		EquipmentRange* range = EquipmentRange::create();
		m_RangeList.push_back(range);
		m_RangeList[i]->setEquipment(*info);
		m_RangeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_RangeContainer->getBoundingBox().getMinX() * RESOLUTION, m_RangeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_RangeList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
		m_RangeContainer->addChild(m_RangeList[i]);
		count++;
	}
	m_RangeContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
	{
		auto info = static_cast<const SteamContainerInfo*>(GET_DATA_MANAGER()->getEquipmentInfo(EMT_STEAMCONTAINTER, i));
		EquipmentSteamContainer* steam = EquipmentSteamContainer::create();
		m_SteamList.push_back(steam);
		m_SteamList[i]->setEquipment(*info);
		m_SteamList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_SteamContainer->getBoundingBox().getMinX() * RESOLUTION, m_SteamContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_SteamList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
		m_SteamContainer->addChild(m_SteamList[i]);
		count++;
	}
	m_SteamContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(LL_START)+1; i < static_cast<int>(LL_END); ++i)
	{
		auto info = static_cast<const LegInfo*>(GET_DATA_MANAGER()->getEquipmentInfo(EMT_LEG, i));
		EquipmentLeg* leg = EquipmentLeg::create();
		m_LegList.push_back(leg);
		m_LegList[i]->setEquipment(*info);
		m_LegList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_LegContainer->getBoundingBox().getMinX() * RESOLUTION, m_LegContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_LegList[i]->getEquipmentIcon()->setIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
		m_LegContainer->addChild(m_LegList[i]);
		count++;
	}
	m_LegContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
}

void AssemblyLineLayer::updateEquipments(float dTime)
{
	for (int i = static_cast<int>(HL_START)+1; i < static_cast<int>(HL_END); ++i)
	{
		m_HeadList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_HeadList[i]->update(dTime);
	}
	for (int i = static_cast<int>(EL_START)+1; i < static_cast<int>(EL_END); ++i)
	{
		m_EngineList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_EngineContainer->getBoundingBox().getMinX() * RESOLUTION, m_EngineContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_EngineList[i]->update(dTime);
	}
	for (int i = static_cast<int>(AL_START)+1; i < static_cast<int>(AL_END); ++i)
	{
		m_ArmorList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_ArmorContainer->getBoundingBox().getMinX() * RESOLUTION, m_ArmorContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_ArmorList[i]->update(dTime);
	}
	for (int i = static_cast<int>(ML_START)+1; i < static_cast<int>(ML_END); ++i)
	{
		m_MeleeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_MeleeContainer->getBoundingBox().getMinX() * RESOLUTION, m_MeleeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_MeleeList[i]->update(dTime);
	}
	for (int i = static_cast<int>(RL_START)+1; i < static_cast<int>(RL_END); ++i)
	{
		m_RangeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_RangeContainer->getBoundingBox().getMinX() * RESOLUTION, m_RangeContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_RangeList[i]->update(dTime);
	}
	for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
	{
		m_SteamList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_SteamContainer->getBoundingBox().getMinX() * RESOLUTION, m_SteamContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_SteamList[i]->update(dTime);
	}
	for (int i = static_cast<int>(LL_START)+1; i < static_cast<int>(LL_END); ++i)
	{
		m_LegList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(m_LegContainer->getBoundingBox().getMinX() * RESOLUTION, m_LegContainer->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
		m_LegList[i]->update(dTime);
	}
}

void AssemblyLineLayer::updateDoubleClickIcon(cocos2d::Point clickPoint)
{
	for (int i = static_cast<int>(HL_START)+1; i < static_cast<int>(HL_END); ++i)
	{
		m_HeadList[i]->getEquipmentIcon()->doubleClickCheck(clickPoint);
	}
	for (int i = static_cast<int>(EL_START)+1; i < static_cast<int>(EL_END); ++i)
	{
		m_EngineList[i]->getEquipmentIcon()->doubleClickCheck(clickPoint);
	}
	for (int i = static_cast<int>(AL_START)+1; i < static_cast<int>(AL_END); ++i)
	{
		m_ArmorList[i]->getEquipmentIcon()->doubleClickCheck(clickPoint);
	}
	for (int i = static_cast<int>(ML_START)+1; i < static_cast<int>(ML_END); ++i)
	{
		m_MeleeList[i]->getEquipmentIcon()->doubleClickCheck(clickPoint);
	}
	for (int i = static_cast<int>(RL_START)+1; i < static_cast<int>(RL_END); ++i)
	{
		m_RangeList[i]->getEquipmentIcon()->doubleClickCheck(clickPoint);
	}
	for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
	{
		m_SteamList[i]->getEquipmentIcon()->doubleClickCheck(clickPoint);
	}
	for (int i = static_cast<int>(LL_START)+1; i < static_cast<int>(LL_END); ++i)
	{
		m_LegList[i]->getEquipmentIcon()->doubleClickCheck(clickPoint);
	}
}

void AssemblyLineLayer::setConfirmSet(cocos2d::Point mousePoint)
{
	if (m_HeadRect.containsPoint(mousePoint))
	{
		auto headTemp = m_ConfirmSet.m_Head;
		for (int i = static_cast<int>(HL_START)+1; i < static_cast<int>(HL_END); ++i)
		{
			if (m_HeadList[i]->getEquipmentIcon()->getSelected())
			{
				auto newEquipment = static_cast<HeadList>(m_HeadList[i]->getEquipmentInfo().m_Type);
				if (m_ConfirmSet.m_Head == HL_START)
				{
					m_ConfirmSet.m_Head = newEquipment;
					break;
				}
				else if (headTemp != newEquipment)
				{
					m_ConfirmSet.m_Head = newEquipment;
					m_HeadList[i]->setEquipmentIcon(ICON_SELECTED);
				}
				else if (headTemp == newEquipment)
				{
					m_HeadList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
			}
		}
	}
	else if (m_EngineRect.containsPoint(mousePoint))
	{
		auto engineTemp = m_ConfirmSet.m_Engine;
		for (int i = static_cast<int>(EL_START)+1; i < static_cast<int>(EL_END); ++i)
		{
			if (m_EngineList[i]->getEquipmentIcon()->getSelected())
			{
				auto newEquipment = static_cast<EngineList>(m_EngineList[i]->getEquipmentInfo().m_Type);
				if (m_ConfirmSet.m_Engine == EL_START)
				{
					m_ConfirmSet.m_Engine = newEquipment;
					break;
				}
				else if (engineTemp != newEquipment)
				{
					m_ConfirmSet.m_Engine = newEquipment;
					m_EngineList[i]->setEquipmentIcon(ICON_SELECTED);
				}
				else if (engineTemp == newEquipment)
				{
					m_EngineList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
			}
		}
	}
	else if (m_ArmorRect.containsPoint(mousePoint))
	{
		auto armorTemp = m_ConfirmSet.m_Armor;
		for (int i = static_cast<int>(AL_START)+1; i < static_cast<int>(AL_END); ++i)
		{
			if (m_ArmorList[i]->getEquipmentIcon()->getSelected())
			{
				auto newEquipment = static_cast<ArmorList>(m_ArmorList[i]->getEquipmentInfo().m_Type);
				if (m_ConfirmSet.m_Armor == AL_START)
				{
					m_ConfirmSet.m_Armor = newEquipment;
					break;
				}
				else if (armorTemp != newEquipment)
				{
					m_ConfirmSet.m_Armor = newEquipment;
					m_ArmorList[i]->setEquipmentIcon(ICON_SELECTED);
				}
				else if (armorTemp == newEquipment)
				{
					m_EngineList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
			}
		}
	}
	else if (m_MeleeRect.containsPoint(mousePoint))
	{
		auto meleeTemp = m_ConfirmSet.m_Melee;
		for (int i = static_cast<int>(ML_START)+1; i < static_cast<int>(ML_END); ++i)
		{
			if (m_MeleeList[i]->getEquipmentIcon()->getSelected())
			{
				auto newEquipment = static_cast<MeleeList>(m_MeleeList[i]->getEquipmentInfo().m_Type);
				if (m_ConfirmSet.m_Melee == ML_START)
				{
					m_ConfirmSet.m_Melee = newEquipment;
					break;
				}
				else if (meleeTemp != newEquipment)
				{
					m_ConfirmSet.m_Melee = newEquipment;
					m_MeleeList[i]->setEquipmentIcon(ICON_SELECTED);
				}
				else if (meleeTemp == newEquipment)
				{
					m_MeleeList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
			}
		}
	}
	else if (m_RangeRect.containsPoint(mousePoint))
	{
		auto rangeTemp = m_ConfirmSet.m_Range;
		for (int i = static_cast<int>(RL_START)+1; i < static_cast<int>(RL_END); ++i)
		{
			if (m_RangeList[i]->getEquipmentIcon()->getSelected())
			{
				auto newEquipment = static_cast<RangeList>(m_RangeList[i]->getEquipmentInfo().m_Type);
				if (m_ConfirmSet.m_Range == RL_START)
				{
					m_ConfirmSet.m_Range = newEquipment;
					break;
				}
				else if (rangeTemp != newEquipment)
				{
					m_ConfirmSet.m_Range = newEquipment;
					m_RangeList[i]->setEquipmentIcon(ICON_SELECTED);
				}
				else if (rangeTemp == newEquipment)
				{
					m_RangeList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
			}
		}
	}
	else if (m_SteamRect.containsPoint(mousePoint))
	{
		auto steamTemp = m_ConfirmSet.m_Steam;
		for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
		{
			if (m_SteamList[i]->getEquipmentIcon()->getSelected())
			{
				auto newEquipment = static_cast<SteamContainerList>(m_SteamList[i]->getEquipmentInfo().m_Type);
				if (m_ConfirmSet.m_Steam == SCL_START)
				{
					m_ConfirmSet.m_Steam = newEquipment;
					break;
				}
				else if (steamTemp != newEquipment)
				{
					m_ConfirmSet.m_Steam = newEquipment;
					m_SteamList[i]->setEquipmentIcon(ICON_SELECTED);
				}
				else if (steamTemp == newEquipment)
				{
					m_SteamList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
			}
		}
	}
	else if (m_LegRect.containsPoint(mousePoint))
	{
		auto legTemp = m_ConfirmSet.m_Leg;
		for (int i = static_cast<int>(LL_START)+1; i < static_cast<int>(LL_END); ++i)
		{
			if (m_LegList[i]->getEquipmentIcon()->getSelected())
			{
				auto newEquipment = static_cast<LegList>(m_LegList[i]->getEquipmentInfo().m_Type);
				if (m_ConfirmSet.m_Leg == LL_START)
				{
					m_ConfirmSet.m_Leg = newEquipment;
					break;
				}
				else if (legTemp != newEquipment)
				{
					m_ConfirmSet.m_Leg = newEquipment;
					m_LegList[i]->setEquipmentIcon(ICON_SELECTED);
				}
				else if (legTemp == newEquipment)
				{
					m_LegList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
			}
		}
	}
}

void AssemblyLineLayer::containerScroll(bool moveLeft, cocos2d::Point mousePoint)
{
	if (m_HeadRect.containsPoint(mousePoint))
	{
		moveContainer(moveLeft, m_HeadContainer, m_HeadRect);
	}
	else if (m_EngineRect.containsPoint(mousePoint))
	{
		moveContainer(moveLeft, m_EngineContainer, m_EngineRect);
	}
	else if (m_ArmorRect.containsPoint(mousePoint))
	{
		moveContainer(moveLeft, m_ArmorContainer, m_ArmorRect);
	}
	else if (m_MeleeRect.containsPoint(mousePoint))
	{
		moveContainer(moveLeft, m_MeleeContainer, m_MeleeRect);
	}
	else if (m_RangeRect.containsPoint(mousePoint))
	{
		moveContainer(moveLeft, m_RangeContainer, m_RangeRect);
	}
	else if (m_SteamRect.containsPoint(mousePoint))
	{
		moveContainer(moveLeft, m_SteamContainer, m_SteamRect);
	}
	else if (m_LegRect.containsPoint(mousePoint))
	{
		moveContainer(moveLeft, m_LegContainer, m_LegRect);
	}
}
