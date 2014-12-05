#include "pch.h"
#include "GameManager.h"
#include "DataManager.h"
#include "StageManager.h"
#include "cocos2d.h"
#include "json/json.h"
#include "Config.h"
#include "EquipmentAbstract.h"
#include "EquipmentArmor.h"
#include "EquipmentEngine.h"
#include "EquipmentHead.h"
#include "EquipmentLeg.h"
#include "EquipmentMelee.h"
#include "EquipmentRange.h"
#include "EquipmentSteamContainer.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
	for (auto stageConfig : m_StageConfig)
	{
		delete stageConfig;
	}

	m_StageConfig.clear();

	for (int i = EMT_START; i < EMT_END; i++)
	{
		for (auto equipmentInfo : m_EquipmentInfo[i])
		{
			delete equipmentInfo.second;
		}

		m_EquipmentInfo[i].clear();
	}

	for (int i = EMT_START; i < EMT_END; i++)
	{
		for (auto equipmentInfo : m_EquipmentBaseInfo[i])
		{
			delete equipmentInfo.second;
		}

		m_EquipmentBaseInfo[i].clear();
	}
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
	loadStageConfigData();
	loadItemBaseData();
	initEquipInfo();

	for (size_t i = 0; i < m_SpriteCaches.size(); i++)
	{
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(m_SpriteCaches[i]);
	}

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
			
			data.m_Type = static_cast <RoomConfig::RoomType>(array[width*height + 1].asInt());
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

			data.append(m_ModuleDatas[dirType][idx].m_Type);
			
			getModuleKey(dirType, idx, "data", buffer);
			moduleData[buffer] = data;
		}
	}

	Json::StyledWriter writer;
	std::string strJSON = writer.write(moduleData);

	if (!saveData(MODULE_FILE_NAME, strJSON.c_str()))
	{
		return false;
	}

	return true;
}

