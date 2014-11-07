#include "pch.h"
#include "Component.h"
#include "ComponentManager.h"
#include "CommandComponent.h"
#include "FSMComponent.h"
#include "ObserverComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "Player.h"
#include "Block.h"

Arthas::ComponentManager::ComponentManager()
{

}

Arthas::ComponentManager::~ComponentManager()
{

}

bool Arthas::ComponentManager::init()
{
	return true;
}



