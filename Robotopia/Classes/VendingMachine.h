/************************************************************************/
/*
CLASS			: VendingMachin
Author			: 김성연
역할				: 아이템이 나오는 체력 키트나오는 VendingMAchin
최종 수정일자		: 2014-12-20
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "NPC.h"

class AnimationComponent;
class VendingMachine : public NPC
{
public:

	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();
	virtual bool				onContactBegin(cocos2d::PhysicsContact& contact);
	virtual void				onContactSeparate(cocos2d::PhysicsContact& contact);


	CREATE_FUNC(VendingMachine);

private:
	AllStatus				m_Info;
	bool					m_SoundId = 0;
	int						m_KitNum = 0;
	AnimationComponent*		m_ContactAni = nullptr;
	AnimationComponent*     m_SeperateAni = nullptr;
};

