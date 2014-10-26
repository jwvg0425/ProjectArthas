#include "LandBlock.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"


bool LandBlock::init()
{
	if (!Object::init())
	{
		return false;
	}

	return true;
}

void LandBlock::setAttribute(int type, cocos2d::Rect size)
{
	PhysicsComponent* physics = new PhysicsComponent(this, size, type, false);
	addComponent(physics);

	for (int j = 0; j < size.size.height / 32; j++)
	{
		for (int i = 0; i < size.size.width / 32; i++)
		{
			SpriteComponent* sprite = new SpriteComponent(this, "block.png", 
												cocos2d::Point(i * 32 - size.size.width / 2 + 16, j * 32 - size.size.height / 2 + 16), 
												false);
			addComponent(sprite);
		}
	}
}

LandBlock::~LandBlock()
{
	removeAllComponent();
}
