/************************************************************************/
/*
CLASS			: ObserverComponent
Author			: 김연우
역할				: Sprite Component의 클래스
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			: Create해서 만든다음에 setSprite해서 해당 스프라이트 추가해주어야한다.
*/
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "Component.h"
#include "Trigger.h"

BEGIN_NS_AT

class ObserverComponent : public Component
{
public:
	OVERRIDE ~ObserverComponent();

	OVERRIDE bool				init();
	OVERRIDE void				update( float dTime );
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	void						addTrigger( Trigger* trigger );
	void						removeTrigger( Trigger* trigger );
	void						removeCurrentTrigger();
	std::vector<Trigger*>&		getTriggers();

	CREATE_FUNC( ObserverComponent );

protected:
	std::vector<Trigger*> m_Triggers;
	std::vector<Trigger*> m_NextTriggers;
};

END_NS_AT