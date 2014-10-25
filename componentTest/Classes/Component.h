#pragma once

class Object;

class Component
{
public:
	virtual void update(float dTime) = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;

	int getType(){
		return type;
	}
protected:
	int type;
	Object* parent;
};