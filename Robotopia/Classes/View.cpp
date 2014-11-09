#include "pch.h"
#include "View.h"
#include "GameLayer.h"
#include "GameManager.h"
#include "DataManager.h"




void Arthas::View::setViewPort(cocos2d::Layer* layer, cocos2d::Point standardPoint, cocos2d::Point anchorPoint)
{
	cocos2d::Size mapSize;
	float windowWidth = cocos2d::Director::getInstance()->getWinSize().width;
	float windowHeight = cocos2d::Director::getInstance()->getWinSize().height;
	float anchorX = windowWidth * anchorPoint.x;
	float anchorY = windowHeight * anchorPoint.y;

	if (standardPoint.x + anchorX > mapSize.width)
	{
		anchorX = standardPoint.x - (mapSize.width - windowWidth);
	}
	if (standardPoint.x - anchorX < 0)
	{
		anchorX = standardPoint.x;
		//만약에 0으로하면 왼쪽 빈 공간이 보이지 않는다. 
		//anchorX = 0;
	}
	if (standardPoint.y + anchorY > mapSize.height)
	{
		anchorY = standardPoint.y - (mapSize.height - windowHeight);
	}
	if (standardPoint.y - anchorY < 0)
	{
		anchorY = standardPoint.y;
	}


	layer->setPosition(anchorX - standardPoint.x, anchorY - standardPoint.y);
}



void Arthas::View::setViewPortWithHighlight(cocos2d::Layer* layer, cocos2d::Rect standardRect)
{
	float windowWidth = cocos2d::Director::getInstance()->getWinSize().width;
	float windowHeight = cocos2d::Director::getInstance()->getWinSize().height;
	cocos2d::Point centerAnchor(0.5f, 0.5f);
	float ratioX = windowWidth / standardRect.size.width;
	float ratioY = windowHeight / standardRect.size.height;

	layer->setPosition(windowWidth * centerAnchor.x - standardRect.origin.x,
					   windowHeight * centerAnchor.y - standardRect.origin.y);
	layer->setScale(ratioX, ratioY);

	return;
}



void Arthas::View::setViewPortShake(cocos2d::Layer* scene, cocos2d::Point standardPoint, cocos2d::Point anchorPoint)
{

	cocos2d::Size mapSize = scene->getContentSize();
	float windowWidth = cocos2d::Director::getInstance()->getWinSize().width;
	float windowHeight = cocos2d::Director::getInstance()->getWinSize().height;
	float anchorX = windowWidth * anchorPoint.x;
	float anchorY = windowHeight * anchorPoint.y;

	if (standardPoint.x + anchorX > mapSize.width)
	{
		anchorX = standardPoint.x - (mapSize.width - windowWidth);
	}
	if (standardPoint.x - anchorX < 0)
	{
		anchorX = standardPoint.x;
		//만약에 0으로하면 왼쪽 빈 공간이 보이지 않는다. 
		//anchorX = 0;
	}
	if (standardPoint.y + anchorY > mapSize.height)
	{
		anchorY = standardPoint.y - (mapSize.height - windowHeight);
	}
	if (standardPoint.y - anchorY < 0)
	{
		anchorY = standardPoint.y;
	}


	anchorX += (10 + rand() % 90) / 5;
	anchorY += (10 + rand() % 90) / 5;

	scene->setPosition(anchorX - standardPoint.x, anchorY - standardPoint.y);


	return;

}

