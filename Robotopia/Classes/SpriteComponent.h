/************************************************************************/
/*
	CLASS			: SpriteComp
	Author			: 김연우
	역할				: Sprite Component의 클래스
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: 추상클래스로 만들고 각 스프라이트 별로 따로 클래스를 만드는 방향을 생각 중
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

	//Sprite를 종류별로 따로 분류하면 아래 create 오버로딩한 함수는 노필요입니다.
	void						setSprite( const char* SpriteName, bool isFrameCache );
	int							getType(){return m_Type;}

	CREATE_FUNC( SpriteComponent );

protected:
	cocos2d::Sprite*			m_Sprite;
	int							m_Type;
};

END_NS_AT