#include "pch.h"
#include "DataManager.h"
#include "cocos2d.h"
#include "json/json.h"

DataManager::DataManager()
{
	//config 파일이 없음. 임시 대입.

	m_FloorNum = 4;
}

DataManager::~DataManager()
{

}

bool DataManager::init()
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

bool DataManager::loadModuleData()
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

		//size 불러오기
		getModuleKey(dirType, "size", key);
		size = root.get(key, 0).asInt();

		if (size <= 0)
		{
			continue;
		}

		for (int idx = 0; idx < size; idx++)
		{
			ModuleData data;

			//ComponentType 배열 불러오기
			getModuleKey(dirType, idx, "data", key);
			Json::Value array = root[key];

			data.m_Name = array[0].asString();

			for (int i = 0; i < width * height; i++)
			{
				RawTileType type;

				type = (RawTileType)array[i+1].asInt();

				data.m_Data.push_back(type);
			}
			m_ModuleDatas[dirType].push_back(data);
		}
		
	}

	return true;
}


bool DataManager::saveModuleData()
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

			data.append(m_ModuleDatas[dirType][idx].m_Name);
			for (int i = 0; i < width * height; i++)
			{
				data.append(m_ModuleDatas[dirType][idx].m_Data[i]);
			}

			//data.append(m_ModuleDatas[dirType][idx].m_Type);
			
			getModuleKey(dirType, idx, "data", buffer);
			moduleData[buffer] = data;
		}
	}

	Json::StyledWriter writer;
	std::string strJSON = writer.write(moduleData);

	saveData(MODULE_FILE_NAME, strJSON.c_str());

	return true;
}

bool DataManager::saveData(std::string fileName, const char* pData)
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

bool DataManager::getModuleKey(int type, int idx, char* category, OUT char* key)
{
	if (key == nullptr || category == nullptr)
		return false;

	sprintf(key, "%d_%d_%s", type, idx, category);

	return true;
}

bool DataManager::getModuleKey(int type, char* category, OUT char* key)
{
	if (key == nullptr || category == nullptr)
		return false;

	sprintf(key, "%d_%s", type, category);

	return true;
}

SpriteInfo DataManager::getSpriteInfo(SpriteType spriteType)
{
	SpriteInfo errorInfo = {};

	_ASSERT(spriteType >= ST_START&&spriteType < ST_END);

	if (!(spriteType >= ST_START&&spriteType < ST_END))
	{
		return errorInfo;
	}

	for (size_t i = 0; i < m_SpriteInfos.size(); i++)
	{
		if (m_SpriteInfos[i].m_Type == spriteType)
		{
			return m_SpriteInfos[i];
		}
	}
	

	return errorInfo;
}

AnimationInfo DataManager::getAnimationInfo(AnimationType animationType)
{
	AnimationInfo errorInfo = {};

	_ASSERT(animationType >= AT_START&& animationType < AT_END);

	if (!(animationType >= AT_START&& animationType < AT_END))
	{
		errorInfo.m_FrameNum = -1;
		return errorInfo;
	}

	for (size_t i = 0; i < m_AnimationInfos.size(); i++)
	{
		if (m_AnimationInfos[i].m_Type == animationType)
		{
			return m_AnimationInfos[i];
		}
	}

	return errorInfo;
}

bool DataManager::getResourceKey(char* category, int idx, OUT char* key)
{
	if (key == nullptr || category == nullptr)
		return false;

	sprintf(key, "%s_%d", category, idx);

	return true;
}

bool DataManager::saveResourceData()
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
		data.append(m_SpriteInfos[i].m_Type);
		data.append(m_SpriteInfos[i].m_SpriteName);
		resourceData[key] = data;
	}

	//animation 정보 저장
	for (size_t i = 0; i < m_AnimationInfos.size(); i++)
	{
		Json::Value data;
		getResourceKey("animation", i, key);
		data.append(m_AnimationInfos[i].m_Type);
		data.append(m_AnimationInfos[i].m_FrameNum);
		data.append(m_AnimationInfos[i].m_Delay);

		for (int j = 0; j < m_AnimationInfos[i].m_FrameNum; j++)
		{
			data.append(m_AnimationInfos[i].m_AnimationName[j]);
		}
		resourceData[key] = data;
	}
	
	Json::StyledWriter writer;
	std::string strJSON = writer.write(resourceData);

	saveData(RESOURCE_FILE_NAME, strJSON.c_str());

	return true;
}

