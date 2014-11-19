#include "pch.h"
#include "Thing.h"

void Thing::update(float dTime)
{
	for (auto& BaseComponent : getChildren())
	{
		BaseComponent->update(dTime);
	}

	for (int i = 0; i < m_States.size(); i++)
	{
		int state = m_States[i];
		if (m_FSMs[i][state] != nullptr)
		{
			m_FSMs[i][state](this, dTime, i);
		}

		if (m_Transitions[i][state] != nullptr)
		{
			m_Transitions[i][state](this, dTime, i);
		}
	}

}

int Thing::getState(int idx)
{
	return m_States[idx];
}

void Thing::setState(int idx, int state)
{
	m_States[idx] = state;
}

void Thing::initFSM(int FSMNum)
{
	m_States.clear();
	m_FSMs.clear();
	m_Transitions.clear();

	m_States.resize(FSMNum);
	m_FSMs.resize(FSMNum);
	m_Transitions.resize(FSMNum);
}
