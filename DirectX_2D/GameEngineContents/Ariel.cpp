#include "PreCompile.h"
#include "Ariel.h"
#include "Player.h"
#include "DamageNumber.h"
#include "DropItem.h"
#include "PinkBeanDummy.h"

Ariel::Ariel() 
{
}

Ariel::~Ariel() 
{
}

void Ariel::Start()
{
	ComponentSetting();
}

void Ariel::Update(float _Delta)
{
	
	if (ArielState == "ArielDie")
	{
		ArielRender->GetColorData().PlusColor.A -= 0.5f * _Delta;
		PinkBeanDummy::Ariel = false;
		return;
	}

	if (false == CognitiveRange->Collision(ObjectCollision::PlayerBody))
	{
		return;
	}
	
	SkillTime += _Delta;

	CoolTimeCheck(_Delta);

	switch (ArielStateE)
	{
	case EArielState::Genesis:
		GenesisUpdate(_Delta);
		break;
	case EArielState::Mteor:
		MteorUpdate(_Delta);
		break;
	default:
		break;
	}
}

void Ariel::GenesisUpdate(float _Delta)
{

	for (size_t i = 0; i < GenesisCollisions.size(); i++)
	{
		GenesisCollisions[i]->Collision(ObjectCollision::PlayerBody, [&](std::vector<GameEngineCollision*>& _Collisions) {

			std::shared_ptr<Player> Player0 = _Collisions[0]->GetActor()->GetDynamic_Cast_This<Player>();
			Player0->Damage(100);
			});
	}
	
	
}

void Ariel::MteorUpdate(float _Delta)
{
	for (size_t i = 0; i < MteorCollisions.size(); i++)
	{
		MteorCollisions[i]->Collision(ObjectCollision::PlayerBody, [&](std::vector<GameEngineCollision*>& _Collisions) {

			std::shared_ptr<Player> Player0 = _Collisions[0]->GetActor()->GetDynamic_Cast_This<Player>();
			Player0->Damage(100);
			});
	}
}

