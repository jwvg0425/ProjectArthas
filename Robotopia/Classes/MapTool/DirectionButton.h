/************************************************************************/
/*
CLASS			: DirectionButton
Author			: 남현욱
역할				: 방향 값 바꿔주는 버튼.
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#include "cocos2d.h"
#include "util.h"

BEGIN_NS_AT


class DirectionButton : public cocos2d::Node
{
public:
	OVERRIDE bool init();
	
	void setTarget(Direction* targetDir);
	void setDirection(DirectionBit direction);

	CREATE_FUNC(DirectionButton);

	void					onMouseDown(cocos2d::Event* event);
private:
	cocos2d::Label* m_Label;
	Direction* m_TargetDir;
	DirectionBit m_Direction;
};

END_NS_AT