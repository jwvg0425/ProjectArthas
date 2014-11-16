/************************************************************************/
/*
CLASS			: PhysicsInfo
Author			: 남현욱
역할				: 다물리 충돌과 관련하여 자세한 정보가 필요한 경우 이 클래스를 붙이면 됩니.
최종 수정일자	: 2014-11-03
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Util.h"
#include "Component.h"

BEGIN_NS_AT

class PhysicsInfo : public Component
{
public:
	typedef std::vector<int> ComponentTypes;

	struct Info
	{
		ComponentTypes contactObjects;
	};
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	Info*						getInfo(); // 받은 구조체 정보 수정하면 그대로 반영됨.
	void						setInfo(Info info);

	CREATE_FUNC(PhysicsInfo);

protected:
	Info						m_Info;
};

END_NS_AT