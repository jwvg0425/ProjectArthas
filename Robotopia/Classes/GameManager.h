//
// GameManager.h
//
// 작성자 : 남현욱
//
//
// 각종 매니저의 인스턴스에 대한 접근 및 게임 전체에서 참조하고 관리해야하는 기능들을 제공한다.
//
//
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