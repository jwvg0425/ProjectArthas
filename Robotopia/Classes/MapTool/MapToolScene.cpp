#include "MapTool/MapToolScene.h"
#include "MapTool/DirectionButton.h"
#include "MapTool/ModuleListLayer.h"


cocos2d::Scene* Arthas::MapToolScene::createScene()
{
	Arthas::MapToolScene* scene = Arthas::MapToolScene::create();
	return scene;
}

bool Arthas::MapToolScene::init()
{
	auto layer = ModuleListLayer::create();
	this->addChild(layer);

	return true;
}