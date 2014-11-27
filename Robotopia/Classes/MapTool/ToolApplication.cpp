#include "ToolApplication.h"

ToolApplication* ToolApplication::sm_pSharedApplication = nullptr;

ToolApplication* ToolApplication::getInstance()
{
	CC_ASSERT(sm_pSharedApplication);
	return sm_pSharedApplication;
}

ToolApplication::ToolApplication()
{
	sm_pSharedApplication = this;
}

ToolApplication::~ToolApplication()
{

}

HINSTANCE ToolApplication::getWindowHandle()
{
	return _instance;
}

