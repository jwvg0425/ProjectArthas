/************************************************************************/
/*
CLASS			: EquipmentAbstract
Author			: 김성연
역할				: 모든 장비형 아이템의 추상 클래스 
최종 수정일자		: 2014-11-27
최종 수정자		:
최종 수정사유		:
Comment			: 
/************************************************************************/

#pragma once
#include "Util.h"
#include "ItemAbstract.h"

class IconLayer;

class EquipmentAbstract : public ItemAbstract
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);
	void						setEquipmentSprite(cocos2d::Sprite* front, cocos2d::Sprite* frontOutLine,
												   cocos2d::Sprite* inGameSprite);
	void						setEquipmentIcon(IconType iconType, cocos2d::Sprite* iconSprite, cocos2d::Point parentAnchorPoint, cocos2d::Point iconPosition);
	void						setEquipmentDescription(std::string description);

	struct EquipmentInfo
	{
		EquipmentType m_EquipmentType = EMT_START;
		int  m_Level = 0;
		int  m_KWatt = 0;
		bool m_IsLock = false;
		int  m_UpgradePrice = 0;
	};


protected:

	cocos2d::Sprite*	m_Front = nullptr;
	cocos2d::Sprite*	m_FrontOutLine = nullptr;
	cocos2d::Sprite*	m_InGameSprite = nullptr;
	IconLayer*			m_Icon = nullptr;

	std::string			m_Name = "";
	std::string			m_Description = "";

};