bool DataManager::loadSpriteCacheData()
{
	//data 불러오기
	ssize_t bufferSize = 0;
	unsigned char* fileData = cocos2d::FileUtils::getInstance()->getFileData(RESOURCE_FILE_NAME, "rb", &bufferSize);
	std::string clearData((char*)fileData, bufferSize);

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

bool DataManager::loadResourceData()
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
		
		info.m_Type = (SpriteType)value[0].asInt();
		strcpy(info.m_SpriteName, value[1].asString().c_str());

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

		info.m_Type = (AnimationType)value[0].asInt();
		info.m_FrameNum = value[1].asInt();
		info.m_Delay = value[2].asFloat();

		for (int j = 0; j < info.m_FrameNum; j++)
		{
			strcpy(info.m_AnimationName[j], value[3+j].asString().c_str());
		}

		m_AnimationInfos.push_back(info);
	}
	
	return true;
}

const StageData& DataManager::getStageData(int floor)
{
	return m_StageDatas[floor];
}

const cocos2d::Size DataManager::getModuleSize()
{
	return m_ModuleSize;
}

const cocos2d::Size DataManager::getTileSize()
{
	return m_TileSize;
}

std::vector<ModuleData>* DataManager::getModuleDatas()
{
	return m_ModuleDatas;
}

void DataManager::setModuleSize(cocos2d::Size size)
{
	m_ModuleSize = size;
}

void DataManager::setTileSize(cocos2d::Size size)
{
	m_TileSize = size;
}

std::vector<SpriteInfo>& DataManager::getSpriteInfos()
{
	return m_SpriteInfos;
}

std::vector<AnimationInfo>& DataManager::getAnimationInfos()
{
	return m_AnimationInfos;
}

int DataManager::getTileData(int floor, int room, cocos2d::Point position)
{
	int tileX = position.x / m_TileSize.width;
	int tileY = position.y / m_TileSize.height;

	auto roomData =  m_StageDatas[floor].m_Rooms[room];

	if (tileY*roomData.m_Width + tileX >= roomData.m_Data.size())
	{
		return CT_NONE;
	}

	if (tileY < 0 || tileY >= roomData.m_Height ||
		tileX < 0 || tileX >= roomData.m_Width)
	{
		return CT_NONE;
	}

	int tile = roomData.m_Data[tileY*roomData.m_Width + tileX];

	if(tile == OT_FLOOR || tile == OT_BLOCK)
	{
		return tile;
	}
	else
	{
		return CT_NONE;
	}
}

void DataManager::initWorldData()
{
	m_StageDatas.clear();
	m_StageDatas.resize(m_FloorNum);

	for (int floor = 0; floor < m_FloorNum; floor++)
	{
		initStageData(floor, 8 + floor * 2 + rand() % (floor + 1));
	}
}

void DataManager::initStageData(int floor, int roomNumber)
{
	if (floor < 0 || floor >= m_FloorNum)
	{
		return;
	}

	StageData& stage = m_StageDatas[floor];

	stage.m_Rooms.clear();

	stage.m_Rooms.resize(roomNumber);

	//방 각각의 기본 정보 초기화
	for (int idx = 0; idx < roomNumber; idx++)
	{
		initRoomData(floor, idx);
	}

	//방간 배치 관계 초기화
	initRoomPlace(floor);

	//방 연결 정보 생성
	makeRoomConnectData(floor);
}

void DataManager::initRoomData(int floor, int roomIdx)
{
	if (floor < 0 || floor >= m_FloorNum)
		return;

	if (roomIdx < 0 || roomIdx >= m_StageDatas[floor].m_Rooms.size())
		return;

	ModulePlaceType mpt = static_cast<ModulePlaceType>(rand() % MPT_NUM);

	initModulePlace(&m_StageDatas[floor].m_Rooms[roomIdx], mpt);
}