void Ariel::ChangeState(std::string _State)
{
	if (ArielState == _State)
	{
		return;
	}

	RenderDifCheck();
	ArielState = _State;


	if (ArielState == "ArielDie")
	{
		ArielRender->Transform.AddLocalPosition({ 0.0f, -12.0f });
		ArielDif = { 0.0f, -12.0f };
	}

	if (ArielState == "ArielSkill1")
	{
		ArielRender->Transform.AddLocalPosition({ 0.0f, 0.0f });
		ArielDif = { 0.0f, 0.0f };
	}

	if (ArielState == "ArielSkill2")
	{
		ArielRender->Transform.AddLocalPosition({ 0.0f, 21.0f });
		ArielDif = { 0.0f, 21.0f };
	}

	if (ArielState == "ArielAttack1Effect")
	{
		ArielStateE = EArielState::Genesis;
		ArielRender->Transform.AddLocalPosition({ 0.0f, 0.0f });
		ArielDif = { 0.0f, 0.0f };
	}

	if (ArielState == "ArielAttack2Effect")
	{
		ArielStateE = EArielState::Mteor;
		ArielRender->Transform.AddLocalPosition({ 9.0f, -12.0f });
		ArielDif = { 9.0f, -12.0f };
	}

	ArielRender->ChangeAnimation(ArielState);
	DifCheck = true;
}
void Ariel::ComponentSetting()
{
	ArielRender = CreateComponent <GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	ArielRender->CreateAnimation("ArielStand","ArielStand",0.15f,-1,-1,false);
	ArielRender->CreateAnimation("ArielDie", "ArielDie",0.15f, - 1, -1, false);
	ArielRender->CreateAnimation("ArielSkill1", "ArielSkill1",0.15f, - 1, -1, false);
	ArielRender->CreateAnimation("ArielSkill2", "ArielSkill2",0.15f, - 1, -1, false);
	ArielRender->CreateAnimation("ArielAttack1Effect", "ArielAttack1Effect",0.15f, - 1, -1, false);
	ArielRender->CreateAnimation("ArielAttack2Effect", "ArielAttack2Effect",0.15f, - 1, -1, false);
	ArielRender->CreateAnimation("ArielHit", "ArielHit", 0.15f);
	ArielRender->AutoSpriteSizeOn();

	ArielRender->ChangeAnimation("ArielStand");

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineSpriteRenderer> SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
		SkillRenderer->CreateAnimation("ArielAttack1Hit","ArielAttack1Hit",0.15f);
		SkillRenderer->Transform.AddLocalPosition({ 0.0f, 90.0f });
		SkillRenderer->AutoSpriteSizeOn();
		SkillRenderer->ChangeAnimation("ArielAttack1Hit");
		//_Animation = SkillRenderer->FindAnimation("ArielAttack1Hit");
		//_Animation->Loop = false;
		SkillRenderer->Off();
		ArielGenesis.push_back(SkillRenderer);
		
	}
	if (BodyCollision == nullptr)
	{
	BodyCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetWorldScale({ 124.0f, 144.0f });

	}
	if (CognitiveRange == nullptr)
	{
	CognitiveRange = CreateComponent<GameEngineCollision>(ObjectCollision::Range);
	CognitiveRange->SetCollisionType(ColType::AABBBOX2D);
	CognitiveRange->Transform.SetWorldScale({ 600.0f, 500.0f });
	CognitiveRange->Transform.AddLocalPosition(float4::DOWN * 100.0f);
	}

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineCollision> Collision0 = CreateComponent<GameEngineCollision>(ObjectCollision::MonsterSkill);
		Collision0->SetCollisionType(ColType::AABBBOX2D);
		Collision0->Transform.SetWorldScale({ 45.0f, 847.0f });
		Collision0->Off();
		
		GenesisCollisions.push_back(Collision0);
	}

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineCollision> Collision0 = CreateComponent<GameEngineCollision>(ObjectCollision::MonsterSkill);
		Collision0->SetCollisionType(ColType::AABBBOX2D);
		Collision0->Transform.SetWorldScale({ 120.0f, 120.0f });
		Collision0->Off();

		MteorCollisions.push_back(Collision0);
	}

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineSpriteRenderer> SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
		SkillRenderer->CreateAnimation("ArielAttack2Hit", "ArielAttack2Hit", 0.15f);
		SkillRenderer->Transform.AddLocalPosition({ 0.0f, 90.0f });
		SkillRenderer->AutoSpriteSizeOn();
		SkillRenderer->ChangeAnimation("ArielAttack2Hit");
		//_Animation = SkillRenderer->FindAnimation("ArielAttack2Hit");
		//_Animation->Loop = false;
		SkillRenderer->Off();
		ArielMteor.push_back(SkillRenderer);
	}

	ArielGenesis[1]->SetFrameEvent("ArielAttack1Hit", 13, [&](GameEngineSpriteRenderer*)
		{
			for (size_t i = 0; i < 5; i++)
			{
				GenesisCollisions[i]->On();
			}

		});

	ArielGenesis[1]->SetEndEvent("ArielAttack1Hit", [&](GameEngineSpriteRenderer*)
		{

			for (size_t i = 0; i < 5; i++)
			{
				GenesisCollisions[i]->Off();
				ArielGenesis[i]->Off();
			}

			//ChangeState("ArielStand");

		});

	ArielMteor[1]->SetFrameEvent("ArielAttack2Hit", 13, [&](GameEngineSpriteRenderer*)
		{
			for (size_t i = 0; i < 5; i++)
			{
				MteorCollisions[i]->On();
			}

		});

	ArielMteor[1]->SetEndEvent("ArielAttack2Hit", [&](GameEngineSpriteRenderer*)
		{

			for (size_t i = 0; i < 5; i++)
			{
				MteorCollisions[i]->Off();
				ArielMteor[i]->Off();
			}
			

		});

	ArielRender->SetEndEvent("ArielDie", [&](GameEngineSpriteRenderer*) 
		{
			std::shared_ptr<DropItem> DropItem0 = GetLevel()->CreateActor<DropItem>(ContentsObjectType::DamageNumber);
			DropItem0->Transform.SetWorldPosition(Transform.GetWorldPosition());
			
			Death();
		});

}
void Ariel::RenderDifCheck()
{
		if (ArielState != "ArielStand")
		{
			if (DifCheck == true)
			{
				ArielRender->Transform.AddLocalPosition(-ArielDif);
				DifCheck = false;
			}
		}
}
void Ariel::Genesis()
{
	GenesisOn = true;

	for (size_t i = 0; i < 5; i++)
	{
		
		int RandomNum = Random.RandomInt(-385, 385);
		ArielGenesis[i]->On();
		ArielGenesis[i]->ChangeAnimation("ArielAttack1Hit");
		ArielGenesis[i]->Transform.SetLocalPosition({ 0.0f, 55.0f,1.0f });
		ArielGenesis[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });
		
		GenesisCollisions[i]->Transform.SetLocalPosition({ 0.0f, 55.0f,1.0f });
		GenesisCollisions[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });
		GenesisCollisions[i]->Off();
	}

	ChangeState("ArielAttack1Effect");
}

