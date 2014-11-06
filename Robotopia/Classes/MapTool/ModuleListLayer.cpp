#include "MapTool/DirectionButton.h"
#include "ModuleListLayer.h"
#include "GameManager.h"
#include "InputManager.h"
#include "DataManager.h"
#include "MapTool/ModuleButton.h"
#include "MapTool/MapToolAppDelegate.h"

bool Arthas::ModuleListLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	m_SortDir = DIR_NONE;
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

	auto item = cocos2d::MenuItemFont::create("create", CC_CALLBACK_1(Arthas::ModuleListLayer::createButtonCallback,this));
	auto menu = cocos2d::Menu::create(item, nullptr);

	menu->setPosition(50, 20);
	addChild(menu);

	scheduleUpdate();
	
	return true;

}

void Arthas::ModuleListLayer::update(float dTime)
{
	if (m_NextSortDir != m_SortDir)
	{
		m_SortDir = m_NextSortDir;
		m_SelectedIdx = -1;
		initModuleList();
	}
}

void Arthas::ModuleListLayer::initModuleList()
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

void Arthas::ModuleListLayer::createButtonCallback(Ref* sender)
{
	ModuleData data;
	char buffer[256];

	sprintf(buffer, "module_%d_%d", m_SortDir, GET_DATA_MANAGER()->getModuleDatas()[m_SortDir].size());

	data.name = buffer;
	data.data.clear();

	auto moduleDatas = GET_DATA_MANAGER()->getModuleDatas();

	moduleDatas[m_SortDir].push_back(data);
	initModuleList();
	if (m_SelectedIdx != -1)
	{
		setSelectedIdx(&moduleDatas[m_SortDir][m_SelectedIdx]);
	}
}

void Arthas::ModuleListLayer::setSelectedIdx(ModuleData* data)
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
