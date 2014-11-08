#include "pch.h"
#include "DataManager.h"
#include "cocos2d.h"
#include "json/json.h"

Arthas::DataManager::DataManager()
{

}

Arthas::DataManager::~DataManager()
{

}

bool Arthas::DataManager::init()
{
	for (int dirType = 0; dirType < DIR_MAX; dirType++)
	{
		m_ModuleDatas[dirType].reserve(40);
	}

	//loadSpriteCacheData();
	//loadResourceData();
	loadModuleData();

	//testCode

	m_SpriteCaches.push_back("Graphic/test.plist");
	SpriteInfo info;

	info.type = ST_BLOCK;
	sprintf(info.spriteName,"%s", "block.png");
	m_SpriteInfos.push_back(info);

	SpriteInfo info2;

	info2.type = ST_PLAYER;
	sprintf(info2.spriteName, "%s", "player_stand1.png");
	m_SpriteInfos.push_back(info2);
	
	AnimationInfo stand, move, jump;

	stand.type = AT_PLAYER_IDLE;
	stand.delay = 0.1f;
	stand.frameNum = 4;
	for (int i = 0; i < 4; i++)
	{
		sprintf(stand.animationName[i], "player_stand%d.png", i + 1);
	}

	move.type = AT_PLAYER_MOVE;
	move.delay = 0.1f;
	move.frameNum = 8;
	for (int i = 0; i < 8; i++)
	{
		sprintf(move.animationName[i], "player_walk%d.png", i + 1);
	}

	jump.type = AT_PLAYER_JUMP;
	jump.delay = 0.1f;
	jump.frameNum = 1;
	for (int i = 0; i < 1; i++)
	{
		sprintf(jump.animationName[i], "player_jump%d.png", i + 1);
	}

	m_AnimationInfos.push_back(stand);
	m_AnimationInfos.push_back(move);
	m_AnimationInfos.push_back(jump);
	////////

	for (size_t i = 0; i < m_SpriteCaches.size(); i++)
	{
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(m_SpriteCaches[i]);
	}

	initWorldData();
	

	return true;
}

bool Arthas::DataManager::loadModuleData()
{
	//data 불러오기
	ssize_t bufferSize = 0;
	unsigned char* fileData = cocos2d::FileUtils::getInstance()->getFileData(MODULE_FILE_NAME, "rb", &bufferSize);
	std::string clearData((const char*)fileData, bufferSize);

	Json::Value root;
	Json::Reader reader;
	char key[BUF_SIZE] = {};
	bool isParsingSuccess = reader.parse(clearData, root);
	int width, height;

	if (!isParsingSuccess)
	{
		cocos2d::log("parser failed : \n %s", MODULE_FILE_NAME);
		return false;
	}
	//너비 높이 불러오기
	m_ModuleSize.width = root.get("moduleWidth", 0).asInt();
	m_ModuleSize.height = root.get("moduleHeight", 0).asInt();
	m_TileSize.width = root.get("tileWidth", 0).asInt();
	m_TileSize.height = root.get("tileHeight", 0).asInt();

	width = m_ModuleSize.width;
	height = m_ModuleSize.height;

	for (int dirType = 0; dirType < DIR_MAX; dirType++)
	{
		int size;

		m_ModuleDatas[dirType].clear();

		ModuleData data;

		//size 불러오기
		getModuleKey(dirType, "size", key);
		size = root.get(key, 0).asInt();

		if (size <= 0)
		{
			continue;
		}

		for (int idx = 0; idx < size; idx++)
		{
			//ComponentType 배열 불러오기
			getModuleKey(dirType, idx, "data", key);
			Json::Value array = root[key];

			data.name = array[0].asString();

			for (int i = 0; i < width * height; i++)
			{
				ComponentType type;

				type = (ComponentType)array[i+1].asInt();

				data.data.push_back(type);
			}
		}
		m_ModuleDatas[dirType].push_back(data);
	}

	return true;
}


