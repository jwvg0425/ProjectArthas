#include "PhysicsComponent.h"

bool Arthas::PhysicsComponent::init()
{
	if(!Component::init())
	{
		return false;
	}
	m_Body = nullptr;
	m_Type = Arthas::ComponentType::CT_PHYSICS;
	return true;
}
void Arthas::PhysicsComponent::update( float dTime )
{

}

void Arthas::PhysicsComponent::enter()
{

}

void Arthas::PhysicsComponent::exit()
{

}



cocos2d::PhysicsBody* Arthas::PhysicsComponent::getBody()
{
	return	m_Body;
}

//물리 바디 설정 rect(바디 위치와 사이즈), isDynamic(움직이냐?), density(무게와 관련), Restitution(탄성 관련), Frinction(마찰력),
//비트마스크는 http://cafe.naver.com/cocos2dxusers/19578 참조
void Arthas::PhysicsComponent::initPhysics( cocos2d::Rect rect, bool isDynamic,
										float density /*= 0.0f */, float Restitution /*= 0.0f*/, float Friction /*= 0.0f*/,
										int ContactTestBitmask /*= 0x00000000*/, int CategoryBitmask /*= 0xffffffff*/, int CollisionBitmask /*= 0xffffffff*/ )
{
	auto material = cocos2d::PhysicsMaterial( density, Restitution, Friction );
	m_Body = cocos2d::PhysicsBody::createBox( rect.size, material );
	m_Body->setContactTestBitmask( ContactTestBitmask );
	m_Body->setCategoryBitmask( CategoryBitmask );
	m_Body->setCollisionBitmask( CollisionBitmask );
	m_Body->setTag( (int)m_Parent->getType() );
	m_Body->setDynamic( isDynamic );
	m_Parent->setPhysicsBody( m_Body );
}

