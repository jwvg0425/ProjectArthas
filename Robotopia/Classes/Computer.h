/************************************************************************/
/*
CLASS			: Computer
Author			: 김연우
역할				: 아이템이 나오는 Computer NPC?
최종 수정일자	: 2014-12-08
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "NPC.h"
#define COMPUTER_WIDTH 50
#define COMPUTER_HEIGHT 50

class GaugeBarContainer;
class Computer : public NPC
{
public:
	enum State
	{
		STAT_IDLE,
		STAT_AVAILABLE,
		STAT_LOADING,
		STAT_COMPLETE,
		STAT_NUM,
	};

	virtual bool	init();
	virtual void	update(float dTime);
	virtual void	enter();
	virtual void	exit();

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

	CREATE_FUNC(Computer);

private:
	void					initFSMAndTransition();
	AllStatus				m_Info;
	GaugeBarContainer*		m_Bar = nullptr;
	bool					m_IsComplete = false;
	float					m_LoadingSpeed = 0.f;
	int						m_Sound = 0;
};

