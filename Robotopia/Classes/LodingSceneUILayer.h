/************************************************************************/
/*
CLASS			: LoadingSceneUILayer
Author			: 우재우
역할			: LoadingScene에 필요한 UILayer
최종 수정일자	: 2014-10-31
최종 수정자		: 우재우
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include "Util.h"
#include "UILayer.h"



class LoadingSceneUILayer : public UILayer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(LoadingSceneUILayer);

private:

};

