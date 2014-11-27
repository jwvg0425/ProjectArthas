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

#define  MAXFILE_NAME 50
#define  MAX_CHAR 256


class ToolSpriteEditLayer : public cocos2d::Layer, public cocos2d::extension::EditBoxDelegate
{
public:
	enum InfoOrder
	{
		INFOSTART = 0,
		TYPE = INFOSTART + 1,
		DELAY,
		FRAMENUM,
		FILENAME,
		SAVE,
		AUTOSAVE,
	};
	~ToolSpriteEditLayer();
	OVERRIDE bool init();
	OVERRIDE void update(float dTime);
	void		  initFileNameBox();
	
	void          ATMenuButtonCallback(cocos2d::Ref* sender);
	void          STMenuButtonCallback(cocos2d::Ref* sender);
	void          ATListShow(cocos2d::Ref* sender);
	void		  STListShow(cocos2d::Ref* sender);

	void		  createMenuButton(AnimationType type, bool isAT);
	void		  createMenuButton(SpriteType type, bool isAT);
	void		  createAniNames(AnimationInfo* aniInfo);
	void		  createAllMenuButton();
	void		  createListButton(std::string string, bool isAT);
	void		  createLabel(std::string title);
	void		  createEditBox(char* boxTitle, int fontSize, int maxLength, InfoOrder tag);
	void		  createEditBox(char* boxTitle, int fontSize, int maxLength, InfoOrder tag, int boxNum);

	void          assignLabels();
	void		  assignMenuButtons();
	void		  assignEditBox();
	void		  assignFileNameBox();

	AnimationInfo getAniMationInfo() const;
	AnimationType getCurrentATInfoType() const;
	SpriteType	  getCurrentSTInfoType() const;
	
	CREATE_FUNC(ToolSpriteEditLayer);
private:

	//에디트 박스 클릭하면 호출하는 메소드
	OVERRIDE void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);

	//에디트 박스 입력을 리턴키를 입력해서 종료할 때 출력되는 메소드
	OVERRIDE void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);

	//에디트 박스를 클릭한 후 글자를 입력할 때마다 호출되는 메소드
	OVERRIDE void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text);

	//리턴키를 입력할 때 출력되는 메소드, 일반적으로 리턴키를 입력하면 editBoxEditingDidEnd()가 호출되고
	//editBoxReturn() 메소드가 그 다음으로 호출됩니다.
	OVERRIDE void editBoxReturn(cocos2d::extension::EditBox* editBox);

	std::vector<cocos2d::Menu*>						 m_ATMenuButtons;
	std::vector<cocos2d::Menu*>						 m_STMenuButtons;
	std::vector<cocos2d::Label*>                     m_Labels;
	std::vector<cocos2d::extension::EditBox*>		 m_EditBoxs;
	std::vector<cocos2d::extension::EditBox*>		 m_FileNameBoxs;

	AnimationType									 m_CurrentATInfoType;
	SpriteType										 m_CurrentSTInfoType;
	bool											 m_IsATStateInList;
};

