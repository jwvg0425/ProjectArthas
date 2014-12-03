#include "pch.h"
#include "EquipmentStatusLayer.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "DataManager.h"
#include "ButtonLayer.h"
#include "EquipmentHead.h"
#include "EquipmentEngine.h"
#include "EquipmentMelee.h"
#include "EquipmentRange.h"
#include "EquipmentArmor.h"
#include "EquipmentLeg.h"
#include "EquipmentSteamContainer.h"
#include "Player.h"
#include "StageManager.h"

#define LABELSIZE 20
#define POSOFBASICDECLABELX 750
#define POSOFBASICDECLABELY 550
#define POSOFALLDECLABELX 665
#define POSOFALLDECLABELY 440
#define REVISIONARROWPOSITIONX 20


bool EquipmentStatusLayer::init()
{
	
	//st_start 대신 뒷 배경으로 바꾸면 됨
	setUIProperties(GET_RESOURCE_MANAGER()->createSprite(ST_START), cocos2d::Point::ANCHOR_MIDDLE,
					cocos2d::Point::ZERO, 1.f, true, 0);

	setButtons();

	setBasicLabels();

	setAllStatusDescLabels();
	setAllStatusValueLabels();
	setAllStatusChangeValueLabels();
	makeArrowLabels();

	

	return true;
}

void EquipmentStatusLayer::update(float dTime)
{
	m_EquipButton->update(dTime);
	m_UpgradeButton->update(dTime);
}


void EquipmentStatusLayer::changeBasicItemValue(const EquipmentInfo* equipmentInfo)
{
	//같은 아이템이면 리턴
	
	char tmpLevel[20];
	char tmpKwatt[20];
	char tmpUpgradePrice[20];

	//prev 전환
	m_PrevClickedItem = m_CurClickedItem;

	//라벨 업데이트 

	sprintf(tmpLevel, "%d", equipmentInfo->m_Level);
	sprintf(tmpKwatt, "%d", equipmentInfo->m_KWatt);
	sprintf(tmpUpgradePrice, "%d", equipmentInfo->m_UpgradePrice);

	m_BasicStatusValue[0]->setString(tmpLevel);
	m_BasicStatusValue[0]->setString(tmpKwatt);
	m_BasicStatusValue[0]->setString(tmpUpgradePrice);
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
	auto Resistance = cocos2d::Label::createWithSystemFont("Anti Poision", "Calibri", LABELSIZE);

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
	m_AllStatusDesc.push_back(Resistance);

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
	auto CoolDownLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto MainMemoryLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto PowerLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto ArmorLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto SteamLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto MeleeDamageLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto RangeDamageLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto MeleeAttackSpeedLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto RangeAttackSpeedLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto MaxSteamLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto DrainLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto SpeedLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto JumpLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto Resistance = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);

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
	m_AllStatusValue.push_back(Resistance);

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

void EquipmentStatusLayer::setAllStatusChangeValueLabels()
{
	auto CoolDownLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto MainMemoryLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto PowerLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto ArmorLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto SteamLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto MeleeDamageLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto RangeDamageLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto MeleeAttackSpeedLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto RangeAttackSpeedLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto RangeAttackSRangeLabel= cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto MaxSteamLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto DrainLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto SpeedLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto JumpLabel = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	auto ResistanceLable = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);

	m_AllStatusChangeValue[COOLDOWN] = CoolDownLabel;
	m_AllStatusChangeValue[MAINMEMORY] = MainMemoryLabel;
	m_AllStatusChangeValue[POWER] = PowerLabel;
	m_AllStatusChangeValue[STEAM_EFF] = SteamLabel;
	m_AllStatusChangeValue[ARMOR] = ArmorLabel;
	m_AllStatusChangeValue[RESISTANCE] = ResistanceLable;
	m_AllStatusChangeValue[MAX_STEAM] = MaxSteamLabel;
	m_AllStatusChangeValue[ABSORB_EFF] = DrainLabel;
	m_AllStatusChangeValue[MELEE_DAMAGE] = MeleeDamageLabel;
	m_AllStatusChangeValue[MELEE_ATTACK_SPEED] = MeleeAttackSpeedLabel;
	m_AllStatusChangeValue[RANGE_DAMAGE] = RangeDamageLabel;
	m_AllStatusChangeValue[RANGE_ATTACK_SPEED] = RangeAttackSpeedLabel;
	m_AllStatusChangeValue[RANGE_ATTACK_RANGE] = RangeAttackSRangeLabel;
	m_AllStatusChangeValue[SPEED] = SpeedLabel;
	m_AllStatusChangeValue[JUMP] = JumpLabel;
	
	for (AllstatusEnum i = STATUS_ENUM_START; i < STATUS_ENUM_END; i = static_cast<AllstatusEnum>(i + 1))
	{
		addChild(m_AllStatusChangeValue[i]);
		m_AllStatusChangeValue[i]->setVisible(false);
	}
	
	setPosAllStatusChangeValueLabel();
}

