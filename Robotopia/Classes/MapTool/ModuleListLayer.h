/************************************************************************/
/*
CLASS			: ModuleListLayer
Author			: 남현욱
역할				: 현재 존재하는 모듈 목록을 띄워주는 레이어.
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#include "cocos2d.h"
#include "util.h"
#include <vector>


BEGIN_NS_AT
class ModuleButton;
class ModuleListLayer : public cocos2d::Layer
{
public:
	OVERRIDE bool					init();
	OVERRIDE void					update(float dTime);

	Direction						getSortDir();
	void							initModuleList();
	void							moduleButtonCallback(Ref* sender);
	void							createButtonCallback(Ref* sender);
	void							deleteButtonCallback(Ref* sender);
	void							moduleSizeButtonCallback(Ref* sender);
	void							setSelectedIdx(ModuleData* data);
	int								getSelectedIdx();
	void							resizeData();

	CREATE_FUNC(ModuleListLayer);

private:
	std::vector<ModuleButton*>			m_ModuleList;

	Direction				m_SortDir;
	Direction				m_NextSortDir;
	int						m_SelectedIdx;
};


END_NS_AT