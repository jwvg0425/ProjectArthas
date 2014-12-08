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
	Tile();
	virtual ~Tile();

	virtual bool			init();
	virtual void			update(float dTime) = 0;
	virtual void			enter() = 0;
	virtual void			exit() = 0;

	virtual void			initTile(cocos2d::Rect tileRect) = 0;
	virtual void			setEnabled(bool enable);

protected:
	virtual void			initPhysicsBody(cocos2d::Rect physicalRect, PhysicsCategory categoryBitmask = PHYC_ALL);
	void					initSprite(cocos2d::Size spriteSize);

	SpriteType				m_SpriteType = ST_START;
	cocos2d::PhysicsBody*	m_Body = nullptr;
};

