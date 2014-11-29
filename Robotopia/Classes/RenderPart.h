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
#include "SpriteComponent.h"

class RenderPart : public SpriteComponent
{
public:
	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();


	CREATE_FUNC(RenderPart);
protected:

};