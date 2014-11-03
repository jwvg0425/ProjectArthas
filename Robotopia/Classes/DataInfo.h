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
#include <vector>

BEGIN_NS_AT

struct SpriteInfo
{
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
	std::vector<ComponentType> data;
};

struct RoomData
{
	//StageData 기준 위치. x,y 좌표.
	int x, y;
	size_t width, height;
	std::vector<ComponentType> data;
};

struct StageData
{
	size_t width, height;
	std::vector<RoomData> Rooms;
};



END_NS_AT