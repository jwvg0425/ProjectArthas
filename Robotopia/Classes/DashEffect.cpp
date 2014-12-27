#include "pch.h"
#include "DashEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool DashEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_EFFECT_DASH);
	auto animate = cocos2d::Animate::create(animation);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(DashEffect::endAnimation, this));


	m_Sprite->runAction(cocos2d::Sequence::create(animate, callfunc, NULL));
	addChild(m_Sprite);

	setVisible(false);

	return true;
}

void DashEffect::enter()
{
	setVisible(true);
}

void DashEffect::exit()
{
	m_IsDead = true; 
}

void DashEffect::update(float dTime)
{

}

void DashEffect::dead()
{
	removeFromParent();
}

void DashEffect::endAnimation(cocos2d::Ref* sender)
{
	m_IsDead = true;
}