void DataManager::fillRoomData(int floor, int roomIdx)
{

	RoomData& room = m_StageDatas[floor].m_Rooms[roomIdx];

	room.m_Data.clear();

	room.m_Data.resize(room.m_Width*room.m_Height);

	cocos2d::Size sizeByModule;

	sizeByModule.width = room.m_Width / m_ModuleSize.width;
	sizeByModule.height = room.m_Height / m_ModuleSize.height;

	for (int y = 0; y < sizeByModule.height; y++)
	{
		for (int x = 0; x < sizeByModule.width; x++)
		{
			//모듈이 배치된 칸만 찾아서 값 채워넣는다.
			if (room.m_ModulePlaceData[y*sizeByModule.width + x] == 0)
				continue;

			Direction dir = getModuleType(&room, x, y);

			matchModuleData(&room, dir, x, y, floor);
		}
	}

}

void DataManager::initRoomPlace(int floor)
{
	if (floor < 0 || floor >= m_FloorNum)
		return;

	cocos2d::Point position;
	std::vector<cocos2d::Point> candidate;
	cocos2d::Size sizeByModule;
	cocos2d::Point minPos, maxPos;
	StageData& stage = m_StageDatas[floor];

	sizeByModule.width = stage.m_Rooms[0].m_Width / m_ModuleSize.width;
	sizeByModule.height = stage.m_Rooms[0].m_Height / m_ModuleSize.height;


	memset(m_PlaceData[floor], 0, sizeof(int)*PLACEMAP_SIZE*PLACEMAP_SIZE);

	//초기화로 첫번째 방의 위치를 랜덤하게 정한다. 혹 첫번째 방을 고정시켜야할 경우 이 부분 수정하면 됨.
	stage.m_Rooms[0].m_X = rand() % (int)(100 - sizeByModule.width);
	stage.m_Rooms[0].m_Y = rand() % (int)(100 - sizeByModule.height);
	minPos.x = stage.m_Rooms[0].m_X;
	minPos.y = stage.m_Rooms[0].m_Y;
	maxPos.x = stage.m_Rooms[0].m_X + sizeByModule.width;
	maxPos.y = stage.m_Rooms[0].m_Y + sizeByModule.height;

	setPlaceData(floor, 0);

	//첫번째 방의 배치를 바탕으로 다른 방들도 랜덤하게 배치한다.

	for (int idx = 1; idx < stage.m_Rooms.size(); idx++)
	{
		sizeByModule.width = stage.m_Rooms[idx].m_Width / m_ModuleSize.width;
		sizeByModule.height = stage.m_Rooms[idx].m_Height / m_ModuleSize.height;

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
				if (isCandidatePos(floor, idx, x, y))
					candidate.push_back(cocos2d::Point(x, y));
			}
		}

		int targetIdx = rand() % candidate.size();

		stage.m_Rooms[idx].m_X = candidate[targetIdx].x;
		stage.m_Rooms[idx].m_Y = candidate[targetIdx].y;

		setPlaceData(floor, idx);

		if (minPos.x > stage.m_Rooms[idx].m_X)
		{
			minPos.x = stage.m_Rooms[idx].m_X;
		}

		if (minPos.y > stage.m_Rooms[idx].m_Y)
		{
			minPos.y = stage.m_Rooms[idx].m_Y;
		}

		if (maxPos.x < stage.m_Rooms[idx].m_X + sizeByModule.width)
		{
			maxPos.x = stage.m_Rooms[idx].m_X + sizeByModule.width;
		}

		if (maxPos.y < stage.m_Rooms[idx].m_Y + sizeByModule.height)
		{
			maxPos.y = stage.m_Rooms[idx].m_Y + sizeByModule.height;
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
	for (int idx = 0; idx < stage.m_Rooms.size(); idx++)
	{
		stage.m_Rooms[idx].m_X -= minPos.x;
		stage.m_Rooms[idx].m_Y -= minPos.y;
		stage.m_Rooms[idx].m_X *= m_ModuleSize.width;
		stage.m_Rooms[idx].m_Y *= m_ModuleSize.height;
	}

	//0,0에 딱 붙여서 placeData 저장.
	for (int y = minPos.y; y < PLACEMAP_SIZE; y++)
	{
		for (int x = minPos.x; x < PLACEMAP_SIZE; x++)
		{
			m_PlaceData[floor][(int)(y - minPos.y)][(int)(x - minPos.x)] = m_PlaceData[floor][y][x];
		}
	}

	//width,height 계산
	int maxX = 0, maxY = 0;
	for (int i = 0; i < stage.m_Rooms.size(); i++)
	{
		if (maxX < stage.m_Rooms[i].m_X + stage.m_Rooms[i].m_Width)
			maxX = stage.m_Rooms[i].m_X + stage.m_Rooms[i].m_Width;

		if (maxY < stage.m_Rooms[i].m_Y + stage.m_Rooms[i].m_Height)
			maxY = stage.m_Rooms[i].m_Y + stage.m_Rooms[i].m_Height;
	}
	stage.m_Width = maxY + 1;
	stage.m_Height = maxX + 1;
}

