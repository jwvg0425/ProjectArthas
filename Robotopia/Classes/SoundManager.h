/************************************************************************/
/*
CLASS			: EffectManager
Author			: 김성연
역할				: Sound 요청시 생성후 전달
최종 수정일자		: 2014-12-17
최종 수정자		:
최종 수정사유		:
Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "SimpleAudioEngine.h"

class SoundManager
{
public:
	enum BGMType
	{
		BGM_START = 0,
		BGM_2,
		BGM_EXOTIC_BATTLE,
		BGM_CALLTOADVANTURE,
		BGM_SPLITINSYNAPSE,
		BGM_FIVEARMIES,
		BGM_END,
	};

	enum SoundType
	{
		SOUND_START = 0,
		STEAM_GET,
		GREANADE_EXPLOSION,
		COLLISION_PLAYER_MONSTER,
		UPGRADE,
		EQUIPCLICK,
		EQUIPDOUBLECLCIK,
		GETMONEY,
		DASH,
		BINDINGMISSILE,
		THUNDER,
		CHARGEGAGE,
		FLYING,
		ELECTRICTRAP,
		AIRSKILLMULTIMISSILE,
		AIRSKILLNORMALMISSILE,
		JUMP,
		UNBEATABLE,
		SUPERARMOR,
		LINEARMISSILE,
		PUNCHMISSILE,
		PIG,
		STANDMONSTERSHOT,
		MENU,
		MONSTERHIT,
		WRONGCLICK,
		CHANGEGEAR,
		SOUND_END,
	};

	SoundManager();
	~SoundManager();

	bool	init();
	void	createBGM(BGMType bgmType, bool isRepeated);
	int	    createSound(SoundType soundType, bool isRepeated);
	void	pauseSound(int soundId);

private:


};


