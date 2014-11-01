/************************************************************************/
/*
	CLASS			: Info
	Author			: 남현욱
	역할				: 각종 Info 구조체 정의.
	최종 수정일자	: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/


#pragma once
#include "Macro.h"
#include "ResourceType.h"

BEGIN_NS_AT


struct PlayerInfo
{
	int maxHp;
	int maxSteam;
	int hp;
	int steam;
};

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

END_NS_AT