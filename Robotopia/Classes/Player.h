	/************************************************************************/
/*
CLASS			: Player
Author			: 김연우
역할				: Player class
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			: 모든 오브젝트를 BaseComponent로 만듭니다.
*/
/************************************************************************/
#pragma once
#include "BaseComponent.h"
#include "Util.h"


class CommonInfo;
class Player : public BaseComponent
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);
	OVERRIDE void			enter();
	OVERRIDE void			exit();

	CREATE_FUNC( Player );
protected:

};

