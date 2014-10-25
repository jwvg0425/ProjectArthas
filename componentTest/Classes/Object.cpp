#include "Object.h"
#include "Component.h"


void Object::update(float dTime)
{
	for (auto& component : m_Components)
	{
		component->update(dTime);
	}
}

Component* Object::getComponent(int type)
{
	for (auto& component : m_Components)
	{
		if (component->getType() == type)
		{
			return component;
		}
	}

	return nullptr;
}

void Object::removeComponent(Component* remComponent)
{
	for (auto& it = m_Components.begin(); it != m_Components.end();)
	{
		Component* component = *it;

		if (remComponent->getType() == component->getType())
		{
			delete component;
			it = m_Components.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool Object::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void Object::addComponent(Component* component)
{
	m_Components.push_back(component);
}

void Object::removeAllComponent()
{
	for (auto& component : m_Components)
	{
		delete component;
	}

	m_Components.clear();
}
