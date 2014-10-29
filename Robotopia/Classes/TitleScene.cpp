#include "TitleScene.h"
#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene* TitleScene::createScene()
{
	TitleScene* scene = TitleScene::create();
	return scene;
}

bool TitleScene::init()
{
	auto layer = Layer::create();
	this->addChild( layer );
	auto playButton = MenuItemFont::create("PLAY", CC_CALLBACK_1( TitleScene::menuCallback , this ) );
	auto menu = Menu::create( playButton , NULL );
	layer->addChild( menu );
	return true;
}

void TitleScene::menuCallback( Ref* sender )
{
	Director::getInstance()->replaceScene( GameScene::createScene() );
}

