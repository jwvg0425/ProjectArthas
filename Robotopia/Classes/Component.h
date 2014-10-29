/************************************************************************/
/*
	CLASS			: Component
	Author			: 김연우
	역할				: 모든 컴포넌트들의 추상클래스
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: 노드 상속받아서 만들었다는 점에 유의할 것, 
					  update를 모든 자식들에게 하지 않는 컴포넌트의 경우 업데이트 오버라이드할 것,
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Util.h"

BEGIN_NS_AT

class Component : public cocos2d::Node
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update( float dTime );
	ABSTRACT void				enter() {};
	ABSTRACT void				exit() {};

	void						addComponent( Component* component );
	Component*					getComponent( int type );
	void						removeComponent( Component* remComponent );
	void						removeAllComponent();
	int							getType() {return m_Type; }
	void						setParent(Component* parent) {m_Parent = parent;}
	Component*					getParnet() {return m_Parent; }

protected:
	int							m_Type;
	Component*					m_Parent;
};

END_NS_AT