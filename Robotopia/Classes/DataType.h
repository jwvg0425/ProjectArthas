//
//DataType.h
//
//최초 작성자 : 남현욱
//
//enum 및 typedef 등 프로젝트 내에서 쓰이는 각종 고유 정의 타입들을 모아놓는 헤더파일 입니다.
//
//
#pragma once

enum DirectionBit
{
	DIR_NONE = 0,
	DIR_UP = 1,
	DIR_RIGHT =2,
	DIR_DOWN = 4,
	DIR_LEFT = 8,
};

typedef char Directions;
