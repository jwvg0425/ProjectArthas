/************************************************************************/
/*
	CLASS			: Block
	Author			: 김연우
	역할				: 타일의 대명사 Block Class
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/
#pragma once
#include "Component.h"
#include "Util.h"

BEGIN_NS_AT

class Block : public Component
{
public:
	OVERRIDE bool init();
	OVERRIDE void update( float dTime );
	OVERRIDE void enter();
	OVERRIDE void exit();

	CREATE_FUNC( Block );

private:
	cocos2d::Rect m_BoxRect;
};

END_NS_AT