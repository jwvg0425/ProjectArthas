#include "FSMComponent.h"
#include "ObserverComponent.h"
#include "StateComponent.h"
#include "KeyboardTrigger.h"
#include "StateChangeTrigger.h"
#include "GameManager.h"
#include "TriggerManager.h"


void Arthas::FSMComponent::update(float dTime)
{
	StateComponent* prevState = m_NowState;

	m_NowState->update(dTime);

	ObserverComponent* observer = (ObserverComponent*)m_Parent->getComponent(CT_OBSERVER);

	if (observer == nullptr)
		return;

	const std::vector<Trigger*>& triggers = observer->getTriggers();


	for (auto& trigger : triggers)
	{
		auto nextState = ((StateComponent*)m_NowState)->getNextState(trigger);
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

		trigger->initChangingStates(prevState, m_NowState);

		observer->addTrigger(trigger);
	}
}

bool Arthas::FSMComponent::init()
{
	if (!Component::init())
		return false;

	return true;
}