bool DataManager::saveData(std::string fileName, const char* pData)
{
	FILE *fp = fopen(fileName.c_str(), "wb");

	if (!fp)
	{
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

	if (!saveData(RESOURCE_FILE_NAME, strJSON.c_str()))
	{
		return false;
	}

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


bool DataManager::loadStageConfigData()
{
	//data 불러오기
	ssize_t bufferSize = 0;
	unsigned char* fileData = cocos2d::FileUtils::getInstance()->getFileData(CONFIG_FILE_NAME, "rb", &bufferSize);
	std::string clearData((const char*)fileData, bufferSize);

	Json::Value root;
	Json::Reader reader;
	char key[BUF_SIZE] = {};
	bool isParsingSuccess = reader.parse(clearData, root);

	if (!isParsingSuccess)
	{
		cocos2d::log("parser failed : \n %s", CONFIG_FILE_NAME);
		return false;
	}

	//Stage Data 불러오기
	m_FloorNum = root.get("FloorNum", 4).asInt();

	for (int i = 0; i < m_FloorNum; i++)
	{
		StageConfig* stageConfig = new StageConfig;
		Json::Value value;

		getStageConfigKey("Stage", i, key);

		value = root.get(key, 0);

		stageConfig->m_RoomNum = value[0].asInt();
		stageConfig->m_RoomNumRand = value[1].asInt();
		stageConfig->m_PlayerStartPos.x = value[2].asFloat();
		stageConfig->m_PlayerStartPos.y = value[3].asFloat();

		m_StageConfig.push_back(stageConfig);
	}

	//room data 불러오기
	for (int roomIdx = 0; true; roomIdx++)
	{
		RoomConfig roomConfig;
		Json::Value value;
		int floor, room;

		getStageConfigKey("Room", roomIdx, key);

		if (!root.isMember(key))
		{
			break;
		}

		value = root.get(key, 0);
		floor = value[0].asInt();
		room = value[1].asInt();
		roomConfig.m_Width = value[2].asInt();
		roomConfig.m_Height = value[3].asInt();
		roomConfig.m_Type = static_cast<RoomConfig::RoomType>(value[4].asInt());

		m_StageConfig[floor]->m_RoomConfig[room] = roomConfig;
	}

	return true;
}

bool DataManager::loadItemBaseData()
{
	//data 불러오기
	ssize_t bufferSize = 0;
	unsigned char* fileData = cocos2d::FileUtils::getInstance()->getFileData(ITEM_FILE_NAME, "rb", &bufferSize);
	std::string clearData((const char*)fileData, bufferSize);

	Json::Value root;
	Json::Reader reader;
	char key[BUF_SIZE] = {};
	bool isParsingSuccess = reader.parse(clearData, root);

	if (!isParsingSuccess)
	{
		cocos2d::log("parser failed : \n %s", ITEM_FILE_NAME);
		return false;
	}

	int starts[EMT_NUM] = { HL_START, EL_START, AL_START, ML_START, RL_START, SCL_START, LL_START };
	int ends[EMT_NUM] = { HL_END, EL_END, AL_END, ML_END, RL_END, SCL_END, LL_END };

	for (int equipment = EMT_START + 1; equipment < EMT_END; equipment++)
	{
		for (int type = starts[equipment] + 1; type < ends[equipment]; type++)
		{
			EquipmentInfo* info;
			Json::Value value;

			switch (equipment)
			{
			case EMT_HEAD:
				info = new HeadInfo;
				break;
			case EMT_ENGINE:
				info = new EngineInfo;
				break;
			case EMT_ARMOR:
				info = new ArmorInfo;
				break;
			case EMT_MELEE:
				info = new MeleeInfo;
				break;
			case EMT_RANGE:
				info = new RangeInfo;
				break;
			case EMT_STEAMCONTAINER:
				info = new SteamContainerInfo;
				break;
			case EMT_LEG:
				info = new LegInfo;
				break;
			}

			m_EquipmentBaseInfo[equipment][type] = info;

			getItemKey(equipment, type, key);

			if (!root.isMember(key))
			{
				continue;
			}

			value = root.get(key, 0);
			info->m_EquipmentType = static_cast<EquipmentType>(value[0].asInt());
			info->m_Type = value[1].asInt();
			info->m_Front = static_cast<SpriteType>(value[2].asInt());
			info->m_OutLine = static_cast<SpriteType>(value[3].asInt());
			info->m_Icon = static_cast<SpriteType>(value[4].asInt());
			info->m_Level = value[5].asInt();
			info->m_KWatt = value[6].asInt();
			info->m_IsLock = value[7].asInt();
			info->m_UpgradePrice = value[8].asInt();

			switch (equipment)
			{
			case EMT_HEAD:
				static_cast<HeadInfo*>(info)->m_SkillCoolTimeDown = value[9].asFloat();
				static_cast<HeadInfo*>(info)->m_MainMemory = value[10].asFloat();
				break;
			case EMT_ENGINE:
				static_cast<EngineInfo*>(info)->m_ElectronicPower = value[9].asFloat();
				static_cast<EngineInfo*>(info)->m_SteamEffectiveness = value[10].asFloat();
				break;
			case EMT_ARMOR:
				static_cast<ArmorInfo*>(info)->m_DefensivePower = value[9].asFloat();
				static_cast<ArmorInfo*>(info)->m_Resistance = value[10].asFloat();
				break;
			case EMT_MELEE:
				static_cast<MeleeInfo*>(info)->m_AttackDamage = value[9].asFloat();
				static_cast<MeleeInfo*>(info)->m_AttackSpeed = value[10].asFloat();
				break;
			case EMT_RANGE:
				static_cast<RangeInfo*>(info)->m_AttackDamage = value[9].asFloat();
				static_cast<RangeInfo*>(info)->m_AttackSpeed = value[10].asFloat();
				static_cast<RangeInfo*>(info)->m_AttackRange = value[11].asFloat();
				break;
			case EMT_STEAMCONTAINER:
				static_cast<SteamContainerInfo*>(info)->m_MaxSteam = value[9].asFloat();
				static_cast<SteamContainerInfo*>(info)->m_AbsorbEffectiveness = value[10].asFloat();
				break;
			case EMT_LEG:
				static_cast<LegInfo*>(info)->m_MoveSpeed = value[9].asFloat();
				static_cast<LegInfo*>(info)->m_jumpPower = value[10].asFloat();
				break;
			}
		}
	}

	return true;
}

const EquipmentInfo* DataManager::getEquipmentInfo(EquipmentType category, int type)
{
	return m_EquipmentInfo[category][type];
}

const EquipmentInfo* DataManager::getEquipmentBaseInfo(EquipmentType category, int type)
{
	return m_EquipmentBaseInfo[category][type];
}

void DataManager::initEquipInfo()
{
	int starts[EMT_NUM] = { HL_START, EL_START, AL_START, ML_START, RL_START, SCL_START, LL_START };
	int ends[EMT_NUM] = { HL_END, EL_END, AL_END, ML_END, RL_END, SCL_END, LL_END };
	
	//전체 초기화 작업.
	for(int i = EMT_START + 1; i < EMT_END; i++)
	{
		for (auto equipmentInfo : m_EquipmentInfo[i])
		{
			delete equipmentInfo.second;
		}

		m_EquipmentInfo[i].clear();
	}


	for (int equipment = EMT_START + 1; equipment < EMT_END; equipment++)
	{
		for (int type = starts[equipment] + 1; type < ends[equipment]; type++)
		{
			EquipmentInfo* info;

			//base로부터 깊은 복사.
			switch (equipment)
			{
			case EMT_HEAD:
				///# 이런식으로 하면 뭔가 좀 이상하다고 생각하지 않음? 복사생성자 놔두고 왜 이렇게 쓰지?
				///# 그리고 이경우 자식을 부모로 강제 업캐스팅하는거... 꼭 해야 할까?
				info = new HeadInfo;
				*static_cast<HeadInfo*>(info) = 
					*static_cast<HeadInfo*>(m_EquipmentBaseInfo[equipment][type]);
				break;
			case EMT_ENGINE:
				info = new EngineInfo;
				*static_cast<EngineInfo*>(info) = 
					*static_cast<EngineInfo*>(m_EquipmentBaseInfo[equipment][type]);
				break;
			case EMT_ARMOR:
				info = new ArmorInfo;
				*static_cast<ArmorInfo*>(info) = 
					*static_cast<ArmorInfo*>(m_EquipmentBaseInfo[equipment][type]);
				break;
			case EMT_MELEE:
				info = new MeleeInfo;
				*static_cast<MeleeInfo*>(info) = 
					*static_cast<MeleeInfo*>(m_EquipmentBaseInfo[equipment][type]);
				break;
			case EMT_RANGE:
				info = new RangeInfo;
				*static_cast<RangeInfo*>(info) = 
					*static_cast<RangeInfo*>(m_EquipmentBaseInfo[equipment][type]);
				break;
			case EMT_STEAMCONTAINER:
				info = new SteamContainerInfo;
				*static_cast<SteamContainerInfo*>(info) = 
					*static_cast<SteamContainerInfo*>(m_EquipmentBaseInfo[equipment][type]);
				break;
			case EMT_LEG:
				info = new LegInfo;
				*static_cast<LegInfo*>(info) = 
					*static_cast<LegInfo*>(m_EquipmentBaseInfo[equipment][type]);
				break;
			}

			m_EquipmentInfo[equipment][type] = info;
		}
	}
}

bool DataManager::getStageConfigKey(char* category, int idx, OUT char* key)
{
	if (key == nullptr || category == nullptr)
		return false;

	sprintf(key, "%s_%d", category, idx);

	return true;
}

bool DataManager::getItemKey(int category, int type, OUT char* key)
{
	if (key == nullptr)
		return false;

	sprintf(key, "item_%d_%d", category, type);

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
		int roomNum = m_StageConfig[floor]->m_RoomNum;
		int randNum = m_StageConfig[floor]->m_RoomNumRand;

		if (randNum != 0)
			roomNum = roomNum - randNum + rand() % (2 * randNum);
		initStageData(floor, roomNum);
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

	m_StageDatas[floor].m_Rooms[roomIdx].m_Portals.clear();
	m_StageDatas[floor].m_Rooms[roomIdx].m_X = 0;
	m_StageDatas[floor].m_Rooms[roomIdx].m_Y = 0;

	auto& roomConfig = m_StageConfig[floor]->m_RoomConfig;
	
	//room 설정에 대해 특수한 config 존재 -> 무조건 사각형에 해당 사이즈로 맞춰줌.
	if (roomConfig.find(roomIdx) != roomConfig.end())
	{
		cocos2d::Size size = cocos2d::Size::ZERO;

		size.width = roomConfig[roomIdx].m_Width;
		size.height = roomConfig[roomIdx].m_Height;
		initModulePlaceByRect(&m_StageDatas[floor].m_Rooms[roomIdx], size);

		m_StageDatas[floor].m_Rooms[roomIdx].m_Width = size.width * m_ModuleSize.width;
		m_StageDatas[floor].m_Rooms[roomIdx].m_Height = size.height * m_ModuleSize.height;
	}
	else
	{
		ModulePlaceType mpt = static_cast<ModulePlaceType>(rand() % MPT_NUM);
		initModulePlace(&m_StageDatas[floor].m_Rooms[roomIdx], mpt);
	}
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

			matchModuleData(floor, roomIdx, dir, x, y);
		}
	}

}

