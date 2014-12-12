/************************************************************************/
/*
CLASS			: GaugeBarContainer
Author			: 김연우
역할				: 퍼센트에 따라서 게이지가 차는 바 컨테이너 클래스
최종 수정일자	: 2014-12-12
최종 수정자		:
최종 수정사유	:
Comment			: initBarContainer로 초기화 해주시고, setBarPercent으로 퍼센트 조절가능합니다.
/************************************************************************/

#include "SpriteComponent.h"

class GaugeBarContainer : public SpriteComponent
{
public:
	virtual bool		init();
	virtual void		update(float dTime);

	void				initBarContainer(BaseComponent* target, SpriteType barContainer, SpriteType bar,
										 cocos2d::Point containerPos);
	void				setBarPercent(float percent);
	float				getBarPercent();

	CREATE_FUNC(GaugeBarContainer);
private:
	cocos2d::Sprite*	m_Bar = nullptr;
	float				m_CurrentPercent = 0.f;
};