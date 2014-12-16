
#pragma once

class SpriteComponent;
class Creature;
typedef std::function<void(Creature*, double, int)> FSMFunction;
typedef std::vector<FSMFunction> FSMFunctions;
typedef std::vector<SpriteComponent*> Render;

struct FSMChange
{
	enum
	{
		STAT_SKILL = -1,
	};
	FSMChange(int gear, int idx, int state, bool isTransition, FSMFunction function)
	:m_Gear(gear), m_Idx(idx), m_State(state), m_IsTransition(isTransition), m_Function(function){}
	int m_Gear;
	int m_Idx;
	int m_State;
	bool m_IsTransition;
	FSMFunction m_Function;
};

struct SkillFSM
{
	std::vector<FSMChange> m_FSMChanges;
};