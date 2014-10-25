#include "Component.h"
#include <vector>

class Trigger;
typedef std::pair<Trigger*, StateComponent*> Event;

class StateComponent : public Component
{
public:
	virtual void update(float dTime) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
protected:
	std::vector<Event> m_Events;
};