#include "AppDelegate.h"
#include "TitleScene.h"
#include "GameManager.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = cocos2d::GLView::createWithRect( "robotopiaPrototype" ,
										 cocos2d::Rect( 0 , 0 , 960 , 540 ) );
        director->setOpenGLView(glview);
    }

	srand( (unsigned)time( NULL ) );
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
	director->runWithScene( Arthas::TitleScene::createScene() );

	//test code
	GET_DATA_MANAGER();
	
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    cocos2d::Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    cocos2d::Director::getInstance()->startAnimation();
}
