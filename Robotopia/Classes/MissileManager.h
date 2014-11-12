/************************************************************************/
/*
CLASS			: MissileManager
Author			: 김성연
역할				: 각종 미사일 미리 생성 및 할당
최종 수정일자		: 2014-11-12
최종 수정자		:
최종 수정사유	    :
Comment			:
*/
/************************************************************************/

#pragma once

#include "Util.h"
#include <vector>

BEGIN_NS_AT

class Missile;
class MissileManager
{
public:
	MissileManager();
	~MissileManager();

	bool					init();
	Missile*				getMissile(ComponentType missileType, cocos2d::Point pos, Direction attackDir,
									   float damage, cocos2d::Vec2 velocity);

private:
	std::vector<Missile*>   m_Missiles;

};

END_NS_AT