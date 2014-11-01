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
	size_t width;
	size_t height;
	std::vector<ComponentType> data;
};

//현재 룸 데이터의 구성과 모듈 데이터의 구성은 동일. 이후 바뀔 시 새로 정의하는 걸로.
typedef ModuleData RoomData;

struct StageData
{
	//모듈 기준으로 방들의 배치도를 저장.
	size_t width;
	size_t height;
	std::vector<int> data;
};

END_NS_AT