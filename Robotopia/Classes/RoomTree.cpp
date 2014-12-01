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
