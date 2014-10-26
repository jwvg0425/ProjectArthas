#include "StateComponent.h"

class MoveState : public StateComponent
{
public:
	MoveState(Object* parent, bool isRightDirection);
	~MoveState();

	virtual void update(float dTime);
	virtual void enter();
	virtual void exit();

protected:
	bool m_IsRightDirection;
};