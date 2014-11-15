/************************************************************************/
/*
CLASS			: ModuleEditLayer
Author			: 남현욱
역할				: 모듈데이터 수정하는 레이어.
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#include "cocos2d.h"
#include "util.h"
#include <map>


BEGIN_NS_AT
class Component;
class ComponentButton;
class ModuleEditLayer : public cocos2d::Layer
{
public:
	OVERRIDE bool					init();
	cocos2d::DrawNode*				makeCell(float x, float y);
	void							update(float dTime);
	void							initPrintedModule();
	void							initConnectedModule();
	void							initBoard();
	
	CREATE_FUNC(ModuleEditLayer);
	void							setSelectedIdx(cocos2d::Sprite* sprite);
	void							onMouseDown(cocos2d::Event* event);
	void							onMouseMove(cocos2d::Event* event);
	void							onMouseUp(cocos2d::Event* event);
private:
	void								printConnectedModules(Direction dir);
	void								printLeftConnectedModule(ModuleData module);
	void								printUpConnectedModule(ModuleData module);
	void								printRightConnectedModule(ModuleData module);
	void								printDownConnectedModule(ModuleData module);
	void								printModuleSprite(ModuleData module, int x, int y, float printX, float printY);

	int									m_PrevSelectedModuleIdx;
	bool								m_IsMouseDown;
	int									m_SelectedComponentIdx;
	std::vector<cocos2d::DrawNode*>		m_Cells;
	std::vector<cocos2d::Sprite*>		m_ConnectedModuleSprites;
	std::vector<ComponentButton*>		m_ComponentList;
	std::map<int, cocos2d::Sprite*>		m_ModuleSprites;
};


END_NS_AT