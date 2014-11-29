#include "pch.h"
#include "PlayerRender.h"

bool PlayerRender::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}

	m_Parts.resize(PT_MAX);
	for(int i = 0; i < m_Parts.size(); ++i)
	{
		m_Parts[i] = nullptr;
	}

	return true;
}

void PlayerRender::update(float dTime)
{

}

void PlayerRender::enter()
{

}

void PlayerRender::exit()
{

}

void PlayerRender::addPart(RenderPart* part, PartsType type)
{
	if(m_Parts[type] == nullptr)
	{
		m_Parts[type] = part;
	}
}

void PlayerRender::removePart(PartsType type)
{
	if(m_Parts[type] != nullptr)
	{
		m_Parts[type] = nullptr;
	}
}
