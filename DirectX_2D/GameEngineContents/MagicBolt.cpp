#include "PreCompile.h"
#include "MagicBolt.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "Monster.h"


MagicBolt::MagicBolt() 
{
}

MagicBolt::~MagicBolt() 
{
}
void MagicBolt::Start()
{
	
	ComponentSetting();

}
void MagicBolt::Update(float _Delta)
{
	MagicBoltUpdate(_Delta);
	MagicBoltColCheck();

	SkillTime += _Delta;
	
	
}

void MagicBolt::MagicBoltUpdate(float _Delta)
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
		if (CurPlayerDirection == 0)
		{
			SkillRenderer1->Transform.SetWorldPosition(PlayerPos1 + float4::LEFT * 50);
			SkillRenderer0->Transform.SetWorldPosition(PlayerPos1 + float4::LEFT * 50);
		}

		if (CurPlayerDirection == 1)
		{
			SkillRenderer1->Transform.SetWorldPosition(PlayerPos1 + float4::RIGHT * 50);
			SkillRenderer0->Transform.SetWorldPosition(PlayerPos1 + float4::RIGHT * 50);
		}
		/*SkillRenderer1->Transform.SetWorldPosition(PlayerPos1);
		SkillRenderer0->Transform.SetWorldPosition(PlayerPos1);*/

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
		
		
		if (MagicBoltShoot == false)
		{
			SkillRenderer1->On();
			ColSkill->On();
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

void MagicBolt::MagicBoltColCheck()
{

	ColSkill->Collision(ObjectCollision::Monster, [&](std::vector<GameEngineCollision*>& _Collisions) {

		std::shared_ptr<Monster> HitMonster = _Collisions[0]->GetActor()->GetDynamic_Cast_This<Monster>();
		HitMonster->Damage(255);
		ColSkill->Off();
		SkillRenderer1->ChangeAnimation("MagicBoltHit");
		});

	
}

void MagicBolt::ComponentSetting()
{
	CurPlayerDirection = static_cast<int>(Player::CurDirection);

	if (nullptr == SkillRenderer0)
	{
		SkillRenderer0 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Skill);
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
		SkillRenderer1->CreateAnimation("MagicBoltHit", "MagicBoltHit", 0.05f);
		SkillRenderer1->ChangeAnimation("MagicBoltBall");
		SkillRenderer1->SetEndEvent("MagicBoltHit", [&](GameEngineSpriteRenderer*) {
			SkillRenderer1->Off();
			Death();
			});
		SkillRenderer1->Off();
	}

	if (nullptr == ColSkill)
	{
		ColSkill = CreateComponent<GameEngineCollision>();
		ColSkill->Transform.SetWorldScale(MagicBoltScale);
		ColSkill->SetCollisionType(ColType::AABBBOX2D);
		ColSkill->Off();
		
	}
}