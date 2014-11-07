#include "ToolSpriteListLayer.h"

bool Arthas::ToolSpriteListLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//시작할 때 현재 가지고 있는 sprite 혹은 animation 정보를 m_SpriteList에 채운다



	return true;
}

