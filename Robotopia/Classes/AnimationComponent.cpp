#include "pch.h"
#include "AnimationComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "CommonInfo.h"
#include "ObserverComponent.h"
#include "StateChangeTrigger.h"
#include "TriggerManager.h"
#include "AnimationEndTrigger.h"


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
	CommonInfo* info = (CommonInfo*)m_RenderTarget->getComponent(IT_COMMON);
	if (info != nullptr)
	{
		if (info->getInfo().dir == DIR_LEFT)
		{
			m_Sprite->setFlippedX(true);
		}
		else
		{
			m_Sprite->setFlippedX(false);
		}
	}
}

void Arthas::AnimationCompnent::enter()
{
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(m_AnimationType);
	auto animate = cocos2d::Animate::create(animation);
	if (m_PlayNum == 0)
	{
		auto repeat = cocos2d::RepeatForever::create(animate);
		m_Sprite->setVisible(true);
		m_Sprite->runAction(repeat);
		
	}
	else
	{
		auto repeat = cocos2d::Repeat::create(animate, m_PlayNum);
		auto aniEnd = cocos2d::CallFunc::create(CC_CALLBACK_0(AnimationCompnent::endAni, this));
		auto sequence = cocos2d::Sequence::create(repeat, aniEnd, NULL);
		m_Sprite->setVisible(true);
		m_Sprite->runAction(sequence);
	}
}

void Arthas::AnimationCompnent::exit()
{
	m_Sprite->setVisible(false);
	m_Sprite->stopAllActions();
}


void Arthas::AnimationCompnent::setAnimation(ResourceType animationType, Component* renderTarget, 
											 int playNum, bool isEndAni)
{
	
	m_AnimationType = animationType;
	m_PlayNum = playNum;
	m_IsEndAni = isEndAni;
	m_Sprite = cocos2d::Sprite::create();
	renderTarget->addChild(m_Sprite);
	
	m_RenderTarget = renderTarget;
	m_Sprite->setAnchorPoint(cocos2d::Point(0.5f,0.5f));
}

void Arthas::AnimationCompnent::endAni()
{
	auto observer = (ObserverComponent*)m_RenderTarget->getComponent(CT_OBSERVER);
	if (observer)
	{
		auto endTrigger = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
		endTrigger->initChangingStates(CT_ANIMATION, CT_NONE);
		observer->addTrigger(endTrigger);

		auto animationEndWithTypeTrigger = GET_TRIGGER_MANAGER()->createTrigger<AnimationEndTrigger>();
		animationEndWithTypeTrigger->initTrigger(m_AnimationType);
		observer->addTrigger(animationEndWithTypeTrigger);
	}

	if (m_IsEndAni)
	{
		exit();
	}
}



