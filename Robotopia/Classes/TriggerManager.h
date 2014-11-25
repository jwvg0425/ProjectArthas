/************************************************************************/
/*
CLASS			: TriggerManager
Author			: 남현욱
역할				: 각종 트리거를 생성해주는 매니저.
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			: 트리거 생성 후 각 트리거 값을 초기화해주는 것을 잊지 말 것.
*/
/************************************************************************/

#pragma once
#include "Util.h"



class Trigger;

class TriggerManager
{
public:
	TriggerManager();
	~TriggerManager();

	bool init();

	template<class T>
	T* createTrigger();
private:
};

template<class T>
T* TriggerManager::createTrigger()
{
	//Trigger형이 맞는지 확인하는 코드

	///# 템플릿은 이렇게 쓰라고 있는게 아니다.

	/// T가 Trigger의 자식인지 컴파일 타임에 검사하고 싶다면 
	static_assert(std::is_base_of<Trigger, T>::value, "T must be a descendant of Trigger");

	Trigger* newTrigger = new T();
	return (T*)newTrigger;
	//나중에 메모리 풀관리하는 코드 추가
}


