/************************************************************************/
/*
CLASS			: PathFinder
Author			: 김연우
역할				: 시작지점 - 목표지점 장애물 넘어서 길 찾아주는 유틸클래스
최종 수정일자	: 2014-12-12
최종 수정자		:
최종 수정사유	:
Comment			: 길찾기가 필요하면 Finder를 생성하고 
				  initFinder를 한다. 길 찾으면 true 못 찾으면 false 리턴하므로 false일때는 길찾기 포기한다.
				  그리고 getPath로 찾은 경로를 얻어온다. vector포인터를 넘긴다.
				  다시 길찾기가 필요하면 같은 인스턴스에 initFinder해서 길찾기를 다시 할 수 있다.
				  예제)
				  if(initFinder(startX, startY, goalX, goalY)
				  {
					getPath(std::vector<cocos2d::Point>* pathes);
				  }
				
/************************************************************************/

#pragma once
#include "util.h"
#define MAX_WIDTH 10
#define MAX_HEIGHT 10

struct Tag
{
	int		m_X = -1;
	int		m_Y = -1;
	int		m_PastCost = 0;
	int		m_FutureCost = 0;

	int	totalCost()
	{
		return m_PastCost + m_FutureCost;
	}
};

class PathFinder
{
public:
	enum Dir
	{
		DIR_UP,
		DIR_DOWN,
		DIR_LEFT,
		DIR_RIGHT,
		DIR_MAX,
	};
	enum CheckResult
	{
		FAIL = 0x00,
		CHECKING = 0x01,
		FIND = 0x02,
	};
	class Compare
	{
	public:
		bool operator() (Tag a, Tag b)
		{
			return a.totalCost() > b.totalCost();
		}
	};

public:
	PathFinder();
	~PathFinder();

	bool			initFinder(int startX, int startY, int goalX, int goalY);
	void			getPath(std::vector<cocos2d::Point>* pathes);

private:
	int				checkPos(cocos2d::Point checkingPos, std::priority_queue<Tag, std::vector<Tag>, Compare>* openTags);
	cocos2d::Point	findNeighbor(int direction);
	bool			findWay(Tag nextCheckTag);

	cocos2d::Size				m_MapSize;
	cocos2d::Point				m_StartPos;
	cocos2d::Point				m_GoalPos;
	Tag							m_CurTag;
	std::vector<int>			m_Map;
	std::hash_map<int, int>		m_CostMap;
	std::stack<cocos2d::Point>	m_Path;

};

