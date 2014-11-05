/************************************************************************/
/*
CLASS			: MovingBlock
Author			: 김연우
역할			: 움직이는 타일 MovingBlock
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#pragma once
#include "Block.h"
#include "Util.h"

BEGIN_NS_AT

class MovingBlock : public Block
{
public:
	OVERRIDE bool init();
	OVERRIDE void update(float dTime);
	OVERRIDE void enter();
	OVERRIDE void exit();

	CREATE_FUNC(MovingBlock);

private:

};

END_NS_AT