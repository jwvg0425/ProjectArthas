#include "SpriteTool/ToolScene.h"




bool Arthas::ToolScene::init()
{
	if (!cocos2d::Scene::init())
	{
		return false;
	}

	//auto layer = SpriteListLayer::create();
	//this->addChild(layer, 0, Sprite);

	//auto editLayer = ModuleEditLayer::create();
	//this->addChild(editLayer);
	//return true;
}


cocos2d::Scene* Arthas::ToolScene::createScene()
{
	ToolScene* scene = ToolScene::create();

	return scene;
}
