#include "PlayerRender.h"
#include "StateChangeTrigger.h"
#include "IdleState.h"
#include "MoveState.h"
#include "JumpState.h"
#include "AnimationComponent.h"


bool Arthas::PlayerRender::init()
{
	if (!RenderComponent::init())
	{
		return false;
	}

	Transition idleTransition = createTransition(new StateChangeTrigger(), new IdleState(), 
												 new AnimationCompnent(), AT_PLAYER_IDLE);
	addTransition(idleTransition);

	Transition moveTransition = createTransition(new StateChangeTrigger(), new MoveState(), 
												 new AnimationCompnent(), AT_PLAYER_MOVE);
	addTransition(moveTransition);

	Transition jumpTransition = createTransition(new StateChangeTrigger(), new JumpState(), 
												new AnimationCompnent(), AT_PLAYER_JUMP);
	addTransition(jumpTransition);

	return true;
}

void Arthas::PlayerRender::enter()
{
}

void Arthas::PlayerRender::exit()
{
}
