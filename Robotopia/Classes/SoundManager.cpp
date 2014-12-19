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

	//effect Sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/SteamGet.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/GrenadeExplosion.wavSteamGet.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/CollisionPlayerAndMonster.wav");
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

void SoundManager::createSound(SoundType soundType, bool isRepeated)
{
	switch (soundType)
	{
	case SoundManager::STEAM_GET:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/SteamGet.wav", isRepeated);
		break;
	case SoundManager::GREANADE_EXPLOSION:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/GrenadeExplosion.wav", isRepeated);
		break;
	case SoundManager::COLLISION_PLAYER_MONSTER:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/CollisionPlayerAndMonster.wav", isRepeated);
		break;
	default:
		break;
	}
}

