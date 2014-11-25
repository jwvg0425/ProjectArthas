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
	///# 아래는 포인터 멤버 변수인데.. 왜 초기화 안함? 나중에 init()에서 초기화 하더라도 그 전에 디폴트값 세팅 바람. 그래야 디버깅시 init전에 죽었는지 후에 죽었는지 판단이 됨
	TitleSceneUILayer*		m_TitleUI;
	LoadingSceneUILayer*	m_LoadingUI;
	GameSceneUILayer*		m_GameUI;
};


