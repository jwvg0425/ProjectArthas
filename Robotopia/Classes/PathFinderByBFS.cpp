#include "pch.h"
#include "PathFinderByBFS.h"
#include "GameManager.h"
#include "DataManager.h"
#include "StageManager.h"


PathFinderByBFS::PathFinderByBFS()
{
	initMapData();
}

PathFinderByBFS::~PathFinderByBFS()
{

}

bool PathFinderByBFS::getPath(int startX, int startY, int goalX, int goalY, std::vector<cocos2d::Point>* pathQueue)
{
	if (pathQueue == nullptr)
	{
		return false;
	}

	pathQueue->clear();

	BFS(startX, startY, goalX, goalY);
	
	return getPathList(getIdx(startX, startY), getIdx(goalX, goalY), pathQueue);
}

void PathFinderByBFS::initMapData()
{
	m_RoomData = GET_STAGE_MANAGER()->getCurrentRoomData();

	m_Vertices.clear();
	m_Width = m_RoomData.m_Width;
	m_Height = m_RoomData.m_Height;
}

void PathFinderByBFS::BFS(int startX, int startY, int goalX, int goalY)
{
	//이전 내용 초기화
	m_Vertices.clear();


	Vertex v(getIdx(startX, startY), -1);
	std::queue<Vertex*> vertexQueue;

	m_Vertices[getIdx(startX, startY)] = v;

	vertexQueue.push(&m_Vertices[getIdx(startX, startY)]);

	while (!vertexQueue.empty())
	{
		Vertex* v = vertexQueue.front();
		vertexQueue.pop();

		int x = 0, y = 0;
		int nextX = 0, nextY = 0;

		getCoord(v->m_Data, &x, &y);

		if (x == goalX && y == goalY)
		{
			break;
		}

		pushCandidateVertex(x - 1, y, v->m_Data, &vertexQueue);
		pushCandidateVertex(x + 1, y, v->m_Data, &vertexQueue);
		pushCandidateVertex(x, y - 1, v->m_Data, &vertexQueue);
		pushCandidateVertex(x, y + 1, v->m_Data, &vertexQueue);
	}
}

int PathFinderByBFS::getIdx(int x, int y)
{
	if (x < 0 || x >= m_Width)
		return -1;
	
	if (y < 0 || y >= m_Height)
		return -1;

	return y*m_Width + x;
}

void PathFinderByBFS::getCoord(int idx, int* x, int* y)
{
	*x = idx % m_Width;
	*y = idx / m_Width;
}

void PathFinderByBFS::pushCandidateVertex(int nextX, int nextY, int predecessor, std::queue<Vertex*>* candidateQueue)
{
	if (getIdx(nextX, nextY) != -1 && m_RoomData.m_Data[getIdx(nextX, nextY)] != OT_BLOCK)
	{
		//이미 방문한 경우 체크
		if (m_Vertices.find(getIdx(nextX, nextY)) != m_Vertices.end())
		{
			return;
		}

		m_Vertices[getIdx(nextX, nextY)] = Vertex(getIdx(nextX, nextY), predecessor);
		candidateQueue->push(&m_Vertices[getIdx(nextX, nextY)]);
	}
}

bool PathFinderByBFS::getPathList(int startIdx, int goalIdx, std::vector<cocos2d::Point>* pathQueue)
{
	int x, y;

	getCoord(goalIdx, &x, &y);

	//base
	if (startIdx == goalIdx)
	{
		pathQueue->push_back(cocos2d::Point(x, y));
		return true;
	}

	//recursive
	
	//경로가 없는 경우
	if (m_Vertices.find(goalIdx) == m_Vertices.end() ||
		m_Vertices[goalIdx].m_Predecessor == -1)
	{
		return false;
	}
	else
	{
		//경로 있는 경우 predecessor까지의 경로를 쭉 집어넣고 자기 위치 집어넣음.
		if (getPathList(startIdx, m_Vertices[goalIdx].m_Predecessor, pathQueue))
		{
			pathQueue->push_back(cocos2d::Point(x, y));
			return true;
		}
		else
		{
			return false;
		}
	}
}

PathFinderByBFS::Vertex::Vertex()
{

}

PathFinderByBFS::Vertex::Vertex(int data, int predecessor) : m_Data(data), m_Predecessor(predecessor)
{

}

PathFinderByBFS::Vertex::~Vertex()
{

}
