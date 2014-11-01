/************************************************************************/
/*
	CLASS			: DataManager
	Author			: 남현욱
	역할				: 외부 파일에서 Data를 가져오는 작업 및 외부 파일에 Data를 쓰는 것과 관련된 작업을 담당한다.
	최종 수정일자	: 2014-10-29
	최종 수정자		: 
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#define MODULE_FILE_NAME ("data/module.json")
#define RESOURCE_FILE_NAME ("data/resource.json")

BEGIN_NS_AT 

class DataManager
{
public:
	DataManager();
	~DataManager();

	bool							init();
	
	bool							loadModuleData();
	bool							saveModuleData();
	
	bool							loadSpriteCacheData();
	bool							loadResourceData();
	bool							saveResourceData();

	SpriteInfo						getSpriteInfo(ResourceType spriteType);
	AnimationInfo					getAnimationInfo(ResourceType animationType);

	//Stage Data 생성 관련
	const std::vector<StageData>&	getStageData();
	void							initStageData();

	//MapTest용.
	ModuleData						MapTestFunction();
	
private:

	bool						saveData(std::string str, const char* pData);
	bool						getModuleKey(int type, int idx, char* category, OUT char* key);
	bool						getModuleKey(int type, char* category, OUT char* key);
	bool						getResourceKey(char* category, int idx, OUT char* key);


	//생성한 맵 데이터
	std::vector<StageData>		m_StageDatas;


	//파일에서 불러오는 데이터 저장 목록
	std::vector<ModuleData>		m_ModuleDatas[DIR_MAX];
	
	std::vector<AnimationInfo>	m_AnimationInfos;
	std::vector<SpriteInfo>		m_SpriteInfos;
	std::vector<std::string>	m_SpriteCaches;
};

END_NS_AT