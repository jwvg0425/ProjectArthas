#include "GameManager.h"
#include "EffectManager.h"
#include "DataManager.h"
#include "RoomLayer.h"




Arthas::EffectManager::EffectManager()
{
	
}

Arthas::EffectManager::~EffectManager()
{

}

bool Arthas::EffectManager::init()
{
	return true;
}


void Arthas::EffectManager::removeEffectCallBack(cocos2d::Ref* sender)
{
	auto spr = (cocos2d::Sprite*)sender;
	spr->removeFromParent();

}

void Arthas::EffectManager::
createEffect(EffectType effectType, Arthas::RoomLayer* layer, 
			 cocos2d::Point point, int playTime)
{
	//auto ani = GET_RESOURCE_MANAGER()->getAni(effectType);
	
	//위에 꺼 받았다고 치자. 
	//리소스 매니저에서 받아올게 많음 spr과 ani
	//데이터 매니저에서 받을 수 있는게 play time을 받아 기본값으로 하거나
	//게임 중간에 playtime정할 수 있도록 한다. 

	auto spr = cocos2d::Sprite::create();
	auto animation = cocos2d::Animation::create();
	auto animate = cocos2d::Animate::create(animation);

	spr->setPosition(point);

	layer->addChild(spr);

	auto action = cocos2d::Repeat::create(animate, playTime);
	auto callback = cocos2d::CallFuncN::
		create(CC_CALLBACK_1(EffectManager::removeEffectCallBack, this));
	spr->runAction(cocos2d::Sequence::create(action, callback, NULL));
	
}

