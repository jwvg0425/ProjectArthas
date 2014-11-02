/************************************************************************/
/*
	CLASS			: CommandComponent
	Author			: 김연우
	역할				: 커맨드의 추상 컴포넌트
	최종 수정일자	: 2014-10-31
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/

#pragma once
#include "Component.h"
#include "cocos2d.h"

BEGIN_NS_AT

class ObserverComponent;
class CommandComponent : public Component
{
public:


	OVERRIDE bool				init();
	OVERRIDE void				update( float dTime );
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	ABSTRACT ObserverComponent*	getObserverComponent();

	CREATE_FUNC( CommandComponent );

protected:

};

END_NS_AT