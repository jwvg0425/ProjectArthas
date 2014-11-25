/************************************************************************/
/*
CLASS				: ResourceManager
Author				: 우재우
역할				: Sprite 및 Animation 요청 시 생성 후 전달
최종 수정일자		: 2014-10-31
최종 수정자			: 우재우
최종 수정사유		: 리소스 매니저 생성
Comment				: 리소스 재생성 문제(맵 사용) 그대로 둘 것인지 결정 못 했음. 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "cocos2d.h"



class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	bool					init();
	cocos2d::Animation*		createAnimation(ResourceType type);
	cocos2d::Sprite*		createSprite(ResourceType type);

private:
// 	std::map <ResourceType, cocos2d::Sprite*>		m_Sprites;
// 	std::map <ResourceType, cocos2d::Animation*>	m_Animations;
	
};

