/************************************************************************/
/*
CLASS			: ModuleButton
Author			: 남현욱
역할				: 맵 모듈 데이터와 연결되어있는 버튼
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#include "cocos2d.h"
#include "util.h"




class ModuleButton : public cocos2d::Node
{
public:
	OVERRIDE bool init();

	void setModule(ModuleData* module);
	cocos2d::Label* getLabel();
	ModuleData* getModule();

	void updateLabel();

	CREATE_FUNC(ModuleButton);

	void					onMouseDown(cocos2d::Event* event);
private:
	ModuleData* m_Module;
	cocos2d::Label* m_Label;
};

