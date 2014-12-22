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

#define RESOLUTION 0.8f
#define ROOMRECT_SIZE 64

enum AssemblyLayerType
{
	NO_ASSEMBLY_LAYER = 0,
	ASSEMBLY_VIEW,
	SKILL_VIEW,
};

enum ButtonType
{
	NO_BUTTON = 0,
	BUTTON_TITLEMENU,
	BUTTON_OPTION,
	BUTTON_UPGRADE,
	BUTTON_ASSEMBLY_CONFIRM,
	BUTTON_GAMEMENU,
};

enum IconState
{
	NO_ICON = 0,
	ICON_DEFAULT,
	ICON_SELECTED,
	ICON_LOCKED,
/*	ICON_CLICKED,*/
};