bool Arthas::DataManager::saveModuleData()
{
	Json::Value moduleData;
	char buffer[BUF_SIZE] = {};

	moduleData["moduleWidth"] = m_ModuleSize.width;
	moduleData["moduleHeight"] = m_ModuleSize.height;
	moduleData["tileWidth"] = m_TileSize.width;
	moduleData["tileHeight"] = m_TileSize.height;

	for (int dirType = 0; dirType < DIR_MAX; dirType++)
	{
		//현재 타입의 모듈 사이즈 삽입
		getModuleKey(dirType, "size", buffer);
		moduleData[buffer] = m_ModuleDatas[dirType].size();

		for (size_t idx = 0; idx < m_ModuleDatas[dirType].size(); idx++)
		{
			int width, height;

			width = m_ModuleSize.width;
			height = m_ModuleSize.height;

			Json::Value data;

			//세부 데이터(오브젝트 타입들) 삽입
			data.append(m_ModuleDatas[dirType][idx].name);
			for (int i = 0; i < width * height; i++)
			{
				data.append(m_ModuleDatas[dirType][idx].data[i]);
			}
			getModuleKey(dirType, idx, "data", buffer);
			moduleData[buffer] = data;
		}
	}

	Json::StyledWriter writer;
	std::string strJSON = writer.write(moduleData);

	saveData(MODULE_FILE_NAME, strJSON.c_str());

	return true;
}

bool Arthas::DataManager::saveData(std::string fileName, const char* pData)
{
	FILE *fp = fopen(fileName.c_str(), "wb");

	if (!fp)
	{
		cocos2d::log("can not create file %s", fileName);
		return false;
	}

	fputs(pData, fp);

	fclose(fp);

	return true;
}

bool Arthas::DataManager::getModuleKey(int type, int idx, char* category, OUT char* key)
{
	if (key == nullptr || category == nullptr)
		return false;

	sprintf(key, "%d_%d_%s", type, idx, category);

	return true;
}

bool Arthas::DataManager::getModuleKey(int type, char* category, OUT char* key)
{
	if (key == nullptr || category == nullptr)
		return false;

	sprintf(key, "%d_%s", type, category);

	return true;
}

Arthas::SpriteInfo Arthas::DataManager::getSpriteInfo(ResourceType spriteType)
{
	Arthas::SpriteInfo errorInfo = {};

	_ASSERT(spriteType >= ST_START&&spriteType < ST_END);

	if (!(spriteType >= ST_START&&spriteType < ST_END))
	{
		return errorInfo;
	}

	for (size_t i = 0; i < m_SpriteInfos.size(); i++)
	{
		if (m_SpriteInfos[i].type == spriteType)
		{
			return m_SpriteInfos[i];
		}
	}
	

	return errorInfo;
}

Arthas::AnimationInfo Arthas::DataManager::getAnimationInfo(ResourceType animationType)
{
	Arthas::AnimationInfo errorInfo = {};

	_ASSERT(animationType >= AT_START&& animationType < AT_END);

	if (!(animationType >= AT_START&& animationType < AT_END))
	{
		errorInfo.frameNum = -1;
		return errorInfo;
	}

	for (size_t i = 0; i < m_AnimationInfos.size(); i++)
	{
		if (m_AnimationInfos[i].type == animationType)
		{
			return m_AnimationInfos[i];
		}
	}

	return errorInfo;
}

bool Arthas::DataManager::getResourceKey(char* category, int idx, OUT char* key)
{
	if (key == nullptr || category == nullptr)
		return false;

	sprintf(key, "%s_%d", category, idx);

	return true;
}

bool Arthas::DataManager::saveResourceData()
{
	Json::Value resourceData;
	char key[BUF_SIZE] = {};


	//spriteCache file 이름 목록 저장
	for (size_t i = 0; i < m_SpriteCaches.size(); i++)
	{
		getResourceKey("cache", i, key);
		resourceData[key] = m_SpriteCaches[i];
	}

	//sprite 정보 저장
	for (size_t i = 0; i < m_SpriteInfos.size(); i++)
	{
		Json::Value data;
		getResourceKey("sprite", i, key);
		data.append(m_SpriteInfos[i].type);
		data.append(m_SpriteInfos[i].spriteName);
		resourceData[key] = data;
	}

	//animation 정보 저장
	for (size_t i = 0; i < m_AnimationInfos.size(); i++)
	{
		Json::Value data;
		getResourceKey("animation", i, key);
		data.append(m_AnimationInfos[i].type);
		data.append(m_AnimationInfos[i].frameNum);
		data.append(m_AnimationInfos[i].delay);

		for (int j = 0; j < m_AnimationInfos[i].frameNum; j++)
		{
			data.append(m_AnimationInfos[i].animationName[j]);
		}
		resourceData[key] = data;
	}
	
	Json::StyledWriter writer;
	std::string strJSON = writer.write(resourceData);

	saveData(RESOURCE_FILE_NAME, strJSON.c_str());

	return true;
}

