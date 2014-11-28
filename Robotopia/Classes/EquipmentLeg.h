/************************************************************************/
/*
CLASS			: EquipmentLeg
Author			: 김성연
역할				: Leg 장비 클래스
최종 수정일자		: 2014-11-28
최종 수정자		:
최종 수정사유		:
Comment			:
/************************************************************************/

#pragma once
#include "Util.h"
#include "EquipmentAbstract.h"

class EquipmentLeg : public EquipmentAbstract
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);
	OVERRIDE void				setEquipment(EquipmentType equipmentType, LegList legType, int level, int kWatt,
											 int upgradePrice, bool isLock, float moveSpeed, float jumpPower);


	struct LegInfo : public EquipmentInfo
	{
		LegList m_LegType = LL_START;
		float m_MoveSpeed = 0.f;
		float m_jumpPower = 0.f;
	};

	CREATE_FUNC(EquipmentLeg);

private:
	LegInfo m_LegInfo;

};
