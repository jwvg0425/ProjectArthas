#include "ComponentButton.h"
#include "GameManager.h"
#include "DataManager.h"
#include "Component.h"
#include "MapToolAppDelegate.h"
#include "ModuleEditLayer.h"
#include "Tile.h"

bool Arthas::ComponentButton::init()
{
	if (!Node::init())
	{
		return false;
	}
	m_Border = nullptr;

	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Arthas::ComponentButton::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void Arthas::ComponentButton::setComponent(Component* component)
{
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	m_Component = component;

	((Tile*)m_Component)->initTile(0, 0, tileSize.width, tileSize.height);
	addChild(m_Component);
}

void Arthas::ComponentButton::changeSelectState(bool isSelected)
{
	if (isSelected)
	{
		if (m_Border == nullptr)
		{
			cocos2d::DrawNode* node = cocos2d::DrawNode::create();
			cocos2d::Point verts[4];
			cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

			verts[0] = cocos2d::Point(getPositionX() - 1, getPositionY() - 1);
			verts[1] = cocos2d::Point(getPositionX() - 1 + tileSize.width + 2, getPositionY() - 1);
			verts[2] = cocos2d::Point(getPositionX() - 1 + tileSize.width + 2, getPositionY() - 1 + tileSize.height + 2);
			verts[3] = cocos2d::Point(getPositionX() - 1, getPositionY() - 1 + tileSize.height + 2);

			node->drawPolygon(verts, 4, cocos2d::Color4F(cocos2d::Color4B(255, 0, 0, 0)), 1, cocos2d::Color4F(cocos2d::Color4B(255, 0, 0, 255)));
			node->setAnchorPoint(cocos2d::Point(0.5, 0.5));
			node->setPosition(cocos2d::Point(0, 0));
			m_Border = node;
			getParent()->addChild(m_Border,25);
		}
		
	}
	else
	{
		if (m_Border != nullptr)
		{
			getParent()->removeChild(m_Border);
		}
	}
}

Arthas::Component* Arthas::ComponentButton::getComponent()
{
	return m_Component;
}

void Arthas::ComponentButton::onMouseDown(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	cocos2d::Rect rect = cocos2d::Rect(getPositionX() - tileSize.width / 2, getPositionY() -tileSize.height / 2,
		tileSize.width, tileSize.height);


	if (rect.containsPoint(cocos2d::Point(ev->getCursorX(), WINSIZE_HEIGHT + ev->getCursorY())))
	{
		((ModuleEditLayer*)getParent())->setSelectedIdx(m_Component);
	}
}
