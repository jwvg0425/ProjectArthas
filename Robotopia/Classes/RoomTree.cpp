#include "pch.h"
#include "GameManager.h"
#include "DataManager.h"

cocos2d::Point DataManager::RoomTree::getOriginalPosition()
{
	cocos2d::Point retPosition;
	if (m_Parent == nullptr)
	{
		retPosition.x = m_Data->m_X;
		retPosition.y = m_Data->m_Y;
	}
	else
	{
		cocos2d::Point parentPosition = m_Parent->getOriginalPosition();
		retPosition.x = parentPosition.x + m_Data->m_X;
		retPosition.y = parentPosition.y + m_Data->m_Y;
	}
	return retPosition;
}

cocos2d::Point DataManager::RoomTree::getMinPosition()
{
	cocos2d::Point pos = getOriginalPosition();
	cocos2d::Point minPos = pos;

	for (int i = 0; i < m_Children.size(); i++)
	{
		cocos2d::Point childPos = m_Children[i]->getMinPosition();

		if (childPos.x < minPos.x)
		{
			minPos.x = childPos.x;
		}

		if (childPos.y < minPos.y)
		{
			minPos.y = childPos.y;
		}
	}

	return minPos;
}

cocos2d::Point DataManager::RoomTree::getMaxPosition()
{
	cocos2d::Size sizeByModule = cocos2d::Size(m_Data->m_Width / GET_DATA_MANAGER()->getModuleSize().width,
		m_Data->m_Height / GET_DATA_MANAGER()->getModuleSize().height);
	cocos2d::Point pos = getOriginalPosition();
	cocos2d::Point maxPos = cocos2d::Point(pos.x + sizeByModule.width, pos.y + sizeByModule.height);

	for (int i = 0; i < m_Children.size(); i++)
	{
		cocos2d::Point childPos = m_Children[i]->getMaxPosition();

		if (childPos.x > maxPos.x)
		{
			maxPos.x = childPos.x;
		}

		if (childPos.y > maxPos.y)
		{
			maxPos.y = childPos.y;
		}
	}

	return maxPos;
}

int DataManager::RoomTree::getModuleData(cocos2d::Point pos)
{
	cocos2d::Point original = getOriginalPosition();
	cocos2d::Size sizeByModule(m_Data->m_Width / GET_DATA_MANAGER()->getModuleSize().width,
		m_Data->m_Height / GET_DATA_MANAGER()->getModuleSize().height);

	for (int y = original.y; y < original.y + sizeByModule.height; y++)
	{
		for (int x = original.x; x < original.x + sizeByModule.width; x++)
		{
			if (m_Data->m_ModulePlaceData[(y - original.y)*sizeByModule.width + x - original.x] != 0 &&
				y == pos.y && x == pos.x)
			{
				return m_Data->m_ModulePlaceData[(y - original.y)*sizeByModule.width + x - original.x];
			}
		}
	}

	for (int i = 0; i < m_Children.size(); i++)
	{
		int childData = m_Children[i]->getModuleData(pos);

		if (childData != 0)
		{
			return childData;
		}
	}

	return 0;
}

int DataManager::RoomTree::getRoomNumberInPos(cocos2d::Point pos)
{
	cocos2d::Point original = getOriginalPosition();
	cocos2d::Size sizeByModule(m_Data->m_Width / GET_DATA_MANAGER()->getModuleSize().width,
		m_Data->m_Height / GET_DATA_MANAGER()->getModuleSize().height);

	for (int y = original.y; y < original.y + sizeByModule.height; y++)
	{
		for (int x = original.x; x < original.x + sizeByModule.width; x++)
		{
			if (m_Data->m_ModulePlaceData[(y - original.y)*sizeByModule.width + x - original.x] != 0 &&
				y == pos.y && x == pos.x)
			{
				return m_RoomNumber;
			}
		}
	}

	for (int i = 0; i < m_Children.size(); i++)
	{
		int childData = m_Children[i]->getRoomNumberInPos(pos);
		if (childData != 0)
		{
			return childData;
		}
	}

	return 0;
}

