/************************************************************************/
/*
CLASS			: Corpse
Author			: 남현욱
역할				: Corpse class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: 몬스터 잡으면 나오는 시체입니다
*/
/************************************************************************/
#include "Util.h"
#include "BaseComponent.h"

class Corpse : public BaseComponent
{
public:
	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();

	CREATE_FUNC(Corpse);
private:
	cocos2d::Sprite*			m_Sprite;
	int							m_Time;
};