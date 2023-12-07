#include "PreCompile.h"
#include "Rex.h"
#include "Player.h"
#include "DamageNumber.h"
#include "PinkBeanDummy.h"

Rex::Rex()
{
}

Rex::~Rex()
{
}

void Rex::Start()
{
	ComponentSetting();
}

void Rex::Update(float _Delta)
{
	//ChangeState("RexAttack1Effect");
	if (RexState == "RexDie")
	{
		RexRender->GetColorData().PlusColor.A -= static_cast<double>(0.5 * _Delta);
		PinkBeanDummy::Rex = false;
		return;
	}

	if (false == CognitiveRange->Collision(ObjectCollision::PlayerBody))
	{
		return;
	}

	RexSkill1->Transform.SetWorldPosition(Player::MainPlayer->Transform.GetWorldPosition());
	RexThunder->Transform.SetWorldPosition({ Player::MainPlayer->Transform.GetWorldPosition().X , -300.0f });

	CoolTimeCheck(_Delta);

	SkillTime += _Delta;
	
	CoolTimeCheck(_Delta);
	
	switch (RexStateE)
	{
	case ERexState::Mteor:
		MteorUpdate(_Delta);
		break;
	default:
		break;
	}
}
void Rex::SetHP(int _HP)
{

}
void Rex::Damage(int _Damge)
{
	std::shared_ptr<DamageNumber>Object = GetLevel()->CreateActor<DamageNumber>();
	Object->Transform.SetWorldPosition(Transform.GetWorldPosition());
	Object->Damage(_Damge);

	HP -= _Damge;

	if (HP <= 0)
	{
		BodyCollision->Off();
		ChangeState("RexDie");
	}
}
void Rex::RendererSetting()
{

}

void Rex::ChangeState(std::string _State)
{
	

	if (RexState == _State)
	{
		return;
	}

	RenderDifCheck();
	RexState = _State;

	if (RexState == "RexStand")
	{
		RexStateE = ERexState::Stand;
	}

	if (RexState == "RexDie")
	{
		RexRender->Transform.AddLocalPosition({ 1.0f, -11.0f });
		RexDif = { 1.0f, -9.0f };
	}

	if (RexState == "RexAttack1Effect")
	{
		RexStateE = ERexState::Thunder;
		RexRender->Transform.AddLocalPosition({ 66.0f, -61.0f });
		RexDif = { 66.0f, -59.0f };
	}

	if (RexState == "RexAttack2Effect")
	{
		RexStateE = ERexState::Mteor;
		RexRender->Transform.AddLocalPosition({ -56.0f, -0.0f });
		RexDif = { -56.0f, -0.0f };
	}

	if (RexState == "RexAttack3Effect")
	{
		RexStateE = ERexState::Mteor;
		RexRender->Transform.AddLocalPosition({ -47.0f, -17.0f });
		RexDif = { -47.0f, -17.0f };
	}

	RexRender->ChangeAnimation(RexState);
	DifCheck = true;
}

void Rex::ComponentSetting()
{

	RexRender = CreateComponent <GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	RexRender->CreateAnimation("RexStand", "RexStand", 0.15f, -1, -1, false);
	RexRender->CreateAnimation("RexDie", "RexDie", 0.15f, -1, -1, false);
	RexRender->CreateAnimation("RexHit", "RexHit", 0.15f, -1, -1, false);
	RexRender->CreateAnimation("RexAttack1Effect", "RexAttack1Effect", 0.15f, -1, -1, false);
	RexRender->CreateAnimation("RexAttack2Effect", "RexAttack2Effect", 0.15f, -1, -1, false);
	RexRender->CreateAnimation("RexAttack3Effect", "RexAttack3Effect", 0.15f, -1, -1, false);
	RexRender->AutoSpriteSizeOn();
	RexRender->SetPivotType(PivotType::Bottom);
	RexRender->ChangeAnimation("RexStand");

	RexThunder = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	RexThunder->CreateAnimation("RexAttack2Hit", "RexAttack2Hit", 0.15f);
	RexThunder->Transform.AddLocalPosition({ 0.0f, 90.0f });
	RexThunder->AutoSpriteSizeOn();
	RexThunder->ChangeAnimation("RexAttack2Hit");
	RexThunder->Off();

	RexSkill1 = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Skill));
	RexSkill1->CreateAnimation("RexAttack3Hit", "RexAttack3Hit", 0.15f);
	RexSkill1->AutoSpriteSizeOn();
	RexSkill1->ChangeAnimation("RexAttack3Hit");
	RexSkill1->Off();

	BodyCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetWorldScale({ 216.0f, 452.0f });
	BodyCollision->Transform.AddWorldPosition(float4::UP * 226);

	CognitiveRange = CreateComponent<GameEngineCollision>(ObjectCollision::Range);
	CognitiveRange->SetCollisionType(ColType::AABBBOX2D);
	CognitiveRange->Transform.SetWorldScale({ 780.0f, 500.0f });
	CognitiveRange->Transform.AddLocalPosition(float4::UP * 210);




	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineSpriteRenderer> SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
		SkillRenderer->CreateAnimation("RexAttack1Hit", "RexAttack1Hit");
		SkillRenderer->Transform.AddLocalPosition({ 0.0f, 90.0f });
		SkillRenderer->AutoSpriteSizeOn();
		SkillRenderer->ChangeAnimation("RexAttack1Hit");
		SkillRenderer->Off();
		RexMteor.push_back(SkillRenderer);
	}

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineCollision> Collision0 = CreateComponent<GameEngineCollision>(ObjectCollision::MonsterSkill);
		Collision0->SetCollisionType(ColType::AABBBOX2D);
		Collision0->Transform.SetWorldScale({ 120.0f, 120.0f });
		Collision0->Off();

		MteorCollisions.push_back(Collision0);
	}

	RexMteor[0]->SetEndEvent("RexAttack1Hit", [&](GameEngineSpriteRenderer*)
		{
			for (size_t i = 0; i < RexMteor.size(); i++)
			{
				RexMteor[i]->Off();
				MteorCollisions[i]->Off();
			}
		});

	RexRender->SetFrameEvent("RexAttack1Effect",11, [&](GameEngineSpriteRenderer*)
		{
			for (size_t i = 0; i < RexMteor.size(); i++)
			{
				RexMteor[i]->On();
				MteorCollisions[i]->On();
			}
		});
	RexRender->SetFrameEvent("RexAttack2Effect", 11, [&](GameEngineSpriteRenderer*)
		{
			RexThunder->On();
			Player::MainPlayer->Damage(156);
		});
	RexThunder->SetEndEvent("RexAttack2Hit", [&](GameEngineSpriteRenderer*)
		{
			RexThunder->Off();
		});

	RexRender->SetFrameEvent("RexAttack3Effect", 11, [&](GameEngineSpriteRenderer*)
		{
			RexSkill1->On();
		});

	RexSkill1->SetEndEvent("RexAttack3Hit", [&](GameEngineSpriteRenderer*)
		{
			RexSkill1->Off();
		});

	RexSkill1->SetFrameEvent("RexAttack3Hit", 3, [&](GameEngineSpriteRenderer*)
		{
			Player::MainPlayer->Damage(256);
	
		});
	RexRender->SetEndEvent("RexDie",  [&](GameEngineSpriteRenderer*)
		{
			Death();

		});
}

