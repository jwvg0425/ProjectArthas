/************************************************************************/
/*
	CLASS			: DataManager
	Author			: 남현욱
	역할				: 외부 파일에서 Data를 가져오는 작업 및 외부 파일에 Data를 쓰는 것과 관련된 작업을 담당한다.
	최종 수정일자	: 2014-10-29
	최종 수정자		: 
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#define MODULE_FILE_NAME ("data/module.json")
#define RESOURCE_FILE_NAME ("data/resource.json")

BEGIN_NS_AT 

enum ModulePlaceType
{
	MPT_RECT, //사각형 형태의 일반적인 배치.
	MPT_RANDOM, //완전 랜덤 형태의 배치.
	MPT_DOUGHNUT, // 도넛 모양의 배치. 가운데 구멍 뚫려있는 모양의 사각형.
	MPT_NUM,
};

class DataManager
{
public:
	DataManager();
	~DataManager();

	//file 입출력 관련
	bool							init();
	
	bool							loadModuleData();
	bool							saveModuleData();
	
	bool							loadSpriteCacheData();
	bool							loadResourceData();
	bool							saveResourceData();

	SpriteInfo						getSpriteInfo(ResourceType spriteType);
	AnimationInfo					getAnimationInfo(ResourceType animationType);

	//Stage Data 생성 관련
	void							setModuleSize(cocos2d::Size size);
	const cocos2d::Size				getModuleSize();
	void							setTileSize(cocos2d::Size size);
	const cocos2d::Size				getTileSize();
	const StageData&				getStageData(int floor);

	void							initWorldData(); // 게임 월드 전체 데이터 초기화
	void							initStageData(StageData& stage, int roomNumber); //stage data 전체 초기화
	void							initRoomData(RoomData& room); //room data 초기화
	void							initModulePlace(RoomData& room, ModulePlaceType mpt); //해당 룸의 모듈 배치 초기화

	void							initModulePlaceByRect(std::vector<int>& modulePlace, cocos2d::Size size);
	void							initModulePlaceByDoughnut(std::vector<int>& modulePlace, cocos2d::Size size);
	void							initModulePlaceByRandom(std::vector<int>& modulePlace, cocos2d::Size size, int moduleNum);

	void							initRoomPlace(StageData& stage); //해당 층의 룸간 배치 관계 초기화. 흔들기도 이 함수로 가능.


	void							fillRoomData(RoomData& room); //룸의 모듈 배치를 바탕으로 모듈 데이터 집어넣음.
	void							matchModuleData(RoomData& room, int type, int startX, int startY); // type 형태의 모듈 데이터를 room의 x,y 좌표에 채워넣음.


	//tool 용 함수
	std::vector<ModuleData>*		getModuleDatas();
	
private:
	//file 입출력 관련
	bool						saveData(std::string fileName, const char* pData);
	bool						getModuleKey(int type, int idx, char* category, OUT char* key);
	bool						getModuleKey(int type, char* category, OUT char* key);
	bool						getResourceKey(char* category, int idx, OUT char* key);

	//생성한 맵 데이터
	std::vector<StageData>		m_StageDatas;


	//파일에서 불러오는 데이터 저장 목록
	std::vector<ModuleData>		m_ModuleDatas[DIR_MAX];
	cocos2d::Size				m_ModuleSize;
	cocos2d::Size				m_TileSize;
	
	std::vector<AnimationInfo>	m_AnimationInfos;
	std::vector<SpriteInfo>		m_SpriteInfos;
	std::vector<std::string>	m_SpriteCaches;
};

END_NS_AT