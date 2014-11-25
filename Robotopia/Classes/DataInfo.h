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


///# 아래 있는 구조체들, 코딩 컨벤션 맞추고, 기본 생성자 만들고, 멤버 변수 초기화 해라.

struct SpriteInfo
{
	/// 이런식으로
	SpriteInfo() : type(ST_NONE)
	{
		memset(spriteName, 0, sizeof(spriteName));
	}

	ResourceType type;
	char spriteName[MAX_LEN];
};

struct AnimationInfo
{
	ResourceType type;
	char animationName[MAX_FRAME][MAX_LEN];
	int frameNum;
	float delay;
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
	int roomIdx[2]; ///< 이런 상수는 따로 분리해서 모을 것
	int dir;
};

struct RoomData
{
	//StageData 기준 위치. x,y 좌표.
	int x, y;
	size_t width, height;
	std::vector<ComponentType> data;
	std::vector<int> modulePlaceData;
};

struct StageData
{
	///# struct도 클래스다. 생성자 만들고, 멤버 값들 초기화 시켜라.
	///# 그리고 멤버 변수들도 컨벤션을 맞춰라.. mWidth, mHeight, mPortals, ....  
	size_t width, height;
	std::vector<PortalData> portals;
	std::vector<RoomData> Rooms;
};

//플레이어 정보 저장
struct PlayerInfo
{
	///# 당연히 초기화
	int				dir;
	cocos2d::Size	size;
	int				maxHp;
	int				maxSteam;
	int				currentHp;
	int				currentSteam;
	float			speed;
	float			jumpSpeed;
	GearType		gear;
};