#include "pch.h"
#include "GameManager.h"
#include "InputManager.h"
#include "DataManager.h"
#include "StageManager.h"
#include "GameLayer.h"
#include "RoomLayer.h"
#include "Player.h"

bool GameLayer::init()
{
	if( !Layer::init() )
	{
		return false;
	}
	
	GET_INPUT_MANAGER()->receiveKeyboardData( this );
	m_Player = Player::create();
	m_Player->retain();

	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(GameLayer::onContactSeparate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	for(int idx = 0; idx < MAX_ROOM_LAYER_NUM; ++idx)
	{
		m_RoomLayers[idx] = nullptr;
	}

	return true;
}

void GameLayer::update( float dTime )
{
	//test code
	testCode();
	setViewPort(this, m_Player->getPosition(), cocos2d::Point::ANCHOR_MIDDLE);
	m_RoomLayers[m_CurrentRoomNum]->update(dTime);
	m_Player->update(dTime);
	checkIn();
}

void GameLayer::initGameLayer( int stageNum )
{
	m_StageNum = stageNum;
	auto data = GET_DATA_MANAGER()->getStageData(m_StageNum);
	m_RoomCount = data.m_Rooms.size();
	for(int idx = 0; idx < m_RoomCount; idx++)
	{
		m_CurrentRoomNum = idx;
		m_RoomLayers[idx] = RoomLayer::create();
		m_RoomLayers[idx]->initRoom(data.m_Rooms[idx]);
		m_RoomLayers[idx]->retain();
		m_RoomLayers[idx]->pause();
		m_RoomLayers[idx]->exit();
	}
	changeRoom(0, cocos2d::Point(GET_DATA_MANAGER()->getStartPos(m_StageNum)));
}

void GameLayer::setPhysicsWorld( cocos2d::PhysicsWorld* physicsWorld )
{
	if(physicsWorld != nullptr)
	{
		m_PhysicsWorld = physicsWorld;
	}
}

Player* GameLayer::getPlayer()
{
	return m_Player;
}

void GameLayer::shakeRooms()
{
	GET_DATA_MANAGER()->shakeRoom(m_StageNum);
	auto data = GET_DATA_MANAGER()->getStageData(m_StageNum);
	auto tileSize = GET_DATA_MANAGER()->getTileSize();
	m_RoomCount = data.m_Rooms.size();

	for(int idx = 0; idx < m_RoomCount; idx++)
	{
		m_RoomLayers[idx]->setPosition(cocos2d::Point(data.m_Rooms[idx].m_X*tileSize.width, data.m_Rooms[idx].m_Y*tileSize.height));
		if (idx == m_CurrentRoomNum)
		{
			continue;
		}
		m_RoomLayers[idx] = RoomLayer::create();
		m_RoomLayers[idx]->initRoom(data.m_Rooms[idx]);
		m_RoomLayers[idx]->retain();
		m_RoomLayers[idx]->pause();
		m_RoomLayers[idx]->exit();
	}
}

int GameLayer::getCurrentRoomNum()
{
	return m_CurrentRoomNum;
}

RoomLayer* GameLayer::getRoomLayer(int roomNum)
{
	RoomLayer* resultRoomLayer = nullptr;
	if(roomNum >= 0 && roomNum < m_RoomCount)
	{
		resultRoomLayer = m_RoomLayers[roomNum];
	}
	return resultRoomLayer;
}

void GameLayer::checkIn()
{
	cocos2d::Point pos = m_Player->getPosition();
	if(m_RoomLayers[m_CurrentRoomNum]->isOutOfRoom(pos))
	{
		int nextRoomNum = GET_DATA_MANAGER()->getNextRoomNumber(m_StageNum, m_CurrentRoomNum, pos);
		changeRoom(nextRoomNum, pos);
	}
}

void GameLayer::changeRoom(int roomNum, cocos2d::Point pos)
{
	m_RoomLayers[m_CurrentRoomNum]->pause();
	m_RoomLayers[m_CurrentRoomNum]->exit();
	m_Player->exit();
	removeChild(m_RoomLayers[m_CurrentRoomNum]);

	m_CurrentRoomNum = roomNum;

	addChild(m_RoomLayers[m_CurrentRoomNum]);
	m_RoomLayers[m_CurrentRoomNum]->enter();
	m_RoomLayers[m_CurrentRoomNum]->resume();
	m_RoomLayers[m_CurrentRoomNum]->addChild(m_Player, 0, PLAYER_TAG);
	m_Player->enter();
	m_Player->setPosition(pos);
}

void GameLayer::testCode()
{
#ifdef _DEBUG
	if(GET_INPUT_MANAGER()->getKeyState(KC_TEST2) == KS_PRESS)
	{
		shakeRooms();
	}
#endif
}

cocos2d::Point GameLayer::findFirstPoint(int roomNum)
{
	cocos2d::Point pos;
	auto data = GET_DATA_MANAGER()->getStageData(m_StageNum);
	auto moduleData = data.m_Rooms[roomNum].m_ModulePlaceData;
	cocos2d::Size mSize = GET_DATA_MANAGER()->getModuleSize();
	cocos2d::Size tSize = GET_DATA_MANAGER()->getTileSize();

	int maxXIdx = data.m_Rooms[roomNum].m_Width / mSize.width;
	int maxYIdx = data.m_Rooms[roomNum].m_Height / mSize.height;
	int xIdx = 0, yIdx = 0;
	bool success = false;

	for(yIdx = 0; yIdx < maxYIdx && !success; yIdx++)
	{
		for(xIdx = 0; xIdx < maxXIdx; xIdx++)
		{
			if(moduleData[xIdx + yIdx * maxXIdx] != 0)
			{
				success = true;
				break;
			}
		}
	}
	--yIdx;

	_ASSERT(success);

	for (int y = 1; y < mSize.height; y++)
	{
		for (int x = 0; x < mSize.width; x++)
		{
			if (data.m_Rooms[roomNum].m_Data[y*data.m_Rooms[roomNum].m_Width + x] == CT_NONE &&
				data.m_Rooms[roomNum].m_Data[(y-1)*data.m_Rooms[roomNum].m_Width + x] == OT_BLOCK)
			{
				pos.x = xIdx * mSize.width * tSize.width + x*tSize.width;
				pos.y = yIdx * mSize.height * tSize.height + y*tSize.height + 10;

				return pos;
			}
		}
	}
}

bool GameLayer::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = static_cast<BaseComponent*>( bodyA->getNode() );
	auto componentB = static_cast<BaseComponent*>( bodyB->getNode() );
	bool resA = componentA->onContactBegin(contact);
	bool resB = componentB->onContactBegin(contact);

	return resA && resB;
}

