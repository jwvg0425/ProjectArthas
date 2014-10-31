/************************************************************************/
/*
CLASS			: Tile
Author			: 김연우
역할				: Tile들의 추상 class
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			: 
*/
/************************************************************************/
#pragma once
#include "Component.h"
#include "Util.h"

BEGIN_NS_AT

class Tile : public Component
{
public:
	OVERRIDE bool init();
	OVERRIDE void update();
	OVERRIDE void enter();
	OVERRIDE void exit();

	ABSTRACT void setRect( float x , float y , float width , float height );
	
protected:
	cocos2d::Rect m_BoxRect;
};

END_NS_AT