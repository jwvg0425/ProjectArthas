#include "pch.h"
#include "UIManager.h"
#include "UILayer.h"
#include "TitleSceneUILayer.h"
#include "LodingSceneUILayer.h"
#include "GameSceneUILayer.h"

UIManager::UIManager()
{

}

UIManager::~UIManager()
{

}

bool UIManager::init()
{
	m_TitleUI = nullptr;
	m_LoadingUI = nullptr;
	m_GameUI = nullptr;
	return true;
}

UILayer* UIManager::getUILayer(SceneType sceneType)
{
	switch (sceneType)
	{
	case TITLE_SCENE:
		if (m_TitleUI == nullptr)
		{
			m_TitleUI = TitleSceneUILayer::create();
		}
		return (UILayer*)m_TitleUI; ///<  C++ 캐스팅을 써라. 
	case LOADING_SCENE:
		if (m_LoadingUI == nullptr)
		{
			m_LoadingUI = LoadingSceneUILayer::create();
		}
		return (UILayer*)m_LoadingUI;
	case GAME_SCENE:
		if (m_GameUI == nullptr)
		{
			m_GameUI = GameSceneUILayer::create();
		}
		return (UILayer*)m_GameUI;
	}
	return nullptr;
}

