#include "AnimationComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"



bool Arthas::AnimationCompnent::init()
{
	if (!Arthas::Component::init())
	{
		return false;
	}

	m_Type = CT_ANIMATION;
	
	return true;
}

void Arthas::AnimationCompnent::update(float dTime)
{
}

void Arthas::AnimationCompnent::enter()
{
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(m_AnimationType);
	auto animate = cocos2d::Animate::create(animation);
	auto repeat = cocos2d::RepeatForever::create(animate);
	m_Sprite->setVisible(true);
	m_Sprite->runAction(repeat);
}

void Arthas::AnimationCompnent::exit()
{
	m_Sprite->setVisible(false);
	m_Sprite->stopAllActions();
}


void Arthas::AnimationCompnent::setAnimation(ResourceType animationType, Component* renderTarget)
{
	m_AnimationType = animationType;
	m_Sprite = cocos2d::Sprite::create();
	renderTarget->addChild(m_Sprite);
	m_Sprite->setAnchorPoint(cocos2d::Point(0.5f, 0.5f));
	m_Sprite->setVisible(false);
}



