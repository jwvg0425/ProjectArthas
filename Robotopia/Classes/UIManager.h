/************************************************************************/
/*
CLASS			: UIManager
Author			: 우재우
역할			: Scene에 맞는 UI 요청 시 해당하는 Layer 전달
최종 수정일자	: 2014-10-31
최종 수정자		: 우재우
최종 수정사유	:
Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "cocos2d.h"



class UILayer;
class TitleSceneUILayer;
class LoadingSceneUILayer;
class GameSceneUILayer;

class UIManager
{
public:
	UIManager();
	~UIManager();

	bool					init();
	UILayer*				getUILayer(SceneType sceneType);
	
private:
	TitleSceneUILayer*		m_TitleUI;
	LoadingSceneUILayer*	m_LoadingUI;
	GameSceneUILayer*		m_GameUI;
};


