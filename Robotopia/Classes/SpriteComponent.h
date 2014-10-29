/************************************************************************/
/*
	CLASS			: SpriteComp
	Author			: 김연우
	역할				: Sprite Component의 클래스
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: Create해서 만든다음에 setSprite해서 해당 스프라이트 추가해주어야한다.
*/
/************************************************************************/
#pragma once
#include "Component.h"
#include "cocos2d.h"

BEGIN_NS_AT

class SpriteComponent : public Component
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update( float dTime );
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	void						setSprite( const char* SpriteName, bool isFrameCache );
	int							getType(){return m_Type;}

	CREATE_FUNC( SpriteComponent );

protected:
	cocos2d::Sprite*			m_Sprite;
	int							m_Type;
};

END_NS_AT