void DataManager::initModulePlace(RoomData* room, ModulePlaceType mpt)
{
	cocos2d::Size size;
	int num;

	room->m_Data.clear();
	room->m_ModulePlaceData.clear();
	
	switch (mpt)
	{
	case MPT_RECT:
		size.width = 1 + rand() % 3;
		size.height = 1 + rand() % 3;
		initModulePlaceByRect(room, size);
		break;
	case MPT_DOUGHNUT:
		size.width = 3 + rand() % 2;
		size.height = 3 + rand() % 2;
		initModulePlaceByDoughnut(room, size);
		break;
	case MPT_RANDOM:
		size.width = 2 + rand() % 5;
		size.height = 2 + rand() % 5;
		num = (size.width / 2)*(size.height / 2) + 2;
		initModulePlaceByRandom(room, size, num);
		break;
	}
	room->m_Width = size.width * m_ModuleSize.width;
	room->m_Height = size.height * m_ModuleSize.height;
}

void DataManager::initModulePlaceByRect(RoomData* room, cocos2d::Size size)
{
	room->m_ModulePlaceData.resize(size.height*size.width);

	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			room->m_ModulePlaceData[y*size.width + x] = 1;
		}
	}
}

void DataManager::initModulePlaceByDoughnut(RoomData* room, cocos2d::Size size)
{
	room->m_ModulePlaceData.resize(size.height*size.width);

	for (int y = 0; y < size.height; y++)
	{
		for (int x = 0; x < size.width; x++)
		{
			if (y == 0 || y == size.height - 1 ||
				x == 0 || x == size.width - 1)
				room->m_ModulePlaceData[y*size.width + x] = 1;
		}
	}
}

void DataManager::initModulePlaceByRandom(RoomData* room, cocos2d::Size size, int moduleNum)
{
	room->m_ModulePlaceData.resize(size.height*size.width);

	cocos2d::Point pos;

	pos.x = rand() % (int)size.width;
	pos.y = rand() % (int)size.height;

	room->m_ModulePlaceData[pos.y*size.width + pos.x] = 1;

	for (int i = 1; i < moduleNum; i++)
	{

		cocos2d::Point nextPos;

		do
		{
			//1이 있는 위치 랜덤 선택.
			do
			{
				pos.x = rand() % static_cast<int>(size.width);
				pos.y = rand() % static_cast<int>(size.height);
			} while (pos.x < 0 || pos.x >= size.width ||
				pos.y < 0 || pos.y >= size.height ||
				room->m_ModulePlaceData[pos.y*size.width + pos.x] == 0);

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
			room->m_ModulePlaceData[nextPos.y*size.width + nextPos.x] == 1); //적절한 빈칸인 경우 해당 포지션에 모듈 배치.

		room->m_ModulePlaceData[nextPos.y*size.width + nextPos.x] = 1;
	}
}