void EquipmentStatusLayer::setPosAllStatusChangeValueLabel()
{
	for (AllstatusEnum i = STATUS_ENUM_START; i < STATUS_ENUM_END; i = static_cast<AllstatusEnum>(i + 1))
	{
		m_AllStatusChangeValue[i]->setPosition(POSOFALLDECLABELX + 170, POSOFALLDECLABELY - 25 * i);
	}
}

void EquipmentStatusLayer::calculateChangeValue(const EquipmentInfo* equipInfo, EquipmentType equipType)
{
	float tmpChangeValue1 = 0.f;
	float tmpChangeValue2 = 0.f;
	float tmpChangeValue3 = 0.f;

	switch (equipType)
	{
	case EMT_HEAD:
		tmpChangeValue1 = m_CurBeInstalledEquipment.m_CoolDown -
			static_cast<const HeadInfo*> (equipInfo)->m_SkillCoolTimeDown;
		tmpChangeValue2 = m_CurBeInstalledEquipment.m_Mainmemory -
			static_cast<const HeadInfo*> (equipInfo)->m_MainMemory;
		
		m_ChangeValue.m_CoolDown = tmpChangeValue1;
		m_ChangeValue.m_Mainmemory = tmpChangeValue2;
		break;
	case EMT_ENGINE:
		tmpChangeValue1 = m_CurBeInstalledEquipment.m_ElectronicPower -
			static_cast<const EngineInfo*> (equipInfo)->m_ElectronicPower;
		tmpChangeValue2 = m_CurBeInstalledEquipment.m_SteamEffectiveness -
			static_cast<const EngineInfo*> (equipInfo)->m_SteamEffectiveness;

		m_ChangeValue.m_ElectronicPower = tmpChangeValue1;
		m_ChangeValue.m_SteamEffectiveness = tmpChangeValue2;

		break;
	case EMT_ARMOR:
		tmpChangeValue1 = m_CurBeInstalledEquipment.m_DefensivePower -
			static_cast<const ArmorInfo*> (equipInfo)->m_DefensivePower;
		tmpChangeValue2 = m_CurBeInstalledEquipment.m_Resistance -
			static_cast<const ArmorInfo*> (equipInfo)->m_Resistance;

		m_ChangeValue.m_DefensivePower = tmpChangeValue1;
		m_ChangeValue.m_Resistance = tmpChangeValue2;

		break;
	case EMT_MELEE:
		tmpChangeValue1 = m_CurBeInstalledEquipment.m_MeleeDamage -
			static_cast<const MeleeInfo*> (equipInfo)->m_AttackDamage;
		tmpChangeValue2 = m_CurBeInstalledEquipment.m_MeleeAttackSpeed -
			static_cast<const MeleeInfo*> (equipInfo)->m_AttackSpeed;

		m_ChangeValue.m_MeleeDamage = tmpChangeValue1;
		m_ChangeValue.m_MeleeAttackSpeed = tmpChangeValue2;
		break;
	case EMT_RANGE:
		tmpChangeValue1 = m_CurBeInstalledEquipment.m_RangeDamage -
			static_cast<const RangeInfo*> (equipInfo)->m_AttackSpeed;
		tmpChangeValue2 = m_CurBeInstalledEquipment.m_RangeAttackSpeed -
			static_cast<const RangeInfo*> (equipInfo)->m_AttackSpeed;
		tmpChangeValue3 = m_CurBeInstalledEquipment.m_AttackRange -
			static_cast<const RangeInfo*> (equipInfo)->m_AttackRange;

		m_ChangeValue.m_RangeDamage = tmpChangeValue1;
		m_ChangeValue.m_RangeAttackSpeed = tmpChangeValue2;
		m_ChangeValue.m_AttackRange = tmpChangeValue3;
		break;
	case EMT_STEAMCONTAINTER:
		tmpChangeValue1 = m_CurBeInstalledEquipment.m_MaxSteam -
			static_cast<const SteamContainerInfo*> (equipInfo)->m_MaxSteam;
		tmpChangeValue2 = m_CurBeInstalledEquipment.m_AbsorbEffectiveness -
			static_cast<const SteamContainerInfo*> (equipInfo)->m_AbsorbEffectiveness;

		m_ChangeValue.m_MaxSteam = tmpChangeValue1;
		m_ChangeValue.m_AbsorbEffectiveness = tmpChangeValue2;
		break;
	case EMT_LEG:
		tmpChangeValue1 = m_CurBeInstalledEquipment.m_Speed -
			static_cast<const LegInfo*> (equipInfo)->m_MoveSpeed;
		tmpChangeValue2 = m_CurBeInstalledEquipment.m_Jump -
			static_cast<const LegInfo*> (equipInfo)->m_jumpPower;

		m_ChangeValue.m_Speed = tmpChangeValue1;
		m_ChangeValue.m_Jump = tmpChangeValue2;
		break;
	default:
		break;
	}


	updateChangeValueLabel(equipType);

}

