#include "pch.h"
#include "PathFinder.h"
#include "GameManager.h"
#include "DataManager.h"
#include "StageManager.h"

PathFinder::PathFinder()
{
	auto roomData = GET_STAGE_MANAGER()->getCurrentRoomData();
	m_MapSize.width = roomData.m_Width;
	m_MapSize.height = roomData.m_Height;
	m_Map = roomData.m_Data;
}


PathFinder::~PathFinder()
{
}

bool PathFinder::initFinder(int startX, int startY, int goalX, int goalY)
{
	m_CostMap.clear();

	m_StartPos.x = startX;
	m_StartPos.y = startY;

	m_GoalPos.x = goalX;
	m_GoalPos.y = goalY;

	Tag firstTag;
	firstTag.m_X = m_StartPos.x;
	firstTag.m_Y = m_StartPos.y;
	firstTag.m_PastCost = 0;
	firstTag.m_FutureCost = abs(goalX - startX) + abs(goalY - startY);
	
	m_CostMap[m_StartPos.x + m_StartPos.y * m_MapSize.width] = firstTag.totalCost();

	return findWay(firstTag);
}

int PathFinder::checkPos(cocos2d::Point checkingPos, std::priority_queue<Tag, std::vector<Tag>, Compare>* openTags)
{
	CheckResult ret;
	int checkingIdx = checkingPos.x + checkingPos.y * m_MapSize.width;
	if(checkingPos.x >= m_MapSize.width || checkingPos.y >= m_MapSize.height
	   || checkingPos.x < 0 || checkingPos.y < 0)
	{
		ret = FAIL;
		return ret;
	}
	else if(checkingPos.y == m_GoalPos.x && checkingPos.y == m_GoalPos.y)
	{
		ret = FIND;
		return ret;
	}
	else if (m_Map[checkingIdx] == OT_BLOCK || m_Map[checkingIdx] == OT_PORTAL)
	{
		ret = FAIL;
		return ret;
	}

	Tag checkingTag;
	checkingTag.m_X = checkingPos.x;
	checkingTag.m_Y = checkingPos.y;
	checkingTag.m_PastCost = m_CurTag.m_PastCost + 1;
	checkingTag.m_FutureCost = abs(m_GoalPos.x - checkingPos.x) + abs(m_GoalPos.y - checkingPos.y);

	auto checkedTagIter = m_CostMap.find(checkingIdx);
	//태그맵에 아직 처리안됨
	if(checkedTagIter == m_CostMap.end())
	{
		m_CostMap[checkingIdx] = checkingTag.totalCost();
		openTags->push(checkingTag);
		ret = CHECKING;
		return ret;
	}

	int checkedCost = ( *checkedTagIter ).second;
	//예전 코스트와 이번 코스트 비교/처리
	if(checkedCost > checkingTag.totalCost())
	{
		m_CostMap[checkingIdx] = checkingTag.totalCost();
		openTags->push(checkingTag);
		ret = CHECKING;
		return ret;
	}
	else
	{
		ret = FAIL;
		return ret;
	}
}

cocos2d::Point PathFinder::findNeighbor(int direction)
{
	cocos2d::Point neighborPos;
	int addX = 0, addY = 0;
	switch(direction)
	{
		case DIR_UP:
			addY = 1;
			break;
		case DIR_DOWN:
			addY = -1;
			break;
		case DIR_LEFT:
			addX = -1;
			break;
		case DIR_RIGHT:
			addX = 1;
			break;
	}
	neighborPos.x = m_CurTag.m_X + addX;
	neighborPos.y = m_CurTag.m_Y + addY;
	return neighborPos;
}

bool PathFinder::findWay(Tag nextCheckTag)
{
	std::priority_queue<Tag, std::vector<Tag>, Compare> openTags;
	int checkResult = FAIL;
	cocos2d::Point checkingPos;
	m_CurTag = nextCheckTag;

	for(int dir = DIR_UP; dir < DIR_MAX; ++dir)
	{
		checkingPos = findNeighbor(dir);
		checkResult |= checkPos(checkingPos, &openTags);
		if(checkResult & FIND)
		{
			return true;
		}
	}

	if(checkResult & CHECKING)
	{
		while(!openTags.empty())
		{
			Tag nextTag = openTags.top();
			if(findWay(nextTag))
			{
				m_Path.push(cocos2d::Point(nextTag.m_X, nextTag.m_Y));
				return true;
			}
			openTags.pop();
		}
	}
	return false;
}

void PathFinder::getPath(std::vector<cocos2d::Point>* pathes)
{
	cocos2d::Point curPos;
	pathes->clear();
	while(!m_Path.empty())
	{
		curPos = m_Path.top();
		pathes->push_back(curPos);
		m_Path.pop();
	}
}
