#include "pch.h"
#include "GearLayer.h"
#include "Player.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"
#include "ResourceManager.h"

Arthas::GearLayer::GearLayer()
{
}

Arthas::GearLayer::~GearLayer()
{
}

bool Arthas::GearLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	return true;
}

void Arthas::GearLayer::update(float dTime)
{

}

