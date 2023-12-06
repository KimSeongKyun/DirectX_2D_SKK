#include "PreCompile.h"
#include "Solomon.h"
#include "Player.h"
#include "DamageNumber.h"

Solomon::Solomon()
{
}

Solomon::~Solomon()
{
}

void Solomon::Start()
{
	ComponentSetting();
}

void Solomon::Update(float _Delta)
{
	//ChangeState("SolomonAttack1Effect");
	if (SolomonState == "SolomonDie")
	{
		SolomonRender->GetColorData().PlusColor.A -= 0.5f * _Delta;
		return;
	}
	
	if (false == CognitiveRange1->Collision(ObjectCollision::PlayerBodyToLadder))
	{
		return;
	}

	SolomonSkill1->Transform.SetWorldPosition(Player::MainPlayer->Transform.GetWorldPosition());
	SolomonThunder->Transform.SetWorldPosition({ Player::MainPlayer->Transform.GetWorldPosition().X , -300.0f });

	CoolTimeCheck(_Delta);

	SkillTime += _Delta;
	
	CoolTimeCheck(_Delta);
	
	switch (SolomonStateE)
	{
	case ESolomonState::Mteor:
		MteorUpdate(_Delta);
		break;
	default:
		break;
	}
}
void Solomon::SetHP(int _HP)
{

}
void Solomon::Damage(int _Damge)
{
	std::shared_ptr<DamageNumber>Object = GetLevel()->CreateActor<DamageNumber>();
	Object->Transform.SetWorldPosition(Transform.GetWorldPosition());
	Object->Damage(_Damge);

	HP -= _Damge;

	if (HP <= 0)
	{
		BodyCollision->Off();
		ChangeState("SolomonDie");
	}
}
void Solomon::RendererSetting()
{

}

void Solomon::ChangeState(std::string _State)
{
	

	if (SolomonState == _State)
	{
		return;
	}

	RenderDifCheck();
	SolomonState = _State;

	if (SolomonState == "SolomonStand")
	{
		SolomonStateE = ESolomonState::Stand;
	}

	if (SolomonState == "SolomonDie")
	{
		SolomonRender->Transform.AddLocalPosition({ -1.0f, -10.0f });
		SolomonDif = { -1.0f, -10.0f };
	}

	if (SolomonState == "SolomonAttack1Effect")
	{
		SolomonStateE = ESolomonState::Thunder;
		SolomonRender->Transform.AddLocalPosition({ -67.0f, -60.0f });
		SolomonDif = { -67.0f, -60.0f };
	}

	if (SolomonState == "SolomonAttack2Effect")
	{
		SolomonStateE = ESolomonState::Mteor;
		SolomonRender->Transform.AddLocalPosition({ 56.0f, -0.0f });
		SolomonDif = { 56.0f, -0.0f };
	}

	if (SolomonState == "SolomonAttack3Effect")
	{
		SolomonStateE = ESolomonState::Mteor;
		SolomonRender->Transform.AddLocalPosition({ 46.0f, -16.0f });
		SolomonDif = { 46.0f, -16.0f };
	}

	SolomonRender->ChangeAnimation(SolomonState);
	DifCheck = true;
}

