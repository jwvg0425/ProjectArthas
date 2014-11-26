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
	AnimationType type = AT_START;
	char animationName[MAX_FRAME][MAX_LEN];
	int frameNum = 0;
	float delay = 0.f;
};

struct ModuleData
{
	std::string name;
	std::vector<RawTileType> data;
};

//roomIdx[0]과 roomIdx[1]이 pos위치에서 roomIdx[0]의 dir 방향으로 연결되어있다는 의미. pos 위치에는 roomIdx[0]번째 방이 존재.
struct PortalData
{
	cocos2d::Point pos;
	int roomIdx[2];
	int dir = 0;
};

struct RoomData
{
	//StageData 기준 위치. x,y 좌표.
	int x = -1, y = -1;
	size_t width, height;
	std::vector<ComponentType> data;
	std::vector<int> modulePlaceData;
};

struct StageData
{
	size_t width, height;
	std::vector<PortalData> portals;
	std::vector<RoomData> Rooms;
};

//플레이어 정보 저장
struct PlayerInfo
{
	cocos2d::Size	size;
	GearType		gear = GEAR_NONE;
	int				dir = 0;
	int				maxHp = 0;
	int				maxSteam = 0;
	int				currentHp = 0;
	int				currentSteam = 0;
	float			speed = 0.f;
	float			jumpSpeed = 0.f;
};