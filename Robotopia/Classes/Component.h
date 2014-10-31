/************************************************************************/
/*
	CLASS			: Component
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

BEGIN_NS_AT

class Component : public cocos2d::Node
{
public:
	OVERRIDE bool				init();
	ABSTRACT void				update( float dTime ) = 0;
	ABSTRACT void				enter() = 0;
	ABSTRACT void				exit() = 0;

	void						addComponent( Component* component );
	Component*					getComponent( ComponentType type ) ;
	void						removeComponent( Component* remComponent );
	void						removeAllComponent();
	ComponentType				getType()const;
	void						setParent( Component* parent );
	Component*					getParent()const;

protected:
	ComponentType				m_Type;
	Component*					m_Parent;
};

END_NS_AT