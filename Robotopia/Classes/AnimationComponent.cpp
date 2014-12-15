#include "pch.h"
#include "AnimationComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"


bool AnimationComponent::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_Type = CT_ANIMATION;
	
	return true;
}

void AnimationComponent::update(float dTime)
{
	/*
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
	*/
}

void AnimationComponent::enter()
{
	m_AniExit = false;

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
		auto aniEnd = cocos2d::CallFunc::create(CC_CALLBACK_0(AnimationComponent::endAni, this));
		auto sequence = cocos2d::Sequence::create(repeat, aniEnd, NULL);
		m_Sprite->setVisible(true);
		m_Sprite->runAction(sequence);
	}
}

void AnimationComponent::exit()
{
	m_Sprite->setVisible(false);
	//m_Sprite->stopAllActions();
}


void AnimationComponent::setAnimation(AnimationType animationType, BaseComponent* renderTarget, 
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

void AnimationComponent::endAni()
{

	if (m_IsEndAni)
	{
		m_AniExit = true;
		exit();
	}
}

bool AnimationComponent::getAniExit()
{
	return m_AniExit;
}



