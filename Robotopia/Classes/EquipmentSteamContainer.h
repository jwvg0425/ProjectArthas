/************************************************************************/
/*
CLASS			: EquipmentSteamContainer
Author			: 김성연
역할				: SteamContainer 장비 클래스
최종 수정일자		: 2014-11-28
최종 수정자		:
최종 수정사유		:
Comment			:
/************************************************************************/

#pragma once
#include "Util.h"
#include "EquipmentAbstract.h"

struct SteamContainerInfo : public EquipmentInfo
{
	virtual SteamContainerInfo* clone();
	SteamContainerInfo();
	SteamContainerInfo(const SteamContainerInfo& other);

	float			   m_MaxSteam = 0.f;
	float			   m_AbsorbEffectiveness = 0.f;
};

class EquipmentSteamContainer : public EquipmentAbstract
{
public:
	

	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);
	
	CREATE_FUNC(EquipmentSteamContainer);
	
	void						setEquipment(SteamContainerInfo steamContainerInfo);
	void						setEquipment(EquipmentType equipmentType, SteamContainerList steamContainerType,
											 int level, int kWatt, int upgradePrice, bool isLock, 
											 float maxSteam, float AbsorbEffectiveness,
											 SpriteType front = ST_START, SpriteType outLine = ST_START, 
											 SpriteType icon = ST_START);


	SteamContainerInfo			getEquipmentInfo();

private:
	SteamContainerInfo m_SteamContainerInfo;

};