void DataManager::matchModuleData(RoomData* room, int type, int startX, int startY, int floor)
{
	int idx;
	int tileX = startX * m_ModuleSize.width;
	int tileY = startY * m_ModuleSize.height;
	int portalDir = DIR_NONE;
	portalDir = isPortal(floor, (room->m_X + tileX) / m_ModuleSize.width, (room->m_Y + tileY) / m_ModuleSize.height);

	do
	{
		idx = rand() % m_ModuleDatas[type].size();
	} while ((!!portalDir) ^ isPortalTypeModule(type, idx));

	int blockRandom = rand() % 100;
	int floorRandom = rand() % 100;


	for (int y = 0; y < m_ModuleSize.height; y++)
	{
		for (int x = 0; x < m_ModuleSize.width; x++)
		{
			int data = CT_NONE;
			switch (m_ModuleDatas[type][idx].m_Data[y*m_ModuleSize.width + x])
			{
			case RT_BLOCK:
				data = OT_BLOCK;
				break;
			case RT_FLOOR:
				data = OT_FLOOR;
				break;
			case RT_PORTAL:
				if ((x == 0 && m_PlaceData[startY][startX - 1] != 0 && (portalDir & DIR_LEFT)) ||
					(x == m_ModuleSize.width - 1 && m_PlaceData[startY][startX + 1] != 0 && (portalDir & DIR_RIGHT)) ||
					(y == 0 && m_PlaceData[startY - 1][startX] != 0 && (portalDir & DIR_DOWN)) ||
					(y == m_ModuleSize.height - 1 && m_PlaceData[startY + 1][startX] != 0 && (portalDir & DIR_UP)))
					data = OT_PORTAL_OPEN;
				else
					data = OT_BLOCK;
				break;
			case RT_BLOCK_RANDOM:
				if (blockRandom < 70)
				{
					data = OT_BLOCK;
				}
				break;
			case RT_FLOOR_RANDOM:
				if (floorRandom < 70)
				{
					data = OT_FLOOR;
				}
				break;
			case RT_MONSTER_RANDOM:
				if (rand() % 100 < 70)
				{
					data = OT_MONSTER_STAND_SHOT;
				}
				break;
			}
			room->m_Data[(tileY + y)*room->m_Width + tileX + x] = data;
		}
	}
}

bool DataManager::isCandidatePos(int floor, int roomIdx, int x, int y)
{
	bool isConnected = false;
	cocos2d::Size sizeByModule;
	RoomData& room = m_StageDatas[floor].m_Rooms[roomIdx];

	sizeByModule.width = room.m_Width / m_ModuleSize.width;
	sizeByModule.height = room.m_Height / m_ModuleSize.height;

	for (int rx = 0; rx < sizeByModule.width; rx++)
	{
		for (int ry = 0; ry < sizeByModule.height; ry++)
		{
			int ridx = ry*sizeByModule.width + rx;
			if (room.m_ModulePlaceData[ridx] == 1)
			{
				//room이 배치되어야 하는 곳은 비어있어야함.
				if (m_PlaceData[floor][y + ry][x + rx] != 0)
					return false;

				//연결 체크 끝났으면 생략.
				if (isConnected)
					continue;

				//해당 칸 주변 4칸이 비지 않았으면 연결된 방.

				//왼쪽
				if (x + rx >= 1 && m_PlaceData[floor][y + ry][x + rx - 1] != 0)
					isConnected = true;

				//오른쪽
				if (x + rx < PLACEMAP_SIZE - 1 && m_PlaceData[floor][y + ry][x + rx + 1] != 0)
					isConnected = true;

				//위
				if (y + ry >= 1 && m_PlaceData[floor][y + ry - 1][x + rx] != 0)
					isConnected = true;

				//아래
				if (y + ry < PLACEMAP_SIZE - 1 && m_PlaceData[floor][y + ry + 1][x + rx] != 0)
					isConnected = true;
			}
		}
	}

	return isConnected;
}

void DataManager::makeRoomConnectData(int floor)
{
	StageData& stage = m_StageDatas[floor];

	for (int i = 0; i < stage.m_Rooms.size(); i++)
	{
		stage.m_Rooms[i].m_Portals.clear();
	}

	for (int i = 0; i < stage.m_Rooms.size(); i++)
	{
		makePortal(floor, i);
		fillRoomData(floor, i);
	}
}

