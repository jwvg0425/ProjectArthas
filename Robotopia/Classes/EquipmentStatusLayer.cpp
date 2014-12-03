#include "pch.h"
#include "EquipmentStatusLayer.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "DataManager.h"
#include "ButtonLayer.h"
#include "EquipmentHead.h"

#define LABELSIZE 20
#define POSOFBASICDECLABELX 750
#define POSOFBASICDECLABELY 550
#define POSOFALLDECLABELX 665
#define POSOFALLDECLABELY 440


bool EquipmentStatusLayer::init()
{
	
	//st_start 대신 뒷 배경으로 바꾸면 됨
	setUIProperties(GET_RESOURCE_MANAGER()->createSprite(ST_START), cocos2d::Point::ANCHOR_MIDDLE,
					cocos2d::Point::ZERO, 1.f, true, 0);

	setButtons();

	setBasicLabels();

	setAllStatusDescLabels();
	setAllStatusValueLabels();
	

	return true;
}

void EquipmentStatusLayer::update(float dTime)
{
	m_EquipButton->update(dTime);
	m_UpgradeButton->update(dTime);
	
	if (m_CurClickedItem.m_Type == m_PrevClickedItem.m_Type &&
		m_CurClickedItem.m_ListItem == m_PrevClickedItem.m_ListItem)
	{
		char* tmpLevel;
		char* tmpKwatt;
		char* tmpUpgradePrice;

		//prev 업데이ㅡ
		m_PrevClickedItem = m_CurClickedItem;

		//라벨 업데이트 
		const EquipmentInfo* curItemInfo = GET_DATA_MANAGER()->getEquipmentInfo(m_CurClickedItem.m_Type, 
																m_CurClickedItem.m_ListItem);
		sprintf(tmpLevel, "%d", curItemInfo->m_Level);
		sprintf(tmpKwatt, "%d", curItemInfo->m_KWatt);
		sprintf(tmpUpgradePrice, "%d", curItemInfo->m_UpgradePrice);

		m_BasicStatusValue[0]->setString(tmpLevel);
		m_BasicStatusValue[0]->setString(tmpKwatt);
		m_BasicStatusValue[0]->setString(tmpUpgradePrice);

	}
}

void EquipmentStatusLayer::setStartEquipmentType(Equipmentes equipmentList)
{
	m_CurBeInstalledEquipmentes = equipmentList;
}

void EquipmentStatusLayer::setPosBasicDescLabel()
{
	for (unsigned int i = 0; i < m_BasicStatusDesc.size() ; ++i)
	{
		m_BasicStatusDesc[i]->setPosition(POSOFBASICDECLABELX, POSOFBASICDECLABELY - 25 * i);
	}
}

void EquipmentStatusLayer::setPosBasicValueLabel()
{
	for (unsigned int i = 0; i < m_BasicStatusDesc.size(); ++i)
	{
		m_BasicStatusValue[i]->setPosition(POSOFBASICDECLABELX + 100, POSOFBASICDECLABELY - 25 * i);
	}
}

void EquipmentStatusLayer::setBasicLabels()
{
	auto levelLabel = cocos2d::Label::createWithSystemFont("LEVEL", "Calibri", LABELSIZE);
	auto kWattLabel = cocos2d::Label::createWithSystemFont("KWATT", "Calibri", LABELSIZE);
	auto upgradePriceLabel = cocos2d::Label::createWithSystemFont("PRICE", "Calibri", LABELSIZE);
	m_BasicStatusDesc.push_back(levelLabel);
	m_BasicStatusDesc.push_back(kWattLabel);
	m_BasicStatusDesc.push_back(upgradePriceLabel);
	for (unsigned int i = 0; i < m_BasicStatusDesc.size(); ++i)
	{
		addChild(m_BasicStatusDesc[i]);
	}
	setPosBasicDescLabel();

	auto levelValueLabel = cocos2d::Label::createWithSystemFont("1", "Calibri", LABELSIZE);
	auto kWattValueLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto upgradePriceValueLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	m_BasicStatusValue.push_back(levelValueLabel);
	m_BasicStatusValue.push_back(kWattValueLabel);
	m_BasicStatusValue.push_back(upgradePriceValueLabel);

	for (unsigned int i = 0; i < m_BasicStatusValue.size(); ++i)
	{
		addChild(m_BasicStatusValue[i]);
	}
	setPosBasicValueLabel();

}

void EquipmentStatusLayer::setButtons()
{
	//버튼 만들기
	//  콜백함수 나중에 정의 
	//	m_ButtonConfirm->setButtonFunc(std::bind(&AssemblyUILayer::confirmAssembly, this));
	//  m_ButtonCancel->setButtonFunc(std::bind(&AssemblyUILayer::toTitleScene, this));
	m_EquipButton = ButtonLayer::create();
	m_UpgradeButton = ButtonLayer::create();
	m_EquipButton->setButtonProperties(BUTTON_ASSEMBLY, cocos2d::Point::ZERO,
									   cocos2d::Point(650, 600), "EQUIP");
	m_UpgradeButton->setButtonProperties(BUTTON_ASSEMBLY, cocos2d::Point::ZERO,
										 cocos2d::Point(850, 600), "UPGRADE");

	addChild(m_EquipButton);
	addChild(m_UpgradeButton);
}

