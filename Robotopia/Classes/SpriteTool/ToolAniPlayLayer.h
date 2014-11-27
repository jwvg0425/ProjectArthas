/************************************************************************/
/*
CLASS			: ToolSpriteListLayer
Author			: 김성연
역할				: 현재 저장된 Sprite의 list 및 정보를 보여주는 레이어
최종 수정일자		: 2014-11-08
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Util.h"
#include <vector>



class ToolAniPlayLayer : public cocos2d::Layer
{
public:
	OVERRIDE bool init();
	void		  playCallBack(cocos2d::Ref* sender);
	void		  stopCallBack(cocos2d::Ref* sender);
	void		  flipCallBack(cocos2d::Ref* sender);
	void		  sprCallBack(cocos2d::Ref* sender);

	CREATE_FUNC(ToolAniPlayLayer);

private:
	cocos2d::Sprite*		   m_MainSpr;
	cocos2d::Sprite*		   m_NoExist;
	bool					   isFlipped;
	AnimationInfo			   m_AniInfo;
	SpriteInfo				   m_SprInfo;
	AnimationType			   m_CurrentAniType;
	SpriteType				   m_CurrentSprType;
	
};



