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
#include <math.h>


#define LABELSIZE 20
#define POSOFBASICDECLABELX 750
#define POSOFBASICDECLABELY 550
#define POSOFALLDECLABELX 665
#define POSOFALLDECLABELY 440
#define REVISIONARROWPOSITIONX 40


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
	clickedSomeEquipment();
	updateAllStatus();
}


void EquipmentStatusLayer::changeBasicItemValue(const EquipmentInfo* equipmentInfo)
{
	
	if (equipmentInfo == nullptr)
	{
		return;
	}
	char tmpLevel[20] = { 0, };
	char tmpKwatt[20] = { 0, };
	char tmpUpgradePrice[20] = { 0, };

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
	m_EquipButton = ButtonLayer::create();
	m_UpgradeButton = ButtonLayer::create();

	m_EquipButton->setButtonProperties(BUTTON_ASSEMBLY, cocos2d::Point::ZERO,
									   cocos2d::Point(650, 600), "EQUIP");
	m_UpgradeButton->setButtonProperties(BUTTON_ASSEMBLY, cocos2d::Point::ZERO,
										 cocos2d::Point(850, 600), "UPGRADE");

	m_EquipButton->setButtonFunc(std::bind(&EquipmentStatusLayer::equipmentButtonClick, this));
	m_UpgradeButton->setButtonFunc(std::bind(&EquipmentStatusLayer::upgradeButtonClick, this));


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
	auto Resistance = cocos2d::Label::createWithSystemFont("Resistance", "Calibri", LABELSIZE);
	auto RangeLabel = cocos2d::Label::createWithSystemFont("Range", "Calibri", LABELSIZE);

	m_AllStatusDesc.push_back(CoolDownLabel);
	m_AllStatusDesc.push_back(MainMemoryLabel);
	m_AllStatusDesc.push_back(PowerLabel);
	m_AllStatusDesc.push_back(SteamLabel);
	m_AllStatusDesc.push_back(ArmorLabel);
	m_AllStatusDesc.push_back(Resistance);
	m_AllStatusDesc.push_back(MeleeDamageLabel);
	m_AllStatusDesc.push_back(MeleeAttackSpeedLabel);
	m_AllStatusDesc.push_back(RangeDamageLabel);
	m_AllStatusDesc.push_back(RangeAttackSpeedLabel);
	m_AllStatusDesc.push_back(RangeLabel);
	m_AllStatusDesc.push_back(MaxSteamLabel);
	m_AllStatusDesc.push_back(DrainLabel);
	m_AllStatusDesc.push_back(SpeedLabel);
	m_AllStatusDesc.push_back(JumpLabel);

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

	cocos2d::Label** labels = (cocos2d::Label**)malloc(sizeof(cocos2d::Label*) * STATUS_ENUM_END);

	for (int i = 0; i < STATUS_ENUM_END; ++i)
	{
		labels[i] = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	}

	for (AllstatusEnum i = STATUS_ENUM_START; i < STATUS_ENUM_END; i = static_cast<AllstatusEnum>(i + 1))
	{
		m_AllStatusValue[i] = labels[i];
		addChild(m_AllStatusValue[i]);
	}

	delete[] labels;

	setPosAllStatusValueLabel();
}


void EquipmentStatusLayer::setPosAllStatusValueLabel()
{

	for (AllstatusEnum i = STATUS_ENUM_START; i < STATUS_ENUM_END; i = static_cast<AllstatusEnum>(i + 1))
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

	
	cocos2d::Label** labels = (cocos2d::Label**)malloc(sizeof(cocos2d::Label*) * STATUS_ENUM_END);

	for (int i = 0; i < STATUS_ENUM_END; ++i)
	{
		labels[i] = cocos2d::Label::createWithSystemFont("0", "Calibri", LABELSIZE);
	}

	for (AllstatusEnum i = STATUS_ENUM_START; i < STATUS_ENUM_END; i = static_cast<AllstatusEnum>(i + 1))
	{
		m_AllStatusChangeValue[i] = labels[i];
		m_AllStatusChangeValue[i]->setVisible(false);
		addChild(m_AllStatusChangeValue[i]);
	}

	delete[] labels;

	
	
	setPosAllStatusChangeValueLabel();
}

