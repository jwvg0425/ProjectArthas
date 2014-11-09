#include "View.h"
#include "cocos-ext.h"

#define WINSIZE_WIDTH 960
#define WINSIZE_HEIGHT 540

void Arthas::View::initView(cocos2d::Layer* scrollingLayer)
{
	m_Scroll = cocos2d::extension::ScrollView::
		create(cocos2d::Size(WINSIZE_WIDTH, WINSIZE_HEIGHT), scrollingLayer);

	m_Scroll->setDirection(cocos2d::extension::ScrollView::Direction::BOTH);
	m_Scroll->setBounceable(false);
}

void Arthas::View::setViewPort(cocos2d::Point pivotPoint)
{
	m_Scroll->setContentOffset(pivotPoint);
}


