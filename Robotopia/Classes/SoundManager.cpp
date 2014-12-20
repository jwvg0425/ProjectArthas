#include "pch.h"
#include "SoundManager.h"


SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

bool SoundManager::init()
{
	//BGM
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/BGM2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/Call to Adventure.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/Exotic Battle.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/Five Armies.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/Split In Synapse.mp3");

	//player 
	////기타
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/CollisionPlayerAndMonster.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/돈얻는소리.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/메뉴키고글때.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/SteamGet.wav");

	////일반행동
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/기어바꿀때.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/점프.wav");

	////근거리상태
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/근거리미사일주먹.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/슈퍼아머.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/무적.wav");

	////원거리상태
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/원거리미사일.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/바인딩미사일.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/GrenadeExplosion.wav");

	////나는상태
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/Flying.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/공중방사형미사일.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/공중일반미사일.wav");
	////일반 스킬
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/대쉬.wav");

	//normalMonster
	////몬스터 공통
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/몬스터맞을때.wav");

	////돼지
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/돼지소리.wav");

	////데빌 몬스터
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/번개.wav");

	////고등어
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/고등어미사일쏘는소리.wav");

	//ETC
	////어셈블리창
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/일반클릭.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/확정클릭.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/upgrade소리.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/시작화면에서잘못클릭.wav");

	////전기트랩
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/전기트랩.mp3");

	////기타
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/Story_Computer_Collision.wav");

	return true;
}

void SoundManager::createBGM(BGMType bgmType, bool isRepeated)
{
	switch (bgmType)
	{
	case SoundManager::BGM_2:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/BGM2.mp3", isRepeated);
		break;
	case SoundManager::BGM_EXOTIC_BATTLE:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/Exotic Battle.mp3", isRepeated);
		break;
	case SoundManager::BGM_CALLTOADVANTURE:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/Call to Adventure.mp3", isRepeated);
		break;
	case SoundManager::BGM_SPLITINSYNAPSE:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/Split In Synapse.mp3", isRepeated);
		break;
	case SoundManager::BGM_FIVEARMIES:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/Five Armies.mp3", isRepeated);
		break;
	default:
		break;
	}
}


int SoundManager::createSound(PlayerSound playerSoundType, bool isRepeated)
{
	int soundId = 0;

	switch (playerSoundType)
	{
	case SoundManager::COLLISION_PLAYER_MONSTER:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/CollisionPlayerAndMonster.wav", isRepeated);
		break;
	case SoundManager::GETMONEY:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/돈얻는소리.wav", isRepeated);
		break;
	case SoundManager::MENU:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/메뉴키고글때.wav", isRepeated);
		break;
	case SoundManager::STEAM_GET:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/SteamGet.wav", isRepeated);
		break;
	case SoundManager::CHANGEGEAR:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/기어바꿀때.wav", isRepeated);
		break;
	case SoundManager::JUMP:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/점프.wav", isRepeated);
		break;
	case SoundManager::PUNCHMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/근거리미사일주먹.wav", isRepeated);
		break;
	case SoundManager::SUPERARMOR:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/슈퍼아머.wav", isRepeated);
		break;
	case SoundManager::UNBEATABLE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/무적.wav", isRepeated);
		break;
	case SoundManager::LINEARMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/원거리미사일.wav", isRepeated);
		break;
	case SoundManager::BINDINGMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/바인딩미사일.wav", isRepeated);
		break;
	case SoundManager::GREANADE_EXPLOSION:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/GrenadeExplosion.wav", isRepeated);
		break;
	case SoundManager::FLYING:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Flying.wav", isRepeated);
		break;
	case SoundManager::AIRSKILLMULTIMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/공중방사형미사일.wav", isRepeated);

		break;
	case SoundManager::AIRSKILLNORMALMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/공중일반미사일.wav", isRepeated);
		break;
	case SoundManager::DASH:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/대쉬.wav", isRepeated);
		break;
	default:
		break;
	}

	return soundId;
}

int SoundManager::createSound(NormalMonsterSound nMonsterType, bool isRepeated)
{
	int soundId = 0;

	switch (nMonsterType)
	{

	case SoundManager::MONSTERHIT:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/몬스터맞을때.wav", isRepeated);
		break;
	case SoundManager::PIG:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/돼지소리.wav", isRepeated);
		break;
	case SoundManager::THUNDER:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/번개.wav", isRepeated);
		break;
	case SoundManager::STANDMONSTERSHOT:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/고등어미사일쏘는소리.wav", isRepeated);
		break;
	default:
		break;
	}

	return soundId;
}

int SoundManager::createSound(ETCType soundType, bool isRepeated)
{
	int soundId = 0;

	switch (soundType)
	{
	case SoundManager::EQUIPCLICK:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/일반클릭.wav", isRepeated);
		break;
	case SoundManager::EQUIPDOUBLECLICK:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/확정클릭.wav", isRepeated);
		break;
	case SoundManager::UPGRADE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/upgrade소리.wav", isRepeated);
		break;
	case SoundManager::WRONGCLICK:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/시작화면에서잘못클릭.wav", isRepeated);
		break;
	case SoundManager::CHARGEGAGE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/게이지채우는소리.wav", isRepeated);
		break;
	case SoundManager::ELECTRICTRAP:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/전기트랩.mp3", isRepeated);
		break;
	default:
		break;
	}

	return soundId;
}



void SoundManager::pauseSound(int soundId)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(soundId);

}