void EquipmentStatusLayer::setPosAllStatusChangeValueLabel()
{
	for (AllstatusEnum i = STATUS_ENUM_START; i < STATUS_ENUM_END; i = static_cast<AllstatusEnum>(i + 1))
	{
		m_AllStatusChangeValue[i]->setPosition(POSOFALLDECLABELX + 200, POSOFALLDECLABELY - 25 * i);
	}
}

void EquipmentStatusLayer::calculateChangeValue(const EquipmentInfo* equipInfo, EquipmentType equipType)
{
	if (equipInfo == nullptr)
	{
		return;
	}
	float tmpChangeValue1 = 0.f;
	float tmpChangeValue2 = 0.f;
	float tmpChangeValue3 = 0.f;

	switch (equipType)
	{
	case EMT_HEAD:
		tmpChangeValue1 =  
			static_cast<const HeadInfo*> (equipInfo)->m_SkillCoolTimeDown -
			m_CurConfirmSetStatus.m_CoolDown;
		tmpChangeValue2 =  
			static_cast<const HeadInfo*> (equipInfo)->m_MainMemory -
			m_CurConfirmSetStatus.m_Mainmemory;
		
		m_ChangeStatus.m_CoolDown = tmpChangeValue1;
		m_ChangeStatus.m_Mainmemory = tmpChangeValue2;
		break;
	case EMT_ENGINE:
		tmpChangeValue1 = 
			static_cast<const EngineInfo*> (equipInfo)->m_ElectronicPower -
			m_CurConfirmSetStatus.m_ElectronicPower;
		tmpChangeValue2 = 
			static_cast<const EngineInfo*> (equipInfo)->m_SteamEffectiveness -
			m_CurConfirmSetStatus.m_SteamEffectiveness;

		m_ChangeStatus.m_ElectronicPower = tmpChangeValue1;
		m_ChangeStatus.m_SteamEffectiveness = tmpChangeValue2;

		break;
	case EMT_ARMOR:
		tmpChangeValue1 =  
			static_cast<const ArmorInfo*> (equipInfo)->m_DefensivePower -
			m_CurConfirmSetStatus.m_DefensivePower;
		tmpChangeValue2 = 
			static_cast<const ArmorInfo*> (equipInfo)->m_Resistance -
			m_CurConfirmSetStatus.m_Resistance;

		m_ChangeStatus.m_DefensivePower = tmpChangeValue1;
		m_ChangeStatus.m_Resistance = tmpChangeValue2;

		break;
	case EMT_MELEE:
		tmpChangeValue1 =  
			static_cast<const MeleeInfo*> (equipInfo)->m_AttackDamage -
			m_CurConfirmSetStatus.m_MeleeDamage;
		tmpChangeValue2 =  
			static_cast<const MeleeInfo*> (equipInfo)->m_AttackSpeed -
			m_CurConfirmSetStatus.m_MeleeAttackSpeed;

		m_ChangeStatus.m_MeleeDamage = tmpChangeValue1;
		m_ChangeStatus.m_MeleeAttackSpeed = tmpChangeValue2;
		break;
	case EMT_RANGE:
		tmpChangeValue1 =  
			static_cast<const RangeInfo*> (equipInfo)->m_AttackSpeed -
			m_CurConfirmSetStatus.m_RangeDamage;
		tmpChangeValue2 =  
			static_cast<const RangeInfo*> (equipInfo)->m_AttackSpeed -
			m_CurConfirmSetStatus.m_RangeAttackSpeed;
		tmpChangeValue3 =  
			static_cast<const RangeInfo*> (equipInfo)->m_AttackRange -
			m_CurConfirmSetStatus.m_AttackRange;

		m_ChangeStatus.m_RangeDamage = tmpChangeValue1;
		m_ChangeStatus.m_RangeAttackSpeed = tmpChangeValue2;
		m_ChangeStatus.m_AttackRange = tmpChangeValue3;
		break;
	case EMT_STEAMCONTAINTER:
		tmpChangeValue1 =  
			static_cast<const SteamContainerInfo*> (equipInfo)->m_MaxSteam -
			m_CurConfirmSetStatus.m_MaxSteam;
		tmpChangeValue2 =  
			static_cast<const SteamContainerInfo*> (equipInfo)->m_AbsorbEffectiveness -
			m_CurConfirmSetStatus.m_AbsorbEffectiveness;

		m_ChangeStatus.m_MaxSteam = tmpChangeValue1;
		m_ChangeStatus.m_AbsorbEffectiveness = tmpChangeValue2;
		break;
	case EMT_LEG:
		tmpChangeValue1 =  
			static_cast<const LegInfo*> (equipInfo)->m_MoveSpeed -
			m_CurConfirmSetStatus.m_Speed;
		tmpChangeValue2 =
			static_cast<const LegInfo*> (equipInfo)->m_jumpPower -
			m_CurConfirmSetStatus.m_Jump;

		m_ChangeStatus.m_Speed = tmpChangeValue1;
		m_ChangeStatus.m_Jump = tmpChangeValue2;
		break;
	default:
		break;
	}


	updateChangeValueLabel(equipType);

}

