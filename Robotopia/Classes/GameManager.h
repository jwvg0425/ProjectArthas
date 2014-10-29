/************************************************************************/
/*
	CLASS			: GameManager
	Author			: 남현욱
	역할				: 각종 매니저의 인스턴스에 대한 접근 및 게임 전체에서 참조하고 관리해야하는 기능들을 제공한다.
	최종 수정일자	: 2014-10-29
	최종 수정자		: 
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#define GET_GAME_MANAEGR() Arthas::GameManager::getInstance()
#define GET_DATA_MANAGER() Arthas::GameManager::getInstance()->getDataManagerInstance()

BEGIN_NS_AT
class DataManager;
class GameManager
{
public:
	static GameManager*		getInstance();
	static void				releaseInstance();

	DataManager*			getDataManagerInstance();
	void					releaseDataManagerInstance();
	

private:
	static GameManager*		m_Instance;
	
	DataManager*			m_DataManagerInstance;

	GameManager();
	~GameManager();
};
END_NS_AT