#include "MapTool/MapToolScene.h"
#include "MapTool/DirectionButton.h"
#include "MapTool/ModuleListLayer.h"
#include "ModuleEditLayer.h"


cocos2d::Scene* MapToolScene::createScene()
{
	MapToolScene* scene = MapToolScene::create();
	return scene;
}

bool MapToolScene::init()
{
	auto layer = ModuleListLayer::create();
	this->addChild(layer, 0, TAG_MODULE_LIST_LAYER);

	auto editLayer = ModuleEditLayer::create();
	this->addChild(editLayer, 0, TAG_MODULE_EDIT_LAYER);

	return true;
}