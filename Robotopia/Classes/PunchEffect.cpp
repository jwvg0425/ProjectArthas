#include "pch.h"
#include "PunchEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool PunchEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_EFFECT_PUNCH_MISSILE);
	auto animate = cocos2d::Animate::create(animation);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(PunchEffect::endAnimation, this));


	m_Sprite->runAction(cocos2d::Sequence::create(animate, callfunc, NULL));
	addChild(m_Sprite);

	setVisible(false);

	return true;
}

void PunchEffect::enter()
{
	setVisible(true);
}

void PunchEffect::exit()
{
	removeFromParent();
}

void PunchEffect::update(float dTime)
{

}

void PunchEffect::dead()
{
	exit();
}

void PunchEffect::endAnimation(cocos2d::Ref* sender)
{
	m_IsDead = true;
}
