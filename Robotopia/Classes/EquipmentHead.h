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

struct HeadInfo : public EquipmentInfo
{
	virtual HeadInfo* clone();
	HeadInfo();
	HeadInfo(const HeadInfo& other);

	float		m_SkillCoolTimeDown = 0.f;
	float		m_MainMemory = 0.f;
};

class EquipmentHead : public EquipmentAbstract
{
public:

	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);

	CREATE_FUNC(EquipmentHead);

	void						setEquipment(HeadInfo headInfo);
	void						setEquipment(EquipmentType equipmentType, HeadList headType, int level, int kWatt,
											 int upgradePrice, bool isLock, float skillCoolTimeDown, float mainMemory,
											 SpriteType front = ST_START, SpriteType outLine = ST_START, 
											 SpriteType icon = ST_START);
	
	HeadInfo					getEquipmentInfo();

private:
	HeadInfo					m_HeadInfo;

};
