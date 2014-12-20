#include "LinearMissile.h"

bool LinearMissile::init()
{
	if(!Missile::init())
	{
		return false;
	}
	return true;
}

void LinearMissile::update(float dTime)
{

}

void LinearMissile::enter()
{

}

void LinearMissile::exit()
{

}

void LinearMissile::initMissile()
{

}

void LinearMissile::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, float damage /*= 0*/, cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/, cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{

}

bool LinearMissile::onContactBegin(cocos2d::PhysicsContact& contact)
{



	return true;
}

void LinearMissile::setEnabled(bool enable)
{

}
