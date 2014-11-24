#include "pch.h"
#include "PhysicsComponent.h"
#include "GameManager.h"
#include "TriggerManager.h"
#include "PhysicsTrigger.h"
#include "ObserverComponent.h"
#include "PhysicsInfo.h"

PhysicsComponent::~PhysicsComponent()
{
	m_Body->release();
}

bool PhysicsComponent::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}
	m_Body = nullptr;
	m_Type = ComponentType::CT_PHYSICS;
	m_IgnoreCollisions.clear();
	return true;
}
void PhysicsComponent::update( float dTime )
{

}

void PhysicsComponent::enter()
{

}

void PhysicsComponent::exit()
{

}



cocos2d::PhysicsBody* PhysicsComponent::getBody()
{
	return	m_Body;
}

//물리 바디 설정 rect(바디 위치와 사이즈), isDynamic(움직이냐?), density(무게와 관련), Restitution(탄성 관련), Frinction(마찰력),
//비트마스크는 http://cafe.naver.com/cocos2dxusers/19578 참조
void PhysicsComponent::initPhysics( cocos2d::Rect rect, bool isDynamic,
										float density /*= 0.0f */, float Restitution /*= 0.0f*/, float Friction /*= 0.0f*/,
										int ContactTestBitmask /*= 0x00000000*/, int CategoryBitmask /*= 0xffffffff*/, int CollisionBitmask /*= 0xffffffff*/ )
{
	auto meterial = cocos2d::PhysicsMaterial( density, Restitution, Friction );
	m_Body = cocos2d::PhysicsBody::createBox(rect.size,meterial, rect.origin);
	m_Body->setContactTestBitmask( ContactTestBitmask );
	m_Body->setCategoryBitmask( CategoryBitmask );
	m_Body->setCollisionBitmask( CollisionBitmask );
	m_Body->setTag( (int)GET_COMP_PARENT()->getType() );
	m_Body->setDynamic( isDynamic );
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->retain();
	GET_COMP_PARENT()->setPhysicsBody( m_Body );

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PhysicsComponent::onContactBegin, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(PhysicsComponent::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);
}

bool PhysicsComponent::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	int tagA = bodyA->getTag();
	int tagB = bodyB->getTag();
	Direction dir = DIR_NONE;
	
	if (contact.getContactData()->normal.y < 0)
	{
		dir |= DIR_UP;
	}
	else if(contact.getContactData()->normal.y > 0)
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

	//물리 정보 갱신
	auto physicsInfo = (PhysicsInfo*)((BaseComponent*)getParent())->getComponent(IT_PHYSICS);

	if (physicsInfo != nullptr)
	{
		auto info = physicsInfo->getInfo();
		int enemyTag = (tagA == getTag()) ? tagB : tagA;

		info->contactObjects.push_back(enemyTag);
	}

	//무시해야하는 충돌인 경우 무시한다.
	PhysicsComponent* physicsA = (PhysicsComponent* )((BaseComponent*)bodyA->getNode())->getComponent(CT_PHYSICS);
	PhysicsComponent* physicsB = (PhysicsComponent*)((BaseComponent*)bodyB->getNode())->getComponent(CT_PHYSICS);

	if (physicsA == nullptr || physicsB == nullptr)
	{
		return true;
	}

	if (physicsA->isIgnoreCollision((ComponentType)tagB, dir) ||
		physicsB->isIgnoreCollision((ComponentType)tagA, dir))
	{
		auto trigger = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();

		trigger->initTrigger((ComponentType)tagA, (ComponentType)tagB, dir, CTT_IGNORE);
		trigger->setContactData(*contact.getContactData());

		ObserverComponent* observer = (ObserverComponent*)GET_COMP_PARENT()->getComponent(CT_OBSERVER);

		if (observer != nullptr)
			observer->addTrigger(trigger);

		return false;
	}

	auto trigger = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();

	trigger->initTrigger((ComponentType)tagA, (ComponentType)tagB, dir, CTT_CONTACT);
	trigger->setContactData(*contact.getContactData());

	ObserverComponent* observer = (ObserverComponent*)GET_COMP_PARENT()->getComponent(CT_OBSERVER);

	if (observer != nullptr)
		observer->addTrigger(trigger);

	return true;
}

