#include "pch.h"
#include "AssemblyLineLayer.h"
#include "DataManager.h"
#include "InputManager.h"
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
#include "SoundManager.h"

bool AssemblyLineLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	initEquipmentContainer();
	displayEquipments();
	return true;
}

void AssemblyLineLayer::update(float dTime)
{
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

	m_HeadContainer->setPosition(cocos2d::Point(140, 550));
	m_EngineContainer->setPosition(cocos2d::Point(140, 465));
	m_ArmorContainer->setPosition(cocos2d::Point(140, 380));
	m_MeleeContainer->setPosition(cocos2d::Point(140, 295));
	m_RangeContainer->setPosition(cocos2d::Point(140, 210));
	m_SteamContainer->setPosition(cocos2d::Point(140, 125));
	m_LegContainer->setPosition(cocos2d::Point(140, 40));

	this->addChild(m_HeadContainer);
	this->addChild(m_EngineContainer);
	this->addChild(m_ArmorContainer);
	this->addChild(m_MeleeContainer);
	this->addChild(m_RangeContainer);
	this->addChild(m_SteamContainer);
	this->addChild(m_LegContainer);

	m_HeadRect.setRect(140 * RESOLUTION, 550 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_EngineRect.setRect(140 * RESOLUTION, 465 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_ArmorRect.setRect(140 * RESOLUTION, 380 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_MeleeRect.setRect(140 * RESOLUTION, 295 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_RangeRect.setRect(140 * RESOLUTION, 210 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_SteamRect.setRect(140 * RESOLUTION, 125 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
	m_LegRect.setRect(140 * RESOLUTION, 40 * RESOLUTION, 390 * RESOLUTION, 70 * RESOLUTION);
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
		m_HeadList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_HeadList[i]->getEquipmentIcon()->createIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
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
		m_EngineList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_EngineList[i]->getEquipmentIcon()->createIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
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
		m_ArmorList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_ArmorList[i]->getEquipmentIcon()->createIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
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
		m_MeleeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_MeleeList[i]->getEquipmentIcon()->createIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
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
		m_RangeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_RangeList[i]->getEquipmentIcon()->createIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
		m_RangeContainer->addChild(m_RangeList[i]);
		count++;
	}
	m_RangeContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
	count = 0;
	for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
	{
		auto info = static_cast<const SteamContainerInfo*>(GET_DATA_MANAGER()->getEquipmentInfo(EMT_STEAMCONTAINER, i));
		EquipmentSteamContainer* steam = EquipmentSteamContainer::create();
		m_SteamList.push_back(steam);
		m_SteamList[i]->setEquipment(*info);
		m_SteamList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_SteamList[i]->getEquipmentIcon()->createIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
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
		m_LegList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_LegList[i]->getEquipmentIcon()->createIconLabel(cocos2d::Point(m_HeadContainer->getBoundingBox().getMinX() * RESOLUTION, m_HeadContainer->getBoundingBox().getMinY() * RESOLUTION), (*info).m_IsLock);
		m_LegContainer->addChild(m_LegList[i]);
		count++;
	}
	m_LegContainer->setContentSize(cocos2d::Size(count * 70 + 10, 70));
}

void AssemblyLineLayer::updateEquipments(float dTime)
{
	for (int i = static_cast<int>(HL_START)+1; i < static_cast<int>(HL_END); ++i)
	{
		m_HeadList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_HeadList[i]->update(dTime);
	}
	for (int i = static_cast<int>(EL_START)+1; i < static_cast<int>(EL_END); ++i)
	{
		m_EngineList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_EngineList[i]->update(dTime);
	}
	for (int i = static_cast<int>(AL_START)+1; i < static_cast<int>(AL_END); ++i)
	{
		m_ArmorList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_ArmorList[i]->update(dTime);
	}
	for (int i = static_cast<int>(ML_START)+1; i < static_cast<int>(ML_END); ++i)
	{
		m_MeleeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_MeleeList[i]->update(dTime);
	}
	for (int i = static_cast<int>(RL_START)+1; i < static_cast<int>(RL_END); ++i)
	{
		m_RangeList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_RangeList[i]->update(dTime);
	}
	for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
	{
		m_SteamList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_SteamList[i]->update(dTime);
	}
	for (int i = static_cast<int>(LL_START)+1; i < static_cast<int>(LL_END); ++i)
	{
		m_LegList[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(40 + 70 * i, 35));
		m_LegList[i]->update(dTime);
	}
}

void AssemblyLineLayer::updateClickItem(cocos2d::Point clickPoint)
{
	for (int i = static_cast<int>(HL_START)+1; i < static_cast<int>(HL_END); ++i)
	{
		m_HeadList[i]->getEquipmentIcon()->clickCheck(clickPoint);
	}
	for (int i = static_cast<int>(EL_START)+1; i < static_cast<int>(EL_END); ++i)
	{
		m_EngineList[i]->getEquipmentIcon()->clickCheck(clickPoint);
	}
	for (int i = static_cast<int>(AL_START)+1; i < static_cast<int>(AL_END); ++i)
	{
		m_ArmorList[i]->getEquipmentIcon()->clickCheck(clickPoint);
	}
	for (int i = static_cast<int>(ML_START)+1; i < static_cast<int>(ML_END); ++i)
	{
		m_MeleeList[i]->getEquipmentIcon()->clickCheck(clickPoint);
	}
	for (int i = static_cast<int>(RL_START)+1; i < static_cast<int>(RL_END); ++i)
	{
		m_RangeList[i]->getEquipmentIcon()->clickCheck(clickPoint);
	}
	for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
	{
		m_SteamList[i]->getEquipmentIcon()->clickCheck(clickPoint);
	}
	for (int i = static_cast<int>(LL_START)+1; i < static_cast<int>(LL_END); ++i)
	{
		m_LegList[i]->getEquipmentIcon()->clickCheck(clickPoint);
	}
}

void AssemblyLineLayer::updateDoubleClickItem(cocos2d::Point clickPoint)
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
		HeadList headPrev = m_ConfirmSet.m_Head;
		HeadList headTemp = HL_START;
		HeadList head = HL_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(HL_START)+1; i < static_cast<int>(HL_END); ++i)
		{
			iconState = m_HeadList[i]->getEquipmentIconState();
			if (iconState == ICON_SELECTED)
			{
				head = static_cast<HeadList>(m_HeadList[i]->getEquipmentInfo().m_Type);
				if (head == headPrev)
				{
					m_HeadList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
				else if (head != headPrev)
				{
					headTemp = head;
				}
			}
		}
		m_ConfirmSet.m_Head = headTemp;
	}
	else if (m_EngineRect.containsPoint(mousePoint))
	{
		EngineList enginePrev = m_ConfirmSet.m_Engine;
		EngineList engineTemp = EL_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(EL_START)+1; i < static_cast<int>(EL_END); ++i)
		{
			iconState = m_EngineList[i]->getEquipmentIconState();
			if (iconState == ICON_SELECTED)
			{
				EngineList engineSelected = static_cast<EngineList>(m_EngineList[i]->getEquipmentInfo().m_Type);
				if (engineSelected == enginePrev)
				{
					m_EngineList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
				else if (engineSelected != enginePrev)
				{
					engineTemp = engineSelected;
				}
			}
		}
		m_ConfirmSet.m_Engine = engineTemp;
	}
	else if (m_ArmorRect.containsPoint(mousePoint))
	{
		ArmorList armorPrev = m_ConfirmSet.m_Armor;
		ArmorList armorTemp = AL_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(AL_START)+1; i < static_cast<int>(AL_END); ++i)
		{
			iconState = m_ArmorList[i]->getEquipmentIconState();
			if (iconState == ICON_SELECTED)
			{
				ArmorList armorSelected = static_cast<ArmorList>(m_ArmorList[i]->getEquipmentInfo().m_Type);
				if (armorSelected == armorPrev)
				{
					m_ArmorList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
				else if (armorSelected != armorPrev)
				{
					armorTemp = armorSelected;
				}
			}
		}
		m_ConfirmSet.m_Armor = armorTemp;
	}
	else if (m_MeleeRect.containsPoint(mousePoint))
	{
		MeleeList meleePrev = m_ConfirmSet.m_Melee;
		MeleeList meleeTemp = ML_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(ML_START)+1; i < static_cast<int>(ML_END); ++i)
		{
			iconState = m_MeleeList[i]->getEquipmentIconState();
			if (iconState == ICON_SELECTED)
			{
				MeleeList meleeSelected = static_cast<MeleeList>(m_MeleeList[i]->getEquipmentInfo().m_Type);
				if (meleeSelected == meleePrev)
				{
					m_MeleeList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
				else if (meleeSelected != meleePrev)
				{
					meleeTemp = meleeSelected;
				}
			}
		}
		m_ConfirmSet.m_Melee = meleeTemp;
	}
	else if (m_RangeRect.containsPoint(mousePoint))
	{
		RangeList rangePrev = m_ConfirmSet.m_Range;
		RangeList rangeTemp = RL_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(RL_START)+1; i < static_cast<int>(RL_END); ++i)
		{
			iconState = m_RangeList[i]->getEquipmentIconState();
			if (iconState == ICON_SELECTED)
			{
				RangeList rangeSelected = static_cast<RangeList>(m_RangeList[i]->getEquipmentInfo().m_Type);
				if (rangeSelected == rangePrev)
				{
					m_RangeList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
				else if (rangeSelected != rangePrev)
				{
					rangeTemp = rangeSelected;
				}
			}
		}
		m_ConfirmSet.m_Range = rangeTemp;
	}
	else if (m_SteamRect.containsPoint(mousePoint))
	{
		SteamContainerList steamPrev = m_ConfirmSet.m_Steam;
		SteamContainerList steamTemp = SCL_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
		{
			iconState = m_SteamList[i]->getEquipmentIconState();
			if (iconState == ICON_SELECTED)
			{
				SteamContainerList steamSelected = static_cast<SteamContainerList>(m_SteamList[i]->getEquipmentInfo().m_Type);
				if (steamSelected == steamPrev)
				{
					m_SteamList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
				else if (steamSelected != steamPrev)
				{
					steamTemp = steamSelected;
				}
			}
		}
		m_ConfirmSet.m_Steam = steamTemp;
	}
	else if (m_LegRect.containsPoint(mousePoint))
	{
		LegList legPrev = m_ConfirmSet.m_Leg;
		LegList legTemp = LL_START;
		IconState iconState = ICON_DEFAULT;
		for (int i = static_cast<int>(LL_START)+1; i < static_cast<int>(LL_END); ++i)
		{
			iconState = m_LegList[i]->getEquipmentIconState();
			if (iconState == ICON_SELECTED)
			{
				LegList legSelected = static_cast<LegList>(m_LegList[i]->getEquipmentInfo().m_Type);
				if (legSelected == legPrev)
				{
					m_LegList[i]->setEquipmentIcon(ICON_DEFAULT);
				}
				else if (legSelected != legPrev)
				{
					legTemp = legSelected;
				}
			}
		}
		m_ConfirmSet.m_Leg = legTemp;
	}
}

void AssemblyLineLayer::setClickedItem(cocos2d::Point mousePoint)
{
	ClickedItem clickedPrev;
	clickedPrev.m_Type = m_ClickedItem.m_Type;
	clickedPrev.m_ListItem = m_ClickedItem.m_ListItem;
	cocos2d::log("Before - Equip: %d  /  Item: %d", (int)clickedPrev.m_Type, (int)clickedPrev.m_ListItem);
	ClickedItem clickedTemp;
	clickedTemp.m_Type = EMT_START;
	clickedTemp.m_ListItem = -1;
	IconState iconState = ICON_DEFAULT;


	for (int i = static_cast<int>(HL_START)+1; i < static_cast<int>(HL_END); ++i)
	{
		iconState = m_HeadList[i]->getEquipmentIconState();
		if (iconState == ICON_CLICKED)
		{
			int headClicked = m_HeadList[i]->getEquipmentInfo().m_Type;
			if (clickedPrev.m_Type == EMT_HEAD && headClicked == clickedPrev.m_ListItem)
			{
				m_HeadList[i]->setEquipmentIcon(ICON_DEFAULT);
				cocos2d::log("Set1 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else if (clickedPrev.m_Type == EMT_HEAD && headClicked != clickedPrev.m_ListItem)
			{
				clickedTemp.m_Type = EMT_HEAD;
				clickedTemp.m_ListItem = headClicked;
				cocos2d::log("Set2 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else
			{
				clickedTemp.m_Type = EMT_HEAD;
				clickedTemp.m_ListItem = headClicked;
				cocos2d::log("Set3 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
		}
	}
	for (int i = static_cast<int>(EL_START)+1; i < static_cast<int>(EL_END); ++i)
	{
		iconState = m_EngineList[i]->getEquipmentIconState();
		if (iconState == ICON_CLICKED)
		{
			int engineClicked = m_EngineList[i]->getEquipmentInfo().m_Type;
			if (clickedPrev.m_Type == EMT_ENGINE && engineClicked == clickedPrev.m_ListItem)
			{
				m_EngineList[i]->setEquipmentIcon(ICON_DEFAULT);
				cocos2d::log("Set1 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else if (clickedPrev.m_Type == EMT_ENGINE && engineClicked != clickedPrev.m_ListItem)
			{
				clickedTemp.m_Type = EMT_ENGINE;
				clickedTemp.m_ListItem = engineClicked;
				cocos2d::log("Set2 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else
			{
				clickedTemp.m_Type = EMT_ENGINE;
				clickedTemp.m_ListItem = engineClicked;
				cocos2d::log("Set3 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
		}
	}
	for (int i = static_cast<int>(AL_START)+1; i < static_cast<int>(AL_END); ++i)
	{
		iconState = m_ArmorList[i]->getEquipmentIconState();
		if (iconState == ICON_CLICKED)
		{
			int armorClicked = m_ArmorList[i]->getEquipmentInfo().m_Type;
			if (clickedPrev.m_Type == EMT_ARMOR && armorClicked == clickedPrev.m_ListItem)
			{
				m_ArmorList[i]->setEquipmentIcon(ICON_DEFAULT);
				cocos2d::log("Set1 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else if (clickedPrev.m_Type == EMT_ARMOR && armorClicked != clickedPrev.m_ListItem)
			{
				clickedTemp.m_Type = EMT_ARMOR;
				clickedTemp.m_ListItem = armorClicked;
				cocos2d::log("Set2 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else
			{
				clickedTemp.m_Type = EMT_ARMOR;
				clickedTemp.m_ListItem = armorClicked;
				cocos2d::log("Set3 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
		}
	}
	for (int i = static_cast<int>(ML_START)+1; i < static_cast<int>(ML_END); ++i)
	{
		iconState = m_MeleeList[i]->getEquipmentIconState();
		if (iconState == ICON_CLICKED)
		{
			int meleeClicked = m_MeleeList[i]->getEquipmentInfo().m_Type;
			if (clickedPrev.m_Type == EMT_MELEE && meleeClicked == clickedPrev.m_ListItem)
			{
				m_MeleeList[i]->setEquipmentIcon(ICON_DEFAULT);
				cocos2d::log("Set1 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else if (clickedPrev.m_Type == EMT_MELEE && meleeClicked != clickedPrev.m_ListItem)
			{
				clickedTemp.m_Type = EMT_MELEE;
				clickedTemp.m_ListItem = meleeClicked;
				cocos2d::log("Set2 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else
			{
				clickedTemp.m_Type = EMT_MELEE;
				clickedTemp.m_ListItem = meleeClicked;
				cocos2d::log("Set3 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
		}
	}
	for (int i = static_cast<int>(RL_START)+1; i < static_cast<int>(RL_END); ++i)
	{
		iconState = m_RangeList[i]->getEquipmentIconState();
		if (iconState == ICON_CLICKED)
		{
			int rangeClicked = m_RangeList[i]->getEquipmentInfo().m_Type;
			if (clickedPrev.m_Type == EMT_RANGE && rangeClicked == clickedPrev.m_ListItem)
			{
				m_RangeList[i]->setEquipmentIcon(ICON_DEFAULT);
				cocos2d::log("Set1 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else if (clickedPrev.m_Type == EMT_RANGE && rangeClicked != clickedPrev.m_ListItem)
			{
				clickedTemp.m_Type = EMT_RANGE;
				clickedTemp.m_ListItem = rangeClicked;
				cocos2d::log("Set2 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else
			{
				clickedTemp.m_Type = EMT_RANGE;
				clickedTemp.m_ListItem = rangeClicked;
				cocos2d::log("Set3 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
		}
	}
	for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
	{
		iconState = m_SteamList[i]->getEquipmentIconState();
		if (iconState == ICON_CLICKED)
		{
			int steamClicked = m_SteamList[i]->getEquipmentInfo().m_Type;
			if (clickedPrev.m_Type == EMT_STEAMCONTAINER && steamClicked == clickedPrev.m_ListItem)
			{
				m_SteamList[i]->setEquipmentIcon(ICON_DEFAULT);
				cocos2d::log("Set1 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else if (clickedPrev.m_Type == EMT_STEAMCONTAINER && steamClicked != clickedPrev.m_ListItem)
			{
				clickedTemp.m_Type = EMT_STEAMCONTAINER;
				clickedTemp.m_ListItem = steamClicked;
				cocos2d::log("Set2 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else
			{
				clickedTemp.m_Type = EMT_STEAMCONTAINER;
				clickedTemp.m_ListItem = steamClicked;
				cocos2d::log("Set3 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
		}
	}
	for (int i = static_cast<int>(LL_START)+1; i < static_cast<int>(LL_END); ++i)
	{
		iconState = m_LegList[i]->getEquipmentIconState();
		if (iconState == ICON_CLICKED)
		{
			int legClicked = m_LegList[i]->getEquipmentInfo().m_Type;
			if (clickedPrev.m_Type == EMT_LEG && legClicked == clickedPrev.m_ListItem)
			{
				m_LegList[i]->setEquipmentIcon(ICON_DEFAULT);
				cocos2d::log("Set1 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else if (clickedPrev.m_Type == EMT_LEG && legClicked != clickedPrev.m_ListItem)
			{
				clickedTemp.m_Type = EMT_LEG;
				clickedTemp.m_ListItem = legClicked;
				cocos2d::log("Set2 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
			else
			{
				clickedTemp.m_Type = EMT_LEG;
				clickedTemp.m_ListItem = legClicked;
				cocos2d::log("Set3 - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
			}
		}
	}
	m_ClickedItem.m_Type = clickedTemp.m_Type;
	m_ClickedItem.m_ListItem = clickedTemp.m_ListItem;
	cocos2d::log("After - Equip: %d  /  Item: %d", (int)clickedTemp.m_Type, (int)clickedTemp.m_ListItem);
}

void AssemblyLineLayer::containerScroll(float scrollValue, cocos2d::Point mousePoint)
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

		if (m_HeadRect.containsPoint(mousePoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_HeadContainer->getPosition()).x, m_HeadContainer, m_HeadRect);
		}
		else if (m_EngineRect.containsPoint(mousePoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_EngineContainer->getPosition()).x, m_EngineContainer, m_EngineRect);
		}
		else if (m_ArmorRect.containsPoint(mousePoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_ArmorContainer->getPosition()).x, m_ArmorContainer, m_ArmorRect);
		}
		else if (m_MeleeRect.containsPoint(mousePoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_MeleeContainer->getPosition()).x, m_MeleeContainer, m_MeleeRect);
		}
		else if (m_RangeRect.containsPoint(mousePoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_RangeContainer->getPosition()).x, m_RangeContainer, m_RangeRect);
		}
		else if (m_SteamRect.containsPoint(mousePoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_SteamContainer->getPosition()).x, m_SteamContainer, m_SteamRect);
		}
		else if (m_LegRect.containsPoint(mousePoint))
		{
			moveContainer(moveLeft, convertToWorldSpace(m_LegContainer->getPosition()).x, m_LegContainer, m_LegRect);
		}
	}
}

void AssemblyLineLayer::hideLabelLayer()
{
	for (int i = static_cast<int>(HL_START)+1; i < static_cast<int>(HL_END); ++i)
	{
		m_HeadList[i]->getEquipmentIcon()->hideLabel();
	}
	for (int i = static_cast<int>(EL_START)+1; i < static_cast<int>(EL_END); ++i)
	{
		m_EngineList[i]->getEquipmentIcon()->hideLabel();
	}
	for (int i = static_cast<int>(AL_START)+1; i < static_cast<int>(AL_END); ++i)
	{
		m_ArmorList[i]->getEquipmentIcon()->hideLabel();
	}
	for (int i = static_cast<int>(ML_START)+1; i < static_cast<int>(ML_END); ++i)
	{
		m_MeleeList[i]->getEquipmentIcon()->hideLabel();
	}
	for (int i = static_cast<int>(RL_START)+1; i < static_cast<int>(RL_END); ++i)
	{
		m_RangeList[i]->getEquipmentIcon()->hideLabel();
	}
	for (int i = static_cast<int>(SCL_START)+1; i < static_cast<int>(SCL_END); ++i)
	{
		m_SteamList[i]->getEquipmentIcon()->hideLabel();
	}
	for (int i = static_cast<int>(LL_START)+1; i < static_cast<int>(LL_END); ++i)
	{
		m_LegList[i]->getEquipmentIcon()->hideLabel();
	}
}

ConfirmSet AssemblyLineLayer::getConfirmSet()
{
	return m_ConfirmSet;
}

ClickedItem AssemblyLineLayer::getClickedItem()
{
	return m_ClickedItem;
}