void EquipmentStatusLayer::updateChangeValueLabel(EquipmentType equipType)
{
	for (unsigned int i = 0; i < m_ArrowSprites.size(); ++i)
	{
		//현재 화살표가 아래인 상태
		if (m_ArrowSprites[i]->getTag() == 0)
		{
			m_ArrowSprites[i]->setFlippedY(false);
			m_ArrowSprites[i]->setTag(1);
		}
		m_ArrowSprites[i]->setVisible(false);
	}

	for (AllstatusEnum i = STATUS_ENUM_START; i < STATUS_ENUM_END; i = static_cast<AllstatusEnum>(i + 1))
	{
		m_AllStatusChangeValue[i]->setVisible(false);
	}

	cocos2d::Point arrowPosition = cocos2d::Point::ZERO;
	char buffer[20] = { 0, };

	switch (equipType)
	{
	case EMT_HEAD:
		arrowPosition = m_AllStatusChangeValue[COOLDOWN]->getPosition();
		m_ArrowSprites[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX, 
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_CoolDown);
		m_AllStatusChangeValue[COOLDOWN]->setString(buffer);
		m_AllStatusChangeValue[COOLDOWN]->setVisible(true);

		m_ArrowSprites[0]->setVisible(true);
		if (m_ChangeStatus.m_CoolDown >= 0)
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::GREEN);
			
		}
		else
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[0]->setFlippedY(true);
			m_ArrowSprites[0]->setTag(0);

		}

		arrowPosition = m_AllStatusChangeValue[MAINMEMORY]->getPosition();
		m_ArrowSprites[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_Mainmemory);
		m_AllStatusChangeValue[MAINMEMORY]->setString(buffer);
		m_AllStatusChangeValue[MAINMEMORY]->setVisible(true);

		m_ArrowSprites[1]->setVisible(true);
		if (m_ChangeStatus.m_Mainmemory >= 0)
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[1]->setFlippedY(true);
			m_ArrowSprites[1]->setTag(0);

		}

		break;
	case EMT_ENGINE:
		arrowPosition = m_AllStatusChangeValue[POWER]->getPosition();
		m_ArrowSprites[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		m_ArrowSprites[0]->setVisible(true);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_ElectronicPower);
		m_AllStatusChangeValue[POWER]->setString(buffer);
		m_AllStatusChangeValue[POWER]->setVisible(true);

		if (m_ChangeStatus.m_ElectronicPower >= 0)
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[0]->setFlippedY(true);
			m_ArrowSprites[0]->setTag(0);

		}

		arrowPosition = m_AllStatusChangeValue[STEAM_EFF]->getPosition();
		m_ArrowSprites[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_SteamEffectiveness);
		m_AllStatusChangeValue[STEAM_EFF]->setString(buffer);
		m_AllStatusChangeValue[STEAM_EFF]->setVisible(true);
		m_ArrowSprites[1]->setVisible(true);

		if (m_ChangeStatus.m_SteamEffectiveness >= 0)
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[1]->setFlippedY(true);
			m_ArrowSprites[1]->setTag(0);

		}
		break;
	case EMT_ARMOR:
		arrowPosition = m_AllStatusChangeValue[ARMOR]->getPosition();
		m_ArrowSprites[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_DefensivePower);
		m_AllStatusChangeValue[ARMOR]->setString(buffer);
		m_AllStatusChangeValue[ARMOR]->setVisible(true);

		m_ArrowSprites[0]->setVisible(true);
		if (m_ChangeStatus.m_DefensivePower >= 0)
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[0]->setFlippedY(true);
			m_ArrowSprites[0]->setTag(0);

		}

		arrowPosition = m_AllStatusChangeValue[RESISTANCE]->getPosition();
		m_ArrowSprites[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_Resistance);
		m_AllStatusChangeValue[RESISTANCE]->setString(buffer);
		m_AllStatusChangeValue[RESISTANCE]->setVisible(true);

		m_ArrowSprites[1]->setVisible(true);
		if (m_ChangeStatus.m_Resistance >= 0)
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[1]->setFlippedY(true);
			m_ArrowSprites[1]->setTag(0);

		}
		break;
	case EMT_MELEE:
		arrowPosition = m_AllStatusChangeValue[MELEE_DAMAGE]->getPosition();
		m_ArrowSprites[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_MeleeDamage);
		m_AllStatusChangeValue[MELEE_DAMAGE]->setString(buffer);
		m_AllStatusChangeValue[MELEE_DAMAGE]->setVisible(true);

		m_ArrowSprites[0]->setVisible(true);
		if (m_ChangeStatus.m_MeleeDamage >= 0)
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[0]->setFlippedY(true);
			m_ArrowSprites[0]->setTag(0);

		}

		arrowPosition = m_AllStatusChangeValue[MELEE_ATTACK_SPEED]->getPosition();
		m_ArrowSprites[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_MeleeAttackSpeed);
		m_AllStatusChangeValue[MELEE_ATTACK_SPEED]->setString(buffer);
		m_AllStatusChangeValue[MELEE_ATTACK_SPEED]->setVisible(true);

		m_ArrowSprites[1]->setVisible(true);
		if (m_ChangeStatus.m_MeleeAttackSpeed >= 0)
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[1]->setFlippedY(true);
			m_ArrowSprites[1]->setTag(0);

		}
		break;
	case EMT_RANGE:
		arrowPosition = m_AllStatusChangeValue[RANGE_DAMAGE]->getPosition();
		m_ArrowSprites[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_RangeDamage);
		m_AllStatusChangeValue[RANGE_DAMAGE]->setString(buffer);
		m_AllStatusChangeValue[RANGE_DAMAGE]->setVisible(true);

		m_ArrowSprites[0]->setVisible(true);
		if (m_ChangeStatus.m_RangeDamage >= 0)
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[0]->setFlippedY(true);
			m_ArrowSprites[0]->setTag(0);

		}

		arrowPosition = m_AllStatusChangeValue[RANGE_ATTACK_SPEED]->getPosition();
		m_ArrowSprites[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_RangeAttackSpeed);
		m_AllStatusChangeValue[RANGE_ATTACK_SPEED]->setString(buffer);
		m_AllStatusChangeValue[RANGE_ATTACK_SPEED]->setVisible(true);

		m_ArrowSprites[1]->setVisible(true);
		if (m_ChangeStatus.m_Mainmemory >= 0)
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[1]->setFlippedY(true);
			m_ArrowSprites[1]->setTag(0);

		}

		arrowPosition = m_AllStatusChangeValue[RANGE_ATTACK_RANGE]->getPosition();
		m_ArrowSprites[2]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_AttackRange);
		m_AllStatusChangeValue[RANGE_ATTACK_RANGE]->setString(buffer);
		m_AllStatusChangeValue[RANGE_ATTACK_RANGE]->setVisible(true);

		m_ArrowSprites[2]->setVisible(true);
		if (m_ChangeStatus.m_AttackRange >= 0)
		{
			m_ArrowSprites[2]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowSprites[2]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[2]->setFlippedY(true);
			m_ArrowSprites[2]->setTag(0);

		}


		break;
	case EMT_STEAMCONTAINTER:
		arrowPosition = m_AllStatusChangeValue[MAX_STEAM]->getPosition();
		m_ArrowSprites[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_MaxSteam);
		m_AllStatusChangeValue[MAX_STEAM]->setString(buffer);
		m_AllStatusChangeValue[MAX_STEAM]->setVisible(true);

		m_ArrowSprites[0]->setVisible(true);
		if (m_ChangeStatus.m_MaxSteam >= 0)
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[0]->setFlippedY(true);
			m_ArrowSprites[0]->setTag(0);

		}

		arrowPosition = m_AllStatusChangeValue[ABSORB_EFF]->getPosition();
		m_ArrowSprites[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_AbsorbEffectiveness);
		m_AllStatusChangeValue[ABSORB_EFF]->setString(buffer);
		m_AllStatusChangeValue[ABSORB_EFF]->setVisible(true);

		m_ArrowSprites[1]->setVisible(true);
		if (m_ChangeStatus.m_AbsorbEffectiveness >= 0)
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[1]->setFlippedY(true);
			m_ArrowSprites[1]->setTag(0);

		}
		break;
	case EMT_LEG:
		arrowPosition = m_AllStatusChangeValue[JUMP]->getPosition();
		m_ArrowSprites[0]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_Jump);
		m_AllStatusChangeValue[JUMP]->setString(buffer);
		m_AllStatusChangeValue[JUMP]->setVisible(true);

		m_ArrowSprites[0]->setVisible(true);
		if (m_ChangeStatus.m_Jump >= 0)
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::GREEN);

		}
		else
		{
			m_ArrowSprites[0]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[0]->setFlippedY(true);
			m_ArrowSprites[0]->setTag(0);

		}

		arrowPosition = m_AllStatusChangeValue[SPEED]->getPosition();
		m_ArrowSprites[1]->setPosition(arrowPosition.x - REVISIONARROWPOSITIONX,
									  arrowPosition.y);
		sprintf(buffer, "%.1f", m_ChangeStatus.m_Speed);
		m_AllStatusChangeValue[SPEED]->setString(buffer);
		m_AllStatusChangeValue[SPEED]->setVisible(true);

		m_ArrowSprites[1]->setVisible(true);
		if (m_ChangeStatus.m_Speed >= 0)
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::GREEN);
		}
		else
		{
			m_ArrowSprites[1]->setColor(cocos2d::Color3B::RED);
			m_ArrowSprites[1]->setFlippedY(true);
			m_ArrowSprites[1]->setTag(0);
		}
		break;
	default:
		break;
	}
}

