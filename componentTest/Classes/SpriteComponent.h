#pragma once
#include "cocos2d.h"
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Object* parent, char* name, cocos2d::Point pos, bool isFromCache = true);
	~SpriteComponent();

	virtual void update(float dTime);
	virtual void enter();
	virtual void exit();

protected:
	cocos2d::Sprite* m_MainSprite;
};