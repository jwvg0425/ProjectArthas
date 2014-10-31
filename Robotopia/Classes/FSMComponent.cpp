#include "FSMComponent.h"
#include "ObserverComponent.h"
#include "StateComponent.h"


void Arthas::FSMComponent::update(float dTime)
{
	m_NowState->update(dTime);

	ObserverComponent* observer = (ObserverComponent*)m_Parent->getComponent(CT_OBSERVER);

	const std::vector<Trigger*>& triggers = observer->getTriggers();


	for (auto& trigger : triggers)
	{
		auto nextState = ((Arthas::StateComponent*)m_NowState)->getNextState(trigger);
		if (nextState)
		{
			m_NowState->exit();
			m_NowState = nextState;
			m_NowState->enter();

			break;
		}
	}
}

bool Arthas::FSMComponent::init()
{
	if (!Component::init())
		return false;

	return true;
}
