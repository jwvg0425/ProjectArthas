#include "pch.h"
#include "PunchMissile.h"


bool PunchMissile::init()
{
	if (!Missile::init())
	{
		return false;
	}

	return true;
}

void PunchMissile::update(float dTime)
{

}

void PunchMissile::enter()
{

}

void PunchMissile::exit()
{

}

void PunchMissile::initMissile()
{

}

void PunchMissile::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, float damage /*= 0*/, 
								cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/,
								cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{

}
