/************************************************************************/
/*
	CLASS			: BaseComponent
	Author			: 김연우
	역할				: 모든 컴포넌트들의 추상클래스
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: 노드 상속받아서 만들었다는 점에 유의할 것
					  업데이트 수정함. 아무것도 안넣었음.
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Util.h"


class BaseComponent : public cocos2d::Node
{
public:
	OVERRIDE bool				init();
	ABSTRACT void				update( float dTime ) = 0;
	ABSTRACT void				enter() = 0;
	ABSTRACT void				exit() = 0;
	ABSTRACT bool				onContactBegin(cocos2d::PhysicsContact& contact);
	ABSTRACT void				onContactSeparate(cocos2d::PhysicsContact& contact);

	void						addComponent( BaseComponent* BaseComponent );
	BaseComponent*				getComponent(ComponentType type)const;
	void						removeComponent( BaseComponent* remComponent );
	void						removeAllComponent();
	ComponentType				getType()const;
	ABSTRACT void				setEnabled(bool enable);
protected:
	ComponentType				m_Type;
	cocos2d::Size				m_Size;
};

