/************************************************************************/
/*
	CLASS			: PhysicsComponent
	Author			: 김연우
	역할				: 물리적용되는 컴포넌트
	최종 수정일자	: 2014-10-31
	최종 수정자		:
	최종 수정사유	:
	Comment			: Body의 tag는 부모의 타입
	*/
/************************************************************************/

#pragma once
#include "Component.h"
#include "cocos2d.h"

BEGIN_NS_AT

class PhysicsComponent : public Component
{
public:


	OVERRIDE bool				init();
	OVERRIDE void				update( float dTime );
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	void						initPhysics();
	void						initPhysics( cocos2d::Rect rect, bool isDynamic,
										 float density = 0.0f, float Restitution = 0.0f,
										 float Friction = 0.0f, int ContactTestBitmask = 0x00000000,
										 int CategoryBitmask = 0xffffffff, int CollisionBitmask = 0xffffffff );
	cocos2d::PhysicsBody*		getBody();
	bool						isIgnoreCollision(ComponentType otherType, Direction collisionDir);

	CREATE_FUNC( PhysicsComponent );

	bool						onContactBegin(cocos2d::PhysicsContact& contact);
	void						onContactSeparate(cocos2d::PhysicsContact& contact);
	void						addIgnoreCollision(ComponentType otherType, Direction collisionDir);

protected:
	cocos2d::PhysicsBody*		m_Body;
	std::map<int, Direction> m_IgnoreCollisions;
};

END_NS_AT