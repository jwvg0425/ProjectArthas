#include "pch.h"
#include "EquipmentStatusLayer.h"

bool EquipmentStatusLayer::init()
{
	if (!UILayer::init())
	{
		return false;
	}

	return true;
}

void EquipmentStatusLayer::update(float dTime)
{

}

void EquipmentStatusLayer::setStartEquipmentType(CurBeChosenEquipmentes equipmentList)
{
	m_CurBeChosenEquipment = equipmentList;
}

