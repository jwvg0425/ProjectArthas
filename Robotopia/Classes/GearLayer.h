/************************************************************************ /
/*
CLASS			: GearLayer
Author			: 우재우
역할			: Gear 전환을 보여준다.
최종 수정일자	: 2014-11-14
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "Util.h"
#include "GameSceneUILayer.h"

BEGIN_NS_AT

class GearLayer : public GameSceneUILayer
{
public:
	GearLayer();
	~GearLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(GearLayer);

private:
	cocos2d::Sprite*		m_GearFrame0;
	cocos2d::Sprite*		m_GearFrame1;

	cocos2d::Sprite*		m_GearRotate0;
	cocos2d::Sprite*		m_GearRotate1;
	cocos2d::Sprite*		m_GearRotate2;
	
	cocos2d::Sprite*		m_GearEagle;
	cocos2d::Sprite*		m_GearBear;
	cocos2d::Sprite*		m_GearMonkey;
};

END_NS_AT