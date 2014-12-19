#include "pch.h"
#include "AimingEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool AimingEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_EFFECT_AIMING_MISSILE);
	auto animate = cocos2d::Animate::create(animation);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(AimingEffect::endAnimation, this));


	m_Sprite->runAction(cocos2d::Sequence::create(animate, callfunc, NULL));
	addChild(m_Sprite);

	setVisible(false);

	return true;
}

void AimingEffect::enter()
{
	setVisible(true);
}

void AimingEffect::exit()
{
	removeFromParent();
}

void AimingEffect::update(float dTime)
{

}

void AimingEffect::dead()
{
	exit();
}

void AimingEffect::endAnimation(cocos2d::Ref* sender)
{
	m_IsDead = true;
}
