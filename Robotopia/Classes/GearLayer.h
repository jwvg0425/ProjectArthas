/************************************************************************ /
/*
CLASS			: GearLayer
Author			: 우재우
역할			: Gear 전환을 보여준다.
최종 수정일자	: 2014-11-17
최종 수정자		: 우재우
최종 수정사유	: 기어 회전 추가
Comment			:
*/
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "Util.h"
#include "GameSceneUILayer.h"

class GearLayer : public GameSceneUILayer
{
public:
	GearLayer();
	~GearLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(GearLayer);

private:
	cocos2d::Sprite*		m_GearFrame0 = nullptr;
	cocos2d::Sprite*		m_GearFrame1 = nullptr;

	cocos2d::Sprite*		m_GearRotate0 = nullptr;
	cocos2d::Sprite*		m_GearRotate1 = nullptr;
	cocos2d::Sprite*		m_GearRotate2 = nullptr;
	
	cocos2d::Sprite*		m_GearEagle = nullptr;
	cocos2d::Sprite*		m_GearBear = nullptr;
	cocos2d::Sprite*		m_GearMonkey = nullptr;

	GearType				m_CurrentGear = GEAR_NONE;

	void					rotateGear(GearType swithGearTo, bool clockwise);
	void					controlGear(GearType newGear);
};
