#pragma once

#include "Component.h"
#include <vector>

class Trigger;

class ObserverComponent : public Component
{
public:
	ObserverComponent(Object* parent);
	~ObserverComponent();

	virtual void update(float dTime);
	virtual void enter();
	virtual void exit();

	void addTrigger(Trigger* trigger);
	void removeTrigger(Trigger* trigger);
	void removeAllTrigger();

	std::vector<Trigger*>& getTriggers();

protected:
	std::vector<Trigger*> m_Triggers;
	std::vector<Trigger*> m_NextTriggers;
};