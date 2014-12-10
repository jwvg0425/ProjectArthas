#include "SpriteComponent.h"

class GaugeBarContainer : public SpriteComponent
{
public:
	virtual bool		init();
	virtual void		update(float dTime);

	void				initBarContainer(BaseComponent* target, SpriteType barContainer, SpriteType bar,
										 cocos2d::Point containerPos);
	void				setBarPercent(float percent);

	CREATE_FUNC(GaugeBarContainer);
private:
	cocos2d::Sprite*	m_Bar = nullptr;
	float				m_CurrentPercent = 0.f;
};