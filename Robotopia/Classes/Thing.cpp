#include "pch.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
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

		if (m_PrevStates[i] != m_States[i])
		{
			if (m_PrevStates[i] != -1)
			{
				m_Renders[i][m_PrevStates[i]]->exit();
			}
			m_Renders[i][m_States[i]]->enter();

			m_PrevStates[i] = m_States[i];
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
	m_Renders.clear();
	m_PrevStates.clear();

	m_States.resize(FSMNum);
	m_PrevStates.resize(FSMNum);
	for (int i = 0; i < FSMNum; i++)
	{
		m_PrevStates[i] = -1;
	}
	m_FSMs.resize(FSMNum);
	m_Transitions.resize(FSMNum);
	m_Renders.resize(FSMNum);
}
