#pragma once
#include "DataInfo.h"


class PathFinderByBFS
{
public:
	PathFinderByBFS();
	~PathFinderByBFS();
	bool getPath(int startX, int startY, int goalX, int goalY, std::vector<cocos2d::Point>* pathQueue);
	void initMapData();

private:
	struct Vertex
	{
		Vertex();
		Vertex(int data, int predecessor);
		~Vertex();
		int		m_Data = 0;
		int		m_Predecessor = -1;
	};

	void BFS(int startX, int startY, int goalX, int goalY);
	bool getPathList(int startIdx, int goalIdx, std::vector<cocos2d::Point>* pathQueue);
	int getIdx(int x, int y);
	void getCoord(int idx, int* x, int* y);
	void pushCandidateVertex(int nextX, int nextY, int predecessor, std::queue<Vertex*>* candidateQueue);

	std::hash_map<int, Vertex>	m_Vertices;
	RoomData					m_RoomData;
	int							m_Width = 0, m_Height = 0;
};