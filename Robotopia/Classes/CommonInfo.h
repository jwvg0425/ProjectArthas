/************************************************************************/
/*
CLASS			: CommonInfo
Author			: 남현욱
역할				: 거의 공통적으로 갖고 있어야하는 info를 모은 컴포넌트.
최종 수정일자	: 2014-11-03
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Util.h"
#include "BaseComponent.h"



class CommonInfo : public BaseComponent
{
public:
	struct Info
	{
		Direction		dir;
		cocos2d::Size	size;
		int				maxHp;
		int				maxSteam;
		int				currentHp;
		int				currentSteam;
		float			speed;
		float			jumpSpeed;
	};
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	Info						getInfo();
	void						setInfo(Info info);

	CREATE_FUNC(CommonInfo);

protected:
	Info						m_Info;
};

