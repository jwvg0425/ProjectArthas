﻿#include "JumpState.h"
#include "PhysicsComponent.h"


bool Arthas::JumpState::init()
{
	if (!StateComponent::init())
		return false;

	return true;
}

void Arthas::JumpState::enter()
{
	cocos2d::PhysicsBody* physicsBody = ((PhysicsComponent*)m_Parent->getComponent(CT_PHYSICS))->getBody();
	cocos2d::Vect speed = physicsBody->getVelocity();

	speed.y += m_Speed;

	physicsBody->setVelocity(speed);
}

void Arthas::JumpState::exit()
{

}

void Arthas::JumpState::update(float dTime)
{

}

void Arthas::JumpState::setAttribute(float speed)
{
	m_Speed = speed;
}

