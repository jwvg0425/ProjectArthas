#include "pch.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "Creature.h"

void Creature::update(float dTime)
{
 	for (auto& BaseComponent : getChildren())
	{
		BaseComponent->update(dTime);
	}

	updateFSM(dTime);
	updateRender(dTime);
}

int Creature::getState(int idx)
{
	return m_States[idx];
}

void Creature::setState(int idx, int state)
{
	m_States[idx] = state;
}

void Creature::initFSM(int FSMNum)
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

void Creature::setEnabled(bool enable)
{
	if (enable == true)
	{
		setPhysicsBody(m_Body);
	}
	else
	{
		setPhysicsBody(nullptr);
		if (m_Body != nullptr)
		{
			m_Body->removeFromWorld();
		}
	}
}

void Creature::flipBody(bool isLeft)
{
	for(int i = 0; i < m_Renders[0].size(); i++)
	{
		m_Renders[0][i]->setFlippedX(isLeft);
	}
}

void Creature::updateFSM(float dTime)
{
	for (int i = 0; i < m_States.size(); i++)
	{
		int state = m_States[i];
		if (m_FSMs[i][state] != nullptr)
		{
			m_FSMs[i][state](this, dTime, i);
		}

		//transition은 절대 nullptr이면 안된다. 이게 nullptr이면 그 상태에서 딴 상태로 빠져나올 방법이 음슴
		_ASSERT(m_Transitions[i][state] != nullptr);
		m_Transitions[i][state](this, dTime, i);
	}
}

void Creature::updateRender(float dTime)
{

	for (int i = 0; i < m_States.size(); i++)
	{
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

Creature::Creature()
{

}

Creature::~Creature()
{
	SAFE_RELEASE(m_Body);
}
