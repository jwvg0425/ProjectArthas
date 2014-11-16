#include"MapTool/DirectionButton.h"
#include"MapTool/MapToolAppDelegate.h"
#include"GameManager.h"
#include"InputManager.h"


bool DirectionButton::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(DirectionButton::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}


void DirectionButton::setTarget(Direction* targetDir)
{
	m_TargetDir = targetDir;
}


void DirectionButton::setDirection(DirectionBit direction)
{
	m_Direction = direction;

	switch (direction)
	{
	case DIR_LEFT:
		m_Label = cocos2d::Label::create("left", "Thonburi", 20);
		break;
	case DIR_UP:
		m_Label = cocos2d::Label::create("up", "Thonburi", 20);
		break;
	case DIR_RIGHT:
		m_Label = cocos2d::Label::create("right", "Thonburi", 20);
		break;
	case DIR_DOWN:
		m_Label = cocos2d::Label::create("down", "Thonburi", 20);
		break;
	}

	addChild(m_Label);
}

void DirectionButton::onMouseDown(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	cocos2d::Rect rect = cocos2d::Rect(getPositionX() - m_Label->getContentSize().width / 2, getPositionY() - m_Label->getContentSize().height/2,
		m_Label->getContentSize().width, m_Label->getContentSize().height);


	if (rect.containsPoint(cocos2d::Point(ev->getCursorX(), WINSIZE_HEIGHT + ev->getCursorY())))
	{
		if (*m_TargetDir & m_Direction)
		{
			m_Label->setColor(cocos2d::Color3B(255, 255, 255));
			*m_TargetDir &= ~m_Direction;
		}
		else
		{
			m_Label->setColor(cocos2d::Color3B(255, 0, 0));
			*m_TargetDir |= m_Direction;
		}
	}
}
