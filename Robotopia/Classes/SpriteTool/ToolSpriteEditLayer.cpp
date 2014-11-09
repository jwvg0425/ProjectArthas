#include "ToolScene.h"
#include "SpriteTool/ToolSpriteEditLayer.h"
#include "GameManager.h"
#include "DataManager.h"

#define BOXWIDTH 170
#define BOXHEIGHT 60
#define WINSIZE_WIDTH 1280
#define WINSIZE_HEIGHT 640
#define FONTSIZE 30
#define LABELFONTSIZE 30
#define LABELWIDTH 200
#define LABELHEIGHT 100

Arthas::ToolSpriteEditLayer::~ToolSpriteEditLayer()
{
	GET_DATA_MANAGER()->getSpriteInfos() = m_SpriteInfos;
	GET_DATA_MANAGER()->getAnimationInfos() = m_AnimationInfos;
	GET_DATA_MANAGER()->saveResourceData();
}

bool Arthas::ToolSpriteEditLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setName("Edit");
	m_EditBoxs.reserve(10);
	m_SpriteInfos.reserve(20);
	m_AnimationInfos.reserve(50);
	m_IsATState = true;
	m_CurrentSTInfoIdx = -1;
	m_CurrentATInfoIdx = -1;

	//현재 가지고 있는 info값 모두 저장
	initSpriteInfo();
	initAnimationInfo();
	//저장된 Info값을 모두 Label로 만든 다음에 보여줄 곳을 지정한다
	createLabel("Type");
	createLabel("Delay");
	createLabel("FrameNum");
	assignLabels();
	//목록 버튼 만들기
	createListButton("ST_LIST", false);
	createListButton("AT_LIST", true);
	createAllMenuButton();
	assignMenuButtons();

	createEditBox("Type", FONTSIZE, 15, TYPE);
	createEditBox("Delay", FONTSIZE, 5, DELAY);
	createEditBox("FrameNum", FONTSIZE, 4, FRAMENUM);
	createEditBox("FileName", FONTSIZE - 10, 30, FILENAME, 27);
	createEditBox("Save", FONTSIZE, 1, SAVE);
	assignEditBox();
	assignFileNameBox();

	return true;
}

void Arthas::ToolSpriteEditLayer::createEditBox(char* boxTitle, int fontSize, int maxLength, InfoOrder tag)
{
	if (boxTitle == nullptr) return;

	auto editBox = cocos2d::extension::EditBox::
		create(cocos2d::Size(BOXWIDTH, BOXHEIGHT),
		cocos2d::extension::Scale9Sprite::create("SpriteToolEditBox.png"));
	editBox->setPlaceHolder(boxTitle);
	editBox->setFont("Corbel", fontSize);
	editBox->setTag(tag);
	editBox->setMaxLength(maxLength);
	editBox->setDelegate(this);
	this->addChild(editBox);

	m_EditBoxs.push_back(editBox);
}

