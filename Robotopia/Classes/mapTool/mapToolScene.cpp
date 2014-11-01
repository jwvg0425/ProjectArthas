#include "mapToolScene.h"

cocos2d::Scene* Arthas::MapToolScene::createScene()
{
	MapToolScene* scene = Arthas::MapToolScene::create();
	return scene;
}

bool Arthas::MapToolScene::init()
{
	auto layer = cocos2d::Layer::create();
	this->addChild(layer);

	return true;
}
