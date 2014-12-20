/************************************************************************/
/*
CLASS			: LabelLayer
Author			: 우재우
역할			: Label 생성
최종 수정일자	: 2014-11-30
최종 수정자		: 우재우
최종 수정사유	: Label type 삭제
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "UILayer.h"

class LabelLayer : public UILayer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC (LabelLayer);

	void					setLabelContents(bool isLocked);
	void					setLabelPosition(cocos2d::Point labelPosition, bool rectDirDown);

private:
	float					m_LabelWidth = 0.0f;
	float					m_LabelHeight = 0.0f;
	cocos2d::Sprite*		m_LabelFrame = nullptr;
	cocos2d::Label*			m_LabelText = nullptr;

};