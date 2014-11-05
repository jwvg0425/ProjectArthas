#include "SpriteTool/ToolAppDelegate.h"
#include "SpriteTool/ToolScene.h"


#define WINSIZE_WIDTH 960
#define WINSIZE_HEIGHT 540

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
		glview = cocos2d::GLView::createWithRect("Robotopia",
												 cocos2d::Rect(0, 0, WINSIZE_WIDTH, WINSIZE_HEIGHT));
		director->setOpenGLView(glview);
	}

	srand((unsigned)time(NULL));
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / 60);
	director->runWithScene(Arthas::ToolScene::createScene());

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
