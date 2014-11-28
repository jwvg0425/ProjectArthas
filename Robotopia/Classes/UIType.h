/************************************************************************/
/*
CLASS			: UIType
Author			: 우재우
역할			: UI에 필요한 enum 관리
최종 수정일자	: 2014-11-22
최종 수정자		: 우재우
최종 수정사유	: 신규(버튼 타입)
Comment			:
*/
/************************************************************************/


#pragma once

enum AssemblyLayerType
{
	NO_ASSEMBLY_LAYER = 0,
	ASSEMBLY_VIEW,
	SKILL_VIEW,
};

enum ButtonType
{
	NO_BUTTON = 0,
	TITLEMENU_BUTTON,
	OPTION_BUTTON,
	ASSEMBLY_BUTTON,
	GAMEMENU_BUTTON,
};

enum IconType
{
	NO_ICON = 0,
	ASSEMBLY_ICON,
	CHARWIN_ICON,
};

enum LabelType
{
	NO_LABEL = 0,
	ASSEMBLY_LABEL,
	CHARWIN_LABEL,
};