void Rex::RenderDifCheck()
{
	
		if (RexState != "RexStand")
		{
			if (DifCheck == true)
			{
				RexRender->Transform.AddLocalPosition(-RexDif);
				DifCheck = false;
			}
		}
	
}

void Rex::Thunder()
{
	ThunderOn = true;

	float4 CurPlayerPos_ = Player::MainPlayer->Transform.GetWorldPosition();
	RexThunder->Off();
	RexThunder->ChangeAnimation("RexAttack2Hit");
	
	

	ChangeState("RexAttack2Effect");
}


void Rex::Mteor()
{
	MteorOn = true;

	for (size_t i = 0; i < 5; i++)
	{

		int RandomNum = Random.RandomInt(-385, 100);
		RexMteor[i]->Off();
		RexMteor[i]->ChangeAnimation("RexAttack1Hit");
		RexMteor[i]->Transform.SetLocalPosition({ 0.0f, 10.0f,1.0f });
		RexMteor[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });

		MteorCollisions[i]->Transform.SetLocalPosition({ 0.0f, 20.0f});
		MteorCollisions[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });
		MteorCollisions[i]->Off();
	}

	ChangeState("RexAttack1Effect");
}

void Rex::Skill1()
{
	
	Skill1On = true;

	float4 CurPlayerPos_ = Player::MainPlayer->Transform.GetWorldPosition();
	
	ChangeState("RexAttack3Effect");
}

void Rex::CoolTimeCheck(float _Delta)
{
	if (ThunderOn == true)
	{
		ThunderCoolTime += _Delta;

		if (ThunderCoolTime >= 10.0f)
		{
			ChangeState("RexStand");
			ThunderCoolTime = 1.0f;
			ThunderOn = false;
		}
		return;
	}

	if (MteorOn == true)
	{
		MteorCoolTime += _Delta;

		if (MteorCoolTime >= 10.0f)
		{
			ChangeState("RexStand");
			MteorCoolTime = 1.0f;
			MteorOn = false;
		}
		return;
	}

	if (Skill1On == true)
	{
		Skill1CoolTime += _Delta;

		if (Skill1CoolTime >= 20.0f)
		{
			ChangeState("RexStand");
			Skill1CoolTime = 1.0f;
			Skill1On = false;
		}
		return;
	}

	int RandomNum = Random.RandomInt(0, 2);

	if (RandomNum == 0)
	{
		Thunder();
	}
	if (RandomNum == 1)
	{
		Mteor();
	}
	if (RandomNum == 2)
	{
		Skill1();
	}
}

void Rex::MteorUpdate(float _Delta)
{
	for (size_t i = 0; i < MteorCollisions.size(); i++)
	{
		MteorCollisions[i]->Collision(ObjectCollision::PlayerBody, [&](std::vector<GameEngineCollision*>& _Collisions) {

			std::shared_ptr<Player> Player0 = _Collisions[0]->GetActor()->GetDynamic_Cast_This<Player>();
			Player0->Damage(250);
			});
	}
}