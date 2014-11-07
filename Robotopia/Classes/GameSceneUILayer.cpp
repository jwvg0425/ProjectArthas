#include "pch.h"
#include "GameSceneUILayer.h"
#include "MinimapLayer.h"

bool Arthas::GameSceneUILayer::init()
{
	return true;
}

void Arthas::GameSceneUILayer::update(float dTime)
{
	//Member update
	m_Minimap->update(dTime);



}

