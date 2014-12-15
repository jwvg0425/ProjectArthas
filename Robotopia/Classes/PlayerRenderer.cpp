#include "pch.h"
#include "PlayerRenderer.h"
#include "RenderPart.h"
#include "GameManager.h"
#include "DataManager.h"
#include "EquipmentAbstract.h"

bool PlayerRenderer::init()
{
	if(!Node::init())
	{
		return false;
	}

	m_Parts.resize(EMT_END);
	for(int i = 0; i < m_Parts.size(); ++i)
	{
		m_Parts[i] = nullptr;
	}


	setScale(0.2f);
	return true;
}

void PlayerRenderer::addPart(PartsRenderInfo info)
{
	if(m_Parts[info.m_EquipmentType] == nullptr)
	{
		auto renderPart = RenderPart::create();
		renderPart->addAnimation(this, static_cast<AnimationType>(info.m_AnimationType), 
								 info.m_FSMIdx, static_cast<Player::State>(info.m_State));
		int zOrder = 0;
		m_Parts[info.m_EquipmentType] = renderPart;
		switch(info.m_EquipmentType)
		{
			case EMT_HEAD:
				zOrder = 3;
				break;
			case EMT_ENGINE:
				zOrder = 0;
				break;
			case EMT_ARMOR:
				zOrder = 2;
				break;
			case EMT_MELEE:
				zOrder = 3;
				break;
			case EMT_RANGE:
				zOrder = 1;
				break;
			case EMT_STEAMCONTAINER:
				zOrder = 0;
				break;
			case EMT_LEG:
				zOrder = 1;
				break;
			default:
				break;
		}
		addChild(renderPart, zOrder);
	}
}

void PlayerRenderer::removePart(EquipmentType type)
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

void PlayerRenderer::initRendererFromData()
{
	ConfirmSet set;
	EquipmentType equipType;
	const EquipmentInfo* equipInfo;
	for(int emt = EMT_HEAD; emt < EMT_END; emt++)
	{
		equipType = static_cast<EquipmentType>( emt );
		set = GET_DATA_MANAGER()->getEquipmentItem();
		equipInfo = GET_DATA_MANAGER()->getEquipmentBaseInfo(equipType, set.getItemType(equipType));
		for(auto renderInfo : equipInfo->m_PartsRenderInfos)
		{
			addPart(renderInfo);
		}
	}
}

