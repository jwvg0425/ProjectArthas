/************************************************************************/
/*
CLASS			: EquipmentStatusLayer
Author			: 김성연
역할				: Equipment의 status를 보여주는 레이어
최종 수정일자		: 2014-12-01
최종 수정자		: 김성연
최종 수정사유		: 신규
Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "AssemblyUILayer.h"


class ButtonLayer;

class EquipmentStatusLayer : public AssemblyUILayer
{
public:


	struct Equipmentes
	{
		HeadList		   m_CurChosenHead = HL_START;
		ArmorList		   m_CurChosenArmor = AL_START;
		EngineList		   m_CurChosenEngine = EL_START;
		LegList			   m_CurChosenLeg = LL_START;
		MeleeList		   m_CurChosenMelee = ML_START;
		RangeList		   m_CurChosenRangeList = RL_START;
		SteamContainerList m_CurChosenSteamContainerList = SCL_START;

	};

	enum BasicStatus
	{
		BASISSTAUTSSTART = -1,
		LEVEL = 0,
		KWATT,
		UPGRADEPRICE,
		BASISSTATUSEND,
	};

	/*struct CurEquipmentesInfo
	{
	HeadInfo		   m_HeadInfo;
	LegInfo			   m_LegInfo;
	ArmorInfo		   m_ArmorInfo;
	SteamContainerInfo m_SteamContainerInfo;
	MeleeInfo		   m_MeleeInfo;
	RangeInfo		   m_RangeInfo;
	EngineInfo		   m_EngineInfo;
	};*/

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);


	CREATE_FUNC(EquipmentStatusLayer);

	void					setStartEquipmentType(Equipmentes equipmentList);
	void					setBasicLabels();
	void					setButtons();
	void					setAllStatusDescLabels();
	void					setAllStatusValueLabels();


	//라벨 배치
	void					setPosBasicDescLabel();
	void					setPosBasicValueLabel();
	void					setPosAllStatusDescLabel();
	void					setPosAllStatusValueLabel();

	//그외
	void					setCurClickedItem(ClickedItem clickedItem);


private:
	//ComponentType		   
	//curEquipmentesInfo     m_CurEquipmentInfo;
	Equipmentes							m_CurBeInstalledEquipmentes;
	Equipmentes							m_CurBeChosenEquipmentDetail;
	EquipmentType						m_CurBeChosenEquipType = EMT_START;
	ButtonLayer*						m_UpgradeButton = nullptr;
	ButtonLayer*						m_EquipButton = nullptr;
	ClickedItem							m_PrevClickedItem;
	ClickedItem							m_CurClickedItem;

	std::string			   				m_StautsString[20];
	std::vector<cocos2d::Label*>		m_BasicStatusDesc;
	std::vector<cocos2d::Label*>		m_BasicStatusValue;
	std::vector<cocos2d::Label*>		m_AllStatusDesc;
	std::vector<cocos2d::Label*>		m_AllStatusValue;

};