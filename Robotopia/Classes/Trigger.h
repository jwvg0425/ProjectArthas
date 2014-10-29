/************************************************************************/
/*
CLASS			: Trigger
Author			: 김연우
역할				: 트리거들의 최상위 클래스.
최종 수정일자	: 2014-10-29
최종 수정자		: 남현욱
최종 수정사유	: Component 상속 받는 쪽이 옵저버 구현하기 편할 듯 합니다.
Comment			: 주의 사항 - == 앞에 오는 쪽이 조건에 해당하는 trigger고 뒤에 오는 쪽이 실제 발생한 trigger입니다. 
					A == B와 B == A 가 다를 수 있기 때문에 이 점에 주의해서 코드 작성 요망.
*/
/************************************************************************/
#pragma once
#include "Util.h"

BEGIN_NS_AT

class Trigger
{
public:
	int getType() const;
	bool isEqualTypeTrigger(const Trigger& enemy);
	virtual bool operator ==( Trigger& trigger ) = 0;
protected:
	int m_Type;
};

END_NS_AT