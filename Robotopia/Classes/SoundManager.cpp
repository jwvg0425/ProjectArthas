#include "pch.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "StageManager.h"
#include "Player.h"


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
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/CalltoAdventure.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/ExoticBattle.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/FiveArmies.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/SplitInSynapse.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/ClockBossEntrance.wav");

	//player 

	////기타
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/CollisionPlayerAndMonster.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/GetMoney.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/Menu.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/SteamGet.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/CorpseGet.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/CorpseLastGet.wav");

	////일반행동
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/ChageGear.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/jump.wav");

	////근거리상태
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/PunchMissile.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/BladeMissile.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/SuperArmor.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/Unbeatable.wav");

	////원거리상태
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/LinearMissile.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/BindingMissile.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/GrenadeExplosion.wav");

	////나는상태
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/Flying.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/AirMultiMissile.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/AirNormalMissile.wav");
	////일반 스킬
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/Dash.wav");



	//normalMonster
	////몬스터 공통
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/MonsterHit.wav");

	////돼지
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/PigSound.wav");

	////데빌 몬스터
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/Thunder.wav");

	////고등어
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/PlantShot.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/AimingMissileCollision.wav");


	//ETC
	////어셈블리창
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/NormalClick.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/EquipClick.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/upgrade.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/WrongClick.wav");

	////전기트랩
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/ElectricTrap.mp3");

	////컴퓨터 
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/GageUpSound.wav");

	////레이저 트랩
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/LaserTrap.wav");

	////기타
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/Story_Computer_Collision.wav");

	//BOSS
	////시계태엽보스
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/ClockBossMove.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/ClockBossLaser.wav");


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
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/ExoticBattle.mp3", isRepeated);
		break;
	case SoundManager::BGM_CALLTOADVANTURE:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/CalltoAdventure.mp3", isRepeated);
		break;
	case SoundManager::BGM_SPLITINSYNAPSE:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/SplitInSynapse.mp3", isRepeated);
		break;
	case SoundManager::BGM_FIVEARMIES:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/FiveArmies.mp3", isRepeated);
		break;
	case SoundManager::BGM_CLOCK_BOSS_ENTRANCE:
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/ClockBossEntrance.wav", isRepeated);
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
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/GetMoney.wav", isRepeated);
		break;
	case SoundManager::MENU:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Menu.wav", isRepeated);
		break;
	case SoundManager::STEAM_GET:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/SteamGet.wav", isRepeated);
		break;
	case SoundManager::CORPSE_GET:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/CorpseGet.wav", isRepeated);
		break;
	case SoundManager::CORPSE_LAST_GET:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/CorpseLastGet.wav", isRepeated);
		break;
	case SoundManager::CHANGEGEAR:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/ChageGear.wav", isRepeated);
		break;
	case SoundManager::JUMP:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/jump.wav", isRepeated);
		break;
	case SoundManager::PUNCHMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/PunchMissile.wav", isRepeated);
		break;
	case SoundManager::BLADEMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/BladeMissile.wav", isRepeated);
	case SoundManager::SUPERARMOR:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/SuperArmor.wav", isRepeated);
		break;
	case SoundManager::UNBEATABLE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Unbeatable.wav", isRepeated);
		break;
	case SoundManager::LINEARMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/LinearMissile.wav", isRepeated);
		break;
	case SoundManager::BINDINGMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/BindingMissile.wav", isRepeated);
		break;
	case SoundManager::GREANADE_EXPLOSION:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/GrenadeExplosion.wav", isRepeated);
		break;
	case SoundManager::FLYING:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Flying.mp3", isRepeated);
		break;
	case SoundManager::AIRSKILLMULTIMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/AirMultiMissile.wav", isRepeated);

		break;
	case SoundManager::AIRSKILLNORMALMISSILE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/AirNormalMissile.wav", isRepeated);
		break;
	case SoundManager::DASH:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Dash.wav", isRepeated);
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
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/MonsterHit.wav", isRepeated);
		break;
	case SoundManager::PIG:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/PigSound.wav", isRepeated);
		break;
	case SoundManager::THUNDER:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Thunder.wav", isRepeated);
		break;
	case SoundManager::STANDMONSTERSHOT:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/PlantShot.wav", isRepeated);
		break;
	case SoundManager::AIMINGMISSIE_COLLISION:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/AimingMissileCollision.wav", isRepeated);
		break;
	default:
		break;
	}

	return soundId;
}

int SoundManager::createSound(ETCSound soundType, bool isRepeated)
{
	int soundId = 0;

	switch (soundType)
	{
	case SoundManager::EQUIPCLICK:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/NormalClick.wav", isRepeated);
		break;
	case SoundManager::EQUIPDOUBLECLICK:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/EquipClick.wav", isRepeated);
		break;
	case SoundManager::UPGRADE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/upgrade.wav", isRepeated);
		break;
	case SoundManager::WRONGCLICK:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/WrongClick.wav", isRepeated);
		break;
	case SoundManager::CHARGEGAGE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/GageUpSound.wav", isRepeated);
		break;
	case SoundManager::ELECTRICTRAP:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/ElectricTrap.mp3", isRepeated);
		break;
	case SoundManager::LASERTRAP:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/LaserTrap.wav", isRepeated);
		break;
	default:
		break;
	}

	return soundId;
}

int SoundManager::createSound(BossSound bossType, bool isRepeated)
{
	int soundId = 0;

	switch (bossType)
	{
	case SoundManager::CLOCK_BOSS_LASER:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/ClockBossLaser.wav", isRepeated);
		break;
	case SoundManager::CLOCK_BOSS_MOVE:
		soundId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/ClockBossMove.wav", isRepeated);
		break;
	default:
		break;
	}
	return soundId;
}

int SoundManager::createSound(ETCSound soundType, bool isRepeated, cocos2d::Point pos)
{
	auto playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();

	if(fabs(playerPos.y - pos.y) <= WINSIZE_HEIGHT/2 &&
		fabs(playerPos.x - pos.x) <= WINSIZE_WIDTH/2)
	{
		return GET_SOUND_MANAGER()->createSound(soundType, false);
	}
	return -1;
}

int SoundManager::createSound(PlayerSound soundType, bool isRepeated, cocos2d::Point pos)
{
	auto playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();

	if (fabs(playerPos.y - pos.y) <= WINSIZE_HEIGHT / 2 &&
		fabs(playerPos.x - pos.x) <= WINSIZE_WIDTH / 2)
	{
		return GET_SOUND_MANAGER()->createSound(soundType, false);
	}
	return -1;
}

int SoundManager::createSound(NormalMonsterSound soundType, bool isRepeated, cocos2d::Point pos)
{
	auto playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();

	if (fabs(playerPos.y - pos.y) <= WINSIZE_HEIGHT / 2 &&
		fabs(playerPos.x - pos.x) <= WINSIZE_WIDTH / 2)
	{
		return GET_SOUND_MANAGER()->createSound(soundType, false);
	}
	return -1;
}

int SoundManager::createSound(BossSound soundType, bool isRepeated, cocos2d::Point pos)
{
	auto playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();

	if (fabs(playerPos.y - pos.y) <= WINSIZE_HEIGHT / 2 &&
		fabs(playerPos.x - pos.x) <= WINSIZE_WIDTH / 2)
	{
		return GET_SOUND_MANAGER()->createSound(soundType, false);
	}
	return -1;
}



void SoundManager::pauseSound(int soundId)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(soundId);
}

void SoundManager::allStopSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

bool SoundManager::isBackGroundMusicPlaying()
{
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		return true;
	}
	else
	{
		return false;
	}
}
