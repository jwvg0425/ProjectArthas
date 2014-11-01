#include "PlayerRender.h"
#include "StateChangeTrigger.h"
#include "IdleState.h"


bool Arthas::PlayerRender::init()
{
	if (!RenderComponent::init())
	{
		return false;
	}

	StateChangeTrigger* idleTrigger = new StateChangeTrigger();
	IdleState* idleState = new IdleState();
	idleTrigger->initChangingStates(nullptr, idleState);
	addTransition(idleTrigger, idleState);

	//



	return true;
}

void Arthas::PlayerRender::enter()
{
}

void Arthas::PlayerRender::exit()
{
}

void Arthas::PlayerRender::update(int dTime)
{

}
