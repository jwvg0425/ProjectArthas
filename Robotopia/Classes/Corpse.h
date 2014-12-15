/************************************************************************/
/*
CLASS			: Corpse
Author			: 남현욱
역할				: Corpse class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: 몬스터 잡으면 나오는 시체입니다
*/
/************************************************************************/
#include "Util.h"
#include "NPC.h"
#define ABSORB_TIME 2

class GaugeBarContainer;
class Corpse : public NPC
{
public:
	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();
	virtual void				dead();

	void						absorb(Creature* target, double dTime, int idx);

	void						idleTransition(Creature* target, double dTime, int idx);
	void						absorbTransition(Creature* target, double dTime, int idx);

	CREATE_FUNC(Corpse);
private:
	enum State
	{
		STAT_IDLE,
		STAT_ABSORB,
		STAT_NUM,
	};
	cocos2d::Sprite*			m_Sprite;
	int							m_Time = 0;
	double						m_AbsorbTime = 0;
	GaugeBarContainer*			m_Bar = nullptr;
};