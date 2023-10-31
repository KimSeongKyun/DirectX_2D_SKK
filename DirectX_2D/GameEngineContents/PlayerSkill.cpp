#include "PreCompile.h"
#include "PlayerSkill.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"


PlayerSkill::PlayerSkill() 
{
}

PlayerSkill::~PlayerSkill() 
{
}
void PlayerSkill::Start()
{
	
	ComponentSetting();

}
void PlayerSkill::Update(float _Delta)
{
	if (CurSkill == SkillList::MagicBolt)
	{
		MagicBoltUpdate(_Delta);
		MagicBoltColCheck();
	}

}


void PlayerSkill::SetSkillName(SkillList _Skill)
{
	CurSkill = _Skill;
}

void PlayerSkill::MagicBoltUpdate(float _Delta)
{
	TickTime += _Delta;

	if (TickTime < 0.5f)
	{
		if (DirectionSet == true)
		{
			DirectionSet = false;
			CurPlayerDirection = static_cast<int>(Player::CurDirection);
		}

		float4 PlayerPos1 = Player::PlayerPos;
		SkillRenderer1->Transform.SetWorldPosition(PlayerPos1);
		SkillRenderer0->Transform.SetWorldPosition(PlayerPos1);

		if (true == SkillRenderer0->IsCurAnimationEnd())
		{
			SkillRenderer0->Off();
		}
		//float4 PlayerPos1 = Player::PlayerPos;
		
		
	

		//if (CurPlayerDirection == 0)
		//{
		//	SkillRenderer1->LeftFlip();
		//
		//	SkillRenderer1->Transform.SetLocalPosition(PlayerPos1 + float4::LEFT * 50.0f);
		//	ColSkill->Transform.SetLocalPosition(PlayerPos1 + float4::LEFT * 50.0f);
		//}
		//if (CurPlayerDirection == 1)
		//{
		//	SkillRenderer1->RightFlip();
		//
		//	SkillRenderer1->Transform.SetLocalPosition(PlayerPos1 + float4::RIGHT * 50.0f);
		//	ColSkill->Transform.SetLocalPosition(PlayerPos1 + float4::RIGHT * 50.0f);
		//}
	}

	if (TickTime >= 0.5f)
	{
		
		SkillRenderer1->On();
		ColSkill->On();
		if (MagicBoltShoot == false)
		{
			MagicBoltShoot = true;
			float4 PlayerPos1 = Player::PlayerPos;
			SkillRenderer1->Transform.SetWorldPosition(PlayerPos1);
			ColSkill->Transform.SetWorldPosition(PlayerPos1);
		}
		
		

		if (CurPlayerDirection == 0)
		{
			SkillRenderer1->LeftFlip();
			SkillRenderer1->Transform.AddWorldPosition(float4::LEFT * _Delta * Speed);
			ColSkill->Transform.AddWorldPosition(float4::LEFT * _Delta * Speed);
		}
		if (CurPlayerDirection == 1)
		{
			SkillRenderer1->RightFlip();
			SkillRenderer1->Transform.AddWorldPosition(float4::RIGHT * _Delta * Speed);
			ColSkill->Transform.AddWorldPosition(float4::RIGHT * _Delta * Speed);
		}

		if (SkillRenderer1->IsCurAnimationEnd() == true)
		{
			DirectionSet = true;
		}

	}

	if (TickTime > 1.0f)
	{	
		TickTime = 0.0f;
	}
}

void PlayerSkill::MagicBoltColCheck()
{
	/*ColSkill->Collision(ContentsObjectType::Monster, [&](std::vector<std::shared_ptr<GameEngineCollision>>& _CollisionGroup)
		{
			std::shared_ptr<Monster> HitMonster = ColCheck->GetActor()->DynamicThis<Monster>();
			HitMonster->Damage(10);
			ColSkill->Off();
			SkillRenderer1->Off();
			CurSkill = SkillList::None;
		}
	);
	if (ColSkill != nullptr)
	{
		
	}*/
}

void PlayerSkill::ComponentSetting()
{
	CurPlayerDirection = static_cast<int>(Player::CurDirection);

	if (nullptr == SkillRenderer0)
	{
		SkillRenderer0 = CreateComponent<GameEngineSpriteRenderer>(5);
		SkillRenderer0->CreateAnimation("MagicBoltEffect", "MagicBoltEffect", 0.05f);
		std::shared_ptr<GameEngineFrameAnimation> _Animation = SkillRenderer0->FindAnimation("MagicBoltEffect");
		_Animation->Loop = false;
		SkillRenderer0->Transform.AddLocalPosition({ -50.0f, 0.0f ,1.0f });
		SkillRenderer0->ChangeAnimation("MagicBoltEffect");
		

		if (CurPlayerDirection == 0)
		{
			SkillRenderer0->RightFlip();
		}

		if (CurPlayerDirection == 1)
		{
			SkillRenderer0->LeftFlip();
		}
		//SkillRenderer0->Off();

		SkillRenderer1 = CreateComponent<GameEngineSpriteRenderer>(5);
		SkillRenderer1->CreateAnimation("MagicBoltBall", "MagicBoltBall",0.05f);
		SkillRenderer1->ChangeAnimation("MagicBoltBall");
		SkillRenderer1->Off();
	}

	if (nullptr == ColSkill)
	{
		ColSkill = CreateComponent<GameEngineCollision>();
		ColSkill->Transform.SetWorldScale(MagicBoltScale);
		ColSkill->Off();
	}
}