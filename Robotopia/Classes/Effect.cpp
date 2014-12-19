#include "pch.h"
#include "Effect.h"
#include "GameManager.h"
#include "StageManager.h"
#include "Player.h"

void Effect::setChasingPlayer(bool chasing)
{
	m_IsChasePlayer = chasing;
}

void Effect::update(float dTime)
{
	if (m_IsChasePlayer)
	{
		setPosition(GET_STAGE_MANAGER()->getPlayer()->getPosition());
	}
}

bool Effect::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	return true;
}

cocos2d::Sprite* Effect::getSprite()
{
	return m_Sprite;
}
