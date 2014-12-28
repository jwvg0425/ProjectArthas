/************************************************************************/
/*
CLASS			: Portal
Author			: 김연우
역할				: 연결가능하면 열리고 아니면 닫히는 타일
최종 수정일자	: 2014-11-09
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Tile.h"
#include "Util.h"

class AnimationComponent;
class SpriteComponent;
class Portal : public Tile
{
public:
	virtual bool	init();
	virtual void	update(float dTime);
	virtual void	enter();
	virtual void	exit();

	virtual void	initTile(cocos2d::Rect tileRect);
	void			gateSwitch(bool isOpen);
	CREATE_FUNC(Portal);

private:
	bool					m_IsOpen = false;
	int						m_Floor = 0;
	cocos2d::Rect			m_MyRect = cocos2d::Rect::ZERO;
	SpriteComponent*		m_MessageBox = nullptr;
	AnimationComponent*		m_OpenAnimation = nullptr;
	AnimationComponent*		m_ClosedAnimation = nullptr;
};

