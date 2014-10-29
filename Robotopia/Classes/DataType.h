//
//DataType.h
//
//최초 작성자 : 남현욱
//
//enum 및 typedef 등 프로젝트 내에서 쓰이는 각종 고유 정의 타입들을 모아놓는 헤더파일 입니다.
//
//
#pragma once
#include <vector>

BEGIN_NS_AT

enum DirectionBit
{
	DIR_NONE = 0,
	DIR_UP = 1,
	DIR_RIGHT =2,
	DIR_DOWN = 4,
	DIR_LEFT = 8,
	DIR_MAX = 16,
};

typedef char Direction;

enum ObjectType
{
	OT_NONE = 0,

	OT_CHARACTER_START = 1,
	OT_PLAYER = OT_CHARACTER_START,
	OT_CHARACTER_END,
	
	OT_TILE_START = 101,
	OT_BLOCK = OT_TILE_START,
	OT_TILE_END,
};

struct ModuleData
{
	size_t width;
	size_t height;
	std::vector<ObjectType> data;
};

END_NS_AT