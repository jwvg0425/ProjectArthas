#include "pch.h"
#include "RenderPart.h"
#include "AnimationComponent.h"

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

bool RenderPart::init()
{
	if(!Node::init())
	{
		return false;
	}
	m_CurrentStateIdx = -1;
	m_Animations.resize(Player::STAT_NUM * Player::STAT_NUM);
	for(auto stateAnimation : m_Animations)
	{
		stateAnimation = nullptr;
	}
	return true;
}

void RenderPart::changeState(int fsmIdx, Player::State state)
{
	int nextIdx = idxize(fsmIdx, state);
	if(nextIdx < m_Animations.size() && m_Animations[nextIdx] != nullptr && m_CurrentStateIdx != state)
	{
		if(m_CurrentStateIdx != -1 && m_Animations[m_CurrentStateIdx] != nullptr)
		{
			m_Animations[m_CurrentStateIdx]->exit();
		}
		m_CurrentStateIdx = nextIdx;
		m_Animations[m_CurrentStateIdx]->enter();
	}
}

void RenderPart::addAnimation(BaseComponent* target, AnimationType type, int fsmIdx, Player::State state)
{
	int stateIdx = idxize(fsmIdx, state);
	if(m_Animations[stateIdx] == nullptr)
	{
		m_Animations[stateIdx] = AnimationComponent::create();
		m_Animations[stateIdx]->retain();
	}
	m_Animations[stateIdx]->setAnimation(type, target);
}


void RenderPart::enter()
{
	AnimationComponent* animation = nullptr;
	animation = ( m_Animations[m_CurrentStateIdx] != nullptr ) ?
		m_Animations[m_CurrentStateIdx] : m_Animations[0];
	animation->enter();
}

void RenderPart::exit()
{
	AnimationComponent* animation = nullptr;
	animation = ( m_Animations[m_CurrentStateIdx] != nullptr ) ?
		m_Animations[m_CurrentStateIdx] : m_Animations[0];
	animation->exit();
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

int RenderPart::idxize(int fsmIdx, Player::State state)
{
	return fsmIdx * Player::STAT_NUM + state;
}
