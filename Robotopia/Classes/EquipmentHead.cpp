#include "pch.h"
#include "EquipmentHead.h"
#include "IconLayer.h"

bool EquipmentHead::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}
	m_Icon = IconLayer::create();
	this->addChild(m_Icon);
	return true;
}

void EquipmentHead::update(float dTime)
{
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
}

void EquipmentHead::enter()
{
}

void EquipmentHead::exit()
{
}

bool EquipmentHead::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentHead::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}


void EquipmentHead::setEquipment(EquipmentType equipmentType, HeadList headType, 
								 int level, int kWatt, int upgradePrice, bool isLock,
								 float skillCoolTimeDown, float mainMemory, 
								 SpriteType front, SpriteType outLine, SpriteType icon)
{
	m_HeadInfo.m_EquipmentType = equipmentType;
	m_HeadInfo.m_Type = headType;
	m_HeadInfo.m_Level = level;
	m_HeadInfo.m_KWatt = kWatt;
	m_HeadInfo.m_UpgradePrice = upgradePrice;
	m_HeadInfo.m_IsLock = isLock;
	m_HeadInfo.m_SkillCoolTimeDown = skillCoolTimeDown;
	m_HeadInfo.m_MainMemory = mainMemory;
	m_HeadInfo.m_FrontSprite = front;
	m_HeadInfo.m_FrontOutline = outLine;
	m_HeadInfo.m_IconSprite = icon;

	if (m_HeadInfo.m_IsLock)
	{
		m_Icon->changeIconState(ICON_LOCKED);
	}
	else
	{
		m_Icon->changeIconState(ICON_DEFAULT);
	}
}

void EquipmentHead::setEquipment(HeadInfo headInfo)
{
	setEquipment(headInfo.m_EquipmentType, static_cast<HeadList>(headInfo.m_Type),
				 headInfo.m_Level, headInfo.m_KWatt,
				 headInfo.m_UpgradePrice, headInfo.m_IsLock,
				 headInfo.m_SkillCoolTimeDown, headInfo.m_MainMemory,
				 headInfo.m_FrontSprite, headInfo.m_FrontOutline, headInfo.m_IconSprite);
	setEquipmentSprite(headInfo.m_FrontSprite, headInfo.m_FrontOutline, headInfo.m_IconSprite);
}

HeadInfo EquipmentHead::getEquipmentInfo()
{
	return m_HeadInfo;
}


HeadInfo* HeadInfo::clone()
{
	return new HeadInfo(*this);
}

HeadInfo::HeadInfo()
{

}

HeadInfo::HeadInfo(const HeadInfo& other) : EquipmentInfo(other)
{
	m_MainMemory = other.m_MainMemory;
	m_SkillCoolTimeDown = other.m_SkillCoolTimeDown;
}