void DataManager::RoomTree::setPosToOriginal()
{
	cocos2d::Point original = getOriginalPosition();

	//자식들부터 먼저 포지션 지정해줌(그래야 안 꼬임).
	for (int i = 0; i < m_Children.size(); i++)
	{
		m_Children[i]->setPosToOriginal();
	}

	m_Data->m_X = original.x;
	m_Data->m_Y = original.y;
}

bool DataManager::RoomTree::isConnected(RoomTree* tree)
{
	cocos2d::Size sizeByModule(m_Data->m_Width / GET_DATA_MANAGER()->getModuleSize().width,
		m_Data->m_Height / GET_DATA_MANAGER()->getModuleSize().height);
	cocos2d::Point originalPos = getOriginalPosition();

	for (int y = originalPos.y; y < originalPos.y + sizeByModule.height; y++)
	{
		for (int x = originalPos.x; x < originalPos.x + sizeByModule.width; x++)
		{
			if (m_Data->m_ModulePlaceData[(y - originalPos.y)*sizeByModule.width + x - originalPos.x] == 1)
			{
				if (tree->getModuleData(cocos2d::Point(x - 1, y)) != 0 ||
					tree->getModuleData(cocos2d::Point(x + 1, y)) != 0 ||
					tree->getModuleData(cocos2d::Point(x, y - 1)) != 0 ||
					tree->getModuleData(cocos2d::Point(x, y + 1)) != 0)
				{
					return true;
				}
			}
		}
	}

	//자식들 중 하나라도 연결되어있으면 연결.
	for (int childIdx = 0; childIdx < m_Children.size(); childIdx++)
	{
		if (m_Children[childIdx]->isConnected(tree))
		{
			return true;
		}
	}

	return false;
}

int DataManager::RoomTree::getNodeNum()
{
	int num = 0;

	for (int childIdx = 0; childIdx < m_Children.size(); childIdx++)
	{
		num += m_Children[childIdx]->getNodeNum();
	}

	return num + 1;
}

DataManager::RoomTree::~RoomTree()
{
	for (int childIdx = 0; childIdx < m_Children.size(); childIdx++)
	{
		delete m_Children[childIdx];
	}
}

void DataManager::RoomTree::getCandidatePos(RoomTree* childTree, std::vector<cocos2d::Point>* candidates)
{
	cocos2d::Point minPos = getMinPosition();
	cocos2d::Point maxPos = getMaxPosition();
	int childWidth = childTree->getMaxPosition().x - childTree->getMinPosition().x;
	int childHeight = childTree->getMaxPosition().y - childTree->getMinPosition().y;

	for (int y = minPos.y - childHeight - 2; y <= maxPos.y + 1; y++)
	{
		for (int x = minPos.x - childWidth - 2; x <= maxPos.x + 1; x++)
		{
			childTree->m_Data->m_X = x;
			childTree->m_Data->m_Y = y;
			if (isCandidatePos(childTree) && isConnected(childTree))
			{
				candidates->push_back(cocos2d::Point(x, y));
			}
		}
	}
}

