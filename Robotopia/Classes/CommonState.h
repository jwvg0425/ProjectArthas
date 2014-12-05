/************************************************************************/
/*
CLASS			: CommonState
Author			: 남현욱
역할				:  대부분의 Creature들이 공유하는 FSM 상태 함수를 정의해 놓는 부분입니다.
최종 수정일자	: 2014-12-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#include "Util.h"

class Creature;
class CommonState
{
public:
	static void enterKnockback(Creature* target, int dir);
	static void	knockback(Creature* target, double dTime, int idx);
};