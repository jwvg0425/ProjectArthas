#pragma once
#include "cocos2d.h"
#include "Util.h"

BEGIN_NS_AT

class MapToolScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	OVERRIDE bool			init();

	CREATE_FUNC(MapToolScene);
};

END_NS_AT