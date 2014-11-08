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
	StageData stage;

	initStageData(stage,1);

	m_StageDatas.push_back(stage);

	///

	m_StageDatas[0].Rooms[0].x = 0;
	m_StageDatas[0].Rooms[0].y = 0;

	/*
	for (int floor = 0; floor < 4; floor++)
	{
		StageData stage;

		initStageData(stage, 8 + floor * 2 + rand() % (floor + 1));

		m_StageDatas.push_back(stage);
	}*/
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

	for (int i = 0; i < moduleNum; i++)
	{
		
		cocos2d::Point nextPos;

		do
		{
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
		

		do
		{
			pos.x = rand() % (int)size.width;
			pos.y = rand() % (int)size.height;
		}while(pos.x < 0 || pos.x >= size.width ||
			pos.y < 0 || pos.y >= size.height ||
			modulePlace[pos.y*size.width + pos.x] == 0);
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
