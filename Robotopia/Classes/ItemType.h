/************************************************************************/
/*
CLASS			: ItemType
Author			: 김성연
역할				: Item에 필요한 enum 관리
최종 수정일자		: 2014-11-27
최종 수정자		: 김성연
최종 수정사유		: 신규(아이템 타입)
Comment			:
*/
/************************************************************************/

enum EquipmentType
{
	EMT_START = 0,
	EMT_HEAD,
	EMT_ENGIENE,
	EMT_ARMOR,
	EMT_MELLE,
	EMT_RANGE,
	EMT_STEAMCONTAINTER,
	EMT_LEG,
	EMT_END,
};

enum HeadList
{
	HL_START = 0,
	HL_SINGLE,
	HL_DOUBLE,
	HL_TRIPLE,
	HL_QUAD,
	HL_HEXA,
	HL_END,
};