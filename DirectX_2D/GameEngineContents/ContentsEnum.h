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

};
