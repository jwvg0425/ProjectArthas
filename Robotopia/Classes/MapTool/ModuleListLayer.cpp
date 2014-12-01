#include "MapTool/DirectionButton.h"
#include "ModuleListLayer.h"
#include "ModuleEditLayer.h"
#include "MapToolScene.h"
#include "GameManager.h"
#include "InputManager.h"
#include "DataManager.h"
#include "MapTool/ModuleButton.h"
#include "MapTool/MapToolAppDelegate.h"

bool ModuleListLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	m_SortDir = (Direction)-1;
	m_NextSortDir = DIR_NONE;
	m_ModuleList.clear();
	m_SelectedIdx = -1;

	GET_INPUT_MANAGER()->receiveKeyboardData(this);
	for (int i = 1, j = 0; i <= 8; i *= 2, j++)
	{
		auto button = DirectionButton::create();

		button->setTarget(&m_NextSortDir);
		button->setDirection((DirectionBit)i);

		button->setPosition(cocos2d::Point(30 + j * 50, 50));

		addChild(button);
	}



	auto item = cocos2d::MenuItemFont::create("create", CC_CALLBACK_1(ModuleListLayer::createButtonCallback,this));
	auto item2 = cocos2d::MenuItemFont::create("delete", CC_CALLBACK_1(ModuleListLayer::deleteButtonCallback, this));
	auto menu = cocos2d::Menu::create(item, item2, nullptr);

	auto plus = cocos2d::MenuItemFont::create("+", CC_CALLBACK_1(ModuleListLayer::moduleSizeButtonCallback, this));
	plus->setName("plus");
	auto minus = cocos2d::MenuItemFont::create("-", CC_CALLBACK_1(ModuleListLayer::moduleSizeButtonCallback, this));
	minus->setName("minus");

	auto buttonMenu = cocos2d::Menu::create(plus, minus, nullptr);
	buttonMenu->setPosition(600, 60);
	buttonMenu->alignItemsHorizontally();
	addChild(buttonMenu);

	auto normal = cocos2d::MenuItemFont::create("normal", CC_CALLBACK_1(ModuleListLayer::typeCallback, this));
	normal->setName("normal");

	auto special = cocos2d::MenuItemFont::create("special", CC_CALLBACK_1(ModuleListLayer::typeCallback, this));
	special->setName("special");

	auto lift = cocos2d::MenuItemFont::create("lift", CC_CALLBACK_1(ModuleListLayer::typeCallback, this));
	lift->setName("lift");

	auto city = cocos2d::MenuItemFont::create("city", CC_CALLBACK_1(ModuleListLayer::typeCallback, this));
	city->setName("city");

	auto typeMenu = cocos2d::Menu::create(normal, special, lift, city, nullptr);
	typeMenu->setScale(0.5);
	typeMenu->setPosition(600, 80);
	typeMenu->alignItemsHorizontally();
	addChild(typeMenu);

	menu->setPosition(100, 20);
	menu->alignItemsHorizontally();
	addChild(menu);

	m_ModuleSizeLabel = cocos2d::Label::create("20", "Thonburi", 15);
	m_ModuleSizeLabel->setPosition(600, 80);
	addChild(m_ModuleSizeLabel);
	m_TypeLabel = cocos2d::Label::create("-", "Thonburi", 15);
	m_TypeLabel->setPosition(800, 120);
	addChild(m_TypeLabel);

	scheduleUpdate();
	
	return true;

}

void ModuleListLayer::update(float dTime)
{
	if (m_NextSortDir != m_SortDir)
	{
		auto layer = (ModuleEditLayer*)getParent()->getChildByTag(TAG_MODULE_EDIT_LAYER);
		m_SortDir = m_NextSortDir;
		m_SelectedIdx = -1;
		initModuleList();
		layer->initConnectedModule();
	}

	if (m_SelectedIdx != -1)
	{
		auto moduleDatas = GET_DATA_MANAGER()->getModuleDatas();

		switch (moduleDatas[m_SortDir][m_SelectedIdx].m_Type)
		{
		case RoomConfig::NORMAL:
			m_TypeLabel->setString("normal");
			break;
		case RoomConfig::SPECIAL:
			m_TypeLabel->setString("special");
			break;
		case RoomConfig::LIFT:
			m_TypeLabel->setString("lift");
			break;
		case RoomConfig::CITY:
			m_TypeLabel->setString("city");
			break;
		}
	}
	else
	{
		m_TypeLabel->setString("-");
	}
}

void ModuleListLayer::initModuleList()
{
	for (auto& button : m_ModuleList)
	{
		removeChild(button);
	}
	m_ModuleList.clear();
	auto moduleDatas = GET_DATA_MANAGER()->getModuleDatas();

	for (int i = 0; i < moduleDatas[m_SortDir].size(); i++)
	{
		auto button = ModuleButton::create();
		button->setModule(&moduleDatas[m_SortDir][i]);
		button->setPosition(70, WINSIZE_HEIGHT - 50 - 20 * i);
		m_ModuleList.push_back(button);
		addChild(button);
	}
}

