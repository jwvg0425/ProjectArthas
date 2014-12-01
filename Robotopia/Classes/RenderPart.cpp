#include "pch.h"
#include "RenderPart.h"
#include "AnimationComponent.h"

bool RenderPart::init()
{
	if(!Node::init())
	{
		return false;
	}
	m_CurrentState = Player::STAT_NUM;
	m_Animations.resize(Player::State::STAT_NUM);
	for(auto stateAnimation : m_Animations)
	{
		stateAnimation = nullptr;
	}
	return true;
}

void RenderPart::changeState(Player::State state)
{
	if(m_Animations[state] != nullptr && m_CurrentState != state)
	{
		if(m_CurrentState != Player::STAT_NUM && m_Animations[m_CurrentState] != nullptr)
		{
			m_Animations[m_CurrentState]->exit();
		}
		m_CurrentState = state;
		m_Animations[m_CurrentState]->enter();
	}
}

void RenderPart::addAnimation(BaseComponent* target, AnimationType type, Player::State state)
{
	if(m_Animations[state] == nullptr)
	{
		m_Animations[state] = AnimationComponent::create();
		m_Animations[state]->retain();
	}
	m_Animations[state]->setAnimation(type, target);
}

RenderPart::~RenderPart()
{
	for(auto animation : m_Animations)
	{
		animation->release();
	}
}

RenderPart::RenderPart()
{

}

void RenderPart::setFlip(bool isLeft)
{
	for(auto animation : m_Animations)
	{
		if(animation != nullptr)
		{
			animation->setFlippedX(isLeft);
		}
	}
}

