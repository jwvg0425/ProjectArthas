/************************************************************************/
/*
	CLASS			: TriggerType
	Author			: 남현욱
	역할				: Trigger들의 Type 값 정의 enum 관리.
	최종 수정일자	: 2014-11-5
	최종 수정자		: 김연우
	최종 수정사유	: 
	Comment			: TT_POSITION 추가
*/
/************************************************************************/


#pragma once
#include "Macro.h"



enum TriggerType
{
	TT_NONE = 0,
	TT_STATE_CHANGE = 1,
	TT_PHYSICS = 2,
	TT_KEYBOARD = 3,
	TT_POSITION = 4,
	TT_SEIZEFIRE = 5,
	TT_TRIVIAL = 6,
	TT_COMMAND = 7,
	TT_NUM,
};


