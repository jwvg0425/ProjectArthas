#include "pch.h"
#include "FSMComponent.h"
#include "ObserverComponent.h"
#include "StateComponent.h"
#include "KeyboardTrigger.h"
#include "StateChangeTrigger.h"
#include "GameManager.h"
#include "TriggerManager.h"


void FSMComponent::update(float dTime)
{
	StateComponent* prevState = m_NowState;

	m_NowState->update(dTime);

	ObserverComponent* observer = static_cast<ObserverComponent*>( GET_COMP_PARENT()->getComponent(CT_OBSERVER) );
	
	if (observer == nullptr)
		return;


	const std::vector<Trigger*>& triggers = observer->getTriggers();

	for (auto& trigger : triggers)
	{
		auto nextState = static_cast<StateComponent*>(m_NowState)->getNextState(trigger);
		if (nextState)
		{
			m_NowState->exit();
			m_NowState = nextState;
			m_NowState->enter();

			break;
		}
	}

	if (prevState != m_NowState)
	{
		auto trigger = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();

		trigger->initChangingStates(prevState->getType(), m_NowState->getType());

		observer->addTrigger(trigger);
	}
}

bool FSMComponent::init()
{
	if (!BaseComponent::init())
		return false;

	return true;
}
