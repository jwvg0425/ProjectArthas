/************************************************************************/
/*
CLASS			: MissilePlayerMelee
Author			: 김성연
역할				: Player의 Melee Missile에 관한 내용 가지고 있음
최종 수정일자		: 2014-11-12
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once

#include "Missile.h"
#include "Util.h"

BEGIN_NS_AT

class PhysicsTrigger;
class MissilePlayerMelee : public Arthas::Missile
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	OVERRIDE void			    initMissile();
	OVERRIDE void				setAttribute(cocos2d::Point pos, Direction attackDir, 
											 float damage, cocos2d::Vec2 velocity);


	CREATE_FUNC(MissilePlayerMelee);

protected:
	PhysicsTrigger* m_PhysicsTirgger;

};

END_NS_AT