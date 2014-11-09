#include "ToolScene.h"
#include "ToolAniPlayLayer.h"
#include "ToolSpriteEditLayer.h"
#include "GameManager.h"
#include "ResourceManager.h"

#define LABELWIDTH  100
#define LABELHEIGHT 30
#define LAYERWIDTH 300
#define LAYERHEIGHT 300

bool Arthas::ToolAniPlayLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	cocos2d::SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("test.plist");

	
	m_MainSpr = cocos2d::Sprite::create();
	m_MainSpr->setPosition(cocos2d::Point(LAYERWIDTH*1.75f, LAYERHEIGHT*0.5f));
	this->addChild(m_MainSpr);

	isFlipped = false;
	this->setPosition(550, 0);
	this->setName("Play");

	auto sprLabel = cocos2d::Label::createWithSystemFont("Sprite", "Gill Sans", 25);
	auto playLabel = cocos2d::Label::createWithSystemFont("Play", "Gill Sans", 25);
	auto stopLabel = cocos2d::Label::createWithSystemFont("stop", "Gill Sans", 25);
	auto flipLabel = cocos2d::Label::createWithSystemFont("flip", "Gill Sans", 25);
	playLabel->setContentSize(cocos2d::Size(LABELWIDTH, LABELHEIGHT));
	stopLabel->setContentSize(cocos2d::Size(LABELWIDTH, LABELHEIGHT));
	flipLabel->setContentSize(cocos2d::Size(LABELWIDTH, LABELHEIGHT));

	auto sprItem = cocos2d::MenuItemLabel::create(sprLabel, CC_CALLBACK_1(ToolAniPlayLayer::sprCallBack, this));
	auto playItem = cocos2d::MenuItemLabel::create(playLabel, CC_CALLBACK_1(ToolAniPlayLayer::playCallBack, this));
	auto stopItem = cocos2d::MenuItemLabel::create(stopLabel, CC_CALLBACK_1(ToolAniPlayLayer::stopCallBack, this));
	auto flipItem = cocos2d::MenuItemLabel::create(flipLabel, CC_CALLBACK_1(ToolAniPlayLayer::flipCallBack, this));

	auto menu = cocos2d::Menu::create(playItem, stopItem, flipItem, sprItem, NULL);
	menu->alignItemsVertically();
	this->addChild(menu);

	return true;
}

void Arthas::ToolAniPlayLayer::playCallBack(cocos2d::Ref* sender)
{
	auto editLayer = (ToolSpriteEditLayer*)(this->getParent()->getChildByName("Edit"));
	m_CurrentAniType = editLayer->getCurrentATInfoType();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(m_CurrentAniType);
	/////////////////ÅÍÁüÁÖÀÇ
	//m_AniInfo = editLayer->getAniMationInfo();
	////////////////////
	//
	//auto animation = cocos2d::Animation::create();
	//animation->setDelayPerUnit(m_AniInfo.delay);
	//
	//for (int i = 0; i < m_AniInfo.frameNum; ++i)
	//{
	//	auto frame = cocos2d::SpriteFrameCache::getInstance()->
	//		getSpriteFrameByName(cocos2d::StringUtils::format("%s", m_AniInfo.animationName[i]));
	//	animation->addSpriteFrame(frame);
	//}

	auto animate = cocos2d::Animate::create(animation);
	auto action = cocos2d::RepeatForever::create(animate);
	m_MainSpr->runAction(action);

}

void Arthas::ToolAniPlayLayer::stopCallBack(cocos2d::Ref* sender)
{
	m_MainSpr->stopAllActions();
}

void Arthas::ToolAniPlayLayer::flipCallBack(cocos2d::Ref* sender)
{
	if (!isFlipped)
	{
		isFlipped = true;
		m_MainSpr->setFlippedX(true);
	}
	else
	{
		isFlipped = false;
		m_MainSpr->setFlippedX(false);
	}
}

void Arthas::ToolAniPlayLayer::sprCallBack(cocos2d::Ref* sender)
{
	auto editLayer = (ToolSpriteEditLayer*)(this->getParent()->getChildByName("Edit"));
	m_CurrentSprType = editLayer->getCurrentSTInfoType();
	if (m_CurrentSprType == ST_END)
	{
		cocos2d::Sprite* noExist = cocos2d::Sprite::create("Graphic/noExist.png");
		m_MainSpr = noExist;
	}
	m_MainSpr = GET_RESOURCE_MANAGER()->createSprite(m_CurrentSprType);
}

