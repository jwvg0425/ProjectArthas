/************************************************************************/
/*
CLASS			: ItemType
Author			: 김성연
역할			: Item에 필요한 enum 관리
최종 수정일자	: 2014-11-27
최종 수정자		: 김성연
최종 수정사유	: 신규(아이템 타입)
Comment			:
*/
/************************************************************************/
#pragma once
#include "Util.h"

#define MAX_EQUIPMENT_TYPE 7

enum EquipmentType
{
	EMT_START = -1,
	EMT_HEAD,
	EMT_ENGINE,
	EMT_ARMOR,
	EMT_MELEE,
	EMT_RANGE,
	EMT_STEAMCONTAINER,
	EMT_LEG,
	EMT_END,
	EMT_NUM = EMT_END,
};

enum HeadList
{
	HL_START = -1,
	HL_PENTIUM,
	HL_DUALCORE,
	HL_TRIPLE,
	HL_QUAD,
	HL_HEXA,
	HL_TEST,
	HL_VVV,
	HL_IRONMAN,
	HL_HIBA,
	HL_TEST1,
	HL_VVV2,
	HL_IRONMAN3,
	HL_HIBA4,
	HL_END,
};

enum EngineList
{
	EL_START = -1,
	EL_STEAM,
	EL_NUCLEAR,
	EL_THIRD,
	EL_FORTH,
	EL_AAA,
	EL_FIFI,
	EL_SKWWW,
	EL_END,
};

enum ArmorList
{
	AL_START = -1,
	AL_PLASTIC,
	AL_COPPER,
	AL_THIRD,
	AL_FORTH,
	AL_FIFTH,
	AL_SE,
	AL_VBBB,
	AL_END,
};

enum MeleeList
{
	ML_START = -1,
	ML_HAMMER,
	ML_ZEALOTBLADE,
	ML_THIRD,
	ML_FORTH,
	ML_FIFTH,
	ML_DDD,
	ML_CCC,
	ML_END,
};

enum RangeList
{
	RL_START = -1,
	RL_STEAMGUN,
	RL_60MMMORTAR,
	RL_THIRD,
	RL_FORTH,
	RL_FIFTH,
	RL_DKDK,
	RL_END,
};

enum SteamContainerList
{
	SCL_START = -1,
	SCL_MASSPRODUCTIONTYPE,
	SCL_IMPROVEDMODEL,
	SCL_THIRD,
	SCL_FORTH,
	SCL_FIFTH,
	SCL_SIXTH,
	SCL_SEVENTH,
	SCL_END,
};

enum LegList
{
	LL_START = -1,
	LL_LEWIS,
	LL_BOLT,
	LL_THIRD,
	LL_FORTH,
	LL_FIFTH,
	LL_JJKKK,
	LL_KDJKF,
	LL_END,
};

struct ConfirmSet
{
	HeadList				m_Head = HL_START;
	EngineList				m_Engine = EL_START;
	ArmorList				m_Armor = AL_START;
	MeleeList				m_Melee = ML_START;
	RangeList				m_Range = RL_START;
	SteamContainerList		m_Steam = SCL_START;
	LegList					m_Leg = LL_START;
};

struct ClickedItem
{
	EquipmentType			m_Type = EMT_START;
	int						m_ListItem = -1;
};