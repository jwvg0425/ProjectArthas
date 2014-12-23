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

struct EquipmentInfo
{
	EquipmentInfo();
	virtual EquipmentInfo* clone();
	EquipmentInfo(const EquipmentInfo& other); ///< 저번에도 이야기했을텐데.. 복사생성자 있으면 웬만하면 복사대입 연산자도 넣으라고.. 그걸 쓰지 않을 거라면 private에 선언만이라도 해놓던가.

	///# 위에서 clone()함수가 다형적임에도.. 가상 소멸자는 어디에?? 

	EquipmentType					m_EquipmentType = EMT_START;
	int								m_Type = 0;
	SpriteType						m_FrontSprite = ST_IMAGE_NONE;
	SpriteType						m_FrontOutline = ST_IMAGE_NONE;
	SpriteType						m_IconSprite = ST_IMAGE_NONE;
	std::vector<PartsRenderInfo>	m_PartsRenderInfos;

	int								m_Level = 0;
	int								m_KWatt = 0;
	bool							m_IsLock = true;
	int								m_UpgradePrice = 0;
};

class EquipmentAbstract : public ItemAbstract
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);

	void						setEquipmentSprite(SpriteType front, SpriteType frontOutLine,
												   SpriteType icon);
	void						setEquipmentIcon(IconState iconState);
	void						setEquipmentDescription(std::string description);

	IconLayer*					getEquipmentIcon();
	IconState					getEquipmentIconState();

protected:
	cocos2d::Sprite*			m_FrontSpr = nullptr;
	cocos2d::Sprite*			m_FrontOutlineSpr = nullptr;
	IconLayer*					m_Icon = nullptr;

	std::string					m_Name = "";
	std::string					m_Description = "";

private:
};