void EquipmentStatusLayer::makeArrowLabels()
{
	float scale = 0.2f;
	auto arrowSprite = GET_RESOURCE_MANAGER()->createSprite(ST_STATUSARROW);
	auto arrowSprite2 = GET_RESOURCE_MANAGER()->createSprite(ST_STATUSARROW);
	auto arrowSprite3 = GET_RESOURCE_MANAGER()->createSprite(ST_STATUSARROW);
	
	
	arrowSprite->setScale(scale);
	arrowSprite2->setScale(scale);
	arrowSprite3->setScale(scale);

	
	//1이면 화살표가 위로인 상태
	//0이면 아래인 상태
	arrowSprite->setTag(1);
	arrowSprite2->setTag(1);
	arrowSprite3->setTag(1);

	m_ArrowSprites.push_back(arrowSprite);
	m_ArrowSprites.push_back(arrowSprite2);
	m_ArrowSprites.push_back(arrowSprite3);

	for (unsigned int i = 0; i < m_ArrowSprites.size(); ++i)
	{
		addChild(m_ArrowSprites[i]);
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
	const EquipmentInfo* equipInfo = GET_DATA_MANAGER()->getEquipmentInfo(m_CurClickedItem.m_Type,
																			m_CurClickedItem.m_ListItem);
	if (equipInfo == nullptr)
	{
		return;
	}

	if (tmpPlayerInfo.m_BitCoin < equipInfo->m_UpgradePrice)
	{
		//실패의 effect소리를 여기다 넣으면 될것 같음
		CCLOG("need more money!");
		return;
	}

	HeadInfo head;
	EngineInfo engine;
	ArmorInfo armor;
	MeleeInfo melee;
	RangeInfo range;
	SteamContainerInfo steamContainer;
	LegInfo leg;


	tmpPlayerInfo.m_BitCoin -= equipInfo->m_UpgradePrice;

	switch (m_CurClickedItem.m_Type)
	{
	case EMT_HEAD:
		head = *static_cast<const HeadInfo*>(equipInfo);
		headUpgrade(&head);
		break;
	case EMT_ENGINE:
		engine = *static_cast<const EngineInfo*>(equipInfo);
		engineUpgrade(&engine);
		break;
	case EMT_ARMOR:
		armor = *static_cast<const ArmorInfo*>(equipInfo);
		armorUpgrade(&armor);
		break;
	case EMT_MELEE:
		melee = *static_cast<const MeleeInfo*>(equipInfo);
		meleeUpgrade(&melee);
		break;
	case EMT_RANGE:
		range = *static_cast<const RangeInfo*>(equipInfo);
		rangeUpgrade(&range);
		break;
	case EMT_STEAMCONTAINTER:
		steamContainer = *static_cast<const SteamContainerInfo*>(equipInfo);
		steamUpgrade(&steamContainer);
		break;
	case EMT_LEG:
		leg = *static_cast<const LegInfo*>(equipInfo);
		legUpgrade(&leg);
		break;
	default:
		break;
	}
	

	

}

void EquipmentStatusLayer::headUpgrade(HeadInfo* headInfo)
{
	_ASSERT(headInfo != nullptr);

	//스킬 쿨타임 
	headInfo->m_SkillCoolTimeDown += 300;

	//메인메모리
	headInfo->m_MainMemory += 200;

	//upgrade price
	headInfo->m_UpgradePrice *= 2;

	GET_DATA_MANAGER()->setEquipmentInfo(m_CurClickedItem.m_Type, 
										 m_CurClickedItem.m_ListItem, headInfo);

}

void EquipmentStatusLayer::setConfirmSet(ConfirmSet confirmSet)
{
	m_CurConfirmSet = confirmSet;
}

void EquipmentStatusLayer::engineUpgrade(EngineInfo* engineInfo)
{
	_ASSERT(engineInfo != nullptr);

	//총 전력량
	engineInfo->m_ElectronicPower += 40;

	//스팀효율량
	engineInfo->m_SteamEffectiveness += 20;

	//upgrade price
	engineInfo->m_UpgradePrice *= 2;

	GET_DATA_MANAGER()->setEquipmentInfo(m_CurClickedItem.m_Type,
										 m_CurClickedItem.m_ListItem, engineInfo);
}

void EquipmentStatusLayer::armorUpgrade(ArmorInfo* armorInfo)
{
	_ASSERT(armorInfo != nullptr);

	//방어력
	armorInfo->m_DefensivePower += 30;

	//저항
	armorInfo->m_Resistance += 20;

	//upgrade price
	armorInfo->m_UpgradePrice *= 2;

	GET_DATA_MANAGER()->setEquipmentInfo(m_CurClickedItem.m_Type,
										 m_CurClickedItem.m_ListItem, armorInfo);
}

void EquipmentStatusLayer::meleeUpgrade(MeleeInfo* meleeInfo)
{
	_ASSERT(meleeInfo != nullptr);

	//공격력
	meleeInfo->m_AttackDamage += 10;

	//공격속도
	meleeInfo->m_AttackSpeed += 10;

	//upgrade price
	meleeInfo->m_UpgradePrice *= 2;

	GET_DATA_MANAGER()->setEquipmentInfo(m_CurClickedItem.m_Type,
										 m_CurClickedItem.m_ListItem, meleeInfo);

}

void EquipmentStatusLayer::rangeUpgrade(RangeInfo* rangeInfo)
{
	_ASSERT(rangeInfo != nullptr);

	//공격력
	rangeInfo->m_AttackDamage += 10;

	//공격속도
	rangeInfo->m_AttackSpeed += 10;

	//공격사거리
	rangeInfo->m_AttackRange += 2;


	//upgrade price
	rangeInfo->m_UpgradePrice *= 2;

	GET_DATA_MANAGER()->setEquipmentInfo(m_CurClickedItem.m_Type,
										 m_CurClickedItem.m_ListItem, rangeInfo);
}

void EquipmentStatusLayer::steamUpgrade(SteamContainerInfo* steamInfo)
{
	_ASSERT(steamInfo != nullptr);

	//Max_steam
	steamInfo->m_MaxSteam += 50;

	//흡수효율
	steamInfo->m_AbsorbEffectiveness += 20;

	//upgrade price
	steamInfo->m_UpgradePrice *= 2;

	GET_DATA_MANAGER()->setEquipmentInfo(m_CurClickedItem.m_Type,
										 m_CurClickedItem.m_ListItem, steamInfo);
}

void EquipmentStatusLayer::legUpgrade(LegInfo* legInfo)
{
	_ASSERT(legInfo != nullptr);

	//점프력
	legInfo->m_jumpPower += 2;

	//이동속도
	legInfo->m_MoveSpeed += 5;

	//upgrade price
	legInfo->m_UpgradePrice *= 2;

	GET_DATA_MANAGER()->setEquipmentInfo(m_CurClickedItem.m_Type,
										 m_CurClickedItem.m_ListItem, legInfo);
}

void EquipmentStatusLayer::confirmSetUpdate()
{
	//이번턴에 뭘골랐는지를 알아야 되네 
	//이번턴에 뭐가 빠졌는지도 알아야돼  
	if (m_CurConfirmSet.m_Head != HL_START)
	{

		HeadInfo head = *static_cast<const HeadInfo*>(GET_DATA_MANAGER()->
													  getEquipmentInfo(EMT_HEAD, m_CurConfirmSet.m_Head));
		m_CurConfirmSetStatus.m_Mainmemory = head.m_MainMemory;
		m_CurConfirmSetStatus.m_CoolDown = head.m_SkillCoolTimeDown;
	}

	if (m_CurConfirmSet.m_Engine != EL_START)
	{

		EngineInfo engine = *static_cast<const EngineInfo*>(GET_DATA_MANAGER()->
															getEquipmentInfo(EMT_ENGINE, m_CurConfirmSet.m_Engine));
		m_CurConfirmSetStatus.m_ElectronicPower = engine.m_ElectronicPower;
		m_CurConfirmSetStatus.m_SteamEffectiveness = engine.m_SteamEffectiveness;
	}

	if (m_CurConfirmSet.m_Steam != SCL_START)
	{

		SteamContainerInfo steam = *static_cast<const SteamContainerInfo*>(GET_DATA_MANAGER()->
																		   getEquipmentInfo(EMT_STEAMCONTAINTER, m_CurConfirmSet.m_Steam));
		m_CurConfirmSetStatus.m_MaxSteam = steam.m_MaxSteam;
		m_CurConfirmSetStatus.m_AbsorbEffectiveness = steam.m_AbsorbEffectiveness;
	}

	if (m_CurConfirmSet.m_Melee != ML_START)
	{

		MeleeInfo melee = *static_cast<const MeleeInfo*>(GET_DATA_MANAGER()->
														 getEquipmentInfo(EMT_MELEE, m_CurConfirmSet.m_Melee));
		m_CurConfirmSetStatus.m_MeleeAttackSpeed = melee.m_AttackSpeed;
		m_CurConfirmSetStatus.m_MeleeDamage = melee.m_AttackDamage;
	}

	if (m_CurConfirmSet.m_Range != RL_START)
	{

		RangeInfo range = *static_cast<const RangeInfo*>(GET_DATA_MANAGER()->
														 getEquipmentInfo(EMT_RANGE, m_CurConfirmSet.m_Range));
		m_CurConfirmSetStatus.m_RangeAttackSpeed = range.m_AttackSpeed;
		m_CurConfirmSetStatus.m_AttackRange = range.m_AttackRange;
		m_CurConfirmSetStatus.m_RangeDamage = range.m_AttackDamage;
	}

	if (m_CurConfirmSet.m_Armor != AL_START)
	{

		ArmorInfo armor = *static_cast<const ArmorInfo*>(GET_DATA_MANAGER()->
														 getEquipmentInfo(EMT_ARMOR, m_CurConfirmSet.m_Armor));
		m_CurConfirmSetStatus.m_DefensivePower = armor.m_DefensivePower;
		m_CurConfirmSetStatus.m_Resistance = armor.m_Resistance;
	}

	if (m_CurConfirmSet.m_Leg != LL_START)
	{
		LegInfo leg = *static_cast<const LegInfo*>(GET_DATA_MANAGER()->
												   getEquipmentInfo(EMT_LEG, m_CurConfirmSet.m_Leg));
		m_CurConfirmSetStatus.m_Speed = leg.m_MoveSpeed;
		m_CurConfirmSetStatus.m_Jump = leg.m_jumpPower;

	}
}

void EquipmentStatusLayer::changeLabelsToInvisible()
{
	for (unsigned int i = 0; i < m_ArrowSprites.size(); ++i)
	{
		m_ArrowSprites[i]->setVisible(false);
	}

	for (AllstatusEnum i = STATUS_ENUM_START; i < STATUS_ENUM_END; i = static_cast<AllstatusEnum>(i + 1))
	{
		m_AllStatusChangeValue[i]->setVisible(false);
	}

}

void EquipmentStatusLayer::equipmentButtonClick()
{
	confirmSetUpdate();

	//AllstatusLabel 업데이트 해주고 
	updateAllStatusLabel();

	//화살표랑 변화된 내용들 사라지기
	changeLabelsToInvisible();
	
}

void EquipmentStatusLayer::updateAllStatusLabel()
{
	char buffer[20] = { 0, };
	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_Mainmemory);
	m_AllStatusValue[MAINMEMORY]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_CoolDown);
	m_AllStatusValue[COOLDOWN]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_ElectronicPower);
	m_AllStatusValue[POWER]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_SteamEffectiveness);
	m_AllStatusValue[STEAM_EFF]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_MaxSteam);
	m_AllStatusValue[MAX_STEAM]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_AbsorbEffectiveness);
	m_AllStatusValue[ABSORB_EFF]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_MeleeDamage);
	m_AllStatusValue[MELEE_DAMAGE]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_MeleeAttackSpeed);
	m_AllStatusValue[MELEE_ATTACK_SPEED]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_RangeAttackSpeed);
	m_AllStatusValue[RANGE_ATTACK_SPEED]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_RangeDamage);
	m_AllStatusValue[RANGE_DAMAGE]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_AttackRange);
	m_AllStatusValue[RANGE_ATTACK_RANGE]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_DefensivePower);
	m_AllStatusValue[ARMOR]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_Resistance);
	m_AllStatusValue[RESISTANCE]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_Jump);
	m_AllStatusValue[JUMP]->setString(buffer);

	sprintf(buffer, "%.1f", m_CurConfirmSetStatus.m_Speed);
	m_AllStatusValue[SPEED]->setString(buffer);

}

