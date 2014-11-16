/************************************************************************/
/*
CLASS			: EffectManager
Author			: 김성연
역할				: Effect 요청시 생성후 전달
최종 수정일자		: 2014-10-29
최종 수정자		: 
최종 수정사유		:
Comment			: 아직 어떤 layer를 전달 받을지 결정 되지 않음
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "cocos2d.h"



//임시로 roomLayer를 받았다고 합니다.(나중에 정확히 무엇을 받을지 정해야됨)
class RoomLayer;

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	bool	init();
	void    createEffect(EffectType effectType,RoomLayer* layer, 
						 cocos2d::Point point, int playTime);



private:
	void	removeEffectCallBack(cocos2d::Ref* sender);

};




