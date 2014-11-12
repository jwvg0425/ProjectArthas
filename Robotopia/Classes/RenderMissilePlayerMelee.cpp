#include "pch.h"
#include "RenderMissilePlayerMelee.h"

bool Arthas::RenderMissilePlayerMelee::init()
{
	if (!RenderComponent::init())
	{
		return false;
	}

	m_CurrentSprite = nullptr;
	m_Type = RENDER_PLAYER;

	return true;
}

void Arthas::RenderMissilePlayerMelee::enter()
{
}

void Arthas::RenderMissilePlayerMelee::exit()
{
}

void Arthas::RenderMissilePlayerMelee::initRender()
{

}