bool EquipmentStatusLayer::isDifferenceConfirmSet()
{
	if (m_CurConfirmSet.m_Armor != m_PrevConfirmSet.m_Armor ||
		m_CurConfirmSet.m_Melee != m_PrevConfirmSet.m_Melee ||
		m_CurConfirmSet.m_Head != m_PrevConfirmSet.m_Head ||
		m_CurConfirmSet.m_Leg != m_PrevConfirmSet.m_Leg ||
		m_CurConfirmSet.m_Range != m_PrevConfirmSet.m_Range ||
		m_CurConfirmSet.m_Steam != m_PrevConfirmSet.m_Steam ||
		m_CurConfirmSet.m_Engine != m_PrevConfirmSet.m_Engine)
	{
		m_PrevConfirmSet.m_Armor = m_CurConfirmSet.m_Armor;
		m_PrevConfirmSet.m_Melee = m_CurConfirmSet.m_Melee;
		m_PrevConfirmSet.m_Head = m_CurConfirmSet.m_Head;
		m_PrevConfirmSet.m_Leg = m_CurConfirmSet.m_Leg;
		m_PrevConfirmSet.m_Range = m_CurConfirmSet.m_Range;
		m_PrevConfirmSet.m_Steam = m_CurConfirmSet.m_Steam;
		m_PrevConfirmSet.m_Engine = m_CurConfirmSet.m_Engine;

		return true;
	}

	return false;
}

void EquipmentStatusLayer::updateAllStatus()
{
	if (isDifferenceConfirmSet())
	{

		confirmSetUpdate();

		//AllstatusLabel 업데이트 해주고 
		updateAllStatusLabel();

		//화살표랑 변화된 내용들 사라지기
		changeLabelsToInvisible();
	}
}