void DataManager::makePortal(int floor, int roomIdx)
{

	RoomData& room = m_StageDatas[floor].m_Rooms[roomIdx];
	int rx = room.m_X / m_ModuleSize.width;
	int ry = room.m_Y / m_ModuleSize.height;
	int width = room.m_Width / m_ModuleSize.width;
	int height = room.m_Height / m_ModuleSize.height;

	std::vector<std::vector<PortalData>> portalCandidates;

	portalCandidates.resize(m_StageDatas[floor].m_Rooms.size() + 1);

	for (int y = ry; y < ry + height; y++)
	{
		for (int x = rx; x < rx + width; x++)
		{
			int ridx = (y - ry)*width + x - rx;

			//모듈이 있는 경우만 판단
			if (room.m_ModulePlaceData[ridx] == 0)
			{
				continue;
			}

			int dir = getConnectedDirections(&room, floor, x, y);
			PortalData portal;
			portal.m_Pos = cocos2d::Point(x, y);

			//위쪽 방향 검사
			if (dir & DIR_UP)
			{
				int nextRoom = m_PlaceData[floor][y + 1][x];

				if (nextRoom > roomIdx + 1)
				{
					portal.m_ConnectedRoomIdx = nextRoom;
					portal.m_Dir = DIR_UP;
				}
				portalCandidates[nextRoom].push_back(portal);
			}

			//오른쪽 방향 검사
			if (dir & DIR_RIGHT)
			{
				int nextRoom = m_PlaceData[floor][y][x + 1];

				if (nextRoom > roomIdx + 1)
				{
					portal.m_ConnectedRoomIdx = nextRoom;
					portal.m_Dir = DIR_RIGHT;
				}
				portalCandidates[nextRoom].push_back(portal);
			}

			//아래쪽 방향 검사
			if (dir & DIR_DOWN)
			{
				int nextRoom = m_PlaceData[floor][y - 1][x];

				if (nextRoom > roomIdx + 1)
				{
					portal.m_ConnectedRoomIdx = nextRoom;
					portal.m_Dir = DIR_DOWN;
				}
				portalCandidates[nextRoom].push_back(portal);
			}

			//왼쪽 방향 검사
			if (dir & DIR_LEFT)
			{
				int nextRoom = m_PlaceData[floor][y][x - 1];

				if (nextRoom > roomIdx + 1)
				{
					portal.m_ConnectedRoomIdx = nextRoom;
					portal.m_Dir = DIR_LEFT;
				}
				portalCandidates[nextRoom].push_back(portal);
			}
		}
	}

	for (int nextRoomIdx = roomIdx + 2; nextRoomIdx < portalCandidates.size(); nextRoomIdx++)
	{
		if (portalCandidates[nextRoomIdx].size() == 0)
		{
			continue;
		}

		int portalIdx = rand() % portalCandidates[nextRoomIdx].size();
		PortalData portal = portalCandidates[nextRoomIdx][portalIdx];
		cocos2d::Point nextPos = portal.m_Pos;
		int nextDir;

		room.m_Portals.push_back(portal);

		if (portal.m_Dir == DIR_UP)
		{
			nextPos.y++;
			nextDir = DIR_DOWN;
		}
		if (portal.m_Dir == DIR_DOWN)
		{
			nextPos.y--;
			nextDir = DIR_UP;
		}

		if (portal.m_Dir == DIR_RIGHT)
		{
			nextPos.x++;
			nextDir = DIR_LEFT;
		}

		if (portal.m_Dir == DIR_LEFT)
		{
			nextPos.x--;
			nextDir = DIR_RIGHT;
		}

		portal.m_ConnectedRoomIdx = roomIdx + 1;
		portal.m_Pos = nextPos;
		portal.m_Dir = nextDir;

		m_StageDatas[floor].m_Rooms[nextRoomIdx - 1].m_Portals.push_back(portal);
	}
}