void Arthas::ToolSpriteEditLayer::createEditBox(char* boxTitle, int fontSize, int maxLength, InfoOrder tag, int boxNum)
{
	if (boxTitle == nullptr) return;

	char titleBuffer[MAX_CHAR];

	for (int i = 0; i < boxNum; ++i)
	{
		auto editBox = cocos2d::extension::EditBox::
			create(cocos2d::Size(BOXWIDTH, BOXHEIGHT / 3),
			cocos2d::extension::Scale9Sprite::create("SpriteToolEditBox.png"));
		sprintf(titleBuffer, "%s%d", boxTitle, i+1);
		editBox->setPlaceHolder(titleBuffer);
		editBox->setFont("Corbel", fontSize);
		editBox->setTag(tag);
		editBox->setZOrder(i);
		editBox->setMaxLength(maxLength);
		editBox->setColor(cocos2d::Color3B::YELLOW);
		editBox->setVisible(true);
		editBox->setDelegate(this);
		
		this->addChild(editBox);
		m_FileNameBoxs.push_back(editBox);
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
	int changedType = 0;
	float changedDelay = 0.0f;
	int changedFrameNum = 0;

	if (m_IsATState && m_CurrentATInfoIdx != -1)
	{
		switch (editBox->getTag())
		{
		case TYPE:
			changedType = atoi(editBox->getText());
			m_AnimationInfos[m_CurrentATInfoIdx].type = 
				(ResourceType) changedType;
			break;
		case DELAY:
			changedDelay = atof(editBox->getText());
			m_AnimationInfos[m_CurrentATInfoIdx].delay =
				changedDelay;
			break;
		case FRAMENUM:
			changedFrameNum = atoi(editBox->getText());
			m_AnimationInfos[m_CurrentATInfoIdx].frameNum =
				changedFrameNum;
			break;
		case FILENAME:
			strcpy_s(m_AnimationInfos[m_CurrentATInfoIdx].animationName[editBox->getZOrder()],
				editBox->getText());
			break;
		case SAVE:
			GET_DATA_MANAGER()->getSpriteInfos() = m_SpriteInfos;
			GET_DATA_MANAGER()->getAnimationInfos() = m_AnimationInfos;
			GET_DATA_MANAGER()->saveResourceData();
			break;
		default:
			break;
		}
	}
	else if (!m_IsATState && m_CurrentSTInfoIdx != -1)
	{
		switch (editBox->getTag())
		{
		case TYPE:
			changedType = atoi(editBox->getText());
			m_SpriteInfos[m_CurrentSTInfoIdx].type =
				(ResourceType)changedType;
			break;
		case FILENAME:
			strcpy_s(m_SpriteInfos[m_CurrentSTInfoIdx].spriteName,
					 editBox->getText());
			break;
		default:
			break;
		}

	}

}

void Arthas::ToolSpriteEditLayer::update(float dTime)
{
}

void Arthas::ToolSpriteEditLayer::initAnimationInfo()
{	
	m_AnimationInfos = GET_DATA_MANAGER()->getAnimationInfos();
}

void Arthas::ToolSpriteEditLayer::initSpriteInfo()
{
	m_SpriteInfos = GET_DATA_MANAGER()->getSpriteInfos();
}

void Arthas::ToolSpriteEditLayer::createMenuButton(ResourceType type, bool isAT)
{
	//std::string title = createButtonTitle(type);
	char title[30];
	memset(title, NULL, sizeof(title)*sizeof(char));
	sprintf(title, "%d", type);

	if (isAT)
	{
		auto playButton = cocos2d::MenuItemFont::create(title, CC_CALLBACK_1(ToolSpriteEditLayer::ATMenuButtonCallback, this));
		auto menu = cocos2d::Menu::create(playButton, NULL);
		menu->setScale(0.8f);
		menu->setVisible(false);
		playButton->setTag(type);
		this->addChild(menu);
		m_ATMenuButtons.push_back(menu);
	}
	else
	{
		auto playButton = cocos2d::MenuItemFont::create(title, CC_CALLBACK_1(ToolSpriteEditLayer::STMenuButtonCallback, this));
		auto menu = cocos2d::Menu::create(playButton, NULL);
		menu->setScale(0.8f);
		menu->setVisible(false);
		playButton->setTag(type);
		this->addChild(menu);
		m_STMenuButtons.push_back(menu);
	}

}


void Arthas::ToolSpriteEditLayer::createListButton(std::string string, bool isAT)
{
	cocos2d::Point pos;
	pos.x = 100;
	pos.y = WINSIZE_HEIGHT * 0.92f;
	cocos2d::Menu* menu;
	if (isAT)
	{
		auto playButton = cocos2d::MenuItemFont::create(string, CC_CALLBACK_1(ToolSpriteEditLayer::ATListShow, this));
		menu = cocos2d::Menu::create(playButton, NULL);
		menu->setPosition(pos);
	}
	else
	{
		auto playButton = cocos2d::MenuItemFont::create(string, CC_CALLBACK_1(ToolSpriteEditLayer::STListShow, this));
		menu = cocos2d::Menu::create(playButton, NULL);
		pos.y -= BOXHEIGHT;
		menu->setPosition(pos);
	}

	this->addChild(menu);
}

std::string Arthas::ToolSpriteEditLayer::createButtonTitle(ResourceType type)
{
	std::string tmpString;

	switch (type)
	{
	case Arthas::ST_PLAYER:
		tmpString = "ST_PLAYER";
		break;
	case Arthas::ST_BLOCK:
		tmpString = "ST_BLOCK";
		break;
	case Arthas::ST_BLOCK_TURRET:
		tmpString = "ST_BLOCK_TURRET";
		break;
	case Arthas::ST_END:
		tmpString = "ST_END";
		break;
	case Arthas::AT_PLAYER:
		tmpString = "AT_PLAYER";
		break;
	case Arthas::AT_PLAYER_IDLE:
		tmpString = "AT_PLAYER_IDLE";
		break;
	case Arthas::AT_PLAYER_MOVE:
		tmpString = "AT_PLAYER_MOVE";
		break;
	case Arthas::AT_PLAYER_JUMP:
		tmpString = "AT_PLAYER_JUMP";
		break;
	case Arthas::AT_END:
		tmpString = "AT_START";
		break;
	default:
		tmpString = "UNKNOWN";
		break;
	}

	return tmpString;
}

void Arthas::ToolSpriteEditLayer::ATMenuButtonCallback(cocos2d::Ref* sender)
{
	//가지고 있는 값들을 보여주고 싶다. 
	//이제 메뉴 콜백이다. 
	initFileNameBox();
	m_IsATState = true;
	auto button = (cocos2d::MenuItemFont*) sender;
	char typeBuf[50] = { 0, };
	char frameNumBuf[50] = { 0, };
	char delayBuf[50] = { 0, };
	
	AnimationInfo tmpAniInfo;
	tmpAniInfo.type = AT_END;
	tmpAniInfo.frameNum = 0;
	tmpAniInfo.delay = 0;
	
	memset(tmpAniInfo.animationName, NULL, sizeof(char) * MAX_FRAME * MAX_CHAR);
	
	for (ResourceType typeEnum = AT_START; typeEnum < AT_END; typeEnum = ResourceType(typeEnum + 1))
	{
		if (button->getTag() == typeEnum)
		{
			m_CurrentATInfoIdx = typeEnum - AT_START;
		}
	}

	if (m_CurrentATInfoIdx < m_AnimationInfos.size())
	{
		tmpAniInfo = m_AnimationInfos[m_CurrentATInfoIdx];
	}
	
	//for (unsigned int aniIdx = 0; aniIdx < m_AnimationInfos.size(); ++aniIdx)
	//{
	//	//이건 무조건 있어야돼
	//	if (button->getTag() == m_AnimationInfos[aniIdx].type)
	//	{
	//		tmpAniInfo = m_AnimationInfos[aniIdx];
	//		m_CurrentATInfoIdx = aniIdx;
	//		break;
	//	}
	//}
	
	//enum 값은 있는데 데이터에는 Enum조차 저장하지 않은 경우와
	//enum 값에 맞는 데이터 타입이 존재하는 경우로 나눴음
	if (tmpAniInfo.type == AT_END)
	{
		strcpy_s(typeBuf, "Undecided");
	}
	else
	{
		_itoa(tmpAniInfo.type, typeBuf, 10);
	}

	if (tmpAniInfo.frameNum == 0)
	{
		strcpy_s(frameNumBuf, "Undecided");
	}
	else
	{
		_itoa(tmpAniInfo.frameNum, frameNumBuf, 10);
	}

	if (tmpAniInfo.delay == 0)
	{
		strcpy_s(delayBuf, "Undecided");
	}
	else
	{
		sprintf(delayBuf, "%f", tmpAniInfo.delay);
	}
	
	//에딧 박스(화면상 가운데 위쪽)에 내용채워넣기
	for (auto pEditBox : m_EditBoxs)
	{
		if (pEditBox->getTag() == TYPE)
		{
			pEditBox->setText(typeBuf);
		}
		else if (pEditBox->getTag() == DELAY)
		{
			pEditBox->setText(delayBuf);
		}
		else if(pEditBox->getTag() == FRAMENUM)
		{
			pEditBox->setText(frameNumBuf);
		}
	}

	//화면상 정 가운데 가장 많은 파일네임 박스에 내용채워넣기
	for (int i = 0; i < tmpAniInfo.frameNum; ++i)
	{
		m_FileNameBoxs[i]->setText(tmpAniInfo.animationName[i]);
	}
}


void Arthas::ToolSpriteEditLayer::STMenuButtonCallback(cocos2d::Ref* sender)
{
	initFileNameBox();
	m_IsATState = false;
	SpriteInfo tmpSprInfo;
	tmpSprInfo.type = ST_END;
	memset(tmpSprInfo.spriteName, 0, sizeof(char)* sizeof(tmpSprInfo.spriteName));
	
	auto button = (cocos2d::MenuItemFont*) sender;
	char buf[30];
	memset(buf, NULL, sizeof(char)* 30);
	char typeBuf[30];
	memset(typeBuf, NULL, sizeof(char)* 30);

	for (ResourceType typeEnum = ST_START; typeEnum < ST_END; typeEnum = ResourceType(typeEnum + 1))
	{
		if (button->getTag() == typeEnum)
		{
			m_CurrentSTInfoIdx = typeEnum - ST_START;
			break;
		}
	}

	if (m_CurrentSTInfoIdx < m_SpriteInfos.size())
	{
		tmpSprInfo = m_SpriteInfos[m_CurrentSTInfoIdx];
	}


	/*for (unsigned int i = 0; i < m_SpriteInfos.size(); ++i)
	{
		if (button->getTag() == m_SpriteInfos[i].type)
		{
			tmpSprInfo = m_SpriteInfos[i];
			m_EditBoxs[TYPE]->setText(_itoa(m_SpriteInfos[i].type, buf, 10));
			m_CurrentSTInfoIdx = i;
			break;
		}
	}*/

	
	//m_EditBoxs[TYPE]->setText(_itoa(typeEnum, buf, 10));

	

	if (tmpSprInfo.type == ST_END)
	{
		strcpy_s(typeBuf, "Undecided");
	}
	else
	{
		_itoa(tmpSprInfo.type, typeBuf, 10);
	}

	for (auto pEditBox : m_EditBoxs)
	{
		if (pEditBox->getTag() == TYPE)
		{
			pEditBox->setText(typeBuf);
		}
	}
	
	if (tmpSprInfo.spriteName[0] != '\0')
	{
		m_FileNameBoxs[0]->setText(tmpSprInfo.spriteName);
	}
}



void Arthas::ToolSpriteEditLayer::ATListShow(cocos2d::Ref* sender)
{
	for (auto pSTButton : m_STMenuButtons)
	{
		pSTButton->setVisible(false);
	}

	for (auto pATButton : m_ATMenuButtons)
	{
		pATButton->setVisible(true);
	}
}

void Arthas::ToolSpriteEditLayer::STListShow(cocos2d::Ref* sender)
{
	for (auto pATButton : m_ATMenuButtons)
	{
		pATButton->setVisible(false);
	}

	for (auto pSTButton : m_STMenuButtons)
	{
		pSTButton->setVisible(true);
	}
}



void Arthas::ToolSpriteEditLayer::createLabel(std::string title)
{
	auto label = cocos2d::Label::createWithSystemFont(title, "Corbel", LABELFONTSIZE,
													  cocos2d::Size(LABELWIDTH, LABELHEIGHT),
													  cocos2d::TextHAlignment::CENTER);
	m_Labels.push_back(label);
	this->addChild(label);
}

void Arthas::ToolSpriteEditLayer::assignLabels()
{
	cocos2d::Point pos;
	pos.x = WINSIZE_WIDTH* 0.3f;
	pos.y = WINSIZE_HEIGHT*0.92f;
	for (auto pLabel:m_Labels)
	{
		pLabel->setPosition(pos);
		pos.x += LABELWIDTH * 1.2;
	}
}

void Arthas::ToolSpriteEditLayer::assignEditBox()
{
	if (m_EditBoxs.empty()) return;

	cocos2d::Point pos;
	pos.x = WINSIZE_WIDTH * 0.35f;
	pos.y = WINSIZE_HEIGHT * 0.88f;

	for (auto pEditBox : m_EditBoxs)
	{
		pEditBox->setPosition(pos);
		pos.x += BOXWIDTH * 1.3f;
	}
}

void Arthas::ToolSpriteEditLayer::assignFileNameBox()
{

	cocos2d::Point pos;
	pos.x = WINSIZE_WIDTH* 0.3f;
	pos.y = WINSIZE_HEIGHT*0.78f + 60;

	for (unsigned int i = 0; i < m_FileNameBoxs.size(); ++i)
	{
		if (i != 0 && (i % 9) == 0)
		{
			pos.x += BOXWIDTH * 1.2f;
			pos.y = WINSIZE_HEIGHT*0.80f;
		}
		else
		{
			pos.y -= 60;
		}
		m_FileNameBoxs[i]->setPosition(pos);
	}
	
}

void Arthas::ToolSpriteEditLayer::createAllMenuButton()
{
	for (ResourceType typeEnum = AT_START; typeEnum < AT_END; typeEnum = ResourceType(typeEnum + 1))
	{
		createMenuButton(typeEnum, true);
	}

	for (ResourceType typeEnum = ST_START; typeEnum < ST_END; typeEnum = ResourceType(typeEnum + 1))
	{
		createMenuButton(typeEnum, false);
	}
}

void Arthas::ToolSpriteEditLayer::assignMenuButtons()
{
	cocos2d::Point pos;

	pos.x = 0;
	pos.y = WINSIZE_HEIGHT * 0.6f;

	for (auto pATButton : m_ATMenuButtons)
	{
		pATButton->setPosition(pos);
		pos.y -= BOXHEIGHT * 0.6f;
	}

	pos.y = WINSIZE_HEIGHT * 0.6f;
	for (auto pSTButton : m_STMenuButtons)
	{
		pSTButton->setPosition(pos);
		pos.y -= BOXHEIGHT * 0.6f;
	}
}

void Arthas::ToolSpriteEditLayer::initFileNameBox()
{
	char buf[30];
	for (unsigned int i = 0; i < m_FileNameBoxs.size(); ++i)
	{
		sprintf(buf, "FileName%d", i+1);
		m_FileNameBoxs[i]->setText(buf);
	}
}

Arthas::AnimationInfo Arthas::ToolSpriteEditLayer::getAniMationInfo() const
{
	return m_AnimationInfos[m_CurrentATInfoIdx];
}

Arthas::SpriteInfo Arthas::ToolSpriteEditLayer::getSprInfo() const
{
	return m_SpriteInfos[m_CurrentSTInfoIdx];
}














