#pragma once
#include "Component.h"
#include "Util.h"

BEGIN_NS_AT

class Player : public Component
{
public:
	OVERRIDE bool init();
	CREATE_FUNC( Player );
protected:

};

END_NS_AT