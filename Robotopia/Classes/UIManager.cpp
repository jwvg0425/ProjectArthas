#include "UIManager.h"
#include "UILayer.h"
#include "TitleSceneUILayer.h"
#include "LodingSceneUILayer.h"
#include "GameSceneUILayer.h"

Arthas::UIManager::UIManager()
{

}

Arthas::UIManager::~UIManager()
{

}

bool Arthas::UIManager::init()
{
	return true;
}

Arthas::UILayer* Arthas::UIManager::getUILayer(SceneType sceneType)
{
	switch (sceneType)
	{
	case Arthas::TITLE_SCENE:
		return (UILayer*)m_TitleUI;
	case Arthas::LOADING_SCENE:
		return (UILayer*)m_LoadingUI;
	case Arthas::GAME_SCENE:
		return (UILayer*)m_GameUI;
	}
	return nullptr;
}

