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
	
	void					moveScanBar();
	bool					getPowerOver();
	bool					getMomoryOver();
	void					setConfirmSet(ConfirmSet confirmSet);
	void					assembleRobot();

private:
	cocos2d::Sprite*		m_Head = nullptr;
	cocos2d::Sprite*		m_Engine = nullptr;
	cocos2d::Sprite*		m_Armor = nullptr;
	cocos2d::Sprite*		m_Melee = nullptr;
	cocos2d::Sprite*		m_Range = nullptr;
	cocos2d::Sprite*		m_Steam = nullptr;
	cocos2d::Sprite*		m_Leg = nullptr;
	cocos2d::Sprite*		m_DisplayScanBar = nullptr;
	cocos2d::Sprite*		m_PowerGauge = nullptr;
	cocos2d::Sprite*		m_MemoryGauge =  nullptr;

	ConfirmSet				m_ConfirmSet = ConfirmSet();
	ConfirmSet				m_PrevConfirmSet = ConfirmSet();

	int						m_MaxPower = 0;
	int						m_MaxMemory = 0;

	bool					m_PowerOver;
	bool					m_MemoryOver;

	void					powerOverCheck();
	void					memoryOverCheck();
};