bool Arthas::DataManager::loadSpriteCacheData()
{
	//data 불러오기
	ssize_t bufferSize = 0;
	unsigned char* fileData = cocos2d::FileUtils::getInstance()->getFileData(RESOURCE_FILE_NAME, "rb", &bufferSize);
	std::string clearData((const char*)fileData, bufferSize);

	Json::Value root;
	Json::Reader reader;
	char key[BUF_SIZE] = {};
	bool isParsingSuccess = reader.parse(clearData, root);

	if (!isParsingSuccess)
	{
		cocos2d::log("parser failed : \n %s", RESOURCE_FILE_NAME);
		return false;
	}

	m_SpriteCaches.clear();

	for(int idx = 0;true;idx++)
	{
		std::string string;

		//cache 파일 이름 불러오기
		getResourceKey("cache", idx, key);

		if (!root.isMember(key))
		{
			break;
		}

		string = root.get(key, 0).asString();
		m_SpriteCaches.push_back(string);
	}
	
	return true;
}

bool Arthas::DataManager::loadResourceData()
{
	//data 불러오기
	ssize_t bufferSize = 0;
	unsigned char* fileData = cocos2d::FileUtils::getInstance()->getFileData(RESOURCE_FILE_NAME, "rb", &bufferSize);
	std::string clearData((const char*)fileData, bufferSize);

	Json::Value root;
	Json::Reader reader;
	char key[BUF_SIZE] = {};
	bool isParsingSuccess = reader.parse(clearData, root);

	if (!isParsingSuccess)
	{
		cocos2d::log("parser failed : \n %s", RESOURCE_FILE_NAME);
		return false;
	}


	//spriteData 불러오기
	m_SpriteInfos.clear();
	for (int idx = 0; true; idx++)
	{
		SpriteInfo info;
		Json::Value value;

		//cache 파일 이름 불러오기
		getResourceKey("sprite", idx, key);

		if (!root.isMember(key))
		{
			break;
		}
		value = root.get(key, 0);
		
		info.type = (ResourceType)value[0].asInt();
		strcpy(info.spriteName, value[1].asString().c_str());

		m_SpriteInfos.push_back(info);
	}

	m_AnimationInfos.clear();
	for (int idx = 0; true; idx++)
	{
		AnimationInfo info;
		Json::Value value;

		//cache 파일 이름 불러오기
		getResourceKey("animation", idx, key);

		if (!root.isMember(key))
		{
			break;
		}
		value = root.get(key, 0);

		info.type = (ResourceType)value[0].asInt();
		info.frameNum = value[1].asInt();
		info.delay = value[2].asFloat();

		for (int j = 0; j < info.frameNum; j++)
		{
			strcpy(info.animationName[j], value[3+j].asString().c_str());
		}

		m_AnimationInfos.push_back(info);
	}
	
	return true;
}

const Arthas::StageData& Arthas::DataManager::getStageData(int floor)
{
	return m_StageDatas[floor];
}

const cocos2d::Size Arthas::DataManager::getModuleSize()
{
	return m_ModuleSize;
}

const cocos2d::Size Arthas::DataManager::getTileSize()
{
	return m_TileSize;
}

std::vector<Arthas::ModuleData>* Arthas::DataManager::getModuleDatas()
{
	return m_ModuleDatas;
}

void Arthas::DataManager::setModuleSize(cocos2d::Size size)
{
	m_ModuleSize = size;
}

void Arthas::DataManager::setTileSize(cocos2d::Size size)
{
	m_TileSize = size;
}

