#pragma once
#include "Component.h"
#include <vector>

class StateComponent;
class Trigger;
typedef std::pair<Trigger*, StateComponent*> Event;

class StateComponent : public Component
{
public:
	StateComponent();
	~StateComponent();

	virtual void update(float dTime) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;

	void addEvent(Event event);
	void removeEvent(Event remEvent);
	void removeAllEvent();
	Event* hasEvent();
protected:
	std::vector<Event> m_Events;
};