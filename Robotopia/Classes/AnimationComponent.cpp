#include "AnimationComponent.h"

Arthas::AnimationCompnent::~AnimationCompnent()
{
	m_Parent->removeChild(m_Sprite);
}

bool Arthas::AnimationCompnent::init()
{
	if (!Arthas::Component::init())
	{
		return false;
	}

	m_Sprite = cocos2d::Sprite::create();
	m_Sprite->retain();
	m_Type = 0;
	return true;
}

void Arthas::AnimationCompnent::update(float dTime)
{
}

void Arthas::AnimationCompnent::enter()
{
	m_Sprite->runAction(m_Action);
	
}

void Arthas::AnimationCompnent::exit()
{
	m_Sprite->stopAllActions();
}

void Arthas::AnimationCompnent::setAnimation(const char* AnimationName)
{

	//auto animation = getresourcemanager->getAnimation(animationname);
	//리소스 매니저에서 가져 온다. 
	//auto animate =cocos2d::Animate::create(animation);
	//m_Action  = cocos2d::RepeatForever::create(animate);
	
	m_Parent->addChild(m_Sprite);
}



