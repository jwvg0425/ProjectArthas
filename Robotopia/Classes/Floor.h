﻿/************************************************************************/
/*
	CLASS			: Floor
	Author			: 김연우
	역할				: 아래 충돌만 하는 타일 Floor
	최종 수정일자	: 2014-11-09
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/
#pragma once
#include "Tile.h"
#include "Util.h"



class Floor : public Tile
{
public:
	virtual bool	init();
	virtual void	update(float dTime);
	virtual void	enter();
	virtual void	exit();
	virtual void	initTile(cocos2d::Rect tileRect);
	void			extendBlock(cocos2d::Rect tileRect);

	CREATE_FUNC(Floor);
private:
	virtual void	initPhysicsBody(cocos2d::Rect physicsRect, PhysicsCategory categoryBitmask /*= PHYC_ALL*/);
	void			extendBody(cocos2d::Rect rect, float density = 0.f, float Restitution = 0.f, float Friction = 0.f);

};

