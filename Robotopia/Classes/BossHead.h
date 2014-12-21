#include "Creature.h"
#define HEAD_RADIUS 150
#define ATTACK_RANGE 1000
#define PRE_DELAY 1.f
#define POST_DELAY 5.f

class BossHead : public Creature
{
public:
	enum State
	{
		STAT_IDLE,
		STAT_MOVE,
		STAT_ATTACK,
		STAT_NUM,
	};

	enum Mode
	{
		MODE_WIDTH,
		MODE_HEIGHT,
		MODE_MISSLE,
		MODE_NUM,
	};

	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();
	virtual bool				onContactBegin(cocos2d::PhysicsContact& contact);
	virtual void				onContactSeparate(cocos2d::PhysicsContact& contact);
	void						setAttacking(bool isAttack);
	void						setMoving(bool isMoving);
	virtual const AllStatus&	getInfo() const;

	void						move(Creature* target, double dTime, int idx);
	void						enterMove();
	void						exitMove();

	void						attack(Creature* target, double dTime, int idx);
	void						enterAttack();
	void						exitAttack();
	void						launch(cocos2d::Node* ref);
	void						seizeFire( cocos2d::Node* ref );

	void						idleTransition(Creature* target, double dTime, int idx);
	void						moveTransition(Creature* target, double dTime, int idx);
	void						attackTransition(Creature* target, double dTime, int idx);
	CREATE_FUNC(BossHead);

protected:
	void						radiateAttack( cocos2d::Point startPos );
	void						makeRadiateMissile( cocos2d::Node* ref , float startDegree , cocos2d::Point startPos);
	bool						m_IsAttacking = false;
	bool						m_IsMoving = false;
	int							m_CurrentMode = 0;
	float						m_Distance = 0.f;
	float						m_PreDelay = 0.f;
	float						m_PostDelay = 0.f;
	SpriteComponent*			m_ModeRender[MODE_NUM];
	cocos2d::Point				m_Origin;
	AllStatus					m_Info;
};

