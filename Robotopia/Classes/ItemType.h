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
	EMT_START = 0,
	EMT_HEAD = EMT_START,
	EMT_ENGIENE,
	EMT_ARMOR,
	EMT_MELEE,
	EMT_RANGE,
	EMT_STEAMCONTAINTER,
	EMT_LEG,
	EMT_END,
};

enum HeadList
{
	HL_START = 0,
	HL_SINGLE = HL_START,
	HL_DOUBLE,
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
	EL_START = 0,
	EL_FIRST = EL_START,
	EL_SECOND,
	EL_THIRD,
	EL_FORTH,
	EL_FIFTH,
	EL_SIXTH,
	EL_SEVENTH,
	EL_END,
};

enum ArmorList
{
	AL_START = 0,
	AL_FIRST = AL_START,
	AL_SECOND,
	AL_THIRD,
	AL_FORTH,
	AL_FIFTH,
	AL_SE,
	AL_VBBB,
	AL_END,
};

enum MeleeList
{
	ML_START = 0,
	ML_FIRST = ML_START,
	ML_SECOND,
	ML_THIRD,
	ML_FORTH,
	ML_FIFTH,
	ML_DDD,
	ML_CCC,
	ML_END,
};

enum RangeList
{
	RL_START = 0,
	RL_FIRST = RL_START,
	RL_SECOND,
	RL_THIRD,
	RL_FORTH,
	RL_FIFTH,
	RL_DKDK,
	RL_END,
};

enum SteamContainerList
{
	SCL_START = 0,
	SCL_FIRST = SCL_START,
	SCL_SECOND,
	SCL_THIRD,
	SCL_FORTH,
	SCL_FIFTH,
	SCL_END,
};

enum LegList
{
	LL_START = 0,
	LL_FIRST = LL_START,
	LL_SECOND,
	LL_THIRD,
	LL_FORTH,
	LL_FIFTH,
	LL_JJKKK,
	LL_KDJKF,
	LL_END,
};