/************************************************************************/
/*
	CLASS			: ComponentManager
	Author			: 김연우
	역할				: 각종 컴포넌트를 생성해주는 매니저.
	최종 수정일자	: 2014-10-31
	최종 수정자		:
	최종 수정사유	:
	Comment			: 컴포넌트 생성방식 Class* newComp = createComponent<Class>();
*/
/************************************************************************/

#pragma once
#include "Util.h"



class BaseComponent;
class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	bool init();

	template<class T>
	T* createComponent();

private:
};

template<class T>
T* ComponentManager::createComponent()
{
	//BaseComponent형이 맞는지 확인하는 코드
	BaseComponent* newComponent = T::create();
	return static_cast<T*>(newComponent);
	//나중에 메모리 풀관리하는 코드 추가
}

