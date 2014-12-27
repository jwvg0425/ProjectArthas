/************************************************************************/
/*
CLASS			: Lever
Author			: 김연우
역할				: 아이템이 나오는 Lever NPC?
최종 수정일자	: 2014-12-08
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "NPC.h"
#define LEVER_WIDTH 60
#define LEVER_HEIGHT 60

class GaugeBarContainer;
class Lever : public NPC
{
public:
	enum State
	{
		STAT_IDLE,
		STAT_OFF,
		STAT_MID,
		STAT_ON,
		STAT_NUM,
	};

	virtual bool	init();
	virtual void	update(float dTime);
	virtual void	enter();
	virtual void	exit();
	virtual void	dead();

	void			available(Creature* target, double dTime, int idx);
	void			loading(Creature* target, double dTime, int idx);
	void			complete(Creature* target, double dTime, int idx);

	void			availableEnter(double dTime, int idx);
	void			availableExit(double dTime, int idx);
	void			loadingEnter(double dTime, int idx);
	void			loadingExit(double dTime, int idx);
	void			completeEnter(double dTime, int idx);
	void			completeExit(double dTime, int idx);

	void			idleTransition(Creature* target, double dTime, int idx);
	void			availableTransition(Creature* target, double dTime, int idx);
	void			loadingTransition(Creature* target, double dTime, int idx);
	void			completeTransition(Creature* target, double dTime, int idx);
	void			setLoadingTime(float sec);

	CREATE_FUNC(Lever);

private:
	void					initFSMAndTransition();
	AllStatus				m_Info;
	GaugeBarContainer*		m_Bar = nullptr;
	bool					m_IsComplete = false;
	float					m_LoadingSpeed = 0.f;
	bool					m_SoundId = 0;
};