void DataManager::initRoomPlace(int floor)
{
	
	std::vector<int> isUsedRoom;
	std::vector<RoomTree*> trees;

	isUsedRoom.resize(m_StageDatas[floor].m_Rooms.size());

	//기본 트리를 먼저 구성한다.
	for (int i = 0; i < isUsedRoom.size(); i++)
	{
		RoomTree* tree = new RoomTree;
		int randIdx;

		tree->m_Parent = nullptr;
		tree->m_RoomNumber = i + 1;
		tree->m_Data = &m_StageDatas[floor].m_Rooms[i];
		tree->m_Data->m_X = 0;
		tree->m_Data->m_Y = 0;
		tree->m_Children.clear();

		trees.push_back(tree);
	}

	for (int i = 0; i < isUsedRoom.size(); i++)
	{
		if (isUsedRoom[i] == 0 && 
			m_StageDatas[floor].m_Rooms[i].m_Portals.size() != 0)
		{
			int randIdx;

			isUsedRoom[i] = 1;

			std::vector<RoomTree*> roomTrees;

			for (int child = 0; child < m_StageDatas[floor].m_Rooms[i].m_Portals.size(); child++)
			{
				//쓰지 않았고 포탈도 없는 애들 중 하나 고름.
				do
				{
					randIdx = rand() % isUsedRoom.size();
				} while (!(isUsedRoom[randIdx] == 0 &&
					m_StageDatas[floor].m_Rooms[randIdx].m_Portals.size() == 0));

				roomTrees.push_back(trees[randIdx]);

				isUsedRoom[randIdx] = 1;
			}

			trees[i]->mergeTrees(roomTrees);
		}
	}

	for (int i = 0; i < trees.size(); i++)
	{
		//이미 병합된 애들. 부모가 있다. 그러므로 삭제.
		if (trees[i]->m_Parent != nullptr)
		{
			trees.erase(trees.begin() + i);
			i--;
		}
	}

	//구성한 트리들을 트리가 하나만 남을 때까지 반복 병합 작업한다.

	while (trees.size() > 1)
	{
		//인접한 2개 병합
		for (int i = 0; i < trees.size() - 1; i++)
		{
			trees[i]->mergeTree(trees[i + 1]);

			trees.erase(trees.begin() + i + 1);
		}
	}

	trees[0]->setPosToOriginal();

	StageData& stage = m_StageDatas[floor];
	cocos2d::Point minPos = cocos2d::Point(stage.m_Rooms[0].m_X, stage.m_Rooms[0].m_Y);
	
	for (int idx = 1; idx < stage.m_Rooms.size(); idx++)
	{
		if (minPos.x > stage.m_Rooms[idx].m_X)
			minPos.x = stage.m_Rooms[idx].m_X;

		if (minPos.y > stage.m_Rooms[idx].m_Y)
			minPos.y = stage.m_Rooms[idx].m_Y;
	}

	//평행이동 및 placeData 초기화

	memset(m_PlaceData[floor], 0, sizeof(int)*PLACEMAP_SIZE*PLACEMAP_SIZE);
	for (int idx = 0; idx < stage.m_Rooms.size(); idx++)
	{
		stage.m_Rooms[idx].m_X -= minPos.x;
		stage.m_Rooms[idx].m_Y -= minPos.y;
		
		cocos2d::Size sizeByModule = cocos2d::Size(stage.m_Rooms[idx].m_Width / m_ModuleSize.width,
													stage.m_Rooms[idx].m_Height / m_ModuleSize.height);

		for (int y = 0; y < sizeByModule.height; y++)
		{
			for (int x = 0; x < sizeByModule.width; x++)
			{
				int xIdx = stage.m_Rooms[idx].m_X + x;
				int yIdx = stage.m_Rooms[idx].m_Y + y;

				if (stage.m_Rooms[idx].m_ModulePlaceData[y*sizeByModule.width + x] != 0)
				{
					m_PlaceData[floor][yIdx][xIdx] = idx + 1;
				}
			}
		}

		stage.m_Rooms[idx].m_X *= m_ModuleSize.width;
		stage.m_Rooms[idx].m_Y *= m_ModuleSize.height;
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

	delete trees[0];
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

void DataManager::matchModuleData(int floor,int roomIdx, int type, int startX, int startY)
{
	int idx;
	int tileX = startX * m_ModuleSize.width;
	int tileY = startY * m_ModuleSize.height;
	int portalDir = DIR_NONE;
	RoomConfig::RoomType roomType = RoomConfig::NORMAL;
	auto& room = m_StageDatas[floor].m_Rooms[roomIdx];

	portalDir = isPortal(floor, (room.m_X + tileX) / m_ModuleSize.width, (room.m_Y + tileY) / m_ModuleSize.height);

	//room 설정에 대해 특수한 config 존재 -> 해당 config의 타입만 가능하게 설정. 기본적으로 지정없으면 normal 타입.
	auto& roomConfig = m_StageConfig[floor]->m_RoomConfig;

	if (roomConfig.find(roomIdx) != roomConfig.end())
	{
		roomType = roomConfig[roomIdx].m_Type;
	}

	do
	{
		idx = rand() % m_ModuleDatas[type].size();
	} while (((!!portalDir) ^ isPortalTypeModule(type, idx)) ||
		m_ModuleDatas[type][idx].m_Type != roomType);

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
				if ((x == 0 && m_PlaceData[floor][startY][startX - 1] != 0 && (portalDir & DIR_LEFT)) ||
					(x == m_ModuleSize.width - 1 && m_PlaceData[floor][startY][startX + 1] != 0 && (portalDir & DIR_RIGHT)) ||
					(y == 0 && m_PlaceData[floor][startY - 1][startX] != 0 && (portalDir & DIR_DOWN)) ||
					(y == m_ModuleSize.height - 1 && m_PlaceData[floor][startY + 1][startX] != 0 && (portalDir & DIR_UP)))
				{
					if (y == 0 && m_PlaceData[floor][startY - 1][startX] != 0 && (portalDir & DIR_DOWN))
					{
						data = OT_FLOOR;
					}
					else
					{
						data = CT_NONE;
					}
				}
				else
				{
					data = OT_BLOCK;
				}
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
			case RT_STAGE_PORTAL:
				data = OT_PORTAL;
				break;
			}
			room.m_Data[(tileY + y)*room.m_Width + tileX + x] = data;
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
			portal.m_Pos = cocos2d::Point(x - rx, y - ry);

			//위쪽 방향 검사
			if (dir & DIR_UP)
			{
				int nextRoom = m_PlaceData[floor][y + 1][x];

				if (nextRoom > roomIdx + 1)
				{
					portal.m_ConnectedRoomIdx = nextRoom;
					portal.m_Dir = DIR_UP;
				}
				_ASSERT(nextRoom != 0);
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
				_ASSERT(nextRoom != 0);
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
				_ASSERT(nextRoom != 0);
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
				_ASSERT(nextRoom != 0);
				portalCandidates[nextRoom].push_back(portal);
			}
		}
	}

	for (int portalIdx = 0; portalIdx < room.m_Portals.size(); portalIdx++)
	{
		cocos2d::Point portalPos = room.m_Portals[portalIdx].m_Pos;
		
		switch (room.m_Portals[portalIdx].m_Dir)
		{
		case DIR_UP:
			portalPos.y++;
			break;
		case DIR_RIGHT:
			portalPos.x++;
			break;
		case DIR_DOWN:
			portalPos.y--;
			break;
		case DIR_LEFT:
			portalPos.x--;
			break;
		}

		room.m_Portals[portalIdx].m_ConnectedRoomIdx = 
			m_PlaceData[floor][static_cast<int>(ry + portalPos.y)][static_cast<int>(rx + portalPos.x)];

		_ASSERT(room.m_Portals[portalIdx].m_ConnectedRoomIdx != 0);
	}

	for (int nextRoomIdx = 0; nextRoomIdx < portalCandidates.size(); nextRoomIdx++)
	{
		bool isPortalExist = false;


		//자기 자신은 당연히 pass
		if (nextRoomIdx == roomIdx)
			continue;

		for (int portalIdx = 0; portalIdx < room.m_Portals.size(); portalIdx++)
		{
			if (room.m_Portals[portalIdx].m_ConnectedRoomIdx == nextRoomIdx)
			{
				isPortalExist = true;
				break;
			}
		}

		//이미 해당 방과 연결된 포탈 존재.
		if (isPortalExist)
			continue;

		if (portalCandidates[nextRoomIdx].size() == 0)
		{
			continue;
		}

		int portalIdx = rand() % portalCandidates[nextRoomIdx].size();
		PortalData portal = portalCandidates[nextRoomIdx][portalIdx];

		room.m_Portals.push_back(portal);
	}

	//상대 포탈도 생성.
	for (int portalIdx = 0; portalIdx < room.m_Portals.size(); portalIdx++)
	{
		PortalData portal = room.m_Portals[portalIdx];
		cocos2d::Point nextPos = portal.m_Pos;
		int nextDir;

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
		auto& nextRoom = m_StageDatas[floor].m_Rooms[room.m_Portals[portalIdx].m_ConnectedRoomIdx - 1];

		portal.m_ConnectedRoomIdx = roomIdx + 1;
		portal.m_Pos = nextPos;
		portal.m_Dir = nextDir;

		portal.m_Pos.x += room.m_X / m_ModuleSize.width;
		portal.m_Pos.y += room.m_Y / m_ModuleSize.height;


		portal.m_Pos.x -= nextRoom.m_X / m_ModuleSize.width;
		portal.m_Pos.y -= nextRoom.m_Y / m_ModuleSize.height;

		//이미 연결된 방이면 포탈 추가 pass.
		bool existPortal = false;
		for (int portalIdx = 0; portalIdx < nextRoom.m_Portals.size(); portalIdx++)
		{
			if (nextRoom.m_Portals[portalIdx].m_ConnectedRoomIdx == portal.m_ConnectedRoomIdx)
			{
				existPortal = true;
			}
		}

		if (!existPortal)
		{
			nextRoom.m_Portals.push_back(portal);
		}
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
		int rx = room.m_X / m_ModuleSize.width;
		int ry = room.m_Y / m_ModuleSize.height;
		for (auto& portal : room.m_Portals)
		{
			if (rx + portal.m_Pos.x == x && ry + portal.m_Pos.y == y)
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

void DataManager::shakeRoom(int floor)
{
	int roomNum = GET_STAGE_MANAGER()->getRoomNum();

	//현재 룸 빼고 싹다 초기화
	for (int roomIdx = 0; roomIdx < m_StageDatas[floor].m_Rooms.size(); roomIdx++)
	{
		if (roomIdx != roomNum)
		{
			initRoomData(floor, roomIdx);
		}
	}

	initRoomPlace(floor);

	//현재 방 제외 나머지 방 데이터 초기화.

	StageData& stage = m_StageDatas[floor];
	for (int i = 0; i < stage.m_Rooms.size(); i++)
	{
		makePortal(floor, i);

		if (i != roomNum)
		{
			fillRoomData(floor, i);
		}
	}

}

cocos2d::Point DataManager::getStartPos(int floor)
{
	return m_StageConfig[floor]->m_PlayerStartPos;
}

bool DataManager::setEquipmentInfo(EquipmentType category, int type, EquipmentInfo* data)
{
	if (category <= EMT_START || category >= EMT_END)
	{
		return false;
	}

	if (type < 0 || type >= m_EquipmentInfo[category].size())
	{
		return false;
	}

	delete m_EquipmentInfo[category][type];
	m_EquipmentInfo[category][type] = data->clone();

	return true;
}

bool DataManager::RoomTree::mergeTree(RoomTree* childTree)
{
	std::vector<cocos2d::Point> candidates;

	getCandidatePos(childTree, &candidates);

	if (candidates.empty())
	{
		return false;
	}

	int targetIdx = rand() % candidates.size();

	childTree->m_Data->m_X = candidates[targetIdx].x;
	childTree->m_Data->m_Y = candidates[targetIdx].y;

	m_Children.push_back(childTree);
	childTree->m_Parent = this;

	return true;
}

void DataManager::RoomTree::mergeTrees(std::vector<RoomTree*> childTrees)
{
	for (int i = 0; i < childTrees.size(); i++)
	{
		//merge에 실패하면 다시 처음부터 시도. 
		if (!mergeTree(childTrees[i]))
		{
			m_Children.clear();
			for (int j = 0; j < i; j++)
			{
				childTrees[j]->m_Parent = nullptr;
				childTrees[j]->m_Data->m_X = 0;
				childTrees[j]->m_Data->m_Y = 0;
			}
		}
	}
}
