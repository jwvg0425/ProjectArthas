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

class ButtonLayer;
class IconLayer;
class EquipmentHead;
class EquipmentEngine;
class EquipmentArmor;
class EquipmentMelee;
class EquipmentRange;
class EquipmentSteamContainer;
class EquipmentLeg;

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

	cocos2d::Rect			m_EquipmentRect = cocos2d::Rect();
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

	AssemblyLayerType		m_CurrentAssembly = NO_ASSEMBLY_LAYER;

	void					equipmentContainerInit();
	void					assemblyLayerButtonInit();
	void					displayEquipments();
	void					setContainerSize();
	
	template <typename T>
	void					listUpEquipment(int listStart, int listEnd, cocos2d::Node* container, std::vector<T*>* listPointer);
	void					updateEquipments(float dTime);
	void					moveContainer(bool moveLeft, cocos2d::Node* container, cocos2d::Rect containerRect);


	void					viewChange(AssemblyLayerType moveViewTo);
	void					moveScanBar();

	void					equipmentContainerVisible(bool visible);
	void					confirmAssembly();
	void					toTitleScene();

};

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

