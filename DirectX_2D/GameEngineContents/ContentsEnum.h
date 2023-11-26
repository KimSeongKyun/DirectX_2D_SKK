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
	PlayerSkill,
	Object,
	DamageNumber,
};

enum class ObjectCollision
{
	PlayerBody,
	PlayerBodyToLadder,
	Portal,
	Ladder,
	Rope,

};
