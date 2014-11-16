/************************************************************************/
/*
CLASS			: AnimationEndTrigger
Author			: 김연우
역할				: 어떤 애니메이션 종류가 끝났는지 알려주는 트리거
최종 수정일자		: 2014-11-16
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/

#pragma once
#include "Trigger.h"



class BaseComponent;

class AnimationEndTrigger : public Trigger
{
public:
	void			initTrigger(ResourceType animationType);
	ResourceType	getAnimationType() const ;
	virtual bool	operator ==(const Trigger& trigger);

	AnimationEndTrigger();
	~AnimationEndTrigger();

private:
	ResourceType m_AnimationType;

};