void EquipmentStatusLayer::updateChangeValueLabel(EquipmentType equipType)
{
	for (unsigned int i = 0; i < m_ArrowLabels.size(); ++i)
	{
		//이게 안먹히면 태그를 달고 down인지 알아내서 180도 돌린다
		m_ArrowLabels[i]->setRotation(0);
		m_ArrowLabels[i]->setVisible(false);
	}

	cocos2d::Point arrowPosition;
	char buffer[20];

	switch (equipType)
	{
	case EMT_HEAD:
		arrowPosition = m_AllStatusChangeValue[COOLDOWN]->getPosition();
		m_ArrowLabels[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX, 
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_CoolDown);
		m_ArrowLabels[0]->setString(buffer);
		m_ArrowLabels[0]->setVisible(true);
		if (m_ChangeValue.m_CoolDown >= 0)
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::GREEN);
			
		}
		else
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[0]->setRotation(180);
		}

		arrowPosition = m_AllStatusChangeValue[MAINMEMORY]->getPosition();
		m_ArrowLabels[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX, 
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_Mainmemory);
		m_ArrowLabels[1]->setString(buffer);
		m_ArrowLabels[1]->setVisible(true);
		if (m_ChangeValue.m_Mainmemory >= 0)
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[1]->setRotation(180);
		}

		break;
	case EMT_ENGINE:
		arrowPosition = m_AllStatusChangeValue[POWER]->getPosition();
		m_ArrowLabels[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		m_ArrowLabels[0]->setVisible(true);
		sprintf(buffer, "%.3f", m_ChangeValue.m_ElectronicPower);
		m_ArrowLabels[0]->setString(buffer);
		if (m_ChangeValue.m_ElectronicPower >= 0)
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[0]->setRotation(180);
		}

		arrowPosition = m_AllStatusChangeValue[STEAM_EFF]->getPosition();
		m_ArrowLabels[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_SteamEffectiveness);
		m_ArrowLabels[1]->setString(buffer);
		m_ArrowLabels[1]->setVisible(true);
		if (m_ChangeValue.m_SteamEffectiveness >= 0)
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[1]->setRotation(180);
		}
		break;
	case EMT_ARMOR:
		arrowPosition = m_AllStatusChangeValue[ARMOR]->getPosition();
		m_ArrowLabels[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_DefensivePower);
		m_ArrowLabels[0]->setString(buffer);
		m_ArrowLabels[0]->setVisible(true);
		if (m_ChangeValue.m_DefensivePower >= 0)
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[0]->setRotation(180);
		}

		arrowPosition = m_AllStatusChangeValue[RESISTANCE]->getPosition();
		m_ArrowLabels[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_Resistance);
		m_ArrowLabels[1]->setString(buffer);
		m_ArrowLabels[1]->setVisible(true);
		if (m_ChangeValue.m_Resistance >= 0)
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[1]->setRotation(180);
		}
		break;
	case EMT_MELEE:
		arrowPosition = m_AllStatusChangeValue[MELEE_DAMAGE]->getPosition();
		m_ArrowLabels[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_MeleeDamage);
		m_ArrowLabels[0]->setString(buffer);
		m_ArrowLabels[0]->setVisible(true);
		if (m_ChangeValue.m_MeleeDamage >= 0)
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[0]->setRotation(180);
		}

		arrowPosition = m_AllStatusChangeValue[MELEE_ATTACK_SPEED]->getPosition();
		m_ArrowLabels[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_MeleeAttackSpeed);
		m_ArrowLabels[1]->setString(buffer);
		m_ArrowLabels[1]->setVisible(true);
		if (m_ChangeValue.m_MeleeAttackSpeed >= 0)
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[1]->setRotation(180);
		}
		break;
	case EMT_RANGE:
		arrowPosition = m_AllStatusChangeValue[RANGE_DAMAGE]->getPosition();
		m_ArrowLabels[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_RangeDamage);
		m_ArrowLabels[0]->setString(buffer);
		m_ArrowLabels[0]->setVisible(true);
		if (m_ChangeValue.m_RangeDamage >= 0)
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[0]->setRotation(180);
		}

		arrowPosition = m_AllStatusChangeValue[RANGE_ATTACK_SPEED]->getPosition();
		m_ArrowLabels[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_RangeAttackSpeed);
		m_ArrowLabels[1]->setString(buffer);
		m_ArrowLabels[1]->setVisible(true);
		if (m_ChangeValue.m_Mainmemory >= 0)
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[1]->setRotation(180);
		}

		arrowPosition = m_AllStatusChangeValue[RANGE_ATTACK_RANGE]->getPosition();
		m_ArrowLabels[2]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_AttackRange);
		m_ArrowLabels[2]->setString(buffer);
		m_ArrowLabels[2]->setVisible(true);
		if (m_ChangeValue.m_AttackRange >= 0)
		{
			m_ArrowLabels[2]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowLabels[2]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[2]->setRotation(180);
		}


		break;
	case EMT_STEAMCONTAINTER:
		arrowPosition = m_AllStatusChangeValue[MAX_STEAM]->getPosition();
		m_ArrowLabels[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_MaxSteam);
		m_ArrowLabels[0]->setString(buffer);
		m_ArrowLabels[0]->setVisible(true);
		if (m_ChangeValue.m_MaxSteam >= 0)
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[0]->setRotation(180);
		}

		arrowPosition = m_AllStatusChangeValue[ABSORB_EFF]->getPosition();
		m_ArrowLabels[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_AbsorbEffectiveness);
		m_ArrowLabels[1]->setString(buffer);
		m_ArrowLabels[1]->setVisible(true);
		if (m_ChangeValue.m_AbsorbEffectiveness >= 0)
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[1]->setRotation(180);
		}
		break;
	case EMT_LEG:
		arrowPosition = m_AllStatusChangeValue[JUMP]->getPosition();
		m_ArrowLabels[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_Jump);
		m_ArrowLabels[0]->setString(buffer);
		m_ArrowLabels[0]->setVisible(true);
		if (m_ChangeValue.m_Jump >= 0)
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowLabels[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[0]->setRotation(180);
		}

		arrowPosition = m_AllStatusChangeValue[SPEED]->getPosition();
		m_ArrowLabels[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.3f", m_ChangeValue.m_Speed);
		m_ArrowLabels[1]->setString(buffer);
		m_ArrowLabels[1]->setVisible(true);
		if (m_ChangeValue.m_Speed >= 0)
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowLabels[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowLabels[1]->setRotation(180);
		}
		break;
	default:
		break;
	}
}