void GameLayer::onContactSeparate(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = static_cast<BaseComponent*>( bodyA->getNode() );
	auto componentB = static_cast<BaseComponent*>( bodyB->getNode() );

	if (componentA != nullptr)
	{
		componentA->onContactSeparate(contact);
	}
	if (componentB != nullptr)
	{
		componentB->onContactSeparate(contact);
	}
}


void GameLayer::setViewPort(cocos2d::Layer* layer, cocos2d::Point playerPosInRoomLayer, cocos2d::Point anchorPoint)
{
	int curFloorIdx = GET_STAGE_MANAGER()->getStageNum();
	int curRoomIdx = GET_STAGE_MANAGER()->getRoomNum();

	if(curFloorIdx == -1 || curRoomIdx == -1) return;

	static bool isChangingAxisX = false;

	cocos2d::Size curRoomSize;
	cocos2d::Point curRoomLayerPos;
	cocos2d::Point playerPosInGameLayer;

	RoomData curRoomData = GET_DATA_MANAGER()->getRoomData(curFloorIdx, curRoomIdx);
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	float windowWidth = cocos2d::Director::getInstance()->getWinSize().width;
	float windowHeight = cocos2d::Director::getInstance()->getWinSize().height;

	float anchorX = windowWidth * anchorPoint.x;
	float anchorY = windowHeight * anchorPoint.y;

	curRoomLayerPos.x = curRoomData.m_X * tileSize.width;
	curRoomLayerPos.y = curRoomData.m_Y * tileSize.height;

	curRoomSize.width = curRoomData.m_Width * tileSize.width;
	curRoomSize.height = curRoomData.m_Height * tileSize.height;

	playerPosInGameLayer.x = curRoomLayerPos.x + playerPosInRoomLayer.x;
	playerPosInGameLayer.y = curRoomLayerPos.y + playerPosInRoomLayer.y;


	/*if (playerPosInRoomLayer.x >= curRoomSize.width - windowWidth / 2 )
	{
	playerPosInRoomLayer.x = curRoomSize.width - windowWidth / 2;
	}
	else if (playerPosInRoomLayer.x <= windowWidth / 2)
	{
	playerPosInRoomLayer.x = windowWidth;
	}
	else
	{

	}*/
	//layer->setPosition(-curRoomLayerPos.x, -curRoomLayerPos.y);


	if(playerPosInRoomLayer.x + anchorX > curRoomSize.width)
	{
		anchorX = playerPosInRoomLayer.x - ( curRoomSize.width - windowWidth );
	}
	if(playerPosInRoomLayer.x - anchorX < 0)
	{
		//플레이어가 Room의 오른쪽 끝에 있는 경우네 
		anchorX = playerPosInRoomLayer.x;
		//만약에 0으로하면 왼쪽 빈 공간이 보이지 않는다.  
		//anchorX = 0;
	}


	if(playerPosInRoomLayer.y + anchorY > curRoomSize.height)
	{
		anchorY = playerPosInRoomLayer.y - ( curRoomSize.height - windowHeight );
	}
	if(playerPosInRoomLayer.y - anchorY < 0)
	{
		anchorY = playerPosInRoomLayer.y;
	}

	layer->setPosition(anchorX - playerPosInGameLayer.x, anchorY - playerPosInGameLayer.y);

}

void GameLayer::setViewPortWithHighlight(cocos2d::Layer* layer, cocos2d::Rect standardRect)
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

void GameLayer::setViewPortShake(cocos2d::Layer* layer, cocos2d::Point playerPosInRoomLayer, cocos2d::Point anchorPoint)
{
	int curFloorIdx = GET_STAGE_MANAGER()->getStageNum();
	int curRoomIdx = GET_STAGE_MANAGER()->getRoomNum();

	if(curFloorIdx == -1 || curRoomIdx == -1) return;

	cocos2d::Size curRoomSize;
	cocos2d::Point curRoomLayerPos;
	cocos2d::Point playerPosInGameLayer;

	RoomData curRoomData = GET_DATA_MANAGER()->getRoomData(curFloorIdx, curRoomIdx);
	cocos2d::Size tileSize = GET_DATA_MANAGER()->getTileSize();

	float windowWidth = cocos2d::Director::getInstance()->getWinSize().width;
	float windowHeight = cocos2d::Director::getInstance()->getWinSize().height;
	float anchorX = windowWidth * anchorPoint.x;
	float anchorY = windowHeight * anchorPoint.y;

	curRoomLayerPos.x = curRoomData.m_X * tileSize.width;
	curRoomLayerPos.y = curRoomData.m_Y * tileSize.height;

	curRoomSize.width = curRoomData.m_Width * tileSize.width;
	curRoomSize.height = curRoomSize.height * tileSize.height;

	playerPosInGameLayer.x = curRoomLayerPos.x + playerPosInRoomLayer.x;
	playerPosInGameLayer.y = curRoomLayerPos.y + playerPosInRoomLayer.y;

	if(playerPosInRoomLayer.x + anchorX > curRoomSize.width)
	{
		anchorX = playerPosInRoomLayer.x - ( curRoomSize.width - windowWidth );
	}
	if(playerPosInRoomLayer.x - anchorX < 0)
	{
		anchorX = playerPosInRoomLayer.x;
		//만약에 0으로하면 왼쪽 빈 공간이 보이지 않는다. 
		//anchorX = 0;
	}
	if(playerPosInRoomLayer.y + anchorY > curRoomSize.height)
	{
		anchorY = playerPosInRoomLayer.y - ( curRoomSize.height - windowHeight );
	}
	if(playerPosInRoomLayer.y - anchorY < 0)
	{
		anchorY = playerPosInRoomLayer.y;
	}

	layer->setPosition(anchorX - playerPosInGameLayer.x, anchorY - playerPosInGameLayer.y);

	anchorX += ( 10 + rand() % 90 ) / 5; ///< int애서 암시적으로 float변환하네.. 그냥 static_cast로 명확하게...
	anchorY += ( 10 + rand() % 90 ) / 5; ///# 코드 전반적으로 암시적 형변환 많이 쓰고 있네.. 

	layer->setPosition(anchorX - playerPosInRoomLayer.x, anchorY - playerPosInRoomLayer.y);


	/*timeval tv;
	timeval prevTV;
	cocos2d::gettimeofday(&tv, nullptr);
	long tvMillisec = tv.tv_usec / 1000 + tv.tv_sec * 1000;
	long prevMillisec = tvMillisec;

	while (tvMillisec - prevMillisec > 5000)
	{
	cocos2d::gettimeofday(&tv, nullptr);
	long tvMillisec = tv.tv_usec / 1000 + tv.tv_sec * 1000;
	}
	*/

	return;
}

void GameLayer::setPlayerState(int idx, int state)
{
	m_Player->setState(idx, state);
}

void GameLayer::setPlayerInfo(const PlayerInfo& info)
{
	m_Player->setInfo(info);
}
