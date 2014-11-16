#include "pch.h"
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
	//추락 상태 - 아무처리도 안함.
	if (m_Speed == 0)
	{
		return;
	}

	if (!m_IsDownJump)
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
	else
	{
		cocos2d::PhysicsBody* physicsBody = ((PhysicsComponent*)m_Ref->getComponent(CT_PHYSICS))->getBody();
		cocos2d::Vect speed = physicsBody->getVelocity();
		speed.y += 100;

		physicsBody->setVelocity(speed);

		((PhysicsComponent*)m_Ref->getComponent(CT_PHYSICS))->addIgnoreCollision(OT_FLOOR, DIR_DOWN);
	}
}

void Arthas::JumpState::exit()
{
	//추락 상태 - 아무처리도 안함.
	if (m_Speed == 0)
	{
		return;
	}

	if (m_IsDownJump)
	{
		((PhysicsComponent*)m_Ref->getComponent(CT_PHYSICS))->removeIgnoreCollision(OT_FLOOR, DIR_DOWN);
	}
}

void Arthas::JumpState::update(float dTime)
{

}

void Arthas::JumpState::setAttribute(Component* ref, float speed, bool isDownJump)
{
	m_Ref = ref;
	m_Speed = speed;
	m_IsDownJump = isDownJump;
}

