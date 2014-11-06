/************************************************************************/
/*
CLASS			: ModuleEditLayer
Author			: 남현욱
역할				: 모듈데이터 수정하는 레이어.
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#include "cocos2d.h"
#include "util.h"
#include <map>


BEGIN_NS_AT
class Component;
class ModuleEditLayer : public cocos2d::Layer
{
public:
	OVERRIDE bool					init();

	CREATE_FUNC(ModuleEditLayer);

private:
	std::map<int, Component*> m_ModuleSprite;
};


END_NS_AT