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

	loadSpriteCacheData();
	loadResourceData();
	loadModuleData();

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

	for (int floor = 0; floor < 1; floor++)
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

			Direction dir = getModuleType(room, x, y);

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


	memset(m_PlaceData, 0, sizeof(int)*PLACEMAP_SIZE*PLACEMAP_SIZE);

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
			if (placeData[y][x] == 0)
			{
				int ridx = (y - stage.Rooms[0].y)*sizeByModule.width + x - stage.Rooms[0].x;

				if (stage.Rooms[0].modulePlaceData[ridx] == 1)
				{
					placeData[y][x] = 1;
				}
			}
		}
	}

	//첫번째 방의 배치를 바탕으로 다른 방들도 랜덤하게 배치한다.

	for (int idx = 1; idx < stage.Rooms.size(); idx++)
	{
		sizeByModule.width = stage.Rooms[idx].width / m_ModuleSize.width;
		sizeByModule.height = stage.Rooms[idx].height / m_ModuleSize.height;

		candidate.clear();
		int startX = minPos.x - sizeByModule.width - 2;
		int startY = minPos.y - sizeByModule.height - 2;
		
		if (startX < 0)
			startX = 0;

		if (startY < 0)
			startY = 0;

		//가능한 후보군을 선정한 후 이 중에서 랜덤하게 택일한다.
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
				if (placeData[y][x] == 0)
				{
					int ridx = (y - stage.Rooms[idx].y)*sizeByModule.width + x - stage.Rooms[idx].x;

					if (stage.Rooms[idx].modulePlaceData[ridx] == 1)
					{
						placeData[y][x] = idx + 1;
					}
				}
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

		if (maxPos.x < stage.Rooms[idx].x + sizeByModule.width)
		{
			maxPos.x = stage.Rooms[idx].x + sizeByModule.width;
		}

		if (maxPos.y < stage.Rooms[idx].y + sizeByModule.height)
		{
			maxPos.y = stage.Rooms[idx].y + sizeByModule.height;
		}

		if (maxPos.x >= PLACEMAP_SIZE)
		{
			maxPos.x = PLACEMAP_SIZE;
		}

		if (maxPos.y >= PLACEMAP_SIZE)
		{
			maxPos.y = PLACEMAP_SIZE;
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

	//0,0에 딱 붙여서 placeData 저장.
	for (int y = minPos.y; y < maxPos.y; y++)
	{
		for (int x = minPos.x; x < maxPos.x; x++)
		{
			m_PlaceData[(int)(y - minPos.y)][(int)(x - minPos.x)] = placeData[y][x];
		}
	}

	//width,height 계산
	int maxX=0, maxY=0;
	for (int i = 0; i < stage.Rooms.size();i++)
	{
		if (maxX < stage.Rooms[i].x + stage.Rooms[i].width)
			maxX = stage.Rooms[i].x + stage.Rooms[i].width;

		if (maxY < stage.Rooms[i].y + stage.Rooms[i].height)
			maxY = stage.Rooms[i].y + stage.Rooms[i].height;
	}
	stage.width = maxY + 1;
	stage.height = maxX + 1;

	//방 연결 정보 생성
	makeRoomConnectData(stage);
}

void Arthas::DataManager::initRoomPlace(int floor)
{
	initRoomPlace(m_StageDatas[floor]);
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
		num = (size.width / 2)*(size.height / 2) + 2;
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
				if (x + rx >= 1 && placeData[y + ry][x + rx - 1] != 0)
					isConnected = true;
				
				//오른쪽
				if (x + rx < PLACEMAP_SIZE - 1 && placeData[y + ry][x + rx + 1] != 0)
					isConnected = true;

				//위
				if (y + ry >= 1 && placeData[y + ry - 1][x + rx] != 0)
					isConnected = true;

				//오른쪽
				if (y + ry < PLACEMAP_SIZE - 1 && placeData[y + ry + 1][x + rx] != 0)
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

void Arthas::DataManager::makeRoomConnectData(StageData& stage)
{
	for (int i = 0; i < stage.Rooms.size(); i++)
	{
		makePortal(stage.Rooms[i]);
	}
}

void Arthas::DataManager::makePortal(RoomData& room)
{
	int rx = room.x / m_ModuleSize.width;
	int ry = room.y / m_ModuleSize.height;
	int width = room.width / m_ModuleSize.width;
	int height = room.height / m_ModuleSize.height;

	for (int y = ry; y < ry + height; y++)
	{
		for (int x = rx; x < rx + width; x++)
		{
			int ridx = (y - ry)*width + x - rx;

			//모듈이 있는 경우만 판단
			if (room.modulePlaceData[ridx] != 0)
			{
				int dir = getConnectedDirections(room, x, y);

				//연결되는 방향이 있는 경우 그 쪽에 포탈 생성. 연결된 거 없는 쪽은 포탈 삭제.
				adjustRoomData(room, x - rx, y - ry, dir);
			}
		}
	}
}

int Arthas::DataManager::getConnectedDirections(RoomData& room, int x, int y)
{

	//rx,ry는 room 기준 좌표.
	//x,y는 전체 world 기준 좌표.
	int rx = x - room.x / m_ModuleSize.width;
	int ry = y - room.y / m_ModuleSize.height;
	int width = room.width / m_ModuleSize.width;
	int height = room.height / m_ModuleSize.height;
	int ridx = ry*width + rx;
	int dir = DIR_NONE;

	//모듈이 있는 경우 어디어디로 연결되는지 파악한다.

	int connectIdx;
	int placeValue;

	//왼쪽 연결 테스트
	connectIdx = ry*width + rx - 1;
	placeValue = (rx > 0) ? room.modulePlaceData[connectIdx] : 0;
	//왼쪽 칸이 자기는 없는 모듈이고 딴 애 모듈은 있는 경우.
	if (x > 0 &&
		placeValue == 0 && m_PlaceData[y][x - 1] != 0)
	{
		dir |= DIR_LEFT;
	}

	//오른쪽 연결 테스트
	connectIdx = ry*width + rx + 1;
	placeValue = (rx < width - 1) ? room.modulePlaceData[connectIdx] : 0;
	//오른쪽 칸이 자기는 없는 모듈이고 딴 애 모듈은 있는 경우.
	if (x < PLACEMAP_SIZE - 1 &&
		placeValue == 0 && m_PlaceData[y][x + 1] != 0)
	{
		dir |= DIR_RIGHT;
	}

	//아래쪽 연결 테스트
	connectIdx = (ry-1)*width + rx;
	placeValue = (ry > 0) ? room.modulePlaceData[connectIdx] : 0;
	//아래쪽 칸이 자기는 없는 모듈이고 딴 애 모듈은 있는 경우.
	if (y > 0 &&
		placeValue == 0 && m_PlaceData[y - 1][x] != 0)
	{
		dir |= DIR_DOWN;
	}

	//위쪽 연결 테스트
	connectIdx = (ry + 1)*width + rx;
	placeValue = (ry < height - 1) ? room.modulePlaceData[connectIdx] : 0;
	//위쪽 칸이 자기는 없는 모듈이고 딴 애 모듈은 있는 경우.
	if (y < PLACEMAP_SIZE - 1 &&
		placeValue == 0 && m_PlaceData[y + 1][x] != 0)
	{
		dir |= DIR_UP;
	}

	return dir;
}

void Arthas::DataManager::adjustRoomData(RoomData& room, int rx, int ry, int dir)
{
	
	int moduleType = getModuleType(room, rx, ry);
	int sx = rx*m_ModuleSize.width;
	int sy = ry*m_ModuleSize.height;

	//왼쪽 체크
	if (moduleType & DIR_LEFT)
	{
		//왼쪽에 포탈 있는 경우 포탈 생성. 없으면 포탈 막음.
		if (dir & DIR_LEFT)
		{
			setRoomData(room, sx, sy + m_ModuleSize.height/2 - PORTAL_SIZE / 2, 
						sx,	sy + m_ModuleSize.height / 2 + PORTAL_SIZE / 2, OT_PORTAL_OPEN);
		}
		else
		{
			setRoomData(room, sx, sy + m_ModuleSize.height/2 - PORTAL_SIZE / 2, 
						sx, sy + m_ModuleSize.height / 2 + PORTAL_SIZE / 2, OT_PORTAL_CLOSED);
		}
	}

	//오른쪽 체크
	if (moduleType & DIR_RIGHT)
	{
		if (dir & DIR_RIGHT)
		{
			setRoomData(room, sx + m_ModuleSize.width - 1, sy + m_ModuleSize.height/2 - PORTAL_SIZE/ 2,
						sx + m_ModuleSize.width - 1, sy + m_ModuleSize.height / 2 + PORTAL_SIZE / 2, OT_PORTAL_OPEN);
		}
		else
		{
			setRoomData(room, sx + m_ModuleSize.width - 1, sy + m_ModuleSize.height/2 - PORTAL_SIZE/ 2,
						sx + m_ModuleSize.width - 1, sy + m_ModuleSize.height/2 + PORTAL_SIZE/ 2, OT_PORTAL_CLOSED);
		}
	}

	//위쪽 체크
	if (moduleType & DIR_UP)
	{
		if (dir & DIR_UP)
		{
			setRoomData(room, sx + m_ModuleSize.width / 2 - PORTAL_SIZE / 2, sy + m_ModuleSize.height - 1,
						sx + m_ModuleSize.width / 2 + PORTAL_SIZE / 2, sy + m_ModuleSize.height - 1, OT_PORTAL_OPEN);
		}
		else
		{
			setRoomData(room, sx + m_ModuleSize.width / 2 - PORTAL_SIZE / 2, sy + m_ModuleSize.height - 1,
						sx + m_ModuleSize.width / 2 + PORTAL_SIZE / 2, sy + m_ModuleSize.height - 1, OT_PORTAL_CLOSED);
		}
	}

	//아래쪽 체크
	if (moduleType & DIR_DOWN)
	{
		if (dir & DIR_DOWN)
		{
			setRoomData(room, sx + m_ModuleSize.width / 2 - PORTAL_SIZE / 2, sy,
						sx + m_ModuleSize.width / 2 + PORTAL_SIZE / 2, sy, OT_PORTAL_OPEN);
		}
		else
		{
			setRoomData(room, sx + m_ModuleSize.width / 2 - PORTAL_SIZE / 2, sy,
						sx + m_ModuleSize.width / 2 + PORTAL_SIZE / 2, sy, OT_PORTAL_CLOSED);
		}
	}
}

int Arthas::DataManager::getModuleType(RoomData& room, int x, int y)
{
	Direction dir = DIR_NONE;
	cocos2d::Size sizeByModule;

	sizeByModule.width = room.width / m_ModuleSize.width;
	sizeByModule.height = room.height / m_ModuleSize.height;

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

	return dir;
}

void Arthas::DataManager::setRoomData(RoomData& room, int sx, int sy, int ex, int ey, ComponentType type)
{
	for (int y = sy; y <= ey; y++)
	{
		for (int x = sx; x <= ex; x++)
		{
			int idx = y*room.width + x;

			room.data[idx] = type;
		}
	}
}

int Arthas::DataManager::getNextRoomNumber(int floor, int room, cocos2d::Point& playerPos)
{
	//전체 월드에서 타일 기준으로 x,y좌표.
	int tileX = m_StageDatas[floor].Rooms[room].x + playerPos.x / m_TileSize.width;
	int tileY = m_StageDatas[floor].Rooms[room].y + playerPos.y / m_TileSize.height;

	//현재 플레이어가 있는 좌표의 모듈 기준 값.
	int moduleX = tileX / m_ModuleSize.width;
	int moduleY = tileY / m_ModuleSize.height;
	int nextRoom;

	//다음 방이 없는 경우(잘못된 접근)
	_ASSERT(m_PlaceData[moduleY][moduleX] != 0);
	if (m_PlaceData[moduleY][moduleX] == 0)
	{
		return -1;
	}

	nextRoom = m_PlaceData[moduleY][moduleX] - 1;
	
	//현재 방의 전체 월드에서의 타일 기준 x,y 시작 좌표.
	int roomStartX = m_StageDatas[floor].Rooms[room].x*m_TileSize.width;
	int roomStartY = m_StageDatas[floor].Rooms[room].y*m_TileSize.width;
	
	//다음 방의 전체 월드에서의 타일 기준 x,y 시작 좌표.
	int nextRoomStartX = m_StageDatas[floor].Rooms[nextRoom].x*m_TileSize.width;
	int nextRoomStartY = m_StageDatas[floor].Rooms[nextRoom].y*m_TileSize.width;

	//현재 룸 내에서 플레이어의 좌표.
	cocos2d::Point playerPosInRoom;
	playerPosInRoom.x = playerPos.x + roomStartX;
	playerPosInRoom.y = playerPos.y + roomStartY;

	//새로 이동한 방에서의 플레이어 좌표.
	playerPos.x = playerPosInRoom.x - nextRoomStartX;
	playerPos.y = playerPosInRoom.y - nextRoomStartY;
	
	return nextRoom;
}

const Arthas::RoomData& Arthas::DataManager::getRoomData(int floor, int room)
{
	_ASSERT(!(floor < 0 || floor >= m_StageDatas.size() ||
		room < 0 || room >= m_StageDatas[floor].Rooms.size()));

	if (floor < 0 || floor >= m_StageDatas.size() ||
		room < 0 || room >= m_StageDatas[floor].Rooms.size())
		return RoomData();

	return m_StageDatas[floor].Rooms[room];
}
