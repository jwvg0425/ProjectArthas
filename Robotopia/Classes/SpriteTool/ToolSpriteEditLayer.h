/************************************************************************/
/*
CLASS			: ToolSpriteEditLayer
Author			: 김성연
역할				: 새로운 Sprite 정보 Edit Box 통해 추가
최종 수정일자		: 2014-11-08
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Util.h"
#include <vector>

BEGIN_NS_AT

class ToolSpriteEditLayer : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
	enum InfoOder
	{
		TYPE = 0,
		DELAY,
		FRAMENUM,
		FILENAME,
		SAVE,
	};

	OVERRIDE bool init();
	void		  createEditBox(const char* boxTitle, int fontSize, int maxLength, InfoOder tag);
	void		  setEditBox();
	void		  createAniNames(AnimationInfo* aniInfo);
	ResourceType  changeStringTypeToResourceType(const char* currentType);
	

	CREATE_FUNC(ToolSpriteEditLayer);
private:
	std::vector<cocos2d::extension::EditBox*> m_EditBoxs;
	const char*								  m_CurrentType;
	ResourceType							  m_CurrentTypeEnum;
	int										  m_CurrentDelay;
	int										  m_CurrentFrameNum;
	const char*								  m_CurrentFileName;

	

	//에디트 박스 클릭하면 호출하는 메소드
	OVERRIDE void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);

	//에디트 박스 입력을 리턴키를 입력해서 종료할 때 출력되는 메소드
	OVERRIDE void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);

	//에디트 박스를 클릭한 후 글자를 입력할 때마다 호출되는 메소드
	OVERRIDE void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);

	//리턴키를 입력할 때 출력되는 메소드, 일반적으로 리턴키를 입력하면 editBoxEditingDidEnd()가 호출되고
	//editBoxReturn() 메소드가 그 다음으로 호출됩니다.
	OVERRIDE void editBoxReturn(cocos2d::extension::EditBox* editBox);
	

};

END_NS_AT