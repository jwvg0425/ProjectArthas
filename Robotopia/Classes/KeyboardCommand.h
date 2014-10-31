#pragma once
#include "CommandComponent.h"
#include "cocos2d.h"
BEGIN_NS_AT

class KeyboardCommand : public CommandComponent
{
public:

	OVERRIDE bool				init();
	OVERRIDE void				update( float dTime );
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	CREATE_FUNC( KeyboardCommand );

protected:
	
};

END_NS_AT