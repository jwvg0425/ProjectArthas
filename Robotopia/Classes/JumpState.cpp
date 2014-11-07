﻿#include "pch.h"
#include "JumpState.h"
#include "PhysicsComponent.h"
#include "CommonInfo.h"


bool Arthas::JumpState::init()
{
	if (!StateComponent::init())
		return false;

	m_Type = STAT_JUMP;

	return true;
}

void Arthas::JumpState::enter()
{
	cocos2d::PhysicsBody* physicsBody = ((PhysicsComponent*)m_Ref->getComponent(CT_PHYSICS))->getBody();
	cocos2d::Vect speed = physicsBody->getVelocity();

	CommonInfo* infoComponent = (CommonInfo*)m_Ref->getComponent(IT_COMMON);
	float jumpSpeed = m_Speed;

	if (infoComponent)
	{
		jumpSpeed = infoComponent->getInfo().jumpSpeed;
	}

	speed.y += jumpSpeed;

	physicsBody->setVelocity(speed);
}

void Arthas::JumpState::exit()
{

}

void Arthas::JumpState::update(float dTime)
{

}

void Arthas::JumpState::setAttribute(Component* ref, float speed)
{
	m_Ref = ref;
	m_Speed = speed;
}