bool DataManager::RoomTree::isCandidatePos(RoomTree* childTree)
{
	cocos2d::Size sizeByModule(m_Data->m_Width / GET_DATA_MANAGER()->getModuleSize().width,
		m_Data->m_Height / GET_DATA_MANAGER()->getModuleSize().height);
	std::vector<int> connectedRoom;
	int remainPortalNum = m_Data->m_Portals.size() - m_Children.size();
	cocos2d::Point originalPos = getOriginalPosition();


	for (int portalIdx = 0; portalIdx < m_Data->m_Portals.size(); portalIdx++)
	{
		cocos2d::Point connectedPos = m_Data->m_Portals[portalIdx].m_Pos;

		connectedPos += originalPos;

		switch (m_Data->m_Portals[portalIdx].m_Dir)
		{
		case DIR_UP:
			connectedPos.y++;
			break;
		case DIR_RIGHT:
			connectedPos.x++;
			break;
		case DIR_DOWN:
			connectedPos.y--;
			break;
		case DIR_LEFT:
			connectedPos.x--;
			break;
		}

		int roomNum = childTree->getRoomNumberInPos(connectedPos);

		if (roomNum == 0)
			continue;

		// 한 방이 두 개 이상의 포탈과 연결되면 안 됨.
		if (std::find(connectedRoom.begin(), connectedRoom.end(), roomNum) != connectedRoom.end())
			return false;

		connectedRoom.push_back(roomNum);
	}

	//아직 남은 포탈이 있는 경우, childTree의 Node 개수와 connectedRoom 개수를 고려해야함.
	if (remainPortalNum > 0)
	{
		int needNum;
		if (childTree->getNodeNum() > remainPortalNum)
		{
			needNum = remainPortalNum;
		}
		else
		{
			needNum = childTree->getNodeNum();
		}

		//연결된 방의 개수가 필요한 방 개수를 만족하지 못하는 경우 후보가 될 수 없다.
		if (connectedRoom.size() != needNum)
		{
			return false;
		}
	}

	for (int y = originalPos.y; y < originalPos.y + sizeByModule.height; y++)
	{
		for (int x = originalPos.x; x < originalPos.x + sizeByModule.width; x++)
		{
			//모듈이 있는 위치만 고려
			if (m_Data->m_ModulePlaceData[(y - originalPos.y)*sizeByModule.width + x - originalPos.x] == 0)
			{
				continue;
			}

			//포탈이 있는 경우, 포탈을 통해 연결되지 않은 방과 붙어 있으면 안 된다.
			if (m_Data->m_Portals.size() != 0)
			{
				int leftNum = childTree->getRoomNumberInPos(cocos2d::Point(x - 1, y));
				int upNum = childTree->getRoomNumberInPos(cocos2d::Point(x, y + 1));
				int rightNum = childTree->getRoomNumberInPos(cocos2d::Point(x + 1, y));
				int downNum = childTree->getRoomNumberInPos(cocos2d::Point(x, y - 1));
				auto begin = connectedRoom.begin();
				auto end = connectedRoom.end();

				if ((leftNum != 0 && std::find(begin, end, leftNum) == end) ||
					(upNum != 0 && std::find(begin, end, upNum) == end) ||
					(rightNum != 0 && std::find(begin, end, rightNum) == end) ||
					(downNum != 0 && std::find(begin, end, downNum) == end))
				{
					return false;
				}
			}

			if (childTree->getModuleData(cocos2d::Point(x, y)) != 0)
			{
				return false;
			}

		}
	}

	//자식에 대한 처리
	for (int i = 0; i < m_Children.size(); i++)
	{
		if (!m_Children[i]->isCandidatePos(childTree))
		{
			return false;
		}
	}

	return true;
}


bool DataManager::RoomTree::mergeTree(RoomTree* childTree)
{
	std::vector<cocos2d::Point> candidates;

	getCandidatePos(childTree, &candidates);

	if (candidates.empty())
	{
		return false;
	}

	int targetIdx = rand() % candidates.size();

	childTree->m_Data->m_X = candidates[targetIdx].x;
	childTree->m_Data->m_Y = candidates[targetIdx].y;

	m_Children.push_back(childTree);
	childTree->m_Parent = this;

	return true;
}

void DataManager::RoomTree::mergeTrees(std::vector<RoomTree*> childTrees)
{
	for (int i = 0; i < childTrees.size(); i++)
	{
		//merge에 실패하면 다시 처음부터 시도. 
		if (!mergeTree(childTrees[i]))
		{
			m_Children.clear();
			for (int j = 0; j < i; j++)
			{
				childTrees[j]->m_Parent = nullptr;
				childTrees[j]->m_Data->m_X = 0;
				childTrees[j]->m_Data->m_Y = 0;
			}
		}
	}
}
