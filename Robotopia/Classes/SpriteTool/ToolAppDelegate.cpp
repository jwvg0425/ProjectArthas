#include "pch.h"

#include "SpriteTool/ToolAppDelegate.h"
#include "SpriteTool/ToolScene.h"


#define WINSIZE_WIDTH 1280
#define WINSIZE_HEIGHT 640

ToolAppDelegate::ToolAppDelegate()
{

}

ToolAppDelegate::~ToolAppDelegate()
{
}

bool ToolAppDelegate::applicationDidFinishLaunching()
{
	auto director = cocos2d::Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = cocos2d::GLView::createWithRect("Robotopia Sprite Tool",
												 cocos2d::Rect(0, 0, WINSIZE_WIDTH, WINSIZE_HEIGHT));
		director->setOpenGLView(glview);
	}

	srand((unsigned)time(NULL));
	director->setDisplayStats(false);
	director->setAnimationInterval(1.0 / 60);
	director->runWithScene(ToolScene::createScene());

	return true;
}

void ToolAppDelegate::applicationDidEnterBackground()
{
	cocos2d::Director::getInstance()->stopAnimation();
}

void ToolAppDelegate::applicationWillEnterForeground()
{
	cocos2d::Director::getInstance()->startAnimation();
}
