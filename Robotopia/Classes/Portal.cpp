#include "pch.h"
#include "Portal.h"
#include "GameManager.h"
#include "DataManager.h"
#include "RoomLayer.h"
#include "InputManager.h"
#include "StageManager.h"
#include "Player.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"

#define MSG_WIDHT 30
#define MSG_HIGHT 90

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
	cocos2d::Rect playerRect;
	playerRect.origin = GET_STAGE_MANAGER()->getPlayer()->getPosition();
	playerRect.size = GET_STAGE_MANAGER()->getPlayer()->getInfo().m_Size;
	playerRect.origin.x -= playerRect.size.width / 2;
	playerRect.origin.y -= playerRect.size.height / 2;
	m_MyRect.origin = getPosition();

	if (playerRect.intersectsRect(m_MyRect))
	{
		
		m_MessageBox->enter();

		if (GET_INPUT_MANAGER()->getKeyState(KC_INTERACT) == KS_PRESS)
		{
			GET_STAGE_MANAGER()->initStage(GET_STAGE_MANAGER()->getStageNum() + 1);
		}
	}
	else
	{
		m_MessageBox->exit();
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
	m_MessageBox = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_MessageBox->initSprite(ST_MESSAGE_BOX, this, cocos2d::Point(MSG_WIDHT, MSG_HIGHT));
	addComponent(m_MessageBox);
	m_MessageBox->exit();

	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
	cocos2d::Rect myRect(getPositionX(), getPositionY(), tileSize.width, tileSize.height);
	m_MyRect = myRect;
	
	setPosition(tileRect.origin);
	initSprite(tileRect.size);

}


