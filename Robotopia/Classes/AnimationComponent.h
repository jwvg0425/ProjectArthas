/************************************************************************/
/*
CLASS			: AnimationComponent
Author			: 김성연
역할				: 이 Component를 갖게 되면 Animation을 그릴 수 있다. 
최종 수정일자		: 2014-10-29
최종 수정자		:
최종 수정사유		:
Comment			: Create해서 만든 다음에 setAnimation해서 해당 애니메이션을 추가해주어야한다.
*/
/************************************************************************/

#pragma once
#include "Component.h"

BEGIN_NS_AT


class AnimationCompnent : public Component
{

public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	void						setAnimation(const char* AnimationName);


	CREATE_FUNC(AnimationCompnent);

private:
	cocos2d::Sprite* m_Sprite;
	int				 m_Type;

};

END_NS_AT