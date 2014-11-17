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
		if (m_FSMFunctions[i][m_States[i]] != nullptr)
		{
			m_FSMFunctions[i][m_States[i]](this, dTime, i);
		}

		if (m_FSMTransitions[i][m_States[i]] != nullptr)
		{
			m_FSMTransitions[i][m_States[i]](this, dTime, i);
		}
	}
}

void Thing::initFSM(int FSMNum)
{
	FSMFunctions emptyFunctions;

	emptyFunctions.clear();

	for (int i = 0; i < FSMNum; i++)
	{
		m_FSMFunctions.push_back(emptyFunctions);
		m_FSMTransitions.push_back(emptyFunctions);
		m_States.push_back(0);
	}
}

void Thing::setState(int idx, int value)
{
	m_States[idx] = value;
}

int Thing::getState(int idx)
{
	return m_States[idx];
}

