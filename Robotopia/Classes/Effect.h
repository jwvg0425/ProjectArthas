/************************************************************************/
/*
CLASS			: Effect
Author			: 남현욱
역할				: Effect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: 각종 효과들의 최상위 클래스.
*/
/************************************************************************/
#pragma once
#include "BaseComponent.h"


class Effect : public BaseComponent
{
public:
	virtual bool				init();
	virtual void				enter() = 0;
	virtual void				exit() = 0;
	virtual void				update(float dTime);
	void						setChasingPlayer(bool chasing);
	cocos2d::Sprite*			getSprite();

protected:
	cocos2d::Sprite*			m_Sprite = nullptr;
	bool						m_IsChasePlayer = false;
};