#include "SpriteTool/ToolScene.h"
#include "SpriteTool/ToolSpriteEditLayer.h"





bool Arthas::ToolScene::init()
{
	if (!cocos2d::Scene::init())
	{
		return false;
	}

	m_EditLayer = ToolSpriteEditLayer::create();
	this->addChild(m_EditLayer);
	//auto layer = SpriteListLayer::create();
	//this->addChild(layer, 0, Sprite);

	//auto editLayer = ModuleEditLayer::create();
	//this->addChild(editLayer);

	scheduleUpdate();

	return true;
}


cocos2d::Scene* Arthas::ToolScene::createScene()
{
	ToolScene* scene = ToolScene::create();

	return scene;
}

void Arthas::ToolScene::update(float dTime)
{
	m_EditLayer->update(dTime);
}
