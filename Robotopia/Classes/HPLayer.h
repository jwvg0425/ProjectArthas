/************************************************************************/
/*
CLASS			: HPLayer
Author			: 우재우
역할			: Player 체력을 보여준다.
최종 수정일자	: 2014-11-18
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "GameSceneUILayer.h"

class HPLayer : public GameSceneUILayer
{
public:
	HPLayer();
	~HPLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(HPLayer);
private:
	cocos2d::Sprite*		m_HPSprite = nullptr;
	cocos2d::ProgressTimer* m_HPBar = nullptr;

	int						m_PrevHP = 0;
	void					controlHP(int maxHP, int currentHP);
};
