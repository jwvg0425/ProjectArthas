#include "pch.h"
#include "View.h"
#include "GameLayer.h"
#include "GameManager.h"
#include "StageManager.h"
#include "DataManager.h"




void Arthas::View::setViewPort(cocos2d::Layer* layer, cocos2d::Point playerPosInRoomLayer, cocos2d::Point anchorPoint)
{
	cocos2d::Size curRoomSize;
	cocos2d::Point curRoomLayerPos;
	cocos2d::Point playerPosInGameLayer;
	
	int curFloorIdx = GET_STAGE_MANAGER()->getStageNum();
	int curRoomIdx = GET_STAGE_MANAGER()->getRoomNum();

	if (curFloorIdx == -1 || curRoomIdx == -1) return;

	

	curRoomLayerPos.x = GET_STAGE_MANAGER()->getCurrentRoomData().x * GET_DATA_MANAGER()->getTileSize().width;
	curRoomLayerPos.y = GET_STAGE_MANAGER()->getCurrentRoomData().y * GET_DATA_MANAGER()->getTileSize().height;

	curRoomSize.width = GET_DATA_MANAGER()->.width * GET_DATA_MANAGER()->getTileSize().width;

	curRoomSize.width = GET_STAGE_MANAGER()->getCurrentRoomData().width * GET_DATA_MANAGER()->getTileSize().width;
	curRoomSize.height = GET_STAGE_MANAGER()->getCurrentRoomData().height * GET_DATA_MANAGER()->getTileSize().height;

	playerPosInGameLayer.x = curRoomLayerPos.x + playerPosInRoomLayer.x;
	playerPosInGameLayer.y = curRoomLayerPos.y + playerPosInRoomLayer.y;

	float windowWidth = cocos2d::Director::getInstance()->getWinSize().width;
	float windowHeight = cocos2d::Director::getInstance()->getWinSize().height;
	float anchorX = windowWidth * anchorPoint.x;
	float anchorY = windowHeight * anchorPoint.y;

	if (playerPosInRoomLayer.x + anchorX > curRoomSize.width)
	{
		anchorX = playerPosInRoomLayer.x - (curRoomSize.width - windowWidth);
	}
	if (playerPosInRoomLayer.x - anchorX < 0)
	{
		anchorX = playerPosInRoomLayer.x;
		//만약에 0으로하면 왼쪽 빈 공간이 보이지 않는다. 
		//anchorX = 0;
	}
	if (playerPosInRoomLayer.y + anchorY > curRoomSize.height)
	{
		anchorY = playerPosInRoomLayer.y - (curRoomSize.height - windowHeight);
	}
	if (playerPosInRoomLayer.y - anchorY < 0)
	{
		anchorY = playerPosInRoomLayer.y;
	}

	layer->setPosition(anchorX - playerPosInGameLayer.x, anchorY - playerPosInGameLayer.y);

//	layer->setPosition(anchorX - playerPosInRoomLayer.x, anchorY - playerPosInRoomLayer.y);
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



void Arthas::View::setViewPortShake(cocos2d::Layer* layer, cocos2d::Point playerPosInRoomLayer, cocos2d::Point anchorPoint)
{

	cocos2d::Size curRoomSize;
	cocos2d::Point curRoomLayerPos;
	cocos2d::Point playerPosInGameLayer;

	curRoomLayerPos.x = GET_STAGE_MANAGER()->getCurrentRoomData().x * GET_DATA_MANAGER()->getTileSize().width;
	curRoomLayerPos.y = GET_STAGE_MANAGER()->getCurrentRoomData().y * GET_DATA_MANAGER()->getTileSize().height;

	curRoomSize.width = GET_STAGE_MANAGER()->getCurrentRoomData().width * GET_DATA_MANAGER()->getTileSize().width;
	curRoomSize.height = GET_STAGE_MANAGER()->getCurrentRoomData().height * GET_DATA_MANAGER()->getTileSize().height;

	playerPosInGameLayer.x = curRoomLayerPos.x + playerPosInRoomLayer.x;
	playerPosInGameLayer.y = curRoomLayerPos.y + playerPosInRoomLayer.y;

	float windowWidth = cocos2d::Director::getInstance()->getWinSize().width;
	float windowHeight = cocos2d::Director::getInstance()->getWinSize().height;
	float anchorX = windowWidth * anchorPoint.x;
	float anchorY = windowHeight * anchorPoint.y;

	if (playerPosInRoomLayer.x + anchorX > curRoomSize.width)
	{
		anchorX = playerPosInRoomLayer.x - (curRoomSize.width - windowWidth);
	}
	if (playerPosInRoomLayer.x - anchorX < 0)
	{
		anchorX = playerPosInRoomLayer.x;
		//만약에 0으로하면 왼쪽 빈 공간이 보이지 않는다. 
		//anchorX = 0;
	}
	if (playerPosInRoomLayer.y + anchorY > curRoomSize.height)
	{
		anchorY = playerPosInRoomLayer.y - (curRoomSize.height - windowHeight);
	}
	if (playerPosInRoomLayer.y - anchorY < 0)
	{
		anchorY = playerPosInRoomLayer.y;
	}

	layer->setPosition(anchorX - playerPosInGameLayer.x, anchorY - playerPosInGameLayer.y); 

	anchorX += (10 + rand() % 90) / 5;
	anchorY += (10 + rand() % 90) / 5;

	layer->setPosition(anchorX - playerPosInRoomLayer.x, anchorY - playerPosInRoomLayer.y);


	timeval tv;
	cocos2d::gettimeofday(&tv, nullptr);
	long lMillisec = tv.tv_usec / 1000 + tv.tv_sec * 1000;




	return;

}

