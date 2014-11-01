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
#define GET_GAME_MANAGER() Arthas::GameManager::getInstance()
#define GET_DATA_MANAGER() Arthas::GameManager::getInstance()->getDataManagerInstance()
#define GET_TRIGGER_MANAGER() Arthas::GameManager::getInstance()->getTriggerManagerInstance()
#define GET_INPUT_MANAGER() Arthas::GameManager::getInstance()->getInputManagerInstance()
#define GET_RESOURCE_MANAGER() Arthas::GameManager::getInstance()->getResourceManagerInstance()
#define GET_COMPONENT_MANAGER() Arthas::GameManager::getInstance()->getComponentManagerInstance()
#define GET_STAGE_MANAGER() Arthas::GameManager::getInstance()->getStageManagerInstance()
#define GET_UI_MANAGER() Arthas::GameManager::getInstance()->getUIManagerInstance()
#define GET_SOUND_MANAGER() Arthas::GameManager::getInstance()->getSoundManagerInstance()
#define GET_SINGLETON_INSTANCE(CLASS)\
{ \
	if (m_ ## CLASS ## Instance == nullptr)\
	{\
		m_ ## CLASS ## Instance = new Arthas::## CLASS ##();\
		m_ ## CLASS ## Instance->init();\
	}\
	return m_ ## CLASS ## Instance;\
}

BEGIN_NS_AT
class DataManager;
class TriggerManager;
class InputManager;
class ResourceManager;
class ComponentManager;
class StageManager;
class UIManager;
class SoundManager;
class GameManager
{
public:
	static GameManager*		getInstance();
	static void				releaseInstance();

	DataManager*			getDataManagerInstance();
	void					releaseDataManagerInstance();

	TriggerManager*			getTriggerManagerInstance();
	void					releaseTriggerManagerInstance();

	InputManager*			getInputManagerInstance();
	void					releaseInputManagerInstance();

	ResourceManager*		getResourceManagerInstance();
	void					releaseResourceManagerInstance();

	ComponentManager*		getComponentManagerInstance();
	void					releaseComponentManagerInstance();

	StageManager*			getStageManagerInstance();
	void					releaseStageManagerInstance();

	UIManager*				getUIManagerInstance();
	void					releaseUIManagerInstance();

	SoundManager*			getSoundManagerInstance();
	void					releaseSoundManagerInstance();

	timeval					getTime();

private:
	static GameManager*		m_Instance;
	
	DataManager*			m_DataManagerInstance;
	TriggerManager*			m_TriggerManagerInstance;
	InputManager*			m_InputManagerInstance;
	ResourceManager*		m_ResourceManagerInstance;
	ComponentManager*		m_ComponentManagerInstance;
	StageManager*			m_StageManagerInstance;
	UIManager*				m_UIManagerInstance;
	SoundManager*			m_SoundManagerInstance;

	GameManager();
	~GameManager();
};
END_NS_AT