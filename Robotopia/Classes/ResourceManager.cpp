#include "pch.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "DataManager.h"


Arthas::ResourceManager::ResourceManager()
{

}

Arthas::ResourceManager::~ResourceManager()
{

}

bool Arthas::ResourceManager::init()
{
	return true;
}

cocos2d::Animation* Arthas::ResourceManager::createAnimation(ResourceType animationType)
{
	AnimationInfo animationInfo = GET_DATA_MANAGER()->getAnimationInfo(animationType);
	auto animation = cocos2d::Animation::create();
	animation->setDelayPerUnit(animationInfo.delay);

	for (int i = 0; i < animationInfo.frameNum; ++i)
	{
		auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(animationInfo.animationName[i]);
		animation->addSpriteFrame(frame);
	}
	return animation;
}

cocos2d::Sprite* Arthas::ResourceManager::createSprite(ResourceType spriteType)
{
	SpriteInfo spriteInfo = GET_DATA_MANAGER()->getSpriteInfo(spriteType);
	auto sprite = cocos2d::Sprite::createWithSpriteFrameName(spriteInfo.spriteName);
	return sprite;
}

