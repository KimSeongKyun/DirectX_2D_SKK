#include "PreCompile.h"
#include "FrozenOrb.h"
#include "Player.h"
#include "Monster.h"

FrozenOrb::FrozenOrb() 
{
}

FrozenOrb::~FrozenOrb() 
{
}

void FrozenOrb::Start()
{
	ComponentSetting();
}
void FrozenOrb::Update(float _Delta)
{
	TickTime += _Delta;
	ColCheckTime += _Delta;

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

	if (TickTime >= 0.5f && TickTime < 1.0f)
	{


		if (FrozenOrbShoot == false)
		{
			SkillRenderer1->On();
			ColSkill->On();
			FrozenOrbShoot = true;
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


	if (TickTime > 2.0f)
	{
		SkillRenderer1->Off();
		Death();
		TickTime = 0.0f;
	}

	if (ColCheckTime > 0.2f)
	{
		FrozenOrbColCheck();
		ColCheckTime = 0.0f;
	}
}

void FrozenOrb::FrozenOrbColCheck()
{

	ColSkill->Collision(ObjectCollision::Monster, [&](std::vector<GameEngineCollision*>& _Collisions) {

		bool PlayerReflect = Player::MainPlayer->GetReflect();
		int RandomNum = Random.RandomInt(5000, 7000);
		if (true == PlayerReflect)
		{
			Player::MainPlayer->Damage(RandomNum);
			return;
		}
		std::shared_ptr<Monster> HitMonster = _Collisions[0]->GetActor()->GetDynamic_Cast_This<Monster>();
		HitMonster->Damage(RandomNum);
		});


}

void FrozenOrb::ComponentSetting()
{
	if (nullptr == SkillRenderer0)
	{
		SkillRenderer0 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Skill);
		SkillRenderer0->CreateAnimation("FrozenOrbEffect", "FrozenOrbEffect", 0.05f);
		std::shared_ptr<GameEngineFrameAnimation> _Animation = SkillRenderer0->FindAnimation("FrozenOrbEffect");
		_Animation->Loop = false;
		SkillRenderer0->Transform.AddLocalPosition({ -50.0f, 0.0f ,1.0f });
		SkillRenderer0->ChangeAnimation("FrozenOrbEffect");
		SkillRenderer0->AutoSpriteSizeOn();


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
		SkillRenderer1->CreateAnimation("FrozenOrbBall", "FrozenOrbBall", 0.05f);
		SkillRenderer1->ChangeAnimation("FrozenOrbBall");
		SkillRenderer1->AutoSpriteSizeOn();
		//SkillRenderer1->SetEndEvent("FrozenOrbBall", [&](GameEngineSpriteRenderer*) {
		//	Death();
		//	SkillRenderer1->Off();
		//	});
		SkillRenderer1->Off();
	}

	if (nullptr == ColSkill)
	{
		ColSkill = CreateComponent<GameEngineCollision>(ObjectCollision::PlayerSkill);
		ColSkill->Transform.SetWorldScale({ 300.0f,300.0f });
		ColSkill->SetCollisionType(ColType::AABBBOX2D);
		ColSkill->Off();

	}
}