void Solomon::ComponentSetting()
{

	SolomonRender = CreateComponent <GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	SolomonRender->CreateAnimation("SolomonStand", "SolomonStand", 0.15f, -1, -1, false);
	SolomonRender->CreateAnimation("SolomonDie", "SolomonDie", 0.15f, -1, -1, false);
	SolomonRender->CreateAnimation("SolomonHit", "SolomonHit", 0.15f, -1, -1, false);
	SolomonRender->CreateAnimation("SolomonAttack1Effect", "SolomonAttack1Effect", 0.15f, -1, -1, false);
	SolomonRender->CreateAnimation("SolomonAttack2Effect", "SolomonAttack2Effect", 0.15f, -1, -1, false);
	SolomonRender->CreateAnimation("SolomonAttack3Effect", "SolomonAttack3Effect", 0.15f, -1, -1, false);
	SolomonRender->AutoSpriteSizeOn();
	SolomonRender->SetPivotType(PivotType::Bottom);
	SolomonRender->ChangeAnimation("SolomonStand");

	SolomonThunder = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	SolomonThunder->CreateAnimation("SolomonAttack2Hit", "SolomonAttack2Hit", 0.15f);
	SolomonThunder->Transform.AddLocalPosition({ 0.0f, 90.0f });
	SolomonThunder->AutoSpriteSizeOn();
	SolomonThunder->ChangeAnimation("SolomonAttack2Hit");
	SolomonThunder->Off();

	SolomonSkill1 = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Skill));
	SolomonSkill1->CreateAnimation("SolomonAttack3Hit", "SolomonAttack3Hit", 0.15f);
	SolomonSkill1->AutoSpriteSizeOn();
	SolomonSkill1->ChangeAnimation("SolomonAttack3Hit");
	SolomonSkill1->Off();

	BodyCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetWorldScale({ 216.0f, 452.0f });
	BodyCollision->Transform.AddWorldPosition(float4::UP * 226);

	CognitiveRange1 = CreateComponent<GameEngineCollision>(ObjectCollision::Range);
	CognitiveRange1->SetCollisionType(ColType::AABBBOX2D);
	CognitiveRange1->Transform.SetWorldScale({ 780.0f, 500.0f });
	CognitiveRange1->Transform.AddLocalPosition(float4::UP * 210);




	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineSpriteRenderer> SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
		SkillRenderer->CreateAnimation("SolomonAttack1Hit", "SolomonAttack1Hit");
		SkillRenderer->Transform.AddLocalPosition({ 0.0f, 90.0f });
		SkillRenderer->AutoSpriteSizeOn();
		SkillRenderer->ChangeAnimation("SolomonAttack1Hit");
		SkillRenderer->Off();
		SolomonMteor.push_back(SkillRenderer);
	}

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineCollision> Collision0 = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
		Collision0->SetCollisionType(ColType::AABBBOX2D);
		Collision0->Transform.SetWorldScale({ 120.0f, 120.0f });
		Collision0->Off();

		MteorCollisions.push_back(Collision0);
	}

	SolomonMteor[0]->SetEndEvent("SolomonAttack1Hit", [&](GameEngineSpriteRenderer*)
		{
			for (size_t i = 0; i < SolomonMteor.size(); i++)
			{
				SolomonMteor[i]->Off();
				MteorCollisions[i]->Off();
			}
		});

	SolomonRender->SetFrameEvent("SolomonAttack1Effect",11, [&](GameEngineSpriteRenderer*)
		{
			for (size_t i = 0; i < SolomonMteor.size(); i++)
			{
				SolomonMteor[i]->On();
				MteorCollisions[i]->On();
			}
		});
	SolomonRender->SetFrameEvent("SolomonAttack2Effect", 11, [&](GameEngineSpriteRenderer*)
		{
			SolomonThunder->On();
			Player::MainPlayer->Damage(156);
		});
	SolomonThunder->SetEndEvent("SolomonAttack2Hit", [&](GameEngineSpriteRenderer*)
		{
			SolomonThunder->Off();
		});

	SolomonRender->SetFrameEvent("SolomonAttack3Effect", 11, [&](GameEngineSpriteRenderer*)
		{
			SolomonSkill1->On();
		});

	SolomonSkill1->SetEndEvent("SolomonAttack3Hit", [&](GameEngineSpriteRenderer*)
		{
			SolomonSkill1->Off();
		});

	SolomonSkill1->SetFrameEvent("SolomonAttack3Hit", 3, [&](GameEngineSpriteRenderer*)
		{
			Player::MainPlayer->Damage(256);
	
		});
	SolomonRender->SetEndEvent("SolomonDie",  [&](GameEngineSpriteRenderer*)
		{
			Death();

		});
}

void Solomon::RenderDifCheck()
{
	
	if (SolomonState != "SolomonStand")
	{
		if (DifCheck == true)
		{
			SolomonRender->Transform.AddLocalPosition(-SolomonDif);
			DifCheck = false;
		}
	}
	
}

void Solomon::Thunder()
{
	ThunderOn = true;

	float4 CurPlayerPos_ = Player::MainPlayer->Transform.GetWorldPosition();
	SolomonThunder->Off();
	SolomonThunder->ChangeAnimation("SolomonAttack2Hit");
	
	

	ChangeState("SolomonAttack2Effect");
}


void Solomon::Mteor()
{
	MteorOn = true;

	for (size_t i = 0; i < 5; i++)
	{

		int RandomNum = Random.RandomInt(-385, 100);
		SolomonMteor[i]->Off();
		SolomonMteor[i]->ChangeAnimation("SolomonAttack1Hit");
		SolomonMteor[i]->Transform.SetLocalPosition({ 0.0f, 10.0f,1.0f });
		SolomonMteor[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });

		MteorCollisions[i]->Transform.SetLocalPosition({ 0.0f, 20.0f});
		MteorCollisions[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });
		MteorCollisions[i]->Off();
	}

	ChangeState("SolomonAttack1Effect");
}

void Solomon::Skill1()
{
	
	Skill1On = true;

	float4 CurPlayerPos_ = Player::MainPlayer->Transform.GetWorldPosition();
	
	ChangeState("SolomonAttack3Effect");
}

void Solomon::CoolTimeCheck(float _Delta)
{
	if (ThunderOn == true)
	{
		ThunderCoolTime += _Delta;

		if (ThunderCoolTime >= 10.0f)
		{
			ChangeState("SolomonStand");
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
			ChangeState("SolomonStand");
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
			ChangeState("SolomonStand");
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

void Solomon::MteorUpdate(float _Delta)
{
	for (size_t i = 0; i < MteorCollisions.size(); i++)
	{
		MteorCollisions[i]->Collision(ObjectCollision::PlayerBody, [&](std::vector<GameEngineCollision*>& _Collisions) {

			std::shared_ptr<Player> Player0 = _Collisions[0]->GetActor()->GetDynamic_Cast_This<Player>();
			Player0->Damage(250);
			});
	}
}