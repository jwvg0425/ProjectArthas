#include "pch.h"
#include "UpMoveEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool UpMoveEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	setVisible(false);

	return true;
}

void UpMoveEffect::enter()
{
	setVisible(true);
}

void UpMoveEffect::exit()
{
	removeFromParent();
}

void UpMoveEffect::update(float dTime)
{
	setPosition(getPosition() + cocos2d::Point(0, 3));
}

void UpMoveEffect::dead()
{
	exit();
}

void UpMoveEffect::endAnimation(cocos2d::Ref* sender)
{
	m_IsDead = true;
}

void UpMoveEffect::setAnimation(AnimationType aniType)
{
	m_Sprite = cocos2d::Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(aniType);
	auto animate = cocos2d::Animate::create(animation);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(UpMoveEffect::endAnimation, this));


	m_Sprite->runAction(cocos2d::Sequence::create(animate, callfunc, NULL));
	addChild(m_Sprite);
}
