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
	cocos2d::Sprite*		m_Steam0 = nullptr;
	cocos2d::Sprite*		m_Steam1 = nullptr;
	cocos2d::Sprite*		m_Steam2 = nullptr;
	cocos2d::Sprite*		m_Steam3 = nullptr;
	cocos2d::Sprite*		m_Steam4 = nullptr;
	cocos2d::Sprite*		m_Steam5 = nullptr;

	cocos2d::Sprite*		m_SteamMask0 = nullptr;
	cocos2d::Sprite*		m_SteamMask1 = nullptr;
	cocos2d::Sprite*		m_SteamMask2 = nullptr;
	cocos2d::Sprite*		m_SteamMask3 = nullptr;
	cocos2d::Sprite*		m_SteamMask4 = nullptr;
	cocos2d::Sprite*		m_SteamMask5 = nullptr;
	cocos2d::Sprite*		m_SteamTest = nullptr;

	GearType				m_CurrentGear = GEAR_NONE;
	int						m_SteamLevel = 0;

	void					setSteamMask(cocos2d::Sprite* steam, cocos2d::Sprite* steamMask);
	void					controlSteam(int SClevel, int MaxSteam, int CurrentSteam);
	void					controlSteamColor();
	void					changeSteamColor(GearType gear);
};

