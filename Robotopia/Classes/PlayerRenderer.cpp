#include "pch.h"
#include "PlayerRenderer.h"
#include "RenderPart.h"

bool PlayerRenderer::init()
{
	if(!Node::init())
	{
		return false;
	}

	m_Parts.resize(PT_MAX);
	for(int i = 0; i < m_Parts.size(); ++i)
	{
		m_Parts[i] = nullptr;
	}

	//test code
// 	PartsRenderInfo renderInfo;
// 	renderInfo.m_AnimationType = AT_PLAYER_PARTS_ENGENE;
// 	renderInfo.m_FSMIdx = 0;
// 	renderInfo.m_State = Player::STAT_IDLE;
// 	renderInfo.m_PartType = PT_ENGENE;
// 	addPart(renderInfo);
// 
// 	renderInfo.m_AnimationType = AT_PLAYER_PARTS_ARMOR;
// 	renderInfo.m_PartType = PT_ARMOR;
// 	addPart(renderInfo);
// 
// 	renderInfo.m_AnimationType = AT_PLAYER_PARTS_RANGE;
// 	renderInfo.m_PartType = PT_RANGE;
// 	addPart(renderInfo);
// 
// 	renderInfo.m_AnimationType = AT_PLAYER_PARTS_MELEE;
// 	renderInfo.m_PartType = PT_MELEE;
// 	addPart(renderInfo);
// 
// 	renderInfo.m_AnimationType = AT_PLAYER_PARTS_LEG;
// 	renderInfo.m_PartType = PT_LEG;
// 	addPart(renderInfo);
// 
// 	renderInfo.m_AnimationType = AT_PLAYER_PARTS_HEAD;
// 	renderInfo.m_PartType = PT_HEAD;
// 	addPart(renderInfo);


	setScaleY(0.6f);
	return true;
}

void PlayerRenderer::addPart(PartsRenderInfo info)
{
	if(m_Parts[info.m_PartType] == nullptr)
	{
		auto renderPart = RenderPart::create();
		renderPart->addAnimation(this, static_cast<AnimationType>(info.m_AnimationType), 
								 info.m_FSMIdx, static_cast<Player::State>(info.m_State));
		int zOrder = 0;
		m_Parts[info.m_PartType] = renderPart;
		switch(info.m_PartType)
		{
			case PlayerRenderer::PT_ENGENE:
				zOrder = 0;
				break;
			case PlayerRenderer::PT_ARMOR:
				zOrder = 2;
				break;
			case PlayerRenderer::PT_RANGE:
				zOrder = 1;
				break;
			case PlayerRenderer::PT_MELEE:
				zOrder = 3;
				break;
			case PlayerRenderer::PT_LEG:
				zOrder = 1;
				break;
			case PlayerRenderer::PT_HEAD:
				zOrder = 3;
				break;
			default:
				break;
		}
		addChild(renderPart, zOrder);
	}
}

void PlayerRenderer::removePart(PartsType type)
{
	if(m_Parts[type] != nullptr)
	{
		removeChild(m_Parts[type]);
		m_Parts[type] = nullptr;
	}
}

void PlayerRenderer::changeState(int fsmIdx, Player::State state)
{
	for(auto part : m_Parts)
	{
		part->changeState(fsmIdx, state);
	}
}

void PlayerRenderer::update(float dTime)
{

}

void PlayerRenderer::enter()
{

} 

void PlayerRenderer::exit()
{

}

void PlayerRenderer::flipUpperBody(bool isLeft)
{
	for(int i = 0; i < PT_MAX; ++i)
	{
		if(i != PT_LEG)
		{
			m_Parts[i]->setFlip(isLeft);
		}
	}
}

void PlayerRenderer::flipLowerBody(bool isLeft)
{
	m_Parts[PT_LEG]->setFlip(isLeft);
}

