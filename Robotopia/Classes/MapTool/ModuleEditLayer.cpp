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
#include "Floor.h"
#include "SpriteComponent.h"
#define MAP_CELL_START_X 350
#define MAP_CELL_START_Y (WINSIZE_HEIGHT - 80)
#define MAP_EDIT_START_X MAP_CELL_START_X
#define MAP_EDIT_START_Y(moduleHeight, tileHeight) (MAP_CELL_START_Y - (moduleHeight - 1)*tileHeight)

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

	initBoard();
	
	auto comButton = ComponentButton::create();

	comButton->setComponent(GET_COMPONENT_MANAGER()->createComponent<Block>());

	comButton->setPosition(cocos2d::Point(300, 60));

	m_ComponentList.push_back(comButton);

	addChild(comButton);

	auto comButton2 = ComponentButton::create();
	comButton2->setComponent(GET_COMPONENT_MANAGER()->createComponent<Floor>());
	comButton2->setPosition(cocos2d::Point(350, 60));

	m_ComponentList.push_back(comButton2);

	addChild(comButton2);

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

	tileSize.width *= 0.5;
	tileSize.height *= 0.5;

	verts[0] = cocos2d::Point(x, y);
	verts[1] = cocos2d::Point(x + tileSize.width, y);
	verts[2] = cocos2d::Point(x + tileSize.width, y + tileSize.height);
	verts[3] = cocos2d::Point(x, y + tileSize.height);

	node->drawPolygon(verts, 4, cocos2d::Color4F(cocos2d::Color4B(255, 255, 255, 255)),
							0.5, cocos2d::Color4F(cocos2d::Color4B(0, 0, 0, 255)));
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
	tileSize.width *= 0.5;
	tileSize.height *= 0.5;
	int cellX = (ev->getCursorX() - MAP_EDIT_START_X) / tileSize.width;
	int cellY = (WINSIZE_HEIGHT + ev->getCursorY() - MAP_EDIT_START_Y(moduleSize.height,tileSize.height)) / tileSize.height;

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
		m_ModuleSprites[cellIdx]->setPosition(MAP_CELL_START_X + cellX*tileSize.width, 
											MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + cellY*tileSize.height);
		m_ModuleSprites[cellIdx]->setAnchorPoint(cocos2d::Point(0, 0));
		m_ModuleSprites[cellIdx]->setScale(0.5);
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
	tileSize.width *= 0.5;
	tileSize.height *= 0.5;

	if (m_PrevSelectedModuleIdx == -1)
		return;

	for (int x = 0; x < moduleSize.width; x++)
	{
		for (int y = 0; y < moduleSize.height; y++)
		{
			int idx = y*moduleSize.width + x;

			if (data[dir][m_PrevSelectedModuleIdx].data[idx] != CT_NONE)
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
					m_ModuleSprites[y*moduleSize.width + x]->setPosition(MAP_EDIT_START_X + x*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + y*tileSize.height);
					m_ModuleSprites[y*moduleSize.width + x]->setAnchorPoint(cocos2d::Point(0, 0));
					m_ModuleSprites[y*moduleSize.width + x]->setScale(0.5);
					addChild(m_ModuleSprites[y*moduleSize.width + x]);
				}
			}
		}
	}
}

void Arthas::ModuleEditLayer::initBoard()
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	for (auto cell : m_Cells)
	{
		removeChild(cell);
	}

	m_Cells.clear();

	tileSize.width *= 0.5;
	tileSize.height *= 0.5;

	for (int x = 0; x < moduleSize.width; x++)
	{
		for (int y = 0; y < moduleSize.height; y++)
		{
			m_Cells.push_back(makeCell(MAP_CELL_START_X + x*tileSize.width, MAP_CELL_START_Y - y*tileSize.height));
			addChild(m_Cells[m_Cells.size()-1]);
		}
	}
}

void Arthas::ModuleEditLayer::initConnectedModule()
{
	for (auto sprite : m_ConnectedModuleSprites)
	{
		removeChild(sprite);
	}
	m_ConnectedModuleSprites.clear();

	auto layer = (ModuleListLayer*)getParent()->getChildByTag(TAG_MODULE_LIST_LAYER);

	//4방향 연결부 그리기
	if ((layer->getSortDir() & DIR_LEFT) == 0)
	{
		printConnectedModules(DIR_LEFT);
	}

	if ((layer->getSortDir() & DIR_UP) == 0)
	{
		printConnectedModules(DIR_UP);
	}

	if ((layer->getSortDir() & DIR_RIGHT) == 0)
	{
		printConnectedModules(DIR_RIGHT);
	}

	if ((layer->getSortDir() & DIR_DOWN) == 0)
	{
		printConnectedModules(DIR_DOWN);
	}
}

