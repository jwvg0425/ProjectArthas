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
	OVERRIDE void				initEquipment();



	struct HeadInfo : public EquipmentInfo
	{
		//HeadListType m_HeadType = HEADTYPE_NONE;
		float m_SkillCoolTime = 0.f;
		float m_MainMemory = 0.f;
	};

private:
	HeadInfo m_HeadInfo;

};
