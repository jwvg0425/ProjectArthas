/************************************************************************/
/*
	CLASS			: ComponentManager
	Author			: 김연우
	역할				: 각종 컴포넌트를 생성해주는 매니저.
	최종 수정일자	: 2014-10-31
	최종 수정자		:
	최종 수정사유	:
	Comment			: 컴포넌트 생성방식 Component* newComp = createComponent<Class>();
*/
/************************************************************************/

#pragma once
#include "Util.h"

BEGIN_NS_AT

class Component;
class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	bool init();

	template<class T>
	Component* createComponent();

private:
};

template<class T>
Component* Arthas::ComponentManager::createComponent()
{
	Component* newComponent = T::create();
	return newComponent;
}

END_NS_AT