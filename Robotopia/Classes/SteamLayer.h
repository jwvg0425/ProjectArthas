/************************************************************************/
/*
CLASS			: SteamLayer
Author			: 우재우
역할			: SteamLayer를 보여준다.
최종 수정일자	: 2014-11-18
최종 수정자		: 우재우
최종 수정사유	: 스팀 이미지 변경 및 기어와 반응
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "GameSceneUILayer.h"

class SteamLayer : public GameSceneUILayer
{
public:
	SteamLayer();
	~SteamLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(SteamLayer);

private:
	cocos2d::Sprite*		m_SteamSprite = nullptr;
	cocos2d::ProgressTimer*	m_SteamBar = nullptr;

	GearType				m_CurrentGear = GEAR_NONE;
	GearType				m_PrevGear = GEAR_NONE;
	int						m_SteamLevel = 0;
	int						m_PrevSteam = 0;
	float					m_SteamMaxPercent = 0;

	void					controlSteam(int MaxSteam, int CurrentSteam);
	void					controlSteamColor();
	void					changeSteamColor(GearType gear);
};

