#include "SpriteTool/ToolSpriteEditLayer.h"
#define BOXWIDTH 170
#define BOXHEIGHT 60


bool Arthas::ToolSpriteEditLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_EditBoxs.reserve(10);
	createEditBox("Type", 45, 15, TYPE);
	createEditBox("delay", 45, 5, DELAY);
	createEditBox("frameNum", 45, 4, FRAMENUM);
	createEditBox("FileName", 45, 30, FILENAME);
	createEditBox("Save", 45, 1, SAVE);
	setEditBox();

	return true;
}

void Arthas::ToolSpriteEditLayer::createEditBox(const char* boxTitle, int fontSize, int maxLength, InfoOder tag)
{
	if (boxTitle == nullptr) return;

	auto editBox = cocos2d::extension::EditBox::
		create(cocos2d::Size(BOXWIDTH, BOXHEIGHT),
		cocos2d::extension::Scale9Sprite::create("SpriteToolEditBox.png"));
	editBox->setPlaceHolder(boxTitle);
	editBox->setPlaceholderFont("Adobe Arabic", fontSize);
	editBox->setTag(tag);
	editBox->setMaxLength(maxLength);
	editBox->setDelegate(this);
	this->addChild(editBox);

	m_EditBoxs.push_back(editBox);
}

void Arthas::ToolSpriteEditLayer::setEditBox()
{
	if (m_EditBoxs.empty()) return;

	cocos2d::Point pos;
	pos.x = 100;
	pos.y = 480;

	for (auto pEditBox : m_EditBoxs)
	{
		pEditBox->setPosition(pos);
		pos.x += BOXWIDTH * 1.2;
	}
}

void Arthas::ToolSpriteEditLayer::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox)
{
}
void Arthas::ToolSpriteEditLayer::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox)
{

}

void Arthas::ToolSpriteEditLayer::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string& text)
{
}

void Arthas::ToolSpriteEditLayer::editBoxReturn(cocos2d::extension::EditBox* editBox)
{
	if (editBox == nullptr) return;
	
	switch (editBox->getTag())
	{
	case TYPE:
		m_CurrentType = editBox->getText();
		break;
	case DELAY:
		m_CurrentDelay = atoi(editBox->getText());
		break;
	case FRAMENUM:
		m_CurrentFrameNum = atoi(editBox->getText());
		break;
	case FILENAME:
		m_CurrentFileName = editBox->getText();
		break;
	case SAVE:
		m_CurrentTypeEnum = changeStringTypeToResourceType(m_CurrentType);

		if (*m_CurrentType == 'S' && *(m_CurrentType + 1) == 'T')
		{
			SpriteInfo tmpSprInfo;
			tmpSprInfo.type = m_CurrentTypeEnum;
			strcpy(tmpSprInfo.spriteName, m_CurrentFileName);
			//getDatamanager()->saveSpriteData(내가 채운 SpriteTYpe구조체);
		}
		else if (*m_CurrentType == 'A' && *(m_CurrentType + 1) == 'T')
		{
			AnimationInfo tmpAniInfo;
			tmpAniInfo.type = m_CurrentTypeEnum;
			tmpAniInfo.delay = m_CurrentDelay;
			tmpAniInfo.frameNum = m_CurrentFrameNum;
			createAniNames(&tmpAniInfo);
			
			//getDatamanager()->saveAnimationData(내가 채운 AnimationTYpe구조체);
		}
	
	default:
		break;
	}
}

Arthas::ResourceType Arthas::ToolSpriteEditLayer::changeStringTypeToResourceType(const char* currentType)
{
	if (currentType == nullptr) return ST_END;
	
	int typeEnum;

	if (strcmp(currentType, "ST_PLAYER") == 0)
	{
		typeEnum = ST_PLAYER;
	}
	else if (strcmp(currentType, "ST_BLOCK") == 0)
	{
		typeEnum = ST_BLOCK;
	}
	else if (strcmp(currentType, "ST_BLOCK_TURRET") == 0)
	{
		typeEnum = ST_BLOCK_TURRET;
	}
	else if (strcmp(currentType, "AT_PLAYER") == 0)
	{
		typeEnum = AT_PLAYER;
	}
	else if (strcmp(currentType, "AT_PLAYER_IDLE") == 0)
	{
		typeEnum = AT_PLAYER_IDLE;
	}
	else if (strcmp(currentType, "AT_PLAYER_JUMP") == 0)
	{
		typeEnum = AT_PLAYER_JUMP;
	}
	else if (strcmp(currentType, "AT_PLAYER_MOVE") == 0)
	{
		typeEnum = AT_PLAYER_MOVE;
	}
	
}

void Arthas::ToolSpriteEditLayer::createAniNames(AnimationInfo* aniInfo)
{
	if (aniInfo == nullptr) return;

	for (int i = 0; i < m_CurrentFrameNum; ++i)
	{
		sprintf(aniInfo->animationName[i], "%s%d.png", m_CurrentFileName, i + 1);
	}
}



enum ResourceType
{
	//Sprite Type
	ST_START = 0,
	ST_PLAYER = ST_START,
	ST_BLOCK = ST_START + 1,
	ST_BLOCK_TURRET,
	ST_END,

	//Animation Type
	AT_START = 500,
	AT_PLAYER = AT_START,
	AT_PLAYER_IDLE,
	AT_PLAYER_IDLE_LEFT,
	AT_PLAYER_IDLE_RIGHT,
	AT_PLAYER_MOVE,
	AT_PLAYER_MOVE_LEFT,
	AT_PLAYER_MOVE_RIGHT,
	AT_PLAYER_JUMP,
	AT_PLAYER_JUMP_LEFT,
	AT_PLAYER_JUMP_RIGHT,
	AT_END,
};
