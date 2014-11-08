#include "pch.h"
#include "PhysicsComponent.h"
#include "GameManager.h"
#include "TriggerManager.h"
#include "PhysicsTrigger.h"
#include "ObserverComponent.h"

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
	m_Body->setPositionOffset(rect.origin);
	m_Body->setContactTestBitmask( ContactTestBitmask );
	m_Body->setCategoryBitmask( CategoryBitmask );
	m_Body->setCollisionBitmask( CollisionBitmask );
	m_Body->setTag( (int)m_Parent->getType() );
	m_Body->setDynamic( isDynamic );
	m_Body->setRotationEnable(false);
	m_Parent->setPhysicsBody( m_Body );

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PhysicsComponent::onContactBegin, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(PhysicsComponent::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);
}

bool Arthas::PhysicsComponent::onContactBegin(cocos2d::PhysicsContact& contact)
{
	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();
	Direction dir = DIR_NONE;
	
	if (contact.getContactData()->normal.y > 0)
	{
		dir |= DIR_UP;
	}
	else if(contact.getContactData()->normal.y < 0)
	{
		dir |= DIR_DOWN;
	}

	if (contact.getContactData()->normal.x > 0)
	{
		dir |= DIR_RIGHT;
	}
	else if(contact.getContactData()->normal.x < 0)
	{
		dir |= DIR_LEFT;
	}

	auto trigger = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();

	trigger->initTrigger((ComponentType)tagA, (ComponentType)tagB, dir, CTT_CONTACT);

	ObserverComponent* observer = (ObserverComponent*)m_Parent->getComponent(CT_OBSERVER);

	if (observer != nullptr)
		observer->addTrigger(trigger);

	return true;
}

void Arthas::PhysicsComponent::onContactSeparate(cocos2d::PhysicsContact& contact)
{
	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();
	Direction dir = DIR_NONE;

	if (contact.getContactData()->normal.y > 0)
	{
		dir |= DIR_UP;
	}
	else
	{
		dir |= DIR_DOWN;
	}

	if (contact.getContactData()->normal.x > 0)
	{
		dir |= DIR_RIGHT;
	}
	else
	{
		dir |= DIR_LEFT;
	}

	auto trigger = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();

	trigger->initTrigger((ComponentType)tagA, (ComponentType)tagB, dir, CTT_SEPARATE);

	ObserverComponent* observer = (ObserverComponent*)m_Parent->getComponent(CT_OBSERVER);

	if(observer!=nullptr)
		observer->addTrigger(trigger);
}

