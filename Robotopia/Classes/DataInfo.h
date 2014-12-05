/************************************************************************/
/*
	CLASS			: MapData
	Author			: 남현욱
	역할				: 파일 입출력 관련 각종 Data 구조체 정의.
	최종 수정일자	: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "ComponentType.h"
#include "ResourceType.h"
#include "RawTileType.h"
#include "GearType.h"
#include "Config.h"
#include <vector>

//임시 지정 상수값 - micro second 단위.
#define TIME_KNOCKBACK 500 //넉백 0.5초
#define TIME_INVINCIBLE 2500 //무적 0.8초



struct SpriteInfo
{
	SpriteType m_Type = ST_START;
	char m_SpriteName[MAX_LEN];
};

struct AnimationInfo
{
	AnimationType m_Type = AT_START;
	char m_AnimationName[MAX_FRAME][MAX_LEN];
	int m_FrameNum = 0;
	float m_Delay = 0.f;
};

struct ModuleData
{

	std::string m_Name;
	std::vector<RawTileType> m_Data;
	RoomConfig::RoomType m_Type = RoomConfig::NORMAL;
};

//
struct PortalData
{
	cocos2d::Point m_Pos;
	int m_ConnectedRoomIdx;
	int m_Dir = 0;
};

struct RoomData
{
	//StageData 기준 위치. x,y 좌표.
	int m_X = -1, m_Y = -1;
	size_t m_Width, m_Height;
	std::vector<int> m_Data;
	std::vector<int> m_ModulePlaceData;
	std::vector<PortalData> m_Portals;
};

struct StageData
{
	size_t m_Width, m_Height;
	std::vector<RoomData> m_Rooms;
};

struct AllStatus
{
	//head
	float		m_CoolDown = 0.f;
	float		m_Mainmemory = 0.f;
	//engine
	float		m_ElectronicPower = 0.f;
	float       m_SteamEffectiveness = 0.f;
	//armor
	float       m_DefensivePower = 0.f;
	float		m_Resistance = 0.f;
	//steamcontainer
	float       m_MaxSteam = 0.f;
	float		m_AbsorbEffectiveness = 0.f;
	//melee
	float		m_MeleeDamage = 0.f;
	float       m_MeleeAttackSpeed = 0.f;
	//range
	float       m_RangeDamage = 0.f;
	float		m_RangeAttackSpeed = 0.f;
	float		m_AttackRange = 0.f;
	//leg
	float		m_Speed = 0.f;
	float		m_Jump = 0.f;

};

//플레이어 정보 저장
struct PlayerInfo : AllStatus
{
	cocos2d::Size	m_Size;
	GearType		m_Gear = GEAR_NONE;
	int				m_UpperDir = 0;
	int				m_LowerDir = 0;
	int				m_MaxHp = 0;
	int				m_MaxSteam = 0;
	int				m_CurrentHp = 0;
	int				m_CurrentSteam = 0;
	float			m_Speed = 0.f;
	float			m_JumpSpeed = 0.f;
	int				m_BitCoin = 0;
};