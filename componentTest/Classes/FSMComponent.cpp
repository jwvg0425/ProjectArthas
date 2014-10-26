#pragma once
#include "FSMComponent.h"
#include "Trigger.h"
#include "StateComponent.h"

void FSMComponent::update(float dTime)
{

	m_NowState->update(dTime);
	
	Event* event = m_NowState->hasEvent();

	if (event)
	{
		m_NowState->exit();
		m_NowState = event->second;
		m_NowState->enter();
	}
}

void FSMComponent::addState(StateComponent* state)
{
	m_States.push_back(state);
}

void FSMComponent::removeState(StateComponent* remState)
{
	for (auto& it = m_States.begin(); it != m_States.end();)
	{
		StateComponent* state = *it;

		if (state->getType() == remState->getType())
		{
			delete state;
			it = m_States.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void FSMComponent::removeAllState()
{
	for (auto& state : m_States)
	{
		delete state;
	}

	m_States.clear();
}
