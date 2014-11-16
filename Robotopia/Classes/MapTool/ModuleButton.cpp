#include "ModuleButton.h"
#include "MapToolAppDelegate.h"
#include "ModuleListLayer.h"


bool ModuleButton::init()
{
	if (!cocos2d::Node::init())
	{
		return false;
	}

	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(ModuleButton::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void ModuleButton::setModule(ModuleData* module)
{
	m_Module = module;

	m_Label = cocos2d::Label::create(m_Module->name, "Thonburi", 20);
	addChild(m_Label);
}

void ModuleButton::updateLabel()
{
	m_Label->setString(m_Module->name);
}

void ModuleButton::onMouseDown(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	cocos2d::Rect rect = cocos2d::Rect(getPositionX() - m_Label->getContentSize().width / 2, getPositionY() - m_Label->getContentSize().height / 2,
		m_Label->getContentSize().width, m_Label->getContentSize().height);


	if (rect.containsPoint(cocos2d::Point(ev->getCursorX(), WINSIZE_HEIGHT + ev->getCursorY())))
	{
		((ModuleListLayer*)getParent())->setSelectedIdx(m_Module);
	}
}

ModuleData* ModuleButton::getModule()
{
	return m_Module;
}

cocos2d::Label* ModuleButton::getLabel()
{
	return m_Label;
}

