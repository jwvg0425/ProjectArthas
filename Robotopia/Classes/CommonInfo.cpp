#include "pch.h"
#include "CommonInfo.h"

bool CommonInfo::init()
{
	if (!BaseComponent::init())
	{
		return false;
	}

	m_Type = IT_COMMON;
	return true;
}

void CommonInfo::update(float dTime)
{

}

void CommonInfo::enter()
{

}

void CommonInfo::exit()
{

}

CommonInfo::Info CommonInfo::getInfo()
{
	return m_Info;
}

void CommonInfo::setInfo(Info info)
{
	m_Info = info;
}