int DataManager::getConnectedDirections(RoomData* room, int floor, int x, int y)
{

	//rx,ry는 room 기준 좌표.
	//x,y는 전체 world 기준 좌표.
	int rx = x - room->m_X / m_ModuleSize.width;
	int ry = y - room->m_Y / m_ModuleSize.height;
	int width = room->m_Width / m_ModuleSize.width;
	int height = room->m_Height / m_ModuleSize.height;
	int ridx = ry*width + rx;
	int dir = DIR_NONE;

	//모듈이 있는 경우 어디어디로 연결되는지 파악한다.

	int connectIdx;
	int placeValue;

	//왼쪽 연결 테스트
	connectIdx = ry*width + rx - 1;
	placeValue = (rx > 0) ? room->m_ModulePlaceData[connectIdx] : 0;
	//왼쪽 칸이 자기는 없는 모듈이고 딴 애 모듈은 있는 경우.
	if (x > 0 &&
		placeValue == 0 && m_PlaceData[floor][y][x - 1] != 0)
	{
		dir |= DIR_LEFT;
	}

	//오른쪽 연결 테스트
	connectIdx = ry*width + rx + 1;
	placeValue = (rx < width - 1) ? room->m_ModulePlaceData[connectIdx] : 0;
	//오른쪽 칸이 자기는 없는 모듈이고 딴 애 모듈은 있는 경우.
	if (x < PLACEMAP_SIZE - 1 &&
		placeValue == 0 && m_PlaceData[floor][y][x + 1] != 0)
	{
		dir |= DIR_RIGHT;
	}

	//아래쪽 연결 테스트
	connectIdx = (ry - 1)*width + rx;
	placeValue = (ry > 0) ? room->m_ModulePlaceData[connectIdx] : 0;
	//아래쪽 칸이 자기는 없는 모듈이고 딴 애 모듈은 있는 경우.
	if (y > 0 &&
		placeValue == 0 && m_PlaceData[floor][y - 1][x] != 0)
	{
		dir |= DIR_DOWN;
	}

	//위쪽 연결 테스트
	connectIdx = (ry + 1)*width + rx;
	placeValue = (ry < height - 1) ? room->m_ModulePlaceData[connectIdx] : 0;
	//위쪽 칸이 자기는 없는 모듈이고 딴 애 모듈은 있는 경우.
	if (y < PLACEMAP_SIZE - 1 &&
		placeValue == 0 && m_PlaceData[floor][y + 1][x] != 0)
	{
		dir |= DIR_UP;
	}

	return dir;
}

int DataManager::getModuleType(RoomData* room, int x, int y)
{
	Direction dir = DIR_NONE;
	cocos2d::Size sizeByModule;

	sizeByModule.width = room->m_Width / m_ModuleSize.width;
	sizeByModule.height = room->m_Height / m_ModuleSize.height;

	//아래 칸이 빈 경우
	if (y == 0 || room->m_ModulePlaceData[(y - 1)*sizeByModule.width + x] == 0)
		dir |= DIR_DOWN;

	//위 칸이 빈 경우
	if (y == sizeByModule.height - 1 || room->m_ModulePlaceData[(y + 1)*sizeByModule.width + x] == 0)
		dir |= DIR_UP;

	//왼쪽 칸이 빈 경우
	if (x == 0 || room->m_ModulePlaceData[y*sizeByModule.width + x - 1] == 0)
		dir |= DIR_LEFT;

	//오른쪽 칸이 빈 경우
	if (x == sizeByModule.width - 1 || room->m_ModulePlaceData[y*sizeByModule.width + x + 1] == 0)
		dir |= DIR_RIGHT;

	return dir;
}

void DataManager::setRoomData(RoomData* room, int sx, int sy, int ex, int ey, ComponentType type)
{
	for (int y = sy; y <= ey; y++)
	{
		for (int x = sx; x <= ex; x++)
		{
			int idx = y*room->m_Width + x;

			room->m_Data[idx] = type;
		}
	}
}

