#pragma once
#include "cocos2d.h"
#include "Util.h"


class  ToolAppDelegate : private cocos2d::Application
{
public:
	ToolAppDelegate();
	virtual ~ToolAppDelegate();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
};
