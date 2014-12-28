#include "ModuleEditLayer.h"
#include "MapToolAppDelegate.h"
#include "MapToolScene.h"
#include "ModuleListLayer.h"
#include "BaseComponent.h"
#include "ComponentButton.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "ResourceManager.h"
#include "MovingBlock.h"
#include "Block.h"
#include "Floor.h"
#include "SpriteComponent.h"
#define MAP_CELL_START_X 350
#define MAP_CELL_START_Y (WINSIZE_HEIGHT - 80)
#define MAP_EDIT_START_X MAP_CELL_START_X
#define MAP_EDIT_START_Y(moduleHeight, tileHeight) (MAP_CELL_START_Y - (moduleHeight - 1)*tileHeight)
#define MAP_EDIT_BUTTON_START_X 300
#define MAP_EDIT_BUTTON_START_Y 30
#define MAP_EDIT_BUTTON_SPLIT 50

bool ModuleEditLayer::init()
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
	comButton->setType(RT_BLOCK);
	comButton->setPosition(cocos2d::Point(300, 30));
	m_ComponentList.push_back(comButton);
	addChild(comButton);

	auto comButton2 = ComponentButton::create();
	comButton2->setType(RT_FLOOR);
	comButton2->setPosition(cocos2d::Point(350, 30));
	addChild(comButton2);
	m_ComponentList.push_back(comButton2);

	auto comButton3 = ComponentButton::create();
	comButton3->setType(RT_PORTAL);
	comButton3->setPosition(cocos2d::Point(400, 30));
	addChild(comButton3);
	m_ComponentList.push_back(comButton3);

	auto comButton4 = ComponentButton::create();
	comButton4->setType(RT_BLOCK_RANDOM);
	comButton4->setPosition(cocos2d::Point(450, 30));
	addChild(comButton4);
	m_ComponentList.push_back(comButton4);

	auto comButton5 = ComponentButton::create();
	comButton5->setType(RT_FLOOR_RANDOM);
	comButton5->setPosition(cocos2d::Point(500, 30));
	addChild(comButton5);
	m_ComponentList.push_back(comButton5);

	auto comButton6 = ComponentButton::create();
	comButton6->setType(RT_MONSTER_RUSH);
	comButton6->setPosition(cocos2d::Point(550, 30));
	addChild(comButton6);
	m_ComponentList.push_back(comButton6);

	auto comButton7 = ComponentButton::create();
	comButton7->setType(RT_STAGE_PORTAL);
	comButton7->setPosition(cocos2d::Point(600, 30));
	addChild(comButton7);
	m_ComponentList.push_back(comButton7);

	auto comButton8 = ComponentButton::create();
	comButton8->setType(RT_LASER_1);
	comButton8->setPosition(cocos2d::Point(650, 30));
	addChild(comButton8);
	m_ComponentList.push_back(comButton8);

	auto comButton9 = ComponentButton::create();
	comButton9->setType(RT_LASER_2);
	comButton9->setPosition(cocos2d::Point(700, 30));
	addChild(comButton9);
	m_ComponentList.push_back(comButton9);

	auto comButton10 = ComponentButton::create();
	comButton10->setType(RT_LASER_3);
	comButton10->setPosition(cocos2d::Point(750, 30));
	addChild(comButton10);
	m_ComponentList.push_back(comButton10);

	auto comButton11 = ComponentButton::create();
	comButton11->setType(RT_ELECTRIC);
	comButton11->setPosition(cocos2d::Point(800, 30));
	addChild(comButton11);
	m_ComponentList.push_back(comButton11);

	auto comButton12 = ComponentButton::create();
	comButton12->setType(RT_COMPUTER);
	comButton12->setPosition(cocos2d::Point(850, 30));
	addChild(comButton12);
	m_ComponentList.push_back(comButton12);
	
	auto comButton13 = ComponentButton::create();
	comButton13->setType(RT_MONSTER_PLANT);
	comButton13->setPosition(cocos2d::Point(900, 30));
	addChild(comButton13);
	m_ComponentList.push_back(comButton13);

	auto comButton14 = ComponentButton::create();
	comButton14->setType(RT_MONSTER_DEVIL);
	comButton14->setPosition(cocos2d::Point(950, 30));
	addChild(comButton14);
	m_ComponentList.push_back(comButton14);

	auto comButton15 = ComponentButton::create();
	comButton15->setType(RT_MONSTER_BOSS_FIRST);
	comButton15->setPosition(cocos2d::Point(300, 70));
	addChild(comButton15);
	m_ComponentList.push_back(comButton15);

	auto comButton16 = ComponentButton::create();
	comButton16->setType(RT_VENDING_MACHINE);
	comButton16->setPosition(cocos2d::Point(350, 70));
	addChild(comButton16);
	m_ComponentList.push_back(comButton16);

	auto comButton17 = ComponentButton::create();
	comButton17->setType(RT_LEVER);
	comButton17->setPosition(cocos2d::Point(400, 70));
	addChild(comButton17);
	m_ComponentList.push_back(comButton17);

	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(ModuleEditLayer::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(ModuleEditLayer::onMouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(ModuleEditLayer::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	scheduleUpdate();

	return true;
}

cocos2d::DrawNode* ModuleEditLayer::makeCell(float x, float y)
{
	cocos2d::DrawNode* node = cocos2d::DrawNode::create();
	cocos2d::Point verts[4];
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	tileSize.width *= 0.25;
	tileSize.height *= 0.25;

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

void ModuleEditLayer::setSelectedIdx(cocos2d::Sprite* sprite)
{
	for (int i = 0; i < m_ComponentList.size(); i++)
	{
		if (m_ComponentList[i]->getSprite() == sprite)
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

void ModuleEditLayer::onMouseDown(cocos2d::Event* event)
{
	m_IsMouseDown = true;
}

void ModuleEditLayer::onMouseMove(cocos2d::Event* event)
{

	if (!m_IsMouseDown || m_PrevSelectedModuleIdx == -1)
		return;

	cocos2d::EventMouse* ev = (cocos2d::EventMouse*)event;

	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	tileSize.width *= 0.25;
	tileSize.height *= 0.25;
	int cellX = (ev->getCursorX() - MAP_EDIT_START_X) / tileSize.width;
	int cellY = (WINSIZE_HEIGHT + ev->getCursorY() - MAP_EDIT_START_Y(moduleSize.height,tileSize.height)) / tileSize.height;

	if (cellX < 0 || cellX >= moduleSize.width ||
		cellY < 0 || cellY >= moduleSize.height)
		return;

	int cellIdx = cellY*moduleSize.width + cellX;

	auto layer = (ModuleListLayer*)getParent()->getChildByTag(TAG_MODULE_LIST_LAYER);
	Direction dir = layer->getSortDir();
	auto data = GET_DATA_MANAGER()->getModuleDatas();
	
	if (ev->getMouseButton() == MOUSE_BUTTON_LEFT &&  m_SelectedComponentIdx != -1)
	{
		if (m_ModuleSprites.find(cellIdx) != m_ModuleSprites.end())
		{
			removeChild(m_ModuleSprites[cellIdx]);
			m_ModuleSprites.erase(cellIdx);
		}
		cocos2d::Sprite* sprite = m_ComponentList[m_SelectedComponentIdx]->getSprite();

		m_ModuleSprites[cellIdx] = cocos2d::Sprite::createWithSpriteFrame(sprite->getSpriteFrame());
		m_ModuleSprites[cellIdx]->setPosition(MAP_CELL_START_X + cellX*tileSize.width, 
											MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + cellY*tileSize.height);
		m_ModuleSprites[cellIdx]->setAnchorPoint(cocos2d::Point(0, 0));
		m_ModuleSprites[cellIdx]->setScale(0.25);
		addChild(m_ModuleSprites[cellIdx]);

		data[dir][m_PrevSelectedModuleIdx].m_Data[cellIdx] = m_ComponentList[m_SelectedComponentIdx]->getType();
	}
	else if(ev->getMouseButton() == MOUSE_BUTTON_RIGHT)
	{
		if (m_ModuleSprites.find(cellIdx) != m_ModuleSprites.end())
		{
			removeChild(m_ModuleSprites[cellIdx]);
			m_ModuleSprites.erase(cellIdx);
		}
		data[dir][m_PrevSelectedModuleIdx].m_Data[cellIdx] = RT_NONE;
	}
}

void ModuleEditLayer::onMouseUp(cocos2d::Event* event)
{
	m_IsMouseDown = false;
}

void ModuleEditLayer::update(float dTime)
{
	auto layer = (ModuleListLayer*)getParent()->getChildByTag(TAG_MODULE_LIST_LAYER);

	if (layer->getSelectedIdx() != m_PrevSelectedModuleIdx)
	{
		m_PrevSelectedModuleIdx = layer->getSelectedIdx();
		initPrintedModule();
	}
}

void ModuleEditLayer::initPrintedModule()
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
	tileSize.width *= 0.25;
	tileSize.height *= 0.25;

	if (m_PrevSelectedModuleIdx == -1)
		return;

	for (int x = 0; x < moduleSize.width; x++)
	{
		for (int y = 0; y < moduleSize.height; y++)
		{
			int idx = y*moduleSize.width + x;

			if (data[dir][m_PrevSelectedModuleIdx].m_Data[idx] != CT_NONE)
			{
				cocos2d::Sprite* sprite = nullptr;
				for (auto& button : m_ComponentList)
				{
					if (button->getType() == data[dir][m_PrevSelectedModuleIdx].m_Data[y*moduleSize.width + x])
					{
						sprite = button->getSprite();
						break;
					}
				}

				if (sprite)
				{

					m_ModuleSprites[y*moduleSize.width + x] = cocos2d::Sprite::createWithSpriteFrame(sprite->getSpriteFrame());
					m_ModuleSprites[y*moduleSize.width + x]->setPosition(MAP_EDIT_START_X + x*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + y*tileSize.height);
					m_ModuleSprites[y*moduleSize.width + x]->setAnchorPoint(cocos2d::Point(0, 0));
					m_ModuleSprites[y*moduleSize.width + x]->setScale(0.25);
					addChild(m_ModuleSprites[y*moduleSize.width + x]);
				}
			}
		}
	}
}

void ModuleEditLayer::initBoard()
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	for (auto cell : m_Cells)
	{
		removeChild(cell);
	}

	m_Cells.clear();

	tileSize.width *= 0.25;
	tileSize.height *= 0.25;

	for (int x = 0; x < moduleSize.width; x++)
	{
		for (int y = 0; y < moduleSize.height; y++)
		{
			m_Cells.push_back(makeCell(MAP_CELL_START_X + x*tileSize.width, MAP_CELL_START_Y - y*tileSize.height));
			addChild(m_Cells[m_Cells.size()-1]);
		}
	}
}

void ModuleEditLayer::initConnectedModule()
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

void ModuleEditLayer::printConnectedModules(Direction dir)
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

void ModuleEditLayer::printLeftConnectedModule(ModuleData module)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	tileSize.width *= 0.25;
	tileSize.height *= 0.25;
	
	for (int y = 0; y < moduleSize.height; y++)
	{
		for (int x = moduleSize.width - 2; x < moduleSize.width; x++)
		{
			if (module.m_Data[y*moduleSize.width + x] != CT_NONE)
			{
				printModuleSprite(module, x, y,
					MAP_EDIT_START_X + (x - moduleSize.width)*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + y*tileSize.height);
			}
		}
	}
}

void ModuleEditLayer::printUpConnectedModule(ModuleData module)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	tileSize.width *= 0.25;
	tileSize.height *= 0.25;

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < moduleSize.width; x++)
		{
			if (module.m_Data[y*moduleSize.width + x] != CT_NONE)
			{
				printModuleSprite(module, x, y,
					MAP_EDIT_START_X + x*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + (y + moduleSize.height)*tileSize.height);
			}
		}
	}
}

