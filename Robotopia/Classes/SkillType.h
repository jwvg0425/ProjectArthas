/************************************************************************/
/*
CLASS			: SkillType
Author			: 우재우
역할			: Skill Type 관리
최종 수정일자	: 2014-12-12
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once

enum SkillType
{
	SKILL_START = -1,
	SKILL_BEAR,
	SKILL_MONKEY,
	SKILL_EAGLE,
	SKILL_COMMON,
	SKILL_END,
	SKILL_NUM = SKILL_END,
};

enum BearSkill
{
	BEAR_START = -1,
	BEAR_SUPER_ARMOR,
	BEAR_JONYA, //순간무적
	BEAR_SUPER_DASH,
	BEAR_CRICAL_PUNCH,
	BEAR_STUN,
	BEAR_EMOLATION,
	BEAR_ATTACK_REFLECT,
	BEAR_END,
};

enum MonkeySkill
{
	MONKEY_START = -1,
	MONKEY_BIND,
	MONKEY_GRENADE,
	MONKEY_MINE,
	MONKEY_KNOCK_BACK,
	MONKEY_SHIELD,
	MONKEY_DUMMY,
	MONKEY_ROLLING,
	MONKEY_END,
};

enum EagleSkill
{
	EAGLE_START = -1,
	EAGLE_FLYING_ATTACK,
	EAGLE_MISSILE_RADIATION,
	EAGLE_BULLET_REMOVER,
	EAGLE_STEALTH,
	EAGLE_FLASH,
	EAGLE_NAPALM,
	EAGLE_END,
};

enum CommonSkill
{
	COMMON_START = -1,
	COMMON_DOUBLE_JUMP,
	COMMON_DASH,
	COMMON_BACKSTEP,
	COMMON_NAP,
	COMMON_END,
};

struct SkillInfo
{
	SkillType	m_SkillType = SKILL_START;
	int			m_Skill = -1;
	int			m_MemoryCost = 0;
	float		m_SteamCost = 0;
	float		m_CoolTime = 0;
	bool		m_IsLock = true;
};

struct SkillSet
{
	BearSkill		m_BearSkill = BEAR_START;
	MonkeySkill		m_MonkeySkill = MONKEY_START;
	EagleSkill		m_EagleSkill = EAGLE_START;
	CommonSkill		m_CommonSkill = COMMON_START;
};