#pragma once
#include "cocos2d.h"
#include "Util.h"
#include "ToolApplication.h"
#define WINSIZE_WIDTH 960
#define WINSIZE_HEIGHT 540


class  AppDelegate : private ToolApplication
{
public:
	AppDelegate();
	virtual ~AppDelegate();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
};
