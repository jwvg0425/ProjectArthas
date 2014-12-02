/************************************************************************/
/*
CLASS			: AssemblyLineLayer
Author			: 우재우
역할			: 장비를 나열하고 선택한다.
최종 수정일자	: 2014-12-02
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "AssemblyUILayer.h"

class EquipmentHead;
class EquipmentEngine;
class EquipmentArmor;
class EquipmentMelee;
class EquipmentRange;
class EquipmentSteamContainer;
class EquipmentLeg;

class AssemblyLineLayer : public AssemblyUILayer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(AssemblyLineLayer);

private:
	cocos2d::Node*			m_HeadContainer = nullptr;
	cocos2d::Node*			m_EngineContainer = nullptr;
	cocos2d::Node*			m_ArmorContainer = nullptr;
	cocos2d::Node*			m_MeleeContainer = nullptr;
	cocos2d::Node*			m_RangeContainer = nullptr;
	cocos2d::Node*			m_SteamContainer = nullptr;
	cocos2d::Node*			m_LegContainer = nullptr;

	cocos2d::Rect			m_HeadRect = cocos2d::Rect();
	cocos2d::Rect			m_EngineRect = cocos2d::Rect();
	cocos2d::Rect			m_ArmorRect = cocos2d::Rect();
	cocos2d::Rect			m_MeleeRect = cocos2d::Rect();
	cocos2d::Rect			m_RangeRect = cocos2d::Rect();
	cocos2d::Rect			m_SteamRect = cocos2d::Rect();
	cocos2d::Rect			m_LegRect = cocos2d::Rect();

	std::vector<EquipmentHead*>				m_HeadList;
	std::vector<EquipmentEngine*>			m_EngineList;
	std::vector<EquipmentArmor*>			m_ArmorList;
	std::vector<EquipmentMelee*>			m_MeleeList;
	std::vector<EquipmentRange*>			m_RangeList;
	std::vector<EquipmentSteamContainer*>	m_SteamList;
	std::vector<EquipmentLeg*>				m_LegList;

	ConfirmSet				m_ConfirmSet;

	void					initEquipmentContainer();
	void					displayEquipments();
	void					updateEquipments(float dTime);
	void					updateDoubleClickIcon(cocos2d::Point clickPoint);
	void					setConfirmSet(cocos2d::Point mousePosition);
	void					containerScroll(bool moveLeft, cocos2d::Point mousePoint);
};


//Equipment Create with template (봉인)
/*
template <typename T>
void					listUpEquipment(int listStart, int listEnd, cocos2d::Node* container, std::vector<T*>* listPointer);

template <typename T>
void AssemblyUILayer::listUpEquipment(int listStart, int listEnd, cocos2d::Node* container, std::vector<T*>* listPointer)
{
auto testSp = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_DEFAULT);
for (int i = listStart; i < listEnd; ++i)
{
T* equipment = T::create();
(*listPointer).push_back(equipment);
(*listPointer)[i]->setEquipmentIcon(ASSEMBLY_ICON, testSp);
(*listPointer)[i]->getEquipmentIcon()->setIconRect(cocos2d::Point(container->getBoundingBox().getMinX() * RESOLUTION, container->getBoundingBox().getMinY() * RESOLUTION), cocos2d::Point(40 + 70 * i, 35));
container->addChild((*listPointer)[i]);
}
}

listUpEquipment(static_cast<int>(HL_START), static_cast<int>(HL_END), m_HeadContainer, &m_HeadList);
listUpEquipment(static_cast<int>(EL_START), static_cast<int>(EL_END), m_EngineContainer, &m_EngineList);
listUpEquipment(static_cast<int>(AL_START), static_cast<int>(AL_END), m_ArmorContainer, &m_ArmorList);
listUpEquipment(static_cast<int>(ML_START), static_cast<int>(ML_END), m_MeleeContainer, &m_MeleeList);
listUpEquipment(static_cast<int>(RL_START), static_cast<int>(RL_END), m_RangeContainer, &m_RangeList);
listUpEquipment(static_cast<int>(SCL_START), static_cast<int>(SCL_END), m_SteamContainer, &m_SteamList);
listUpEquipment(static_cast<int>(LL_START), static_cast<int>(LL_END), m_LegContainer, &m_LegList);
*/