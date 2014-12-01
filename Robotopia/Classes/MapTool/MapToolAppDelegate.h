#pragma once
#include "cocos2d.h"
#include "Util.h"
#define WINSIZE_WIDTH 960
#define WINSIZE_HEIGHT 540


class  AppDelegate : private cocos2d::Application
{
public:
	AppDelegate();
	virtual ~AppDelegate();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
};
