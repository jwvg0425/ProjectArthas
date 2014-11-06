/************************************************************************/
/*
CLASS			: ComponentButton
Author			: 남현욱
역할				: 컴포넌트 데이터와 연결되어있는 버튼
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#include "cocos2d.h"
#include "util.h"

BEGIN_NS_AT

class Component;
class ComponentButton : public cocos2d::Node
{
public:
	OVERRIDE bool init();

	void setComponent(Component* component);
	void changeSelectState(bool isSelected);
	Component* getComponent();


	CREATE_FUNC(ComponentButton);

	void					onMouseDown(cocos2d::Event* event);
private:

	cocos2d::DrawNode* m_Border;
	Component* m_Component;
	cocos2d::Label* m_Label;
};

END_NS_AT