void ModuleEditLayer::printRightConnectedModule(ModuleData module)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	tileSize.width *= 0.25;
	tileSize.height *= 0.25;

	for (int y = 0; y < moduleSize.height; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			if (module.m_Data[y*moduleSize.width + x] != CT_NONE)
			{
				printModuleSprite(module, x, y,
					MAP_EDIT_START_X + (x + moduleSize.width)*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + y*tileSize.height);
			}
		}
	}
}

void ModuleEditLayer::printDownConnectedModule(ModuleData module)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	tileSize.width *= 0.25;
	tileSize.height *= 0.25;

	for (int y = moduleSize.height - 2; y < moduleSize.height; y++)
	{
		for (int x = 0; x < moduleSize.width; x++)
		{
			if (module.m_Data[y*moduleSize.width + x] != CT_NONE)
			{
				printModuleSprite(module, x, y,
					MAP_EDIT_START_X + x*tileSize.width, MAP_EDIT_START_Y(moduleSize.height, tileSize.height) + (y - moduleSize.height)*tileSize.height);
			}
		}
	}
}

void ModuleEditLayer::printModuleSprite(ModuleData module, int x, int y, float printX, float printY)
{
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Sprite* sprite = nullptr;
	for (auto& button : m_ComponentList)
	{
		if (button->getType() == module.m_Data[y*moduleSize.width + x])
		{
			sprite = button->getSprite();
			break;
		}
	}

	if (sprite)
	{
		cocos2d::Sprite* newSprite = cocos2d::Sprite::createWithSpriteFrame(sprite->getSpriteFrame());

		newSprite->setPosition(printX, printY);
		newSprite->setAnchorPoint(cocos2d::Point(0, 0));
		newSprite->setScale(0.25);
		newSprite->setOpacity(64);
		m_ConnectedModuleSprites.push_back(newSprite);
		addChild(newSprite);
	}
}
