#pragma once
#include "Component.h"
#include "Util.h"

class Player : public Component
{
public:
	OVERRIDE bool init();
	CREATE_FUNC( Player );
protected:

};