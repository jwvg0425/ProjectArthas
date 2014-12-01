/************************************************************************/
/*
CLASS			: EquipmentRange
Author			: 김성연
역할				: Range 장비 클래스
최종 수정일자		: 2014-11-28
최종 수정자		:
최종 수정사유		:
Comment			:
/************************************************************************/

#pragma once
#include "Util.h"
#include "EquipmentAbstract.h"

class EquipmentRange : public EquipmentAbstract
{

public:
	struct RangeInfo : public EquipmentInfo
	{
		RangeList m_RangeType = RL_START;
		float	  m_AttackDamage = 0.f;
		float	  m_AttackSpeed = 0.f;
		float	  m_AttackRange = 0.f;
	};

	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);
	
	CREATE_FUNC(EquipmentRange);

	void						setEquipment(RangeInfo rangeInfo);
	void						setEquipment(EquipmentType equipmentType, RangeList rangeType, int level, int kWatt,
											 int upgradePrice, bool isLock, float attackDamage, float attackSpeed,
											 float attackRange, SpriteType front = ST_START, 
											 SpriteType outLine = ST_START, SpriteType icon = ST_START);

	RangeInfo					getEquipmentInfo();

private:
	RangeInfo m_RangeInfo;

};
