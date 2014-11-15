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

BEGIN_NS_AT

class Player;
class MapLayer;
class GearLayer;
class SteamLayer;
class CharWindowLayer;

class GameSceneUILayer : public UILayer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(GameSceneUILayer);

	void					setMapUI(int stageNum, int roomNum);
	
private:
	GearLayer*				m_GearLayer;
	SteamLayer*				m_SteamBarLayer;
	MapLayer*				m_MapLayer;
	CharWindowLayer*		m_CharWInLayer;

	bool					m_MenuWindowOn;
	bool					m_MapWindowOn;
	bool					m_CharWindowOn;

	void					UIInputControl();
};

END_NS_AT