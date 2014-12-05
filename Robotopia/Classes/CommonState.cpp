#include "pch.h"
#include "CommonState.h"
#include "Creature.h"
//임시로 지정
#define KNOCKBACK_X_VECT 250
#define KNOCKBACK_Y_VECT 400

void CommonState::enterKnockback(Creature* target, int dir)
{
	auto body = target->getPhysicsBody();
	auto velocity = cocos2d::Vect::ZERO;
	
	velocity.y = KNOCKBACK_Y_VECT;

	if (dir == DIR_LEFT)
	{
		velocity.x = -KNOCKBACK_X_VECT;
	}
	else if (dir == DIR_RIGHT)
	{
		velocity.x = KNOCKBACK_X_VECT;
	}

	body->setVelocity(velocity);
}

void CommonState::knockback(Creature* target, double dTime, int idx)
{
	//넉백 상태에선 어떤 행동도 불가능.
}
