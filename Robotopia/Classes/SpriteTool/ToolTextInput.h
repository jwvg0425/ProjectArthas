#pragma once
#include "cocos2d.h"
#include "Util.h"

class ToolTextInput : public cocos2d::TextFieldTTF
{
public:
	OVERRIDE bool init();
	void		  insetText(std::string text);




	CREATE_FUNC(ToolTextInput)

private:
	std::string m_String;

};