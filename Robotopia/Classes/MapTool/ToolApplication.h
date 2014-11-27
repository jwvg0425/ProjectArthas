#pragma once

#include "cocos2d.h"
#include "Util.h"


class ToolApplication : public cocos2d::Application
{
public:
	ToolApplication();
	OVERRIDE ~ToolApplication();

	static ToolApplication* getInstance();

	HINSTANCE getWindowHandle();
private:
	static ToolApplication* sm_pSharedApplication;
};