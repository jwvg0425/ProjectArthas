/************************************************************************/
/*
CLASS			: AssemblyDisplayLayer
Author			: 우재우
역할			: 선택된 장비를 보여준다.
최종 수정일자	: 2014-12-02
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "AssemblyUILayer.h"

class AssemblyDisplayLayer : public AssemblyUILayer
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(AssemblyDisplayLayer);
private:
	cocos2d::Sprite*		m_DisplayScanBar = nullptr;

	void					moveScanBar();
};