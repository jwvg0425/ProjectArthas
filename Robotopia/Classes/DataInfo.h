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
#include <vector>



struct SpriteInfo
{
	SpriteType type = ST_START;
	char spriteName[MAX_LEN];
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
};

//roomIdx[0]과 roomIdx[1]이 pos위치에서 roomIdx[0]의 dir 방향으로 연결되어있다는 의미. pos 위치에는 roomIdx[0]번째 방이 존재.
struct PortalData
{
	cocos2d::Point m_Pos;
	int m_RoomIdx[2];
	int m_Dir = 0;
};

struct RoomData
{
	//StageData 기준 위치. x,y 좌표.
	int m_X = -1, m_Y = -1;
	size_t m_Width, m_Height;
	std::vector<ComponentType> m_Data;
	std::vector<int> m_ModulePlaceData;
};

struct StageData
{
	size_t m_Width, m_Height;
	std::vector<PortalData> m_Portals;
	std::vector<RoomData> m_Rooms;
};

//플레이어 정보 저장
struct PlayerInfo
{
	cocos2d::Size	m_Size;
	GearType		m_Gear = GEAR_NONE;
	int				m_Dir = 0;
	int				m_MaxHp = 0;
	int				m_MaxSteam = 0;
	int				m_CurrentHp = 0;
	int				m_CurrentSteam = 0;
	float			m_Speed = 0.f;
	float			m_JumpSpeed = 0.f;
};