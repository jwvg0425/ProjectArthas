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
#include "AnimationComponent.h"

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

	m_OpenAnimation = AnimationComponent::create();
	m_OpenAnimation->setAnimation(AT_LAND_PORTAL_OPEN, this);
	m_OpenAnimation->setSpriteAnchor(cocos2d::Vec2::ZERO);
	m_ClosedAnimation = AnimationComponent::create();
	m_ClosedAnimation->setAnimation(AT_LAND_PORTAL_CLOSED, this);
	addComponent(m_OpenAnimation);
	addComponent(m_ClosedAnimation);


	//나중에 문열닫 하고 싶으면 이 아래부분 빼고 다른 분기에서 gateSwitch를 건드시오
	gateSwitch(true);
}

void Portal::gateSwitch(bool isOpen)
{
	m_IsOpen = isOpen;
	if(m_IsOpen)
	{
		m_ClosedAnimation->exit();
		m_OpenAnimation->enter();
	}
	else
	{
		m_OpenAnimation->exit();
		m_ClosedAnimation->enter();
	}

}


