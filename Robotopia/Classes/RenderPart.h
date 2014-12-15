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

	virtual bool						init();
	void								changeState(int fsmIdx, Player::State state);
	void								addAnimation(BaseComponent* target, AnimationType type, int fsmIdx, Player::State state);
	void								setFlip(bool isLeft);

	CREATE_FUNC(RenderPart);
protected:
	int									idxize(int fsmIdx, Player::State state);
	std::vector<AnimationComponent*>	m_Animations;
	int									m_CurrentStateIdx;
};