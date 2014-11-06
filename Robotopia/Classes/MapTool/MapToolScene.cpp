#include "MapTool/MapToolScene.h"
#include "MapTool/DirectionButton.h"
#include "MapTool/ModuleListLayer.h"
#include "ModuleEditLayer.h"


cocos2d::Scene* Arthas::MapToolScene::createScene()
{
	Arthas::MapToolScene* scene = Arthas::MapToolScene::create();
	return scene;
}

bool Arthas::MapToolScene::init()
{
	auto layer = ModuleListLayer::create();
	this->addChild(layer, 0, TAG_MODULE_LIST_LAYER);

	auto editLayer = ModuleEditLayer::create();
	this->addChild(editLayer);

	return true;
}