void Arthas::ModuleEditLayer::printConnectedModules(Direction dir)
{
	auto moduleDatas = GET_DATA_MANAGER()->getModuleDatas();
	Direction ignoreDir;

	switch (dir)
	{
	case DIR_LEFT:
		ignoreDir = DIR_RIGHT;
		break;
	case DIR_UP:
		ignoreDir = DIR_DOWN;
		break;
	case DIR_RIGHT:
		ignoreDir = DIR_LEFT;
		break;
	case DIR_DOWN:
		ignoreDir = DIR_UP;
		break;
	}

	for (int type = 0; type < 16; type++)
	{
		if ((type & ignoreDir) != 0)
		{
			continue;
		}

		for (auto module : moduleDatas[type])
		{
			switch (dir)
			{
			case DIR_LEFT:
				printLeftConnectedModule(module);
				break;
			case DIR_UP:
				printUpConnectedModule(module);
				break;
			case DIR_RIGHT:
				printRightConnectedModule(module);
				break;
			case DIR_DOWN:
				printDownConnectedModule(module);
				break;
			}

		}
	}
}

void Arthas::ModuleEditLayer::printLeftConnectedModule(ModuleData module)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	tileSize.width *= 0.5;
	tileSize.height *= 0.5;

	for (int y = 0; y < moduleSize.height; y++)
	{
		for (int x = moduleSize.width - 2; x < moduleSize.width; x++)
		{
			if (module.data[y*moduleSize.width + x] != CT_NONE)
			{
				printModuleSprite(module, x, y,
					MAP_EDIT_START_X + (x - moduleSize.width)*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + y*tileSize.height);
			}
		}
	}
}

void Arthas::ModuleEditLayer::printUpConnectedModule(ModuleData module)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	tileSize.width *= 0.5;
	tileSize.height *= 0.5;

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < moduleSize.width; x++)
		{
			if (module.data[y*moduleSize.width + x] != CT_NONE)
			{
				printModuleSprite(module, x, y,
					MAP_EDIT_START_X + x*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + (y + moduleSize.height)*tileSize.height);
			}
		}
	}
}

void Arthas::ModuleEditLayer::printRightConnectedModule(ModuleData module)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	tileSize.width *= 0.5;
	tileSize.height *= 0.5;

	for (int y = 0; y < moduleSize.height; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			if (module.data[y*moduleSize.width + x] != CT_NONE)
			{
				printModuleSprite(module, x, y,
					MAP_EDIT_START_X + (x + moduleSize.width)*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + y*tileSize.height);
			}
		}
	}
}

void Arthas::ModuleEditLayer::printDownConnectedModule(ModuleData module)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	tileSize.width *= 0.5;
	tileSize.height *= 0.5;

	for (int y = moduleSize.height - 2; y < moduleSize.height; y++)
	{
		for (int x = 0; x < moduleSize.width; x++)
		{
			if (module.data[y*moduleSize.width + x] != CT_NONE)
			{
				printModuleSprite(module, x, y,
					MAP_EDIT_START_X + x*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + (y - moduleSize.height)*tileSize.height);
			}
		}
	}
}

void Arthas::ModuleEditLayer::printModuleSprite(ModuleData module, int x, int y, float printX, float printY)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	SpriteComponent* sprComponent = nullptr;
	for (auto& button : m_ComponentList)
	{
		if (button->getComponent()->getType() == module.data[y*moduleSize.width + x])
		{
			sprComponent = (SpriteComponent*)button->getComponent()->getComponent(CT_SPRITE);
			break;
		}
	}

	if (sprComponent)
	{
		cocos2d::Sprite* sprite = sprComponent->getSprite();
		cocos2d::Sprite* newSprite = cocos2d::Sprite::createWithSpriteFrame(sprite->getSpriteFrame());

		newSprite->setPosition(printX, printY);
		newSprite->setAnchorPoint(cocos2d::Point(0, 0));
		newSprite->setScale(0.5);
		newSprite->setOpacity(32);
		m_ConnectedModuleSprites.push_back(newSprite);
		addChild(newSprite);
	}
}
