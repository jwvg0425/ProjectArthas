/************************************************************************/
/*
	CLASS			: UILayer
	Author			: 김연우
	역할				: UI관련 오브젝트들을 담는 레이어
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: 그냥 클래스만 만들어둠
*/
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include "Util.h"

BEGIN_NS_AT

class UILayer : public cocos2d::Layer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void					update( float dTime );

	CREATE_FUNC( UILayer );
protected:

};

END_NS_AT