void PhysicsComponent::onContactSeparate(cocos2d::PhysicsContact& contact)
{
	int tagA = contact.getShapeA()->getBody()->getTag();
	int tagB = contact.getShapeB()->getBody()->getTag();
	Direction dir = DIR_NONE;

	if (contact.getContactData()->normal.y < 0)
	{
		dir |= DIR_UP;
	}
	else if (contact.getContactData()->normal.y > 0)
	{
		dir |= DIR_DOWN;
	}

	if (contact.getContactData()->normal.x > 0)
	{
		dir |= DIR_RIGHT;
	}
	else if (contact.getContactData()->normal.x < 0)
	{
		dir |= DIR_LEFT;
	}

	//물리 정보 갱신
	auto physicsInfo = (PhysicsInfo*)((BaseComponent*)getParent())->getComponent(IT_PHYSICS);

	if (physicsInfo != nullptr)
	{
		auto info = physicsInfo->getInfo();
		int enemyTag = (tagA == getTag()) ? tagB : tagA;

		for (int loopDir = DIR_UP; loopDir < DIR_MAX; loopDir *= 2)
		{
			if (dir & loopDir)
			{
				auto enemy = std::find(info->contactObjects.begin(), info->contactObjects.end(), enemyTag);

				_ASSERT(enemy != info->contactObjects.end());

				info->contactObjects.erase(enemy);
			}
		}
	}

	auto trigger = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();

	trigger->initTrigger((ComponentType)tagA, (ComponentType)tagB, dir, CTT_SEPARATE);
	trigger->setContactData(*contact.getContactData());

	ObserverComponent* observer = (ObserverComponent*)GET_COMP_PARENT()->getComponent(CT_OBSERVER);

	if(observer!=nullptr)
		observer->addTrigger(trigger);
}

void PhysicsComponent::addIgnoreCollision(ComponentType otherType, Direction collisionDir)
{
	if (m_IgnoreCollisions.find(otherType) != m_IgnoreCollisions.end())
	{
		m_IgnoreCollisions[otherType] |= collisionDir;
	}
	else
	{
		m_IgnoreCollisions[otherType] = collisionDir;
	}
}

bool PhysicsComponent::isIgnoreCollision(ComponentType otherType, Direction collisionDir)
{
	if (m_IgnoreCollisions.find(otherType) != m_IgnoreCollisions.end())
	{
		if ((m_IgnoreCollisions[otherType] & collisionDir) != 0)
			return true;
	}

	return false;
}

void PhysicsComponent::setEnabled(bool enable)
{
	if (enable == true)
	{
		GET_COMP_PARENT()->setPhysicsBody(m_Body);
	}
	else
	{
		GET_COMP_PARENT()->setPhysicsBody(nullptr);
		if(m_Body != nullptr)
		{
			m_Body->removeFromWorld();
		}
	}
}

void PhysicsComponent::extendBody(cocos2d::Rect rect, float density /*= 0.f*/, float Restitution /*= 0.f*/, float Friction /*= 0.f*/)
{
	if(m_Body)
	{
		auto originalShape = m_Body->getFirstShape();
		cocos2d::PhysicsMaterial material;
		if(originalShape)
			material = originalShape->getMaterial();
		else
			material = cocos2d::PhysicsMaterial(density, Restitution, Friction);
		auto shape = cocos2d::PhysicsShapeBox::create(rect.size, material, rect.origin);
		shape->setContactTestBitmask(PHYC_ALL);
		m_Body->addShape(shape);
	}
}

void PhysicsComponent::removeIgnoreCollision(ComponentType otherType, Direction collisionDir)
{
	if (m_IgnoreCollisions.find(otherType) != m_IgnoreCollisions.end())
	{
		m_IgnoreCollisions[otherType] &= ~collisionDir;
		if (m_IgnoreCollisions[otherType] == DIR_NONE)
			m_IgnoreCollisions.erase(otherType);
	}
}
