#pragma once

#include "cocos2d.h"

class Component;

class Object : public cocos2d::Node
{
public:
	virtual bool init();

	CREATE_FUNC(Object);

	void update(float dTime);

	void addComponent(Component* component);

	Component* getComponent(int type);
	void removeComponent(Component* remComponent);
	void removeAllComponent();

protected:
	std::vector<Component*> m_Components;
};
