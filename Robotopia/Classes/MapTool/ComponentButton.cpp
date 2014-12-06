#include "ComponentButton.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "MapToolAppDelegate.h"
#include "ModuleEditLayer.h"
#include "Tile.h"

bool ComponentButton::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_Border = nullptr;

	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(ComponentButton::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void ComponentButton::setType(RawTileType type)
{
	m_Type = type;

	switch (m_Type)
	{
	case RT_BLOCK:
		m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_MAPTOOL_BLOCK);
		break;
	case RT_FLOOR:
		m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_MAPTOOL_FLOOR);
		break;
	case RT_PORTAL:
		m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_MAPTOOL_PORTAL);
		break;
	case RT_BLOCK_RANDOM:
		m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_MAPTOOL_BLOCK_RANDOM);
		break;
	case RT_FLOOR_RANDOM:
		m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_MAPTOOL_FLOOR_RANDOM);
		break;
	case RT_MONSTER_RANDOM:
		m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_MAPTOOL_MONSTER_RANDOM);
		break;
	case RT_STAGE_PORTAL:
		m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_MAPTOOL_PORTAL); //임시
		break;
	case RT_LASER_1:	//임시
	case RT_LASER_2:
	case RT_LASER_3:
		m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_LASER_RELEASE);
		break;
	case RT_ELECTRIC:
		m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_ELECTRICT_TRAP);
		break;
	}
	
	m_Sprite->setScale(0.5);

	addChild(m_Sprite);
}

void ComponentButton::changeSelectState(bool isSelected)
{
	if (isSelected)
	{
		if (m_Border == nullptr)
		{
			cocos2d::DrawNode* node = cocos2d::DrawNode::create();
			cocos2d::Point verts[4];
			cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
			tileSize.width *= 0.5;
			tileSize.height *= 0.5;

			verts[0] = cocos2d::Point(-1, -1);
			verts[1] = cocos2d::Point(-1 + tileSize.width + 2, -1);
			verts[2] = cocos2d::Point(-1 + tileSize.width + 2, -1 + tileSize.height + 2);
			verts[3] = cocos2d::Point(-1, -1 + tileSize.height + 2);

			node->drawPolygon(verts, 4, cocos2d::Color4F(cocos2d::Color4B(255, 0, 0, 0)), 1, cocos2d::Color4F(cocos2d::Color4B(255, 0, 0, 255)));
			node->setAnchorPoint(cocos2d::Point(0.5, 0.5));
			node->setPosition(cocos2d::Point(0, 0));
			m_Border = node;
			addChild(m_Border, 25);
		}
	}
	else
	{
		if (m_Border != nullptr)
		{
			removeChild(m_Border);
			m_Border = nullptr;
		}
	}
}

cocos2d::Sprite* ComponentButton::getSprite()
{
	return m_Sprite;
}

void ComponentButton::onMouseDown(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	cocos2d::Rect rect = cocos2d::Rect(getPositionX() - tileSize.width / 2, getPositionY() -tileSize.height / 2,
		tileSize.width, tileSize.height);


	if (rect.containsPoint(cocos2d::Point(ev->getCursorX(), WINSIZE_HEIGHT + ev->getCursorY())))
	{
		((ModuleEditLayer*)getParent())->setSelectedIdx(m_Sprite);
	}
}

RawTileType ComponentButton::getType()
{
	return m_Type;
}
