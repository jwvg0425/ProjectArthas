/************************************************************************/
/*
	CLASS			: PhysicsType
	Author			: 남현욱
	역할				: 물리와 관련된 enum값 정의.
	최종 수정일자	: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"



enum ContactType
{
	CTT_NONE = 0,
	CTT_CONTACT,
	CTT_SEPARATE,
	CTT_IGNORE,
};

enum PhysicsCategory
{
	PHYC_NONE = 0x00000000,
	PHYC_PLAYER = 0x00000001,
	PHYC_BLOCK = 0x00000002,
	PHYC_FLOOR = 0x00000004,
	PHYC_MISSILE = 0x00000008,
	PHYC_MONSTER = 0x00000010,
	PHYC_ALL = 0xffffffff,
};