void EquipmentStatusLayer::makeArrowLabels()
{
	auto ArrowLabel = cocos2d::Label::createWithSystemFont("▲", "Calibri", LABELSIZE);
	auto ArrowLabel2 = cocos2d::Label::createWithSystemFont("▲", "Calibri", LABELSIZE);
	auto ArrowLabel3 = cocos2d::Label::createWithSystemFont("▲", "Calibri", LABELSIZE);

	m_ArrowLabels.push_back(ArrowLabel);
	m_ArrowLabels.push_back(ArrowLabel2);
	m_ArrowLabels.push_back(ArrowLabel3);

	for (unsigned int i = 0; i < m_ArrowLabels.size(); ++i)
	{
		addChild(m_ArrowLabels[i]);
	}

}

void EquipmentStatusLayer::clickedSomeEquipment()
{
	if ((m_CurClickedItem.m_Type == m_PrevClickedItem.m_Type &&
		m_CurClickedItem.m_ListItem == m_PrevClickedItem.m_ListItem))
	{
		return;
	}


	const EquipmentInfo* curItemInfo = GET_DATA_MANAGER()->getEquipmentInfo(m_CurClickedItem.m_Type,
																			m_CurClickedItem.m_ListItem);
	changeBasicItemValue(curItemInfo);
	calculateChangeValue(curItemInfo, m_CurClickedItem.m_Type);
}

void EquipmentStatusLayer::upgradeButtonClick()
{
	PlayerInfo tmpPlayerInfo = GET_STAGE_MANAGER()->getPlayer()->getInfo();
	EquipmentInfo equipInfo = *(GET_DATA_MANAGER()->getEquipmentInfo(m_CurClickedItem.m_Type,
																			m_CurClickedItem.m_ListItem));

	if (tmpPlayerInfo.m_BitCoin < equipInfo.m_UpgradePrice)
	{
		//실패의 effect소리를 여기다 넣으면 될것 같음
		return;
	}

	

	switch (m_CurClickedItem.m_Type)
	{
	case EMT_HEAD:
		break;
	case EMT_ENGINE:
		break;
	case EMT_ARMOR:
		break;
	case EMT_MELEE:
		break;
	case EMT_RANGE:
		break;
	case EMT_STEAMCONTAINTER:
		break;
	case EMT_LEG:
		break;
	default:
		break;
	}


	tmpPlayerInfo.m_BitCoin -= curEquipmentInfo.m_UpgradePrice;
	curEquipmentInfo.m_UpgradePrice *= 2;
	


	//GET_DATA_MANAGER()->setEquipmentInfo();
}

