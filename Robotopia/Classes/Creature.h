/************************************************************************/
/*
CLASS			: Thing
Author			: 남현욱
역할				: Thing class
최종 수정일자	: 
최종 수정자		:
최종 수정사유	:
Comment			: FSM을 갖고 있는 객체들의 최상위 클래스.
*/
/************************************************************************/
#pragma once
#include "BaseComponent.h"
#include "Util.h"

class SpriteComponent;
class Creature;
typedef std::function<void(Creature*, double, int)> FSMFunction;
typedef std::vector<FSMFunction> FSMFunctions;
typedef std::vector<SpriteComponent*> Render;

class Creature : public BaseComponent
{
public:
	virtual bool					init() = 0;
	virtual void					update(float dTime);
	virtual void					updateFSM(float dTime);
	virtual void					updateRender(float dTime);
	virtual void					enter() = 0;
	virtual void					exit() = 0;
	int								getState(int idx);
	void							setState(int idx, int state);
	void							initFSM(int FSMNum);
	void							setEnabled(bool enable);
	void							FlipBody(bool isLeft);
	virtual const AllStatus&		getInfo() const = 0;

protected:
	std::vector<int>				m_States;
	std::vector<int>				m_PrevStates;
	std::vector<FSMFunctions>		m_FSMs;
	std::vector<FSMFunctions>		m_Transitions;
	std::vector<Render>				m_Renders;
	cocos2d::PhysicsBody*			m_Body = nullptr;
};

