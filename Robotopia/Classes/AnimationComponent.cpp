#include "AnimationComponent.h"


bool Arthas::AnimationCompnent::init()
{
	if (!Arthas::Component::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	m_Type = 0;
	return true;
}

void Arthas::AnimationCompnent::update(float dTime)
{

}

void Arthas::AnimationCompnent::enter()
{
	m_Parent->addChild(m_Sprite);
}

void Arthas::AnimationCompnent::exit()
{
	m_Parent->removeChild(m_Sprite);
}

void Arthas::AnimationCompnent::setAnimation(const char* AnimationName)
{
	//auto animation = getresourcemanager->getAnimation(animationname);
	//리소스 매니저에서 가져 온다. 

	

	//auto animate =cocos2d::Animate::create(animation);
	//auto action = cocos2d::RepeatForever::create(animate);
	//m_Sprite->runAction(action);
	
	

}

