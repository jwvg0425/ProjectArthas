/************************************************************************/
/*
CLASS			: PlayerRender
Author			: 김연우
역할				: Player 파츠별 렌더링 구현
최종 수정일자	: 2014-11-29
최종 수정자		:
최종 수정사유	:
Comment			: 파츠의 집합. 땟다 붙였다 가능하게.
*/
/************************************************************************/

#pragma once
#include "BaseComponent.h"
#include "RenderPart.h"

class PlayerRender : public BaseComponent
{
public:
	enum PartsType
	{
		PT_TOROSO,
		PT_HEAD,
		PT_ARM_LEFT,
		PT_ARM_RIGHT,
		PT_LEG_LEFT,
		PT_LEG_RIGHT,
		PT_MAX,
	};

	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();

	void						addPart(RenderPart* part, PartsType type);
	void						removePart(PartsType type);


	CREATE_FUNC(PlayerRender);

protected:
	std::vector<RenderPart*>	m_Parts;
};
