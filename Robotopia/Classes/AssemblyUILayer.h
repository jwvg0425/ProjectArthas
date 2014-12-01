/************************************************************************/
/*
CLASS			: RobotAssemblyLayer
Author			: 우재우
역할			: GameScene 시작 시 로봇 조립창을 보여줌
최종 수정일자	: 2014-11-23
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "UILayer.h"
#include "EquipmentAbstract.h"

class ButtonLayer;
class IconLayer;
class EquipmentHead;
class EquipmentEngine;
class EquipmentArmor;
class EquipmentMelee;
class EquipmentRange;
class EquipmentSteamContainer;
class EquipmentLeg;
class EquipmentStatusLayer;

class AssemblyUILayer : public UILayer
{
public:
	AssemblyUILayer();
	~AssemblyUILayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(AssemblyUILayer);

private:
	bool					m_IsStarted = false;

	EquipmentStatusLayer*   m_EquipStatusLayer = nullptr;
	cocos2d::Sprite*		m_AssemblyBackground = nullptr;
	cocos2d::Sprite*		m_AssemblyFrame = nullptr;
	cocos2d::Sprite*		m_ViewChangeArrow = nullptr;
	cocos2d::Sprite*		m_DisplayScanBar = nullptr;
	cocos2d::Rect			m_viewChangeRect;

	ButtonLayer*			m_ButtonConfirm = nullptr;
	ButtonLayer*			m_ButtonCancel = nullptr;

	cocos2d::Node*			m_HeadContainer = nullptr;
	cocos2d::Node*			m_EngineContainer = nullptr;
	cocos2d::Node*			m_ArmorContainer = nullptr;
	cocos2d::Node*			m_MeleeContainer = nullptr;
	cocos2d::Node*			m_RangeContainer = nullptr;
	cocos2d::Node*			m_SteamContainer = nullptr;
	cocos2d::Node*			m_LegContainer = nullptr;

	cocos2d::Node*			m_BearSkillContainer = nullptr;
	cocos2d::Node*			m_MonkeySkillContainer = nullptr;
	cocos2d::Node*			m_EagleSkillContainer = nullptr;
	cocos2d::Node*			m_CommonSkillContainer = nullptr;

	cocos2d::Rect			m_EquipmentRect = cocos2d::Rect();
	cocos2d::Rect			m_HeadRect = cocos2d::Rect();
	cocos2d::Rect			m_EngineRect = cocos2d::Rect();
	cocos2d::Rect			m_ArmorRect = cocos2d::Rect();
	cocos2d::Rect			m_MeleeRect = cocos2d::Rect();
	cocos2d::Rect			m_RangeRect = cocos2d::Rect();
	cocos2d::Rect			m_SteamRect = cocos2d::Rect();
	cocos2d::Rect			m_LegRect = cocos2d::Rect();

	cocos2d::Rect			m_BearSkillRect = cocos2d::Rect();
	cocos2d::Rect			m_MonkeySkillRect = cocos2d::Rect();
	cocos2d::Rect			m_EagleSkillRect = cocos2d::Rect();
	cocos2d::Rect			m_CommonSkillRect = cocos2d::Rect();

	std::vector<EquipmentHead*>				m_HeadList;
	std::vector<EquipmentEngine*>			m_EngineList;
	std::vector<EquipmentArmor*>			m_ArmorList;
	std::vector<EquipmentMelee*>			m_MeleeList;
	std::vector<EquipmentRange*>			m_RangeList;
	std::vector<EquipmentSteamContainer*>	m_SteamList;
	std::vector<EquipmentLeg*>				m_LegList;

	struct ConfirmSet
	{
		HeadList							m_Head = HL_START;
		EngineList							m_Engine = EL_START;
		ArmorList							m_Armor = AL_START;
		MeleeList							m_Melee = ML_START;
		RangeList							m_Range = RL_START;
		SteamContainerList					m_Steam = SCL_START;
		LegList								m_Leg = LL_START;
	};
	ConfirmSet								m_ConfirmSet;
	
	AssemblyLayerType		m_CurrentAssembly = NO_ASSEMBLY_LAYER;

	void					equipmentContainerInit();
	void					assemblyLayerButtonInit();

	void					displayEquipments();
	void					updateEquipments(float dTime);
	void					updateDoubleClickIcon(cocos2d::Point clickPoint);
	void					setConfirmSet(cocos2d::Point mousePosition);
	
	template <typename T, typename T2>
	void					setConfirmSet2(std::vector<T*>* equipmentList, T2 confirmedPart, int listStart, int listEnd);

	void					viewChange(AssemblyLayerType moveViewTo);
	void					equipmentContainerVisible(bool visible);
	void					moveScanBar();
	void					moveContainer(bool moveLeft, cocos2d::Node* container, cocos2d::Rect containerRect);
	void					containerScroll(bool moveLeft, cocos2d::Point mousePoint);
	void					confirmAssembly();
	void					toTitleScene();

};

/* T = Equipment *//* T2 = EquipmentList */
template <typename T, typename T2>
void AssemblyUILayer::setConfirmSet2(std::vector<T*>* equipmentList, T2 confirmedPart, int listStart, int listEnd)
{
	T2 temp = confirmedPart;
	for (int i = listStart + 1; i < listEnd; ++i)
	{
		if ((*equipmentList)[i]->getEquipmentIcon()->getSelected())
		{
			if (confirmedPart == static_cast<T2>(listStart));
			{
				confirmedPart = (*equipmentList)[i]->getEquipmentInfo().m_Type;
			}
			else if (temp != (*equipmentList)[i]->getEquipmentInfo().m_Type)
			{
				confirmedPart = (*equipmentList)[i]->getEquipmentInfo().m_Type;
				(*equipmentList)[i]->setEquipmentIcon(ICON_SELECTED);
			}
			else if (temp == (*equipmentList)[i]->getEquipmentInfo().m_Type)
			{
				(*equipmentList)[i]->setEquipmentIcon(ICON_DEFAULT);
			}
		}
	}
}

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