void Arthas::DataManager::initWorldData()
{
	m_StageDatas.clear();

	//test
	/*
	StageData stage;

	initStageData(stage,1);

	m_StageDatas.push_back(stage);


	m_StageDatas[0].Rooms[0].x = 0;
	m_StageDatas[0].Rooms[0].y = 0;
	///
	*/

	for (int floor = 0; floor < 4; floor++)
	{
		StageData stage;

		initStageData(stage, 8 + floor * 2 + rand() % (floor + 1));
		initRoomPlace(stage);

		m_StageDatas.push_back(stage);
	}
}

void Arthas::DataManager::initStageData(StageData& stage, int roomNumber)
{
	stage.Rooms.clear();

	for (int idx = 0; idx < roomNumber; idx++)
	{
		RoomData room;

		initRoomData(room);

		stage.Rooms.push_back(room);
	}

	initRoomPlace(stage);
}

void Arthas::DataManager::initRoomData(RoomData& room)
{
	ModulePlaceType mpt = (ModulePlaceType)(rand() % MPT_NUM);

	initModulePlace(room, mpt);
	fillRoomData(room);
}

void Arthas::DataManager::fillRoomData(RoomData& room)
{

	room.data.clear();

	room.data.resize(room.width*room.height);

	cocos2d::Size sizeByModule;

	sizeByModule.width = room.width / m_ModuleSize.width;
	sizeByModule.height = room.height / m_ModuleSize.height;

	for (int y = 0; y < sizeByModule.height; y++)
	{
		for (int x = 0; x < sizeByModule.width; x++)
		{
			//모듈이 배치된 칸만 찾아서 값 채워넣는다.
			if (room.modulePlaceData[y*sizeByModule.width + x] == 0)
				continue;

			Direction dir = DIR_NONE;

			//아래 칸이 빈 경우
			if (y == 0 || room.modulePlaceData[(y - 1)*sizeByModule.width + x] == 0)
				dir |= DIR_DOWN;

			//위 칸이 빈 경우
			if (y == sizeByModule.height - 1 || room.modulePlaceData[(y + 1)*sizeByModule.width + x] == 0)
				dir |= DIR_UP;

			//왼쪽 칸이 빈 경우
			if (x == 0 || room.modulePlaceData[y*sizeByModule.width + x - 1] == 0)
				dir |= DIR_LEFT;

			//오른쪽 칸이 빈 경우
			if (x == sizeByModule.width - 1 || room.modulePlaceData[y*sizeByModule.width + x + 1] == 0)
				dir |= DIR_RIGHT;

			matchModuleData(room, dir, x*m_ModuleSize.width, y*m_ModuleSize.height);
		}
	}

}

