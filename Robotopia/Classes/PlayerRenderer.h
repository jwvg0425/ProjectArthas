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
#include "Player.h"

class RenderPart;
class PlayerRenderer : public BaseComponent
{
public:
	enum PartsType
	{
		PT_ENGENE,
		PT_ARMOR,
		PT_RANGE,
		PT_MELEE,
		PT_LEG,
		PT_HEAD,
		PT_MAX,
	};

	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();

	void						changeState(Player::State state);
	void						addPart(RenderPart* part, PartsType type);
	void						removePart(PartsType type);

	CREATE_FUNC(PlayerRenderer);

protected:
	std::vector<RenderPart*>	m_Parts;
};
