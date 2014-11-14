#include "pch.h"
#include "SteamLayer.h"
#include "Player.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"
#include "ResourceManager.h"

Arthas::SteamLayer::SteamLayer()
{
}

Arthas::SteamLayer::~SteamLayer()
{
}

bool Arthas::SteamLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	return true;
}

void Arthas::SteamLayer::update(float dTime)
{

}