void Ariel::Mteor()
{
	MteorOn = true;

	for (size_t i = 0; i < 5; i++)
	{

		int RandomNum = Random.RandomInt(-385, 385);
		ArielMteor[i]->On();
		ArielMteor[i]->ChangeAnimation("ArielAttack2Hit");
		ArielMteor[i]->Transform.SetLocalPosition({ 0.0f, -105.0f,1.0f });
		ArielMteor[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });

		MteorCollisions[i]->Transform.SetLocalPosition({ 0.0f, -292.0f,1.0f });
		MteorCollisions[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });
		MteorCollisions[i]->Off();
	}

	ChangeState("ArielAttack2Effect");
}

void Ariel::Reflect()
{
	ReflectOn = true;
	ChangeState("ArielSkill1");
	Player::MainPlayer->SetReflect(true);
}

void Ariel::SetHP(int _HP)
{
	HP = _HP;
}

void Ariel::Damage(int _Damge)
{
	
	std::shared_ptr<DamageNumber>Object = GetLevel()->CreateActor<DamageNumber>();
	Object->Transform.SetWorldPosition(Transform.GetWorldPosition());
	Object->Damage(_Damge);

	HP -= _Damge;

	if (HP <= 0)
	{
		BodyCollision->Off();
		ChangeState("ArielDie");
	}

}

void Ariel::CoolTimeCheck(float _Delta)
{
	if (GenesisOn == true)
	{
		GenesisCoolTime += _Delta;

		if (GenesisCoolTime >= 10.0f)
		{
			ChangeState("ArielStand");
			GenesisCoolTime = 1.0f;
			GenesisOn = false;
		}
		return;
	}

	if (MteorOn == true)
	{
		MteorCoolTime += _Delta;

		if (MteorCoolTime >= 10.0f)
		{
			ChangeState("ArielStand");
			MteorCoolTime = 1.0f;
			MteorOn = false;
		}
		return;
	}

	if (ReflectOn == true)
	{
		ReflectCoolTime += _Delta;

		if (ReflectCoolTime >= 20.0f)
		{
			ChangeState("ArielStand");
			ReflectCoolTime = 1.0f;
			ReflectOn = false;
		}
		return;
	}

	int RandomNum = Random.RandomInt(0, 2);

	if (RandomNum == 0)
	{
		Genesis();
	}
	if (RandomNum == 1)
	{
		Mteor();
	}
	if (RandomNum == 2)
	{
		Reflect();
	}
}

void Ariel::RendererSetting()
{
}
