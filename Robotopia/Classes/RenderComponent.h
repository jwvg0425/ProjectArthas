/************************************************************************/
/*
CLASS				: RenderComponent
Author				: 우재우
역할				: Render들의 추상 클래스
최종 수정일자		: 2014-10-31
최종 수정자			: 우재우
최종 수정사유		: 
Comment				:
*/
/************************************************************************/

#pragma once
#include "Component.h"
#include "cocos2d.h"
#include "Util.h"

BEGIN_NS_AT

class Trigger;
class SpriteComponent;

class RenderComponent : public Component
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE void				update(float dTime);
	void						addTransition(Arthas::Transition addTransition);
	void						removeTransition(Arthas::Transition remTranstion);

protected:
	SpriteComponent*            m_CurrentSprite;
	std::vector<Trigger*>		m_Triggers;
	std::vector<Transition>		m_Transitions;
};

END_NS_AT