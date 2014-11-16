/************************************************************************/
/*
	CLASS			: SimpleRoaming
	Author			: 김연우
	역할				: 정해진 위치에서 좌로 우로 이동하는 심플한 Roaming
	최종 수정일자	: 2014-11-05
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/
#pragma once
#include "Util.h"
#include "FSMComponent.h"



class SimpleRoamingFSM : public FSMComponent
{
public:
	OVERRIDE bool				init();
	void						initRoaming(BaseComponent* parent, cocos2d::Point leftPoint, cocos2d::Point rightPoint, float time);
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	CREATE_FUNC(SimpleRoamingFSM);
private:
};

