#include "MoveState.h"
#include "Object.h"
#include "PhysicsComponent.h"

MoveState::MoveState(Object* parent, bool isRightDirection)
{
	m_Parent = parent;

	m_IsRightDirection = isRightDirection;
}

MoveState::~MoveState()
{

}

void MoveState::update(float dTime)
{
}

void MoveState::enter()
{
	PhysicsComponent* component = (PhysicsComponent*)m_Parent->getComponent(1);

	auto body = component->getBody();
	auto velocity = body->getVelocity();

	if (m_IsRightDirection)
	{
		velocity.x = 200;
	}
	else
	{
		velocity.x = -200;
	}

	body->setVelocity(velocity);
}

void MoveState::exit()
{
	PhysicsComponent* component = (PhysicsComponent*)m_Parent->getComponent(1);

	auto body = component->getBody();
	auto velocity = body->getVelocity();

	velocity.x = 0;

	body->setVelocity(velocity);
}
