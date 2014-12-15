#include "pch.h"
#include "Floor.h"
#include "GameManager.h"
#include "ComponentManager.h"

bool Floor::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_FLOOR;
	m_SpriteType = ST_FLOOR;

	return true;
}

void Floor::update(float dTime)
{

}

void Floor::enter()
{

}

void Floor::exit()
{

}

void Floor::initTile(cocos2d::Rect tileRect)
{
	setPosition(tileRect.origin);
	initPhysicsBody(tileRect, PHYC_ALL);
}

void Floor::extendBlock(cocos2d::Rect rect)
{
	rect.origin.x += rect.size.width / 2;
	rect.origin.y += rect.size.height / 2;
	extendBody(rect);
}

void Floor::initPhysicsBody(cocos2d::Rect physicsRect, PhysicsCategory categoryBitmask /*= PHYC_ALL*/)
{
	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(physicsRect.size, meterial, physicsRect.origin);
	m_Body->setContactTestBitmask(PHYC_NONE);
	m_Body->setCategoryBitmask(PHYC_FLOOR);
	m_Body->setCollisionBitmask(PHYC_ALL);
	m_Body->setTag(static_cast<int>(getType()));
	m_Body->setDynamic(false);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->retain();

	setPhysicsBody(m_Body);
}

void Floor::extendBody(cocos2d::Rect rect, float density /*= 0.f*/, float Restitution /*= 0.f*/, float Friction /*= 0.f*/)
{
	if (m_Body)
	{
		auto originalShape = m_Body->getFirstShape();
		cocos2d::PhysicsMaterial material;

		if (originalShape)
			material = originalShape->getMaterial();
		else
			material = cocos2d::PhysicsMaterial(density, Restitution, Friction);
		
		auto shape = cocos2d::PhysicsShapeBox::create(rect.size, material, rect.origin);
		shape->setContactTestBitmask(PHYC_ALL);
		m_Body->addShape(shape);
	}
}

