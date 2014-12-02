/************************************************************************/
/*
CLASS			: SkillLineLayer
Author			: 우재우
역할			: 스킬을 나열하고 선택한다.
최종 수정일자	: 2014-12-02
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "AssemblyUILayer.h"

class SkillLineLayer : public AssemblyUILayer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(SkillLineLayer);

private:
	cocos2d::Node*			m_BearSkillContainer = nullptr;
	cocos2d::Node*			m_MonkeySkillContainer = nullptr;
	cocos2d::Node*			m_EagleSkillContainer = nullptr;
	cocos2d::Node*			m_CommonSkillContainer = nullptr;

	cocos2d::Rect			m_BearSkillRect = cocos2d::Rect();
	cocos2d::Rect			m_MonkeySkillRect = cocos2d::Rect();
	cocos2d::Rect			m_EagleSkillRect = cocos2d::Rect();
	cocos2d::Rect			m_CommonSkillRect = cocos2d::Rect();

};