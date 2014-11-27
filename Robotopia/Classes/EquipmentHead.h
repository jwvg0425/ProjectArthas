/************************************************************************/
/*
CLASS			: EquipmentHead
Author			: 김성연
역할				: head 장비 클래스 
최종 수정일자		: 2014-11-27
최종 수정자		:
최종 수정사유		:
Comment			:
/************************************************************************/

#pragma once
#include "Util.h"
#include "EquipmentAbstract.h"

class EquipmentHead : public EquipmentAbstract
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);
	OVERRIDE void				setEquipment(EquipmentType equipmentType, HeadType headType, int level, int kWatt,
											 int upgradePrice, bool isLock, float skillCoolTimeDown, float mainMemory);


	struct HeadInfo : public EquipmentInfo
	{
		HeadType m_HeadType = HL_START;
		float m_SkillCoolTimeDown = 0.f;
		float m_MainMemory = 0.f;
	};

private:
	HeadInfo m_HeadInfo;

};
