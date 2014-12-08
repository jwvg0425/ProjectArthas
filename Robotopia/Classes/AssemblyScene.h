/************************************************************************/
/*
CLASS			: AssemblyScene
Author			: 우재우
역할			: AssemblyScene을 보여준다.
최종 수정일자	: 2014-11-28
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "cocos2d.h"

class UILayer;
class AssemblyScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene*	createScene();
	virtual bool			init();
	virtual void			update(float dTime);
	virtual	void			onExit();

	CREATE_FUNC(AssemblyScene);

private:
	bool					m_IsStarted = false;
	UILayer*				m_UILayer = nullptr;
};