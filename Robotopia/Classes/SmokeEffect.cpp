#include "pch.h"
#include "SmokeEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool SmokeEffect::init()
{
	if (!FlyRoundEffect::init())
	{
		return false;
	}

	return true;
}

void SmokeEffect::enter()
{
	setVisible(true);
}

void SmokeEffect::exit()
{
	m_IsDead = true;
}

void SmokeEffect::update(float dTime)
{
	FlyRoundEffect::update(dTime);

	setPosition(getPosition() + cocos2d::Point(-3 + (rand() % 6), 3));
}

void SmokeEffect::dead()
{
	removeFromParent();
}
