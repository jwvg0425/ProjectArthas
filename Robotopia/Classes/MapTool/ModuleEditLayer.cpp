#include "ModuleEditLayer.h"
#include "Component.h"

bool Arthas::ModuleEditLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	return true;
}
