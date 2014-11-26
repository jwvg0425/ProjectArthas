#include "pch.h"
#include "UIManager.h"
#include "UILayer.h"
#include "TitleSceneUILayer.h"
#include "LodingSceneUILayer.h"
#include "AssemblyUILayer.h"
#include "GameSceneUILayer.h"

bool UIManager::init()
{
	m_TitleUI = nullptr;
	m_LoadingUI = nullptr;
	m_AssemblyUI = nullptr;
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
		return static_cast<UILayer*>(m_TitleUI);
	case LOADING_SCENE:
		if (m_LoadingUI == nullptr)
		{
			m_LoadingUI = LoadingSceneUILayer::create();
		}
		return static_cast<UILayer*>(m_LoadingUI);
	case ASSEMBLY_SCENE:
		if (m_AssemblyUI == nullptr)
		{
			m_AssemblyUI = AssemblyUILayer::create();
		}
		return static_cast<UILayer*>(m_AssemblyUI);
	case GAME_SCENE:
		if (m_GameUI == nullptr)
		{
			m_GameUI = GameSceneUILayer::create();
		}
		return static_cast<UILayer*>(m_GameUI);
	}
	return nullptr;
}

