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
#define PLACEMAP_SIZE 100
#define PORTAL_SIZE 3 //구멍 뚫리는 크기
#define MAX_FLOOR 10 // 최대 층수. 넉넉하게 잡아놓음.

 

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

	SpriteInfo						getSpriteInfo(SpriteType spriteType);
	AnimationInfo					getAnimationInfo(AnimationType animationType);

	//Stage Data 생성 관련
	int								getNextRoomNumber(int floor, int room, cocos2d::Point& playerPos);
	void							setModuleSize(cocos2d::Size size);
	const cocos2d::Size				getModuleSize();
	void							setTileSize(cocos2d::Size size);
	const cocos2d::Size				getTileSize();
	const StageData&				getStageData(int floor);
	const RoomData&					getRoomData(int floor, int room);

	void							initWorldData(); // 게임 월드 전체 데이터 초기화

	//floor층의 room의 position 위치에 해당하는 타일이 어떤 것인지 반환해준다.
	int								getTileData(int floor, int room, cocos2d::Point position);

	//해당 층의 룸간 배치 관계 초기화. 흔들기도 이 함수로 가능.
	void							initRoomPlace(StageData& stage, int floor); 
	void							initRoomPlace(int floor); 



	//tool 용 함수
	std::vector<ModuleData>*		getModuleDatas();
	std::vector<SpriteInfo>&		getSpriteInfos();
	std::vector<AnimationInfo>&		getAnimationInfos();
	
private:
	//file 입출력 관련
	bool							saveData(std::string fileName, const char* pData);
	bool							getModuleKey(int type, int idx, char* category, OUT char* key);
	bool							getModuleKey(int type, char* category, OUT char* key);
	bool							getResourceKey(char* category, int idx, OUT char* key);

	//맵 데이터 생성 관련
	void							initStageData(StageData& stage, int floor, int roomNumber); //stage data 전체 초기화
	void							initRoomData(RoomData& room); //room data 초기화
	void							initModulePlace(RoomData& room, ModulePlaceType mpt); //해당 룸의 모듈 배치 초기화

	void							initModulePlaceByRect(std::vector<int>& modulePlace, cocos2d::Size size);
	void							initModulePlaceByDoughnut(std::vector<int>& modulePlace, cocos2d::Size size);
	void							initModulePlaceByRandom(std::vector<int>& modulePlace, cocos2d::Size size, int moduleNum);

	void							fillRoomData(RoomData& room, int floor); //룸의 모듈 배치를 바탕으로 모듈 데이터 집어넣음.
	void							matchModuleData(RoomData& room, int type, int startX, int startY, int floor); // type 형태의 모듈 데이터를 room의 x,y 좌표에 채워넣음.
	bool							isCandidatePos(int placeData[PLACEMAP_SIZE][PLACEMAP_SIZE], int x, int y, RoomData& room); // placeData의 해당 위치에 room이 배치가능한지 확인.
	void							setPlaceData(int placeData[PLACEMAP_SIZE][PLACEMAP_SIZE], RoomData& room, int roomIdx);

	int								isPortal(int floor, int x, int y); //x,y 위치에 포탈있는지 확인
	bool							isPortalType(int type, int idx); //type의 idx번째 module이 portal을 포함하는 타입인지 확인.

	void							makeRoomConnectData(StageData& stage, int floor); //stage의 room들간 연결 관계 생성.
	void							makePortal(RoomData& room, int floor, int idx); //room에 다른 방과 연결되는 포탈 생성.
	int								getConnectedDirections(RoomData& room, int floor, int x, int y); //x,y좌표 모듈이 연결된 모듈이 있다면 그 방향 리턴.
	void							adjustRoomData(RoomData& room, int rx, int ry, int dir); //rx,ry좌표 모듈에 dir이 방향 연결된 모듈이 있음. 이를 반영하도록 데이터 수정 + 형태 자연스럽게 수정.
	int								getModuleType(RoomData& room, int x, int y); //roomData의 x,y좌표 모듈이 어떤 타입인지 리턴.
	void							setRoomData(RoomData& room, int sx, int sy, int ex, int ey, ObjectType type); // room의 data sx, sy좌표 ~ ex,ey좌표 값을 type으로 변경.

	//생성한 맵 데이터
	std::vector<StageData>			m_StageDatas = std::vector<StageData>();
	int								m_PlaceData[MAX_FLOOR][PLACEMAP_SIZE][PLACEMAP_SIZE]; //실제 맵 배치도. 100x100사이즈로 저장됨.


	//파일에서 불러오는 데이터 저장 목록
	std::vector<ModuleData>			m_ModuleDatas[DIR_MAX];
	cocos2d::Size					m_ModuleSize = cocos2d::Size::ZERO;
	cocos2d::Size					m_TileSize = cocos2d::Size::ZERO;
	
	std::vector<AnimationInfo>		m_AnimationInfos;
	std::vector<SpriteInfo>			m_SpriteInfos;
	std::vector<std::string>		m_SpriteCaches;

	struct RoomTree
	{
		RoomTree()
			:m_Data(nullptr), m_Parent(nullptr)
		{
		}
		~RoomTree()
		{
		}

		RoomData*				m_Data;
		RoomTree*				m_Parent;
		std::vector<RoomTree*>	m_Children;

		cocos2d::Point getOriginalPosition(void);
	};
};