void EquipmentStatusLayer::setAllStatusDescLabels()
{
	m_AllStatusDesc.reserve(20);
	auto CoolDownLabel = cocos2d::Label::createWithSystemFont("CoolDown", "Calibri", LABELSIZE);
	auto MainMemoryLabel = cocos2d::Label::createWithSystemFont("MainMemory", "Calibri", LABELSIZE);
	auto PowerLabel = cocos2d::Label::createWithSystemFont("Power", "Calibri", LABELSIZE);
	auto ArmorLabel = cocos2d::Label::createWithSystemFont("Armor", "Calibri", LABELSIZE);
	auto SteamLabel = cocos2d::Label::createWithSystemFont("Steam Eff.", "Calibri", LABELSIZE);
	auto MeleeDamageLabel = cocos2d::Label::createWithSystemFont("MeleeDamage", "Calibri", LABELSIZE);
	auto RangeDamageLabel = cocos2d::Label::createWithSystemFont("RangeDamage", "Calibri", LABELSIZE);
	auto MeleeAttackSpeedLabel = cocos2d::Label::createWithSystemFont("MeleeAttackSpeed", "Calibri", LABELSIZE);
	auto RangeAttackSpeedLabel = cocos2d::Label::createWithSystemFont("RangeAttackSpeed", "Calibri", LABELSIZE);
	auto MaxSteamLabel = cocos2d::Label::createWithSystemFont("MaxSteam", "Calibri", LABELSIZE);
	auto DrainLabel = cocos2d::Label::createWithSystemFont("Drain Eff.", "Calibri", LABELSIZE);
	auto SpeedLabel = cocos2d::Label::createWithSystemFont("Speed", "Calibri", LABELSIZE);
	auto JumpLabel = cocos2d::Label::createWithSystemFont("Jump", "Calibri", LABELSIZE);
	auto AntiSlowLabel = cocos2d::Label::createWithSystemFont("Anti Poision", "Calibri", LABELSIZE);
	auto AntiPoisonLabel = cocos2d::Label::createWithSystemFont("Anti Slow", "Calibri", LABELSIZE);

	m_AllStatusDesc.push_back(CoolDownLabel);
	m_AllStatusDesc.push_back(MainMemoryLabel);
	m_AllStatusDesc.push_back(PowerLabel);
	m_AllStatusDesc.push_back(ArmorLabel);
	m_AllStatusDesc.push_back(SteamLabel);
	m_AllStatusDesc.push_back(MeleeDamageLabel);
	m_AllStatusDesc.push_back(RangeDamageLabel);
	m_AllStatusDesc.push_back(MeleeAttackSpeedLabel);
	m_AllStatusDesc.push_back(RangeAttackSpeedLabel);
	m_AllStatusDesc.push_back(MaxSteamLabel);
	m_AllStatusDesc.push_back(DrainLabel);
	m_AllStatusDesc.push_back(SpeedLabel);
	m_AllStatusDesc.push_back(JumpLabel);
	m_AllStatusDesc.push_back(AntiSlowLabel);
	m_AllStatusDesc.push_back(AntiPoisonLabel);

	for (unsigned int i = 0; i < m_AllStatusDesc.size(); ++i)
	{
		addChild(m_AllStatusDesc[i]);
	}
	setPosAllStatusDescLabel();
}

void EquipmentStatusLayer::setPosAllStatusDescLabel()
{
	for (unsigned int i = 0; i < m_AllStatusDesc.size(); ++i)
	{
		m_AllStatusDesc[i]->setPosition(POSOFALLDECLABELX, POSOFALLDECLABELY - 25 * i);
	}
}

void EquipmentStatusLayer::setAllStatusValueLabels()
{
	//정보를 받아서
	//계산을 해서 
	auto CoolDownLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto MainMemoryLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto PowerLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto ArmorLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto SteamLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto MeleeDamageLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto RangeDamageLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto MeleeAttackSpeedLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto RangeAttackSpeedLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto MaxSteamLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto DrainLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto SpeedLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto JumpLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto AntiSlowLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);
	auto AntiPoisonLabel = cocos2d::Label::createWithSystemFont("100", "Calibri", LABELSIZE);

	m_AllStatusValue.push_back(CoolDownLabel);
	m_AllStatusValue.push_back(MainMemoryLabel);
	m_AllStatusValue.push_back(PowerLabel);
	m_AllStatusValue.push_back(ArmorLabel);
	m_AllStatusValue.push_back(SteamLabel);
	m_AllStatusValue.push_back(MeleeDamageLabel);
	m_AllStatusValue.push_back(RangeDamageLabel);
	m_AllStatusValue.push_back(MeleeAttackSpeedLabel);
	m_AllStatusValue.push_back(RangeAttackSpeedLabel);
	m_AllStatusValue.push_back(MaxSteamLabel);
	m_AllStatusValue.push_back(DrainLabel);
	m_AllStatusValue.push_back(SpeedLabel);
	m_AllStatusValue.push_back(JumpLabel);
	m_AllStatusValue.push_back(AntiSlowLabel);
	m_AllStatusValue.push_back(AntiPoisonLabel);

	for (unsigned int i = 0; i < m_AllStatusValue.size(); ++i)
	{
		addChild(m_AllStatusValue[i]);
	}
	setPosAllStatusValueLabel();
}


void EquipmentStatusLayer::setPosAllStatusValueLabel()
{
	for (unsigned int i = 0; i < m_AllStatusValue.size(); ++i)
	{
		m_AllStatusValue[i]->setPosition(POSOFALLDECLABELX + 100, POSOFALLDECLABELY - 25 * i);
	}
}

void EquipmentStatusLayer::setCurClickedItem(ClickedItem clickedItem)
{
	m_CurClickedItem = clickedItem;
}


