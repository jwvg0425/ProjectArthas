/************************************************************************/
/*
	CLASS			: SpriteComponent
	Author			: 김연우
	역할				: Sprite BaseComponent의 클래스
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			: Create해서 만든다음에 setSprite해서 해당 스프라이트 추가해주어야한다.
*/
/************************************************************************/

#pragma once
#include "BaseComponent.h"
#include "cocos2d.h"



class StateComponent;
class SpriteComponent : public BaseComponent
{
public:
	SpriteComponent();
	virtual ~SpriteComponent();

	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();

	void						initSprite( SpriteType resourceType, BaseComponent* parent , 
											cocos2d::Point position = cocos2d::Point(0.f, 0.f), 
											cocos2d::Point anchorPoint = cocos2d::Point(0.5f, 0.5f));

	void						setSpritePosition(cocos2d::Point pos);
	void						setSpriteAnchor(cocos2d::Vec2 anchor);
	void						setSpriteVisible(bool visible);
	void						setFlippedX(bool flip);
	cocos2d::Sprite*			getSprite();

	CREATE_FUNC(SpriteComponent);

protected:
	std::vector<Transition>		m_Transitions;
	cocos2d::Sprite*			m_Sprite = nullptr;
	BaseComponent*				m_RenderTarget = nullptr;
};

