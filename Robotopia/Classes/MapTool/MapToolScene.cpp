#include "MapTool/MapToolScene.h"
#include "MapTool/DirectionButton.h"
#include "GameManager.h"
#include "InputManager.h"


cocos2d::Scene* Arthas::MapToolScene::createScene()
{
	Arthas::MapToolScene* scene = Arthas::MapToolScene::create();
	return scene;
}

bool Arthas::MapToolScene::init()
{
	auto layer = cocos2d::Layer::create();
	this->addChild(layer);
	GET_INPUT_MANAGER()->receiveKeyboardData(layer);
	for (int i = 1, j = 0; i <= 8; i *= 2, j++)
	{
		auto button = DirectionButton::create();

		button->setTarget(&m_SortDir);
		button->setDirection((DirectionBit)i);

		button->setPosition(cocos2d::Point(30 + j*50, 50));

		addChild(button);
	}

	return true;
}