#include "pch.h"
#include "FlyRoundEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"


bool FlyRoundEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_EFFECT_FLYING);
	auto animate = cocos2d::Animate::create(animation);
	m_Sprite->runAction(cocos2d::RepeatForever::create(animate));
	m_Opacity = 255;
	addChild(m_Sprite);

	setVisible(false);

	return true;
}

void FlyRoundEffect::enter()
{
	setVisible(true);
}

void FlyRoundEffect::exit()
{
	m_IsDead = true; 
}

void FlyRoundEffect::update(float dTime)
{
	m_Opacity-= OPACITY_CONSUME_VALUE * dTime;
	m_Sprite->setOpacity(m_Opacity);

	if (m_Opacity <= 0)
	{
		m_IsDead = true;
	}
	Effect::update(dTime);
}

void FlyRoundEffect::dead()
{
	removeFromParent();
}
