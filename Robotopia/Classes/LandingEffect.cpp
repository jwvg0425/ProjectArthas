#include "pch.h"
#include "LandingEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool LandingEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_EFFECT_LANDING);
	auto animate = cocos2d::Animate::create(animation);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(LandingEffect::endAnimation, this));


	m_Sprite->runAction(cocos2d::Sequence::create(animate, callfunc, NULL));
	addChild(m_Sprite);

	setVisible(false);

	return true;
}

void LandingEffect::enter()
{
	setVisible(true);
}

void LandingEffect::exit()
{
	m_IsDead = true;
}

void LandingEffect::update(float dTime)
{

}

void LandingEffect::dead()
{
	removeFromParent();
}

void LandingEffect::endAnimation(cocos2d::Ref* sender)
{
	m_IsDead = true;
}
