#include "AnimationComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"

Arthas::AnimationCompnent::~AnimationCompnent()
{
	m_Animation->release();
	m_Parent->removeChild(m_Sprite);
}

bool Arthas::AnimationCompnent::init()
{
	if (!Arthas::Component::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	m_Type = 0;
	m_Parent->addChild(m_Sprite);
	return true;
}

void Arthas::AnimationCompnent::update(float dTime)
{
}

void Arthas::AnimationCompnent::enter()
{
	auto ani = cocos2d::Animate::create(m_Animation);
	auto repeat = cocos2d::RepeatForever::create(ani);
	m_Sprite->runAction(repeat);
}

void Arthas::AnimationCompnent::exit()
{
	m_Sprite->stopAllActions();
}

void Arthas::AnimationCompnent::setAnimation(ResourceType AnimationName)
{
	m_Animation = GET_RESOURCE_MANAGER()->createAnimation(AnimationName);
	m_Animation->retain();
}



