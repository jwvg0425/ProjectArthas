#include "CommonInfo.h"

bool Arthas::CommonInfo::init()
{
	if (!Component::init())
	{
		return false;
	}

	m_Type = IT_COMMON;
	return true;
}

void Arthas::CommonInfo::update(float dTime)
{

}

void Arthas::CommonInfo::enter()
{

}

void Arthas::CommonInfo::exit()
{

}

Arthas::CommonInfo::Info Arthas::CommonInfo::getInfo()
{
	return m_Info;
}

void Arthas::CommonInfo::setInfo(Info info)
{
	m_Info = info;
}
