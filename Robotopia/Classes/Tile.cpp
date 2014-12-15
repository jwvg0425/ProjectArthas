#include "pch.h"
#include "Tile.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"



bool Tile::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_SpriteType = ST_END;
	return true;
}

void Tile::initPhysicsBody(cocos2d::Rect physicalRect, PhysicsCategory categoryBitmask)
{
	cocos2d::Rect physicsRect = cocos2d::Rect::ZERO;

	physicsRect.origin.x = physicalRect.size.width / 2;
	physicsRect.origin.y = physicalRect.size.height / 2;
	physicsRect.size = physicalRect.size;

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(physicsRect.size, meterial, physicsRect.origin);
	m_Body->setContactTestBitmask(PHYC_ALL);
	m_Body->setCategoryBitmask(categoryBitmask);
	m_Body->setCollisionBitmask(PHYC_ALL);
	m_Body->setTag(static_cast<int>(getType()));
	m_Body->setDynamic(false);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setPositionOffset(physicalRect.origin);
	m_Body->retain();

	setPhysicsBody(m_Body);
}

void Tile::initSprite(cocos2d::Size spriteSize)
{
	for(int yIdx = 0; yIdx < spriteSize.height; yIdx += GET_DATA_MANAGER()->getTileSize().height)
	{
		for(int xIdx = 0; xIdx < spriteSize.width; xIdx += GET_DATA_MANAGER()->getTileSize().width)
		{
			auto spriteComp = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
			spriteComp->initSprite(m_SpriteType, this, cocos2d::Point(xIdx, yIdx), cocos2d::Point(0,0));
			addComponent(spriteComp);
			spriteComp->enter();
		}
	}
}

void Tile::setEnabled(bool enable)
{
	if (enable == true)
	{
		setPhysicsBody(m_Body);
	}
	else
	{
		setPhysicsBody(nullptr);
		if (m_Body != nullptr)
		{
			m_Body->removeFromWorld();
		}
	}
}

Tile::Tile()
{

}

Tile::~Tile()
{
	SAFE_RELEASE(m_Body);
}
