#pragma once

enum class ContentsRenderType
{
	BackGround,
	Play,
};


enum class ContentsObjectType
{
	BackGround,
	Ground,
	Monster,
	Player,
	Skill,
	Object,
	DamageNumber,
	Fade,
};

enum class ObjectCollision
{
	PlayerBody,
	PlayerBodyToLadder,
	PlayerSkill,
	Portal,
	Ladder,
	Rope,
	Monster,
	Range,
	Mouse,
	Item,
	DropItem,
	UI,
};

enum class EItemType
{
	Equip,
	Use,
	Etc,
	Setup,
	Cash
};
