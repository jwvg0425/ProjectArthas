/************************************************************************/
/*
CLASS			: IconLayer
Author			: 우재우
역할			: Icon 상호 작용에 관여
최종 수정일자	: 2014-11-28
최종 수정자		: 우재우
최종 수정사유	: Icon Type 삭제
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "UILayer.h"

class LabelLayer;

class IconLayer : public UILayer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC (IconLayer);

	void					setIconContent(cocos2d::Sprite* contentIcon);
	void					changeIconState(IconState iconState);
	void					setIconRect(cocos2d::Point parentAnchorPoint, cocos2d::Point iconPosition);
	void					setIconLabel(cocos2d::Point iconPosition, bool isLocked);
	void					hideLabel();
	bool					getSelected();
	bool					getLocked();

	void					doubleClickCheck(cocos2d::Point mouseClickPoint);

private:
	bool					m_Selected = false;
	bool					m_Locked = false;
	bool					m_DragOn = false;
	bool					m_Labeled = false;

	IconState				m_IconState = NO_ICON;
	LabelLayer*				m_IconLabel = nullptr;
	cocos2d::Sprite*		m_IconFrameDefault = nullptr;
	cocos2d::Sprite*		m_IconFrameSelected = nullptr;
	cocos2d::Sprite*		m_IconFrameLocked = nullptr;
	cocos2d::Sprite*		m_IconContent = nullptr;
	cocos2d::Rect			m_IconRect = cocos2d::Rect();
	cocos2d::Point			m_PrevPoint;

	void					changeIconDefault();
	void					changeIconSelected();
	void					changeIconLocked();
};