/************************************************************************/
/*
	CLASS			: KeyboardComponent
	Author			: 김연우
	역할				: 키보드 커맨드
	최종 수정일자	: 2014-10-31
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/
#pragma once
#include "CommandComponent.h"
#include "cocos2d.h"
BEGIN_NS_AT

class KeyboardCommand : public CommandComponent
{
public:

	OVERRIDE bool				init();
	OVERRIDE void				update( float dTime );
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	CREATE_FUNC( KeyboardCommand );

protected:
	
};

END_NS_AT