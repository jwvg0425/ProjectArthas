#include "SpriteTool/ToolScene.h"




bool Arthas::ToolScene::init()
{
	return true;
}

void Arthas::ToolScene::update(float dTime)
{

}

cocos2d::Scene* Arthas::ToolScene::createScene()
{
	cocos2d::Scene* scene = cocos2d::Scene::createWithPhysics();
	cocos2d::Vect gravity = cocos2d::Vect(0.0f, 0.0f);
	scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(gravity);

	Arthas::ToolScene* layer = Arthas::ToolScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer, NULL, GAME_SCENE_TAG);

	return scene;
}
