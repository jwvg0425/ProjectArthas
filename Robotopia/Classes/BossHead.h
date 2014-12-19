#include "BaseComponent.h"
#define HEAD_RADIUS 128

class BossHead : public BaseComponent
{
public:

	virtual bool			init();
	virtual void			update(float dTime);
	virtual void			enter();
	virtual void			exit();
	virtual void			setEnabled(bool enable);
	virtual bool			onContactBegin(cocos2d::PhysicsContact& contact);
	virtual void			onContactSeparate(cocos2d::PhysicsContact& contact);
	CREATE_FUNC(BossHead);
protected:
	cocos2d::PhysicsBody*			m_Body = nullptr;
};

