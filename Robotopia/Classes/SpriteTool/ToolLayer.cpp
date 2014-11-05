#include "SpriteTool/ToolLayer.h"
#include "GameManager.h"
#include "InputManager.h"

bool Arthas::ToolLayer::init()
{
	if (!cocos2d::LayerColor::initWithColor(cocos2d::Color4B(255,255,255,255)))
	{
		return false;
	}

	//GET_INPUT_MANAGER()->receiveKeyboardData(this);
	m_PhysicsWorld = nullptr;

	
	return true;
}

void Arthas::ToolLayer::update(float dTime)
{
	
}



void Arthas::ToolLayer::setPhysicsWorld(cocos2d::PhysicsWorld* physicsWorld)
{
	if (physicsWorld != nullptr)
	{
		m_PhysicsWorld = physicsWorld;
	}
}


