#include "pch.h"
#include "AppDelegate.h"
#include "TitleScene.h"
#include "GameManager.h"
#include "UIManager.h"
#include "StageManager.h"
#include "Util.h"

#define WINSIZE_WIDTH 960
#define WINSIZE_HEIGHT 540

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
		glview = cocos2d::GLView::createWithRect( "Robotopia" ,
										 cocos2d::Rect( 0 , 0 , WINSIZE_WIDTH , WINSIZE_HEIGHT ) );
        director->setOpenGLView(glview);
    }

	srand( (unsigned)time( NULL ) );
#ifdef _DEBUG
    director->setDisplayStats(true);
#else
	director->setDisplayStats(false);
#endif
    director->setAnimationInterval(1.0 / 60);
	GET_GAME_MANAGER()->changeScene(Arthas::TitleScene::createScene(), Arthas::SceneType::TITLE_SCENE);

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
