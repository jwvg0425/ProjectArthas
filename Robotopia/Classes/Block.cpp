#include "pch.h"
#include "Block.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"

bool Block::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_BLOCK;
	m_SpriteType = ST_BLOCK;

	return true;
}

void Block::update( float dTime )
{

}

void Block::enter()
{
}

void Block::exit()
{
}

void Block::initTile( cocos2d::Rect tileRect )
{
	setPosition(tileRect.origin);
	initPhysicsBody(tileRect, PHYC_BLOCK);
}

void Block::extendBlock(cocos2d::Rect rect)
{
	rect.origin.x += rect.size.width / 2;
	rect.origin.y += rect.size.height / 2;
	extendBody(rect);
}

void Block::initPhysicsBody(cocos2d::Rect physicsRect, PhysicsCategory categoryBitmask /*= PHYC_ALL*/)
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

void Block::extendBody(cocos2d::Rect rect, float density /*= 0.f*/, float Restitution /*= 0.f*/, float Friction /*= 0.f*/)
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
