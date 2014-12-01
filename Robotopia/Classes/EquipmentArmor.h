/************************************************************************/
/*
CLASS			: EquipmentArmor
Author			: 김성연
역할				: Engine 장비 클래스
최종 수정일자		: 2014-11-28
최종 수정자		:
최종 수정사유		:
Comment			:
/************************************************************************/

#pragma once
#include "Util.h"
#include "EquipmentAbstract.h"

struct ArmorInfo : public EquipmentInfo
{
	float m_DefensivePower = 0.f;
	float m_AntiSlow = 0.f;
};

class EquipmentArmor : public EquipmentAbstract
{
public:
	
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);

	CREATE_FUNC(EquipmentArmor);

	void						setEquipment(ArmorInfo armorInfo);
	void						setEquipment(EquipmentType equipmentType, ArmorList armorType, int level, int kWatt,
											 int upgradePrice, bool isLock, float defensivePower, float antiSlow,
											 SpriteType front = ST_START, SpriteType outLine = ST_START, 
											 SpriteType icon = ST_START);


	ArmorInfo					getEquipmentInfo();

private:
	ArmorInfo m_ArmorInfo;

};
