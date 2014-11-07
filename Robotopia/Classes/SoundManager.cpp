#include "pch.h"
#include "SoundManager.h"


Arthas::SoundManager::SoundManager()
{
}

Arthas::SoundManager::~SoundManager()
{
}

bool Arthas::SoundManager::init()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&m_Systems);
	errCheck(result);

	//채널 개수, 이닛 모드, 아마 그냥 0일듯 (추가 드라이브데이터 포인터라는데 뭔지모름)
	result = m_Systems->init(2, FMOD_INIT_NORMAL, 0);
	errCheck(result);
	return true;
}

void Arthas::SoundManager::errCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		char str[256] = { 0, };
		sprintf_s(str, "FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		MessageBoxA(NULL, str, NULL, MB_OK);
		//messageBox를 사용할지는 한번 해보고 결정해야지 
	}
}