void ModuleListLayer::createButtonCallback(Ref* sender)
{
	ModuleData data;
	char buffer[256];

	sprintf(buffer, "module_%d_%d", m_SortDir, GET_DATA_MANAGER()->getModuleDatas()[m_SortDir].size());

	data.m_Name = buffer;
	data.m_Data.clear();

	auto moduleDatas = GET_DATA_MANAGER()->getModuleDatas();
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();

	data.m_Data.resize(moduleSize.width*moduleSize.width);

	moduleDatas[m_SortDir].push_back(data);
	
	initModuleList();
	if (m_SelectedIdx != -1)
	{
		setSelectedIdx(&moduleDatas[m_SortDir][m_SelectedIdx]);
	}
}

void ModuleListLayer::setSelectedIdx(ModuleData* data)
{
	for (int i = 0; i< m_ModuleList.size();i++)
	{
		if (m_ModuleList[i]->getModule() == data)
		{
			m_ModuleList[i]->getLabel()->setColor(cocos2d::Color3B(255, 0, 0));
			m_SelectedIdx = i;
		}
		else
		{
			m_ModuleList[i]->getLabel()->setColor(cocos2d::Color3B(255, 255, 255));
		}
	}
}

int ModuleListLayer::getSelectedIdx()
{
	return m_SelectedIdx;
}

Direction ModuleListLayer::getSortDir()
{
	return m_SortDir;
}

void ModuleListLayer::deleteButtonCallback(Ref* sender)
{
	if (m_SelectedIdx == -1)
		return;

	auto moduleDatas = GET_DATA_MANAGER()->getModuleDatas();

	moduleDatas[m_SortDir].erase(moduleDatas[m_SortDir].begin() + m_SelectedIdx);
	initModuleList();
	m_SelectedIdx = -1;
}

void ModuleListLayer::moduleSizeButtonCallback(Ref* sender)
{
	auto item = (cocos2d::MenuItemFont*)sender;
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size prevSize = moduleSize;
	char buf[30];

	if (item->getName() == "plus")
	{
		moduleSize.width += 1;
		moduleSize.height += 1;

		GET_DATA_MANAGER()->setModuleSize(moduleSize);
	}
	else
	{
		moduleSize.width -= 1;
		moduleSize.height -= 1;

		GET_DATA_MANAGER()->setModuleSize(moduleSize);
	}

	sprintf(buf, "%d", (int)moduleSize.width);

	m_ModuleSizeLabel->setString(buf);
	resizeData(prevSize);
}

void ModuleListLayer::resizeData(cocos2d::Size prevSize)
{
	auto moduleDatas = GET_DATA_MANAGER()->getModuleDatas();
	cocos2d::Size moduleSize = GET_DATA_MANAGER()->getModuleSize();
	int size = moduleSize.width*moduleSize.height;
	ModuleEditLayer* editLayer = (ModuleEditLayer*)getParent()->getChildByTag(TAG_MODULE_EDIT_LAYER);

	for (int type = 0; type < 16; type++)
	{
		for (int idx = 0; idx < moduleDatas[type].size(); idx++)
		{
			auto prevData = moduleDatas[type][idx].m_Data;

			moduleDatas[type][idx].m_Data.clear();
			moduleDatas[type][idx].m_Data.resize(size);

			for (int y = 0; y< prevSize.height; y++)
			{
				for (int x = 0; x < prevSize.width; x++)
				{
					if (y*moduleSize.width + x >= size)
						continue;

					moduleDatas[type][idx].m_Data[y*moduleSize.width + x] = prevData[y*prevSize.width + x];
				}
			}
		}
	}
	editLayer->initBoard();
	editLayer->initPrintedModule();
}

void ModuleListLayer::typeCallback(Ref* sender)
{
	auto moduleDatas = GET_DATA_MANAGER()->getModuleDatas();

	if (m_SelectedIdx == -1)
		return;

	auto item = (cocos2d::MenuItemFont*)sender;

	if (item->getName() == "normal")
	{
		moduleDatas[m_SortDir][m_SelectedIdx].m_Type = RoomConfig::NORMAL;
	}
	else if (item->getName() == "special")
	{
		moduleDatas[m_SortDir][m_SelectedIdx].m_Type = RoomConfig::SPECIAL;
	}
	else if (item->getName() == "lift")
	{
		moduleDatas[m_SortDir][m_SelectedIdx].m_Type = RoomConfig::LIFT;
	}
	else if (item->getName() == "city")
	{
		moduleDatas[m_SortDir][m_SelectedIdx].m_Type = RoomConfig::CITY;
	}
}
