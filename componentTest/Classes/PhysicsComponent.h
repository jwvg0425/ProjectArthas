#pragma once
#include "Component.h"
#include "cocos2d.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(cocos2d::Rect rect,
					float density = 0.0f , float Restitution = 0.0f, float Friction = 0.0f,
					int ContactTestBitmask = 0x00000000, int CategoryBitmask = 0xffffffff, int CollisionBitmask = 0xffffffff);
	~PhysicsComponent();

	virtual void update(float dTime);
	virtual void enter();
	virtual void exit();
protected:
	cocos2d::PhysicsBody m_Body;
};