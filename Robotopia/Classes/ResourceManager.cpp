#include "pch.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "DataManager.h"


ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

bool ResourceManager::init()
{
	return true;
}

cocos2d::Animation* ResourceManager::createAnimation(ResourceType animationType)
{
	AnimationInfo animationInfo = GET_DATA_MANAGER()->getAnimationInfo(animationType);
	auto animation = cocos2d::Animation::create();
	animation->setDelayPerUnit(animationInfo.delay);

	for (int i = 0; i < animationInfo.frameNum; ++i)
	{
		auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(animationInfo.animationName[i]);

		if (frame == nullptr)
		{
			char name[256] = { 0, };

			sprintf(name, "Graphic/%s", animationInfo.animationName[i]);
			auto sprite = cocos2d::Sprite::create(name);
			animation->addSpriteFrame(sprite->getSpriteFrame());
		}
		else
		{
			animation->addSpriteFrame(frame);
		}
	}
	return animation;
}

cocos2d::Sprite* ResourceManager::createSprite(ResourceType spriteType)
{
	SpriteInfo spriteInfo = GET_DATA_MANAGER()->getSpriteInfo(spriteType);
	

	auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteInfo.spriteName);

	if (frame == nullptr)
	{
		char name[256] = { 0, };

		sprintf(name, "Graphic/%s", spriteInfo.spriteName);
		return cocos2d::Sprite::create(name);
	}
	else
	{
		auto sprite = cocos2d::Sprite::createWithSpriteFrameName(spriteInfo.spriteName);
		return sprite;
	}
}

