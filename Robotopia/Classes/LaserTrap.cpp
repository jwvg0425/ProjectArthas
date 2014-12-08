#include "pch.h"
#include "LaserTrap.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "DataManager.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "SpriteComponent.h"
#include "cocos2d.h"

bool LaserTrap::init()
{
	if (!Tile::init())
	{
		return false;
	}
	m_Type = OT_LASER;
	m_SpriteType = ST_START; // 임시
	scheduleUpdate();
	return true;
}

void LaserTrap::update(float dTime)
{
	if(m_IsOn)
	{
		m_AccTime += dTime;
		if(m_AccTime > m_Duration)
		{
			m_AccTime = 0.f;
			m_IsOn = false;
			switchTurn(m_IsOn);
		}
	}
	else
	{
		auto time = GET_GAME_MANAGER()->getTime();
		if((time.tv_sec) % MAX_INTERVAL == m_Interval - 1 )
		{
			m_IsOn = true;
			switchTurn(m_IsOn);
		}
	}
}

void LaserTrap::enter()
{

}

void LaserTrap::exit()
{

}

void LaserTrap::initTile(cocos2d::Rect tileRect)
{
	auto tileSize = GET_DATA_MANAGER()->getTileSize();
	setPosition(tileRect.origin);

}

//vertical인 경우 바닥에, horizontal인 경우 왼쪽 벽에 붙여주시죠.
void LaserTrap::setLaser(bool isVertical, int interval)
{
	cocos2d::Rect bodyRect;
	if(isVertical)
	{
		cocos2d::Point curPos = getPosition();
		cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();
		cocos2d::Size moveUnit(0, tileSize.height);
		cocos2d::Point checkPos = curPos - moveUnit; //아래쪽 타일
		int stageNum = GET_STAGE_MANAGER()->getStageNum();
		int roomNum = GET_STAGE_MANAGER()->getRoomNum();
		int checkType = OT_START;

		//제대로 세팅했는지 검사
		checkType = GET_DATA_MANAGER()->getTileData(stageNum, roomNum, checkPos);
		if(checkType != OT_BLOCK)
		{
			cocos2d::log("laser set in wrong position.");
			return;
		}

		auto lower = GET_RESOURCE_MANAGER()->createSprite(ST_LASER_LOWER);
		auto upper = GET_RESOURCE_MANAGER()->createSprite(ST_LASER_UPPER);
		addChild(lower);
		addChild(upper);
		lower->setAnchorPoint(cocos2d::Point::ZERO);
		upper->setAnchorPoint(cocos2d::Point::ZERO);
		lower->setPosition(cocos2d::Point(0, 0));

		m_Laser = cocos2d::Sprite::create();
		addChild(m_Laser, -1);
		m_Laser->setAnchorPoint(cocos2d::Point::ZERO);

		checkType = OT_START;
		checkPos = curPos;
		int height = 0;
		while(true)
		{
			checkType = GET_DATA_MANAGER()->getTileData(stageNum, roomNum, checkPos);
			auto laser = GET_RESOURCE_MANAGER()->createSprite(ST_LASER_RELEASE);
			m_Laser->addChild(laser);
			laser->setPosition(cocos2d::Point(0, height));
			laser->setAnchorPoint(cocos2d::Point::ZERO);
			if(checkType == OT_BLOCK)
			{
				break;
			}
			height += tileSize.height;
			checkPos += moveUnit;
			if(height > MAX_HEIGHT)
			{
				this->release();
				return;
			}
		}

		if(checkType == OT_BLOCK)
		{
			upper->setPosition(cocos2d::Point(0, height - tileSize.height));
		}
		bodyRect = cocos2d::Rect(tileSize.width / 2, 0, LASER_WIDTH, height);
	}
	initPhysicsBody(bodyRect, PHYC_MISSILE);
	m_Interval = interval - OT_LASER;
	switchTurn(m_IsOn);
}

void LaserTrap::switchTurn(bool isOn)
{
	if(m_Laser != nullptr)
	{
		m_Laser->setVisible(isOn);
	}
	if(m_Body != nullptr)
	{
		m_Body->setEnable(isOn);
	}
}

LaserTrap::~LaserTrap()
{
	SAFE_RELEASE(m_Laser);
}

LaserTrap::LaserTrap()
{

}

