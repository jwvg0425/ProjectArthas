#include "BaseComponent.h"

class Electric : public BaseComponent
{
public:
	virtual bool			init();
	virtual void			update(float dTime);
	virtual void			enter();
	virtual void			exit();

	CREATE_FUNC(Electric);
protected:
	cocos2d::PhysicsBody*			m_Body = nullptr;
};

