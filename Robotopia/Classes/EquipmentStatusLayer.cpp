#include "pch.h"
#include "EquipmentStatusLayer.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "ButtonLayer.h"

bool EquipmentStatusLayer::init()
{
	if (!UILayer::init())
	{
		return false;
	}

	//st_start 대신 뒷 배경으로 바꾸면 됨
	setUIProperties(GET_RESOURCE_MANAGER()->createSprite(ST_START), cocos2d::Point::ANCHOR_MIDDLE,
					cocos2d::Point::ZERO, 1.f, true, 0);


	//버튼 만들기
	m_EquipButton->setButtonProperties(BUTTON_ASSEMBLY, cocos2d::Point::ANCHOR_MIDDLE,
									   cocos2d::Point::ZERO, "EQUIP");
	m_UpgradeButton->setButtonProperties(BUTTON_ASSEMBLY, cocos2d::Point::ANCHOR_MIDDLE,
									   cocos2d::Point::ZERO, "UPGRADE");

	//콜백함수 나주엥 정의 
//	m_ButtonConfirm->setButtonFunc(std::bind(&AssemblyUILayer::confirmAssembly, this));
	//m_ButtonCancel->setButtonFunc(std::bind(&AssemblyUILayer::toTitleScene, this));



	return true;
}

void EquipmentStatusLayer::update(float dTime)
{
	m_EquipButton->update(dTime);
	m_UpgradeButton->update(dTime);

	//getCurBeChosenEquipment를 해서 아이템을  
}

void EquipmentStatusLayer::setStartEquipmentType(Equipmentes equipmentList)
{
	m_CurBeInstalledEquipmentes = equipmentList;
}

