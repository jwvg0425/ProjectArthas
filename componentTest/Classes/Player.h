#pragma once
#include "Object.h"

class Player : public Object
{
public:
	virtual bool init();

	~Player();
	
	CREATE_FUNC(Player);
protected:

};