void Arthas::DataManager::initRoomPlace(StageData& stage)
{
	int placeData[PLACEMAP_SIZE][PLACEMAP_SIZE] = { 0, };
	cocos2d::Point position;
	std::vector<cocos2d::Point> candidate;
	cocos2d::Size sizeByModule;
	cocos2d::Point minPos, maxPos;

	sizeByModule.width = stage.Rooms[0].width / m_ModuleSize.width;
	sizeByModule.height = stage.Rooms[0].height / m_ModuleSize.height;

	//초기화로 첫번째 방의 위치를 랜덤하게 정한다. 혹 첫번째 방을 고정시켜야할 경우 이 부분 수정하면 됨.
	stage.Rooms[0].x = rand() % (int)(100 - sizeByModule.width);
	stage.Rooms[0].y = rand() % (int)(100 - sizeByModule.height);
	minPos.x = stage.Rooms[0].x;
	minPos.y = stage.Rooms[0].y;
	maxPos.x = stage.Rooms[0].x + sizeByModule.width;
	maxPos.y = stage.Rooms[0].y + sizeByModule.height;

	for (int y = stage.Rooms[0].y; y < stage.Rooms[0].y + sizeByModule.height; y++)
	{
		for (int x = stage.Rooms[0].x; x < stage.Rooms[0].x + sizeByModule.width; x++)
		{
			placeData[y][x] = 
				stage.Rooms[0].modulePlaceData[(y - stage.Rooms[0].y)*sizeByModule.width + x - stage.Rooms[0].x];
		}
	}

	//첫번째 방의 배치를 바탕으로 다른 방들도 랜덤하게 배치한다.

	for (int idx = 1; idx < stage.Rooms.size(); idx++)
	{
		sizeByModule.width = stage.Rooms[idx].width / m_ModuleSize.width;
		sizeByModule.height = stage.Rooms[idx].height / m_ModuleSize.height;

		candidate.clear();
		int startX = minPos.x - sizeByModule.width - 1;
		int startY = minPos.y - sizeByModule.height - 1;
		
		if (startX < 0)
			startX = 0;

		if (startY < 0)
			startY = 0;

		for (int y = startY; y <= maxPos.y; y++)
		{
			for (int x = startX; x <= maxPos.x; x++)
			{
				if (isCandidatePos(placeData, x, y, stage.Rooms[idx]))
					candidate.push_back(cocos2d::Point(x, y));
			}
		}

		int targetIdx = rand() % candidate.size();

		stage.Rooms[idx].x = candidate[targetIdx].x;
		stage.Rooms[idx].y = candidate[targetIdx].y;

		for (int y = stage.Rooms[idx].y; y < stage.Rooms[idx].y + sizeByModule.height; y++)
		{
			for (int x = stage.Rooms[idx].x; x < stage.Rooms[idx].x + sizeByModule.width; x++)
			{
				placeData[y][x] =
					stage.Rooms[idx].modulePlaceData[(y - stage.Rooms[idx].y)*sizeByModule.width + x - stage.Rooms[idx].x];
			}
		}

		if (minPos.x > stage.Rooms[idx].x)
		{
			minPos.x = stage.Rooms[idx].x;
		}

		if (minPos.y > stage.Rooms[idx].y)
		{
			minPos.y = stage.Rooms[idx].y;
		}

		if (maxPos.x < stage.Rooms[idx].x + stage.Rooms[idx].width)
		{
			maxPos.x = stage.Rooms[idx].x + stage.Rooms[idx].width;
		}

		if (maxPos.y < stage.Rooms[idx].y + stage.Rooms[idx].height)
		{
			maxPos.y = stage.Rooms[idx].y + stage.Rooms[idx].height;
		}
	}

	//평행이동
	for (int idx = 0; idx < stage.Rooms.size(); idx++)
	{
		stage.Rooms[idx].x -= minPos.x;
		stage.Rooms[idx].y -= minPos.y;
		stage.Rooms[idx].x *= m_ModuleSize.width;
		stage.Rooms[idx].y *= m_ModuleSize.height;
	}

	stage.width = (maxPos.x - minPos.x)*m_ModuleSize.width;
	stage.height = (maxPos.y - minPos.y)*m_ModuleSize.height;
}

void Arthas::DataManager::initModulePlace(RoomData& room, ModulePlaceType mpt)
{
	cocos2d::Size size;
	int num;

	room.modulePlaceData.clear();

	switch (mpt)
	{
	case MPT_RECT:
		size.width = 1 + rand() % 4;
		size.height = 1 + rand() % 4;
		initModulePlaceByRect(room.modulePlaceData, size);
		break;
	case MPT_DOUGHNUT:
		size.width = 3 + rand() % 4;
		size.height = 3 + rand() % 4;
		initModulePlaceByDoughnut(room.modulePlaceData, size);
		break;
	case MPT_RANDOM:
		size.width = 2 + rand() % 5;
		size.height = 2 + rand() % 5;
		num = (size.width / 2)*(size.height / 2);
		initModulePlaceByRandom(room.modulePlaceData, size, num);
		break;
	}
	room.width = size.width * m_ModuleSize.width;
	room.height = size.height * m_ModuleSize.height;
}

void Arthas::DataManager::initModulePlaceByRect(std::vector<int>& modulePlace, cocos2d::Size size)
{
	modulePlace.resize(size.height*size.width);

	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			modulePlace[y*size.width + x] = 1;
		}
	}
}

void Arthas::DataManager::initModulePlaceByDoughnut(std::vector<int>& modulePlace, cocos2d::Size size)
{
	modulePlace.resize(size.height*size.width);

	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			if (y == 0 || y == size.height - 1 ||
				x == 0 || x == size.width - 1)
				modulePlace[y*size.width + x] = 1;
		}
	}
}

void Arthas::DataManager::initModulePlaceByRandom(std::vector<int>& modulePlace, cocos2d::Size size, int moduleNum)
{
	modulePlace.resize(size.height*size.width);
	
	cocos2d::Point pos;
	
	pos.x = rand() % (int)size.width;
	pos.y = rand() % (int)size.height;

	modulePlace[pos.y*size.width + pos.x] = 1;

	for (int i = 1; i < moduleNum; i++)
	{
		
		cocos2d::Point nextPos;

		do
		{
			//1이 있는 위치 랜덤 선택.
			do
			{
				pos.x = rand() % (int)size.width;
				pos.y = rand() % (int)size.height;
			} while (pos.x < 0 || pos.x >= size.width ||
				pos.y < 0 || pos.y >= size.height ||
				modulePlace[pos.y*size.width + pos.x] == 0);

			int dir = rand() % 4;

			nextPos = pos;

			switch (dir)
			{
			case 0: // 위쪽
				nextPos.y++;
				break;
			case 1: // 오른쪽
				nextPos.x++;
				break;
			case 2: //아래쪽
				nextPos.y--;
				break;
			case 3: //왼쪽
				nextPos.x--;
				break;
			}
		} while (nextPos.x < 0 || nextPos.x >= size.width ||
			nextPos.y < 0 || nextPos.y >= size.height ||
			modulePlace[nextPos.y*size.width + nextPos.x] == 1); //적절한 빈칸인 경우 해당 포지션에 모듈 배치.

		modulePlace[nextPos.y*size.width + nextPos.x] = 1;
	}
}

void Arthas::DataManager::matchModuleData(RoomData& room, int type, int startX, int startY)
{
	int idx = rand() % m_ModuleDatas[type].size();

	for (int y = 0; y < m_ModuleSize.height; y++)
	{
		for (int x = 0; x < m_ModuleSize.width; x++)
		{
			room.data[(startY+y)*room.width + startX + x] = m_ModuleDatas[type][idx].data[y*m_ModuleSize.width + x];
		}
	}
}

bool Arthas::DataManager::isCandidatePos(int placeData[PLACEMAP_SIZE][PLACEMAP_SIZE],int x, int y, RoomData& room)
{
	bool isConnected = false;
	cocos2d::Size sizeByModule;

	sizeByModule.width = room.width / m_ModuleSize.width;
	sizeByModule.height = room.height / m_ModuleSize.height;

	for (int rx = 0; rx < sizeByModule.width; rx++)
	{
		for (int ry = 0; ry < sizeByModule.height; ry++)
		{
			int ridx = ry*sizeByModule.width + rx;
			if (room.modulePlaceData[ridx] == 1)
			{
				//room이 배치되어야 하는 곳은 비어있어야함.
				if (placeData[y + ry][x + rx] != 0)
					return false;

				//연결 체크 끝났으면 생략.
				if (isConnected)
					continue;

				//해당 칸 주변 4칸이 비지 않았으면 연결된 방.

				//왼쪽
				if (x + rx >= 1 && placeData[y + ry][x + rx - 1] == 1)
					isConnected = true;
				
				//오른쪽
				if (x + rx < PLACEMAP_SIZE - 1 && placeData[y + ry][x + rx + 1] == 1)
					isConnected = true;

				//위
				if (y + ry >= 1 && placeData[y + ry - 1][x + rx] == 1)
					isConnected = true;

				//오른쪽
				if (y + ry < PLACEMAP_SIZE - 1 && placeData[y + ry + 1][x + rx] == 1)
					isConnected = true;
			}
		}
	}

	return isConnected;
}

std::vector<Arthas::SpriteInfo>& Arthas::DataManager::getSpriteInfos()
{
	return m_SpriteInfos;
}

std::vector<Arthas::AnimationInfo>& Arthas::DataManager::getAnimationInfos()
{
	return m_AnimationInfos;
}
