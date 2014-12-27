#include "pch.h"
#include "ParalysisEffect.h"
#include "GameManager.h"
#include "ResourceManager.h"

bool ParalysisEffect::init()
{
	if (!Effect::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_EFFECT_PARALYSIS);
	auto animate = cocos2d::Animate::create(animation);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(ParalysisEffect::endAnimation, this));


	m_Sprite->runAction(cocos2d::Sequence::create(animate, callfunc, NULL));
	addChild(m_Sprite);

	setVisible(false);

	return true;
}

void ParalysisEffect::enter()
{
	setVisible(true);
}

void ParalysisEffect::exit()
{
	m_IsDead = true;
}

void ParalysisEffect::update(float dTime)
{
	Effect::update(dTime);
}

void ParalysisEffect::dead()
{
	removeFromParent();
}

void ParalysisEffect::endAnimation(cocos2d::Ref* sender)
{
	m_IsDead = true;
}
