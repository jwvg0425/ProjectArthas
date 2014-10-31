#include "FSMComponent.h"
#include "ObserverComponent.h"


void Arthas::FSMComponent::update(float dTime)
{
	m_NowState->update(dTime);

	ObserverComponent* observer = (ObserverComponent*)m_Parent->getComponent(CT_OBSERVER);

	const std::vector<Trigger*>& triggers = observer->getTriggers();


	for (auto& trigger : triggers)
	{
		//이 부분 getNextState 함수 추가되면 하는 걸로.
		//auto nextState = m_NowState->getNextState(trigger);
		//if (nextState)
		{
			m_NowState->exit();
			//m_NowState = nextState;
			m_NowState->enter();

			break;
		}
	}
}
