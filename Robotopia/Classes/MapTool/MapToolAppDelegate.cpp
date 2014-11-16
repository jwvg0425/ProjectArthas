#include "MapTool/MapToolAppDelegate.h"
#include "MapTool/MapToolScene.h"
#include "GameManager.h"
#include "DataManager.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
	GET_DATA_MANAGER()->saveModuleData();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = cocos2d::Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = cocos2d::GLView::createWithRect("Robotopia Map Tool",
			cocos2d::Rect(0, 0, WINSIZE_WIDTH, WINSIZE_HEIGHT));
		director->setOpenGLView(glview);
	}

	srand((unsigned)time(NULL));
	director->setDisplayStats(false);
	director->setAnimationInterval(1.0 / 60);
	director->runWithScene(MapToolScene::createScene());

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
