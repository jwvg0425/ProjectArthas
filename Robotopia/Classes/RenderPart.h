/************************************************************************/
/*
CLASS			: RenderPart
Author			: 김연우
역할				: Player 렌더의 부분 렌더링 구현
최종 수정일자	: 2014-11-29
최종 수정자		:
최종 수정사유	:
Comment			: 부분 파츠별 FSM적용 enter exit구현작업 필요
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "Player.h"

class AnimationComponent;
class RenderPart : public cocos2d::Node
{
public:
	RenderPart();
	virtual ~RenderPart();

	virtual bool				init();

	void						changeState(Player::State state);
	void						addAnimation(BaseComponent* target, AnimationType type, Player::State state);

	CREATE_FUNC(RenderPart);
protected:
	std::vector<AnimationComponent*>	m_Animations;
	Player::State						m_CurrentState;
};