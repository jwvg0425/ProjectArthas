/************************************************************************/
/*
	CLASS			: UILayer
	Author			: 우재우
	역할			: Scene에 맞는 UILayer들이 공통으로 쓰는 함수를 모은 조상 레이어
	최종 수정일자	: 2014-10-31
	최종 수정자		: 우재우
	최종 수정사유	: 이제 내꺼다!!!
	Comment			: 
*/
/************************************************************************/

#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include "Util.h"

BEGIN_NS_AT

class TitleSceneUILayer;
class LoadingSceneUILayer;
class GameSceneUILayer;

class UILayer : public cocos2d::Layer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update( float dTime );

	CREATE_FUNC( UILayer );
protected:
	void					setUIProperties(OUT cocos2d::Sprite* sprite, cocos2d::Point anchorPoint,
											cocos2d::Point positionPoint, float scale, bool visible, int zOrder);

	int m_WinWidth;
	int m_WinHeight;

	SceneType				m_CurrentScene;

	TitleSceneUILayer*		m_TitleUILayer;
	LoadingSceneUILayer*	m_LodingUILayer;
	GameSceneUILayer*		m_GameUILayer;

};

END_NS_AT