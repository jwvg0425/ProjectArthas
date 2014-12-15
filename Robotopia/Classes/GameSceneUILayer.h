/************************************************************************/
/*
CLASS			: GameSceneUILayer
Author			: 우재우
역할			: GameScene에 필요한 UILayer
최종 수정일자	: 2014-10-31
최종 수정자		: 우재우
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#pragma once
#include "GameManager.h"
#include "Util.h"
#include "UILayer.h"



class Player;
class HPLayer;
class MapLayer;
class GearLayer;
class SteamLayer;
class GameMenuLayer;
class SkillUseLayer;
class CharWindowLayer;

class GameSceneUILayer : public UILayer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(GameSceneUILayer);

	void					setMapUI(int stageNum, int roomNum);
	
private:
	HPLayer*				m_HPLayer = nullptr;
	MapLayer*				m_MapLayer = nullptr;
	GearLayer*				m_GearLayer = nullptr;
	SteamLayer*				m_SteamBarLayer = nullptr;
	GameMenuLayer*			m_GameMenuLayer = nullptr;
	SkillUseLayer*			m_SkillUseLayer = nullptr;
	CharWindowLayer*		m_CharWInLayer = nullptr;

	bool					m_MenuWindowOn = false;
	bool					m_MapWindowOn = false;
	bool					m_CharWindowOn = false;

	cocos2d::Rect			m_MapWinRect = cocos2d::Rect();
	cocos2d::Rect			m_CharWinRect = cocos2d::Rect();

	void					controlUIKeyboard();
	void					controlUIMouse();

	void					openGameMenu();
	void					closeGameMenu();
	void					openMapWindow();
	void					closeMapWindow();
	void					openCharWindow();
	void					closeCharWindow();
};

