/************************************************************************/
/*
CLASS			: MapToolScene
Author			: 남현욱
역할				: 맵툴 처리 담당 씬.
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			: 
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Util.h"
#define TAG_MODULE_EDIT_LAYER 1
#define TAG_MODULE_LIST_LAYER 2



class MapToolScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	OVERRIDE bool			init();

	CREATE_FUNC(MapToolScene);
private:
};

