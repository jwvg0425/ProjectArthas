#pragma once
#include "Util.h"

BEGIN_NS_AT

enum RawTileType
{
	RT_NONE = 0,
	RT_BLOCK = OT_BLOCK,
	RT_FLOOR = OT_FLOOR,
	RT_BLOCK_RANDOM = 1,
	RT_TRAP_RANDOM = 2,
	RT_MONSTER_RANDOM = 3,
};

END_NS_AT