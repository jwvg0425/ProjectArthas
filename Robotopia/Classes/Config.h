/************************************************************************/
/*
	CLASS			: Config.h
	Author			: 남현욱
	역할				: 파일에서 불러와서 관리해야하는 각종 Config Data들 모음.
	최종 수정일자	: 2014-12-1
	최종 수정자		: 남현욱
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/
#include<map>


struct RoomConfig
{
	enum RoomType
	{
		NONE = -1,
		NORMAL = 0, // 일반 방
		SPECIAL = 1, // 특수 방
		LIFT = 2, //리프트 방
		CITY = 3, //마을에 해당하는 방
	};

	RoomConfig();
	~RoomConfig();

	int m_Width; //방 너비.
	int m_Height; //방 높이.
	RoomType m_Type; //방의 타입. 
};

struct StageConfig
{
	StageConfig();
	~StageConfig();

	int m_RoomNum; //방 개수가 몇개인지
	int m_RoomNumRand; //방 개수가 roomNum에서 +- 몇만큼 왔다갔다 할건지.
	std::map<int, RoomConfig*> m_RoomConfig; //방 각각에 대한 config 데이터. config가 지정된 방만 설정함.
};