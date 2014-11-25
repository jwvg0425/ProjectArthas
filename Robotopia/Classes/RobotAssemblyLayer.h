/************************************************************************/
/*
CLASS			: RobotAssemblyLayer
Author			: 우재우
역할			: GameScene 시작 시 로봇 조립창을 보여줌
최종 수정일자	: 2014-11-23
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "GameSceneUILayer.h"

class RobotAssemblyLayer : public GameSceneUILayer
{
public:
	RobotAssemblyLayer();
	~RobotAssemblyLayer();

	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);

	CREATE_FUNC(RobotAssemblyLayer);
private:

};