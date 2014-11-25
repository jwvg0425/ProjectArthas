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
#define GET_GAME_MANAGER() GameManager::getInstance()
#define GET_DATA_MANAGER() GameManager::getInstance()->getDataManagerInstance()
#define GET_TRIGGER_MANAGER() GameManager::getInstance()->getTriggerManagerInstance()
#define GET_INPUT_MANAGER() GameManager::getInstance()->getInputManagerInstance()
#define GET_RESOURCE_MANAGER() GameManager::getInstance()->getResourceManagerInstance()
#define GET_COMPONENT_MANAGER() GameManager::getInstance()->getComponentManagerInstance()
#define GET_STAGE_MANAGER() GameManager::getInstance()->getStageManagerInstance()
#define GET_UI_MANAGER() GameManager::getInstance()->getUIManagerInstance()
#define GET_SOUND_MANAGER() GameManager::getInstance()->getSoundManagerInstance()
#define GET_MISSILE_MANAGER() GameManager::getInstance()->getMissileManagerInstance()

//싱글톤 객체 얻어오는 코드 자동 생성(초기화까지)
#define GET_SINGLETON_INSTANCE(CLASS)\
{ \
	if (m_ ## CLASS ## Instance == nullptr)\
	{\
		m_ ## CLASS ## Instance = new CLASS ##();\
		m_ ## CLASS ## Instance->init();\
	}\
	return m_ ## CLASS ## Instance;\
}

// 기본 형태의 get, release 함수 자동 생성
#define CREATE_SINGLETON_FUNC(CLASS)\
CLASS* GameManager::get ## CLASS ## Instance()\
{\
	GET_SINGLETON_INSTANCE(CLASS); \
}\
void GameManager::release ## CLASS ## Instance()\
{\
	SAFE_DELETE(m_TriggerManagerInstance); \
}

//싱글톤 함수 원형 및 멤버 자동 생성
#define SINGLETON_INSTANCE(CLASS)\
public:\
	CLASS* get ## CLASS ## Instance();\
	void release ## CLASS ## Instance();\
private:\
	CLASS* m_ ## CLASS ## Instance = nullptr;

#define MULTI_CONTACT -1


class DataManager;
class TriggerManager;
class InputManager;
class ResourceManager;
class ComponentManager;
class StageManager;
class UIManager;
class SoundManager;
class MissileManager;

class GameManager
{
	SINGLETON_INSTANCE(DataManager);
	SINGLETON_INSTANCE(TriggerManager);
	SINGLETON_INSTANCE(InputManager);
	SINGLETON_INSTANCE(ResourceManager);
	SINGLETON_INSTANCE(ComponentManager);
	SINGLETON_INSTANCE(StageManager);
	SINGLETON_INSTANCE(UIManager);
	SINGLETON_INSTANCE(SoundManager);
	SINGLETON_INSTANCE(MissileManager);
public:
	static GameManager*		getInstance();
	static void				releaseInstance();

	timeval					getTime();
	SceneType				getCurrentSceneType();
	void					changeScene(cocos2d::Scene* scene, SceneType sType);

	int						getContactComponentType(BaseComponent* target, cocos2d::Rect rect, Direction dir);

private:
	static GameManager*		m_Instance;
	SceneType				m_CurrentSceneType;

	GameManager();
	~GameManager();
};
