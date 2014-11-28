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
class EquipmentSteam;
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
	cocos2d::Sprite*		m_viewChangeArrow = nullptr;
	cocos2d::Rect			m_viewChangeRect;

	ButtonLayer*			m_ButtonConfirm;
	ButtonLayer*			m_ButtonCancel;

	cocos2d::Node*			m_HeadContainer = nullptr;
	cocos2d::Node*			m_EngineContainer = nullptr;
	cocos2d::Node*			m_ArmorContainer = nullptr;
	cocos2d::Node*			m_MeleeContainer = nullptr;
	cocos2d::Node*			m_RangeContainer = nullptr;
	cocos2d::Node*			m_SteamContainer = nullptr;
	cocos2d::Node*			m_LegContainer = nullptr;

	std::vector<EquipmentHead*>		m_HeadList;
	std::vector<EquipmentEngine*>	m_EngineList;
	std::vector<EquipmentArmor*>	m_ArmorList;
	std::vector<EquipmentMelee*>	m_MeleeList;
	std::vector<EquipmentRange*>	m_RangeList;
	std::vector<EquipmentSteam*>	m_SteamList;
	std::vector<EquipmentLeg*>		m_LegList;

	AssemblyLayerType		m_CurrentAssembly = NO_ASSEMBLY_LAYER;
	void					viewChange(AssemblyLayerType moveViewTo);

	void					confirmAssembly();
	void					toTitleScene();

};