/************************************************************************/
/*
	CLASS			: MapData
	Author			: 남현욱
	역할				: Map Data와 관련된 구조체 정의.
	최종 수정일자	: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "ComponentType.h"
#include <vector>

BEGIN_NS_AT

struct ModuleData
{
	size_t width, height;
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