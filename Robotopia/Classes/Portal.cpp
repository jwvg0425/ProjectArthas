#include "pch.h"
#include "Portal.h"
#include "GameManager.h"
#include "DataManager.h"
#include "RoomLayer.h"
#include "InputManager.h"
#include "StageManager.h"
#include "Player.h"

bool Portal::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_PORTAL;
	m_SpriteType = ST_MAPTOOL_PORTAL; // 임시
	scheduleUpdate();
	return true;
}

void Portal::update(float dTime)
{
	if (GET_INPUT_MANAGER()->getKeyState(KC_UP) == KS_PRESS)
	{
		cocos2d::Rect playerRect;
		cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
		cocos2d::Rect myRect(getPositionX(), getPositionY(), tileSize.width, tileSize.height);

		playerRect.origin = GET_STAGE_MANAGER()->getPlayer()->getPosition();
		playerRect.size = GET_STAGE_MANAGER()->getPlayer()->getInfo().m_Size;
		playerRect.origin.x -= playerRect.size.width / 2;
		playerRect.origin.y -= playerRect.size.height / 2;

		if (playerRect.intersectsRect(myRect))
		{
			GET_STAGE_MANAGER()->initStage(GET_STAGE_MANAGER()->getStageNum() + 1);
		}
	}
}

void Portal::enter()
{

}

void Portal::exit()
{

}

void Portal::initTile(cocos2d::Rect tileRect)
{
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	setPosition(tileRect.origin);
	initSprite(tileRect.size);
}