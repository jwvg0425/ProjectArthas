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
	auto engine = RenderPart::create();
	engine->addAnimation(this, AT_PLAYER_PARTS_ENGENE, Player::STAT_IDLE);
	addPart(engine, PT_ENGENE);

	auto armor = RenderPart::create();
	armor->addAnimation(this, AT_PLAYER_PARTS_ARMOR, Player::STAT_IDLE);
	addPart(armor, PT_ARMOR);

	auto range = RenderPart::create();
	range->addAnimation(this, AT_PLAYER_PARTS_RANGE, Player::STAT_IDLE);
	addPart(range, PT_RANGE);

	auto melee = RenderPart::create();
	melee->addAnimation(this, AT_PLAYER_PARTS_MELEE, Player::STAT_IDLE);
	addPart(melee, PT_MELEE);

	auto leg = RenderPart::create();
	leg->addAnimation(this, AT_PLAYER_PARTS_LEG, Player::STAT_IDLE);
	addPart(leg, PT_LEG);

	auto head = RenderPart::create();
	head->addAnimation(this, AT_PLAYER_PARTS_HEAD, Player::STAT_IDLE);
	addPart(head, PT_HEAD);

	setScaleY(0.6f);
	return true;
}

void PlayerRenderer::addPart(RenderPart* part, PartsType type)
{
	if(m_Parts[type] == nullptr)
	{
		int zOrder = 0;
		m_Parts[type] = part;
		switch(type)
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
		addChild(part, zOrder);
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

void PlayerRenderer::changeState(Player::State state)
{
	for(auto part : m_Parts)
	{
		part->changeState(state);
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

