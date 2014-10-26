#include "StateComponent.h"

class IdleState : public StateComponent
{
public:
	IdleState(Object* parent);
	~IdleState();

	virtual void update(float dTime);
	virtual void enter();
	virtual void exit();
protected:
};