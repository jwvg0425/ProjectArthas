/************************************************************************/
/*
CLASS			: NPC
Author			: 김연우
역할				: 플레이어와 상호작용가능한 NPC
최종 수정일자	: 2014-12-08
최종 수정자		:
최종 수정사유	:
Comment			: 
*/
/************************************************************************/
#pragma once
#include "Creature.h"
#include "Util.h"


class SpriteComponent;
struct AllStatus;
class NPC : public Creature
{
public:
	virtual bool				init();
	virtual void				update(float dTime) = 0;
	virtual void				enter();
	virtual void				exit();

	virtual bool				onContactBegin(cocos2d::PhysicsContact& contact);
	virtual void				onContactSeparate(cocos2d::PhysicsContact& contact);
	virtual const AllStatus&	getInfo() const;

protected:
	void						bodyInit(cocos2d::Size size);

	SpriteComponent*			m_MessageBox = nullptr;
	AllStatus					m_Info;
	bool						m_OnContact = false;
};	

