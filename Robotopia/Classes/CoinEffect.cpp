#include "pch.h"
#include "CoinEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool CoinEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_EFFECT_COIN);
	auto animate = cocos2d::Animate::create(animation);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(CoinEffect::endAnimation, this));


	m_Sprite->runAction(cocos2d::Sequence::create(animate, callfunc, NULL));
	addChild(m_Sprite);

	setVisible(false);

	return true;
}

void CoinEffect::enter()
{
	setVisible(true);
}

void CoinEffect::exit()
{
	removeFromParent();
}

void CoinEffect::update(float dTime)
{
	setPosition(getPosition() + cocos2d::Point(0, 3));
}

void CoinEffect::dead()
{
	exit();
}

void CoinEffect::endAnimation(cocos2d::Ref* sender)
{
	m_IsDead = true;
}
