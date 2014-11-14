/************************************************************************/
/*
	CLASS			: DataType
	Author			: 남현욱
	역할				: enum 및 typedef 등 프로젝트 내에서 쓰이는
					  각종 고유 정의 타입들 보유
	최종 수정일자	: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유	: 한 파일에 너무 많은 내용이 몰려있어 여러 개의 파일로 분리함.
	Comment			: 이런 형식으로 앞으로 바꾸는 사람이 있으면 정리 하세요
*/
/************************************************************************/

#pragma once
#include <utility>
#include "ComponentType.h"
#include "EffectType.h"
#include "InputType.h"
#include "DataInfo.h"
#include "ResourceType.h"
#include "SceneType.h"
#include "TriggerType.h"
#include "PhysicsType.h"
#include "EtcType.h"
#include "RawTileType.h"

BEGIN_NS_AT

class Trigger;
class Component;

enum DirectionBit
{
	DIR_NONE = 0,
	DIR_UP = 1,
	DIR_RIGHT =2,
	DIR_DOWN = 4,
	DIR_LEFT = 8,
	DIR_MAX = 16,
};

typedef char Direction;

typedef std::pair<Trigger*, Component*> Transition;

END_NS_AT