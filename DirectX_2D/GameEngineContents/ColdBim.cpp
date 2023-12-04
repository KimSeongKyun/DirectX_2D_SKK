#include "PreCompile.h"
#include "ColdBim.h"
#include "Player.h"
#include "Monster.h"

ColdBim::ColdBim() 
{
}

ColdBim::~ColdBim() 
{
}

void ColdBim::Start()
{
	ComponentSetting();
}
void ColdBim::Update(float _Delta)
{
	
	ColdBimUpdate(_Delta);
	ColdBimColCheck();

}

void ColdBim::ComponentSetting()
{
	SkillRenderer0 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Skill);
	SkillRenderer0->CreateAnimation("ColdBimBodyEffect", "ColdBimBodyEffect",0.05f);
	SkillRenderer0->ChangeAnimation("ColdBimBodyEffect");
	SkillRenderer0->AutoSpriteSizeOn();

	SkillRenderer1 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Skill);
	SkillRenderer1->CreateAnimation("ColdBimObjEffect", "ColdBimObjEffect",0.05f);
	SkillRenderer1->ChangeAnimation("ColdBimObjEffect");
	SkillRenderer1->AutoSpriteSizeOn();

	

	ColSkill = CreateComponent<GameEngineCollision>(ObjectCollision::PlayerSkill);
	ColSkill->SetCollisionType(ColType::AABBBOX2D);
	ColSkill->Transform.SetWorldScale({300.0f, 300.0f});
	ColSkill->Off();

	SkillRenderer1->SetEndEvent("ColdBimObjEffect", [&](GameEngineSpriteRenderer*)
		{

			SkillRenderer1->Off();
			SkillRenderer0->Off();
			ColSkill->Off();
			DirectionSet = true;
		});
	SkillRenderer1->SetFrameEvent("ColdBimObjEffect", 6, [&](GameEngineSpriteRenderer*)
		{
			ColSkill->On();
			ColSkill->Transform.SetWorldPosition(SkillRenderer1->Transform.GetWorldPosition() + float4::UP * 25.0f);
			float4 Testfloat = ColSkill->Transform.GetWorldPosition();
		});
}

void ColdBim::ColdBimUpdate(float _Delta)
{
	TickTime += _Delta;
	float4 PlayerPos1 = Player::PlayerPos;
	if (DirectionSet == true)
	{
		DirectionSet = false;
		CurPlayerDirection = static_cast<int>(Player::CurDirection);

		if (CurPlayerDirection == 0)
		{
			
			SkillRenderer1->Transform.SetWorldPosition(PlayerPos1 + float4::LEFT * 200 + float4::UP * 85.0f);
		}

		if (CurPlayerDirection == 1)
		{
			
			SkillRenderer1->Transform.SetWorldPosition(PlayerPos1 + float4::RIGHT * 200 + float4::UP * 85.0f);
		}
	}

	
	if (CurPlayerDirection == 0)
	{
		SkillRenderer0->Transform.SetWorldPosition(PlayerPos1 + float4::LEFT * 40);
		
	}

	if (CurPlayerDirection == 1)
	{
		SkillRenderer0->Transform.SetWorldPosition(PlayerPos1 + float4::RIGHT * 40);
		
	}

	if (true == SkillRenderer0->IsCurAnimationEnd())
	{
		SkillRenderer0->Off();
	}

	if (TickTime > 1.0f)
	{
		TickTime = 0.0f;
	}
}

void ColdBim::ColdBimColCheck()
{
	ColSkill->Collision(ObjectCollision::Monster, [&](std::vector<GameEngineCollision*>& _Collisions) {

		for (size_t i = 0; i < _Collisions.size(); i++)
		{
			bool PlayerReflect = Player::MainPlayer->GetReflect();
			if (true == PlayerReflect)
			{
				Player::MainPlayer->Damage(20);
				return;
			}
			std::shared_ptr<Monster> HitMonster = _Collisions[i]->GetActor()->GetDynamic_Cast_This<Monster>();
			HitMonster->Damage(100);
			ColSkill->Off();
			std::shared_ptr<GameEngineSpriteRenderer> HitEffect;
			HitEffect = CreateComponent< GameEngineSpriteRenderer>(ContentsObjectType::Skill);
			HitEffect->CreateAnimation("ColdBimHit", "ColdBimHit", 0.05f,-1,-1,false);
			HitEffect->ChangeAnimation("ColdBimHit");
			HitEffect->Transform.SetWorldPosition(HitMonster->Transform.GetWorldPosition());
			
				
		}
		
		});
}
