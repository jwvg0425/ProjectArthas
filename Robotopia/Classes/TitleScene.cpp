#include "TitleScene.h"
#include "GameScene.h"

cocos2d::Scene* Arthas::TitleScene::createScene()
{
	Arthas::TitleScene* scene = Arthas::TitleScene::create();
	return scene;
}

bool Arthas::TitleScene::init()
{
	auto layer = cocos2d::Layer::create();
	this->addChild( layer );
	auto playButton = cocos2d::MenuItemFont::create("PLAY", CC_CALLBACK_1( TitleScene::menuCallback , this ) );
	auto menu = cocos2d::Menu::create( playButton , NULL );
	layer->addChild( menu );
	return true;
}

void Arthas::TitleScene::menuCallback( cocos2d::Ref* sender )
{
	cocos2d::Director::getInstance()->replaceScene( Arthas::GameScene::createScene() );
}

