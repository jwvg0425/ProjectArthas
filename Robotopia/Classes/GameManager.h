#pragma once
#define GET_GAME_MANAEGR() GameManager::getInstance()

class GameManager
{
public:
	GameManager* getInstance();
	void releaseInstance();
private:
	static GameManager* m_Instance;
	GameManager();
	~GameManager();
};