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

	void					hideLabelLayer();
	SkillSet				getSkillSet();

	void					updateSkills(float dTime);
	void					updateDoubleClickSkill(cocos2d::Point clickPoint);
	void					setSkillSet(cocos2d::Point clickPoint);
	void					containerScroll(float scrollValue, cocos2d::Point clickPoint);

private:
	cocos2d::Node*			m_BearContainer = nullptr;
	cocos2d::Node*			m_MonkeyContainer = nullptr;
	cocos2d::Node*			m_EagleContainer = nullptr;
	cocos2d::Node*			m_CommonContainer = nullptr;

	cocos2d::Rect			m_BearRect = cocos2d::Rect();
	cocos2d::Rect			m_MonkeyRect = cocos2d::Rect();
	cocos2d::Rect			m_EagleRect = cocos2d::Rect();
	cocos2d::Rect			m_CommonRect = cocos2d::Rect();

	std::vector<IconLayer*>		m_BearList;
	std::vector<IconLayer*>		m_MonkeyList;
	std::vector<IconLayer*>		m_EagleList;
	std::vector<IconLayer*>		m_CommonList;

	SkillSet				m_SkillSet = SkillSet();

	void					initSkillContainer();
	void					displaySkills();

};