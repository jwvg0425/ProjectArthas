#include "pch.h"
#include "EquipmentRange.h"
#include "IconLayer.h"

bool EquipmentRange::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}
	m_Icon = IconLayer::create();
	this->addChild(m_Icon);
	return true;
}

void EquipmentRange::update(float dTime)
{
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
}

void EquipmentRange::enter()
{
}

void EquipmentRange::exit()
{
}

bool EquipmentRange::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentRange::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentRange::setEquipment(EquipmentType equipmentType, RangeList rangeType, int level, int kWatt, int upgradePrice, 
								  bool isLock, float attackDamage, float attackSpeed, float attackRange,
								  SpriteType front, SpriteType outLine, SpriteType icon)
{
	m_RangeInfo.m_EquipmentType = equipmentType;
	m_RangeInfo.m_Type = rangeType;
	m_RangeInfo.m_Level = level;
	m_RangeInfo.m_KWatt = kWatt;
	m_RangeInfo.m_UpgradePrice = upgradePrice;
	m_RangeInfo.m_IsLock = isLock;
	m_RangeInfo.m_AttackDamage = attackDamage;
	m_RangeInfo.m_AttackSpeed = attackSpeed;
	m_RangeInfo.m_AttackRange = attackRange;
	m_RangeInfo.m_Front = front;
	m_RangeInfo.m_OutLine = outLine;
	m_RangeInfo.m_Icon = icon;

	if (m_RangeInfo.m_IsLock)
	{
		m_Icon->changeIconState(ICON_LOCKED);
	}
	else
	{
		m_Icon->changeIconState(ICON_DEFAULT);
	}
}

void EquipmentRange::setEquipment(RangeInfo rangeInfo)
{
	setEquipment(rangeInfo.m_EquipmentType, static_cast<RangeList>(rangeInfo.m_Type),
				 rangeInfo.m_Level, rangeInfo.m_KWatt,
				 rangeInfo.m_UpgradePrice, rangeInfo.m_IsLock,
				 rangeInfo.m_AttackDamage, rangeInfo.m_AttackSpeed,
				 rangeInfo.m_AttackRange, rangeInfo.m_Front,
				 rangeInfo.m_OutLine, rangeInfo.m_Icon);
}

RangeInfo EquipmentRange::getEquipmentInfo()
{
	return m_RangeInfo;
}


RangeInfo* RangeInfo::clone()
{
	return new RangeInfo(*this);
}

RangeInfo::RangeInfo()
{

}

RangeInfo::RangeInfo(const RangeInfo& other) : EquipmentInfo(other)
{
	m_AttackDamage = m_AttackDamage;
	m_AttackSpeed = m_AttackSpeed;
	m_AttackRange = m_AttackRange;
}
