#include "FSMComponent.h"
#include "ObserverComponent.h"
#include "StateComponent.h"
#include "KeyboardTrigger.h"


void Arthas::FSMComponent::update(float dTime)
{
	m_NowState->update(dTime);

	ObserverComponent* observer = (ObserverComponent*)m_Parent->getComponent(CT_OBSERVER);

	if (observer == nullptr)
		return;

	const std::vector<Trigger*>& triggers = observer->getTriggers();


	for (auto& trigger : triggers)
	{
		cocos2d::log("%d : %d", ((KeyboardTrigger*)trigger)->m_KeyCode, ((KeyboardTrigger*)trigger)->m_KeyState);
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
