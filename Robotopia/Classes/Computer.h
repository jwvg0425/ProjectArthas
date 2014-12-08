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

class Computer : public NPC
{
public:
	virtual bool	init();
	virtual void	update(float dTime);
	virtual void	enter();
	virtual void	exit();

	CREATE_FUNC(Computer);

private:
	AllStatus				m_Info;
};

