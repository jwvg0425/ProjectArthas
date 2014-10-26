#include "Object.h"

class LandBlock : public Object
{
public:
	virtual bool init();

	void setAttribute(int type, cocos2d::Rect size);

	~LandBlock();

	CREATE_FUNC(LandBlock);
protected:
};