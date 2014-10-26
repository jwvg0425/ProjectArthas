#include "Trigger.h"

class KeyboardTrigger : public Trigger
{
public:
	KeyboardTrigger(int keyState);
	~KeyboardTrigger();

	int getKeyState(){
		return m_KeyState;
	}

	virtual bool operator ==(Trigger& trigger);
protected:
	int m_KeyState;
};