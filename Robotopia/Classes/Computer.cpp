#include "pch.h"
#include "Computer.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"

bool Computer::init()
{
	if(!NPC::init())
	{
		return false;
	}
	m_Type = OT_COMPUTER;
	m_Info.m_Size = cocos2d::Size(COMPUTER_WIDTH, COMPUTER_HEIGHT);
	bodyInit(m_Info.m_Size);
	auto sprite = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	sprite->initSprite(ST_COMPUTER_NORMAL, this);
	addComponent(sprite);
	return true;
}

void Computer::update(float dTime)
{

}

void Computer::exit()
{

}

void Computer::enter()
{

}
