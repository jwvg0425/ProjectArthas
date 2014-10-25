#pragma once
#include "FSMComponent.h"
#include "Trigger.h"
#include "StateComponent.h"

void FSMComponent::update(float dTime)
{
	m_NowState->update(dTime);
}
