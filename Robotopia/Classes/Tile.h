/************************************************************************/
/*
	CLASS			: Tile
	Author			: 김연우
	역할				: Tile들의 추상 class
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: 만들고 반드시 setRect할 것!
*/
/************************************************************************/
#pragma once
#include "BaseComponent.h"
#include "Util.h"



class Tile : public BaseComponent
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime) = 0;
	OVERRIDE void			enter() = 0;
	OVERRIDE void			exit() = 0;

	ABSTRACT void			initTile(cocos2d::Rect tileRect) = 0;
	void					setEnabled(bool enable);

protected:
	ABSTRACT void			initPhysicsBody(cocos2d::Rect physicalRect, PhysicsCategory categoryBitmask = PHYC_ALL);
	void					initSprite(cocos2d::Size spriteSize);

	SpriteType				m_SpriteType = ST_START;
	cocos2d::PhysicsBody*	m_Body = nullptr;
};