int DataManager::getNextRoomNumber(int floor, int room, cocos2d::Point& playerPos)
{
	//전체 월드에서 타일 기준으로 x,y좌표.
	int tileX = m_StageDatas[floor].m_Rooms[room].m_X + playerPos.x / m_TileSize.width;
	int tileY = m_StageDatas[floor].m_Rooms[room].m_Y + playerPos.y / m_TileSize.height;

	//현재 플레이어가 있는 좌표의 모듈 기준 값.
	int moduleX = tileX / m_ModuleSize.width;
	int moduleY = tileY / m_ModuleSize.height;
	int nextRoom;

	//다음 방이 없는 경우(잘못된 접근)
	_ASSERT(m_PlaceData[floor][moduleY][moduleX] != 0);
	if (m_PlaceData[floor][moduleY][moduleX] == 0)
	{
		return -1;
	}

	nextRoom = m_PlaceData[floor][moduleY][moduleX] - 1;

	//현재 방의 전체 월드에서의 타일 기준 x,y 시작 좌표.
	int roomStartX = m_StageDatas[floor].m_Rooms[room].m_X*m_TileSize.width;
	int roomStartY = m_StageDatas[floor].m_Rooms[room].m_Y*m_TileSize.width;

	//다음 방의 전체 월드에서의 타일 기준 x,y 시작 좌표.
	int nextRoomStartX = m_StageDatas[floor].m_Rooms[nextRoom].m_X*m_TileSize.width;
	int nextRoomStartY = m_StageDatas[floor].m_Rooms[nextRoom].m_Y*m_TileSize.width;

	//현재 룸 내에서 플레이어의 좌표.
	cocos2d::Point playerPosInRoom;
	playerPosInRoom.x = playerPos.x + roomStartX;
	playerPosInRoom.y = playerPos.y + roomStartY;

	//새로 이동한 방에서의 플레이어 좌표.
	playerPos.x = playerPosInRoom.x - nextRoomStartX;
	playerPos.y = playerPosInRoom.y - nextRoomStartY;

	return nextRoom;
}

const RoomData& DataManager::getRoomData(int floor, int room)
{
	_ASSERT(!(floor < 0 || floor >= m_StageDatas.size() ||
		room < 0 || room >= m_StageDatas[floor].m_Rooms.size()));

	return m_StageDatas[floor].m_Rooms[room];
}


void DataManager::setPlaceData(int floor, int roomIdx)
{
	cocos2d::Size sizeByModule;
	RoomData& room = m_StageDatas[floor].m_Rooms[roomIdx];

	sizeByModule.width = room.m_Width / m_ModuleSize.width;
	sizeByModule.height = room.m_Height / m_ModuleSize.height;

	for (int y = room.m_Y; y < room.m_Y + sizeByModule.height; y++)
	{
		for (int x = room.m_X; x < room.m_X + sizeByModule.width; x++)
		{
			if (m_PlaceData[floor][y][x] == 0)
			{
				int ridx = (y - room.m_Y)*sizeByModule.width + x - room.m_X;

				if (room.m_ModulePlaceData[ridx] != 0)
				{
					m_PlaceData[floor][y][x] = roomIdx + 1;
				}
			}
		}
	}
}

int DataManager::isPortal(int floor, int x, int y)
{
	int dir = DIR_NONE;
	for (RoomData& room : m_StageDatas[floor].m_Rooms)
	{
		for (auto& portal : room.m_Portals)
		{
			if (portal.m_Pos.x == x && portal.m_Pos.y == y)
			{
				dir |= portal.m_Dir;
			}
		}
	}

	return dir;
}

bool DataManager::isPortalTypeModule(int type, int idx)
{

	for (int x = 0; x < m_ModuleSize.width; x++)
	{
		if (m_ModuleDatas[type][idx].m_Data[x] == RT_PORTAL ||
			m_ModuleDatas[type][idx].m_Data[(m_ModuleSize.height - 1)*m_ModuleSize.height + x] == RT_PORTAL)
			return true;
	}

	for (int y = 0; y < m_ModuleSize.height; y++)
	{
		if (m_ModuleDatas[type][idx].m_Data[y*m_ModuleSize.height] == RT_PORTAL ||
			m_ModuleDatas[type][idx].m_Data[(y)*m_ModuleSize.height + m_ModuleSize.width - 1] == RT_PORTAL)
			return true;
	}

	return false;
}

cocos2d::Point DataManager::RoomTree::getOriginalPosition()
{
	cocos2d::Point retPosition;
	if (m_Parent == nullptr)
	{
		retPosition.x = m_Data->m_X;
		retPosition.y = m_Data->m_Y;
	}
	else
	{
		cocos2d::Point parentPosition = m_Parent->getOriginalPosition();
		retPosition.x = parentPosition.x + m_Data->m_X;
		retPosition.y = parentPosition.y + m_Data->m_Y;
	}
	return retPosition;
}