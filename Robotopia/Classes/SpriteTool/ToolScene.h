/************************************************************************/
/*
CLASS			: SpriteToolScene
Author			: 김성연
역할				: SpirteTool관련 layer를 담는 scene
최종 수정일자		: 2014-11-03
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Util.h"

BEGIN_NS_AT

class ToolSpriteEditLayer;
class ToolAniPlayLayer;
class ToolScene : cocos2d::Scene
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);

	static cocos2d::Scene*	    createScene();
	CREATE_FUNC(ToolScene);

	enum LayerType
	{
		SPRITE_EDIT_LAYER,
		ANI_PLAY_LAYER,
	};

private:
	ToolSpriteEditLayer* m_EditLayer;
	ToolAniPlayLayer*	 m_AniLayer;

};

END_NS_AT