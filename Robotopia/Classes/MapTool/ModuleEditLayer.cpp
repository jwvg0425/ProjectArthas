#include "ModuleEditLayer.h"
#include "MapToolAppDelegate.h"
#include "MapToolScene.h"
#include "ModuleListLayer.h"
#include "Component.h"
#include "ComponentButton.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "ResourceManager.h"
#include "Block.h"
#include "SpriteComponent.h"

bool Arthas::ModuleEditLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	m_ModuleSprites.clear();
	m_SelectedComponentIdx = -1;
	m_PrevSelectedModuleIdx = -1;
	m_IsMouseDown = false;

	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	for (int x = 0; x < moduleSize.width; x++)
	{
		for (int y = 0; y < moduleSize.height; y++)
		{
			addChild(makeCell(300 + x*tileSize.width, 200 + y*tileSize.height));
		}
	}
	
	auto comButton = ComponentButton::create();

	comButton->setComponent(GET_COMPONENT_MANAGER()->createComponent<Block>());

	comButton->setPosition(cocos2d::Point(300, 60));

	m_ComponentList.push_back(comButton);

	addChild(comButton);

	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Arthas::ModuleEditLayer::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(Arthas::ModuleEditLayer::onMouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(Arthas::ModuleEditLayer::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	scheduleUpdate();

	return true;
}

cocos2d::DrawNode* Arthas::ModuleEditLayer::makeCell(float x, float y)
{
	cocos2d::DrawNode* node = cocos2d::DrawNode::create();
	cocos2d::Point verts[4];
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	verts[0] = cocos2d::Point(x, y);
	verts[1] = cocos2d::Point(x + tileSize.width + 1, y);
	verts[2] = cocos2d::Point(x + tileSize.width + 1, y + tileSize.height + 1);
	verts[3] = cocos2d::Point(x, y + tileSize.height + 1);

	node->drawPolygon(verts, 4, cocos2d::Color4F(cocos2d::Color4B(255, 255, 255, 255)), 1, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 255)));
	node->setAnchorPoint(cocos2d::Point(0, 0));
	node->setPosition(cocos2d::Point(0, 0));
	
	return node;
}

void Arthas::ModuleEditLayer::setSelectedIdx(Component* data)
{
	for (int i = 0; i < m_ComponentList.size(); i++)
	{
		if (m_ComponentList[i]->getComponent() == data)
		{
			m_ComponentList[i]->changeSelectState(true);
			m_SelectedComponentIdx = i;
		}
		else
		{
			m_ComponentList[i]->changeSelectState(false);
		}
	}

}

void Arthas::ModuleEditLayer::onMouseDown(cocos2d::Event* event)
{
	m_IsMouseDown = true;
}

void Arthas::ModuleEditLayer::onMouseMove(cocos2d::Event* event)
{

	if (!m_IsMouseDown || m_PrevSelectedModuleIdx == -1 || m_SelectedComponentIdx == -1)
		return;

	cocos2d::EventMouse* ev = (cocos2d::EventMouse*)event;

	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	int cellX = (ev->getCursorX() - 300)/tileSize.width;
	int cellY = (WINSIZE_HEIGHT + ev->getCursorY() - 200) / tileSize.height;

	if (cellX < 0 || cellX >= moduleSize.width ||
		cellY < 0 || cellY >= moduleSize.height)
		return;

	int cellIdx = cellY*moduleSize.width + cellX;

	auto layer = (ModuleListLayer*)getParent()->getChildByTag(TAG_MODULE_LIST_LAYER);
	Direction dir = layer->getSortDir();
	auto data = GET_DATA_MANAGER()->getModuleDatas();

	if (ev->getMouseButton() == MOUSE_BUTTON_LEFT)
	{
		if (m_ModuleSprites.find(cellIdx) != m_ModuleSprites.end())
		{
			removeChild(m_ModuleSprites[cellIdx]);
			m_ModuleSprites.erase(cellIdx);
		}
		Arthas::Component* component = m_ComponentList[m_SelectedComponentIdx]->getComponent();
		SpriteComponent* sprComponent = (SpriteComponent*)component->getComponent(CT_SPRITE);
		cocos2d::Sprite* sprite = sprComponent->getSprite();

		m_ModuleSprites[cellIdx] = cocos2d::Sprite::createWithSpriteFrame(sprite->getSpriteFrame());
		m_ModuleSprites[cellIdx]->setPosition(300 + cellX*tileSize.width, 200 + cellY*tileSize.height);
		m_ModuleSprites[cellIdx]->setAnchorPoint(cocos2d::Point(0, 0));
		addChild(m_ModuleSprites[cellIdx]);

		data[dir][m_PrevSelectedModuleIdx].data[cellIdx] = component->getType();
	}
	else
	{
		if (m_ModuleSprites.find(cellIdx) != m_ModuleSprites.end())
		{
			removeChild(m_ModuleSprites[cellIdx]);
			m_ModuleSprites.erase(cellIdx);
		}
		data[dir][m_PrevSelectedModuleIdx].data[cellIdx] = CT_NONE;
	}
}

void Arthas::ModuleEditLayer::onMouseUp(cocos2d::Event* event)
{
	m_IsMouseDown = false;
}

void Arthas::ModuleEditLayer::update(float dTime)
{
	auto layer = (ModuleListLayer*)getParent()->getChildByTag(TAG_MODULE_LIST_LAYER);

	if (layer->getSelectedIdx() != m_PrevSelectedModuleIdx)
	{
		m_PrevSelectedModuleIdx = layer->getSelectedIdx();
		initPrintedModule();
	}
}

void Arthas::ModuleEditLayer::initPrintedModule()
{
	auto layer = (ModuleListLayer*)getParent()->getChildByTag(TAG_MODULE_LIST_LAYER);

	for (auto pair : m_ModuleSprites)
	{
		removeChild(pair.second);
	}
	m_ModuleSprites.clear();

	Direction dir = layer->getSortDir();
	auto data = GET_DATA_MANAGER()->getModuleDatas();
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	if (m_PrevSelectedModuleIdx == -1)
		return;

	for (int x = 0; x < moduleSize.width; x++)
	{
		for (int y = 0; y < moduleSize.height; y++)
		{
			if (data[dir][m_PrevSelectedModuleIdx].data[y*moduleSize.width + x] != CT_NONE)
			{
				SpriteComponent* sprComponent = nullptr;
				for (auto& button : m_ComponentList)
				{
					if (button->getComponent()->getType() == data[dir][m_PrevSelectedModuleIdx].data[y*moduleSize.width + x])
					{
						sprComponent = (SpriteComponent*)button->getComponent()->getComponent(CT_SPRITE);
						break;
					}
				}

				if (sprComponent)
				{
					cocos2d::Sprite* sprite = sprComponent->getSprite();

					m_ModuleSprites[y*moduleSize.width + x] = cocos2d::Sprite::createWithSpriteFrame(sprite->getSpriteFrame());
					m_ModuleSprites[y*moduleSize.width + x]->setPosition(300 + x*tileSize.width, 200 + y*tileSize.height);
					m_ModuleSprites[y*moduleSize.width + x]->setAnchorPoint(cocos2d::Point(0, 0));
					addChild(m_ModuleSprites[y*moduleSize.width + x]);
				}
			}
		}
	}
}
