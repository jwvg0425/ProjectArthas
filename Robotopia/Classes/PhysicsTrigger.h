/************************************************************************/
/*
CLASS			: ContactTrigger
Author			: 남현욱
역할				: 두 개의 물체가 물리적으로 접촉했을 때 발생하는 트리거 클래스.
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Trigger.h"



class BaseComponent;

class PhysicsTrigger : public Trigger
{
public:
	void							initTrigger(ComponentType componentA, ComponentType componentB, 
											Direction dir, ContactType type);
	virtual bool					operator ==( const Trigger& trigger );

	void							setContactData(cocos2d::PhysicsContactData contactData);
	cocos2d::PhysicsContactData		getContactData();

	PhysicsTrigger();
	~PhysicsTrigger();

private:
	ComponentType				m_ComponentA;
	ComponentType				m_ComponentB;
	Direction					m_Direction;
	ContactType					m_ContactType;
	cocos2d::PhysicsContactData m_ContactData;
};

