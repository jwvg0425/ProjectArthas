#pragma once

#include "FSMComponent.h"


class PlayerFSM : public FSMComponent
{
public:
	virtual void enter();
	virtual void exit();

	PlayerFSM(Object* parent);
	~PlayerFSM();
protected:
};