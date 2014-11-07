#include "pch.h"
#include "UILayer.h"

bool Arthas::UILayer::init()
{
	return true;
}


void Arthas::UILayer::update( float dTime )
{

}

void Arthas::UILayer::setUIProperties(OUT cocos2d::Sprite* sprite, cocos2d::Point anchorPoint, cocos2d::Point positionPoint, float scale, bool visible)
{
	sprite->setAnchorPoint(anchorPoint);
	sprite->setPosition(positionPoint);
	sprite->setScale(scale);
	sprite->setVisible(visible);
}
