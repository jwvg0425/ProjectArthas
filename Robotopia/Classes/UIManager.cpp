#include "pch.h"
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
		if (m_TitleUI == nullptr)
		{
			m_TitleUI = Arthas::TitleSceneUILayer::create();
		}
		return (UILayer*)m_TitleUI;
	case Arthas::LOADING_SCENE:
		if (m_LoadingUI == nullptr)
		{
			m_LoadingUI = Arthas::LoadingSceneUILayer::create();
		}
		return (UILayer*)m_LoadingUI;
	case Arthas::GAME_SCENE:
		if (m_GameUI == nullptr)
		{
			m_GameUI = Arthas::GameSceneUILayer::create();
		}
		return (UILayer*)m_GameUI;
	}
	return nullptr;
}

