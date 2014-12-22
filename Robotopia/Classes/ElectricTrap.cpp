#include "pch.h"
#include "ElectricTrap.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"
#include "BaseComponent.h"
#include "Electric.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "Player.h"
#include "StageManager.h"

#define SOUND_REPEATE_TIME 4500

bool ElectricTrap::init()
{
	if(!Tile::init())
	{
		return false;
	}
	m_Type = OT_TRAP_ELECTRIC;
	m_SpriteType = ST_START; // юс╫ц
	m_MovingVelocity.x = ELECTRIC_VELOCITY;

	m_Electric = Electric::create();
	addChild(m_Electric);
	m_Electric->setPosition(0, 0);
	m_Electric->setAnchorPoint(cocos2d::Point(0, 0));
	m_Electric->retain();
	return true;
}

void ElectricTrap::update(float dTime)
{
	auto tileSize = GET_DATA_MANAGER()->getTileSize();
	cocos2d::Point electPos = m_Electric->getPosition();
	if(electPos.x < tileSize.width/2)
	{
		m_IsLeftMoving = false;
	}
	else if(electPos.x > m_ActivateRect.size.width - tileSize.width/2)
	{
		m_IsLeftMoving = true;
	}

	if(m_IsLeftMoving)
	{
		electPos -= m_MovingVelocity * dTime;
	}
	else
	{
		electPos += m_MovingVelocity * dTime;
	}

	int nowTime = GET_GAME_MANAGER()->getMicroSecondTime();
	if (nowTime - m_SoundStartTime > SOUND_REPEATE_TIME)
	{
		m_SoundStartTime = nowTime;
		if (GET_STAGE_MANAGER()->getPlayer()->getPosition().getDistance(getPosition()) <
			(WINSIZE_WIDTH + WINSIZE_HEIGHT) / 2)
		{
			m_SoundId = GET_SOUND_MANAGER()->createSound(SoundManager::ELECTRICTRAP, false);
		}
	}

	m_Electric->setPosition(electPos);
}

void ElectricTrap::enter()
{

}

void ElectricTrap::exit()
{

}

void ElectricTrap::initTile(cocos2d::Rect tileRect)
{

	setPosition(tileRect.origin);
	setAnchorPoint(cocos2d::Point::ZERO);
	auto tileSize = GET_DATA_MANAGER()->getTileSize();
	for(int xPos = 0; xPos < tileRect.size.width; xPos+= tileSize.width)
	{
		auto trapBlock = GET_RESOURCE_MANAGER()->createSprite(ST_ELECTRICT_TRAP);
		addChild(trapBlock);
		trapBlock->setPosition(cocos2d::Point(xPos, 0));
		trapBlock->setScale(2.f);
		trapBlock->setAnchorPoint(cocos2d::Point::ZERO);
	}
	m_ActivateRect = tileRect;
	m_Electric->setPosition(tileSize.width / 2, tileSize.height / 2);

	m_SoundStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
}

void ElectricTrap::setEnabled(bool enable)
{
	/*if (enable)
	{
		
	else
	{
		GET_SOUND_MANAGER()->pauseSound(m_SoundId);
	}
*/
	m_Electric->setEnabled(enable);
}
