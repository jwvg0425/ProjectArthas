/************************************************************************/
/*
CLASS			: ItemAbstact
Author			: 김성연
역할				: 모든 아이템의 추상 클래스, 스토리 조각, equipment, kit 포함
최종 수정일자		: 2014-11-27
최종 수정자		:
최종 수정사유		:
Comment			:
/************************************************************************/

#pragma once

#include "BaseComponent.h"

class ItemAbstract : public BaseComponent
{
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE bool				onContactBegin(cocos2d::PhysicsContact& contact);
	OVERRIDE void				onContactSeparate(cocos2d::PhysicsContact& contact);


protected:
	
};

