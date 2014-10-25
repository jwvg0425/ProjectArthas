#pragma once
#include "Component.h"
#include <vector>

class StateComponent;

class FSMComponent : public Component
{
public:
	virtual void update(float dTime);
	virtual void enter() = 0;
	virtual void exit() = 0;
protected:
	StateComponent* m_NowState;
	std::vector<StateComponent*> m_States;
};