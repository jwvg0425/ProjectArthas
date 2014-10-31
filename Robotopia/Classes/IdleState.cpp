#include "IdleState.h"


bool Arthas::IdleState::init()
{
	if (!StateComponent::init())
	{
		return false;
	}




	return true;
}

void Arthas::IdleState::enter()
{
	//들어올 때 해줘야 되는거 sprite 바꾸는 거지. 
	//m_Parent로가서 렌더 컴포넌트로 가서 저를 켜주세요 해야겠네. 
}

void Arthas::IdleState::exit()
{
	//스프라이트 애니메이션 끄는거지 
}

void Arthas::IdleState::update(int dTime)
{

}

