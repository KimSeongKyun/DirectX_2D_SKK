#include "PreCompile.h"
#include "Ariel.h"
#include "DamageNumber.h"

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
	

	SkillTime += _Delta;

	if (SkillTime >= 5.0f)
	{
		Genesis();
		SkillTime = 0.0f;
	}



	switch (ArielStateE)
	{
	case EArielState::Stand:
		StandUpdate(_Delta);
		break;
	case EArielState::Genesis:
		GenesisUpdate(_Delta);
		break;
	case EArielState::Mteor:
		break;
	case EArielState::Die:
		break;
	default:
		break;
	}
}

void Ariel::GenesisUpdate(float _Delta)
{

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
			}

			ChangeState("ArielStand");

		});
	
	
	
	if (ArielState != "ArielStand")
	{
		if (true == ArielRender->IsCurAnimationEnd())
		{
			ChangeState("ArielStand");
			ArielRender->ChangeAnimation("ArielStand");
		}
	}
	
}

void Ariel::StandUpdate(float _Delta)
{

}


void Ariel::ChangeState(std::string _State)
{
	RenderDifCheck();
	ArielState = _State;

	if (ArielState == "ArielStand")
	{
		ArielStateE = EArielState::Stand;
	}

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
	ArielRender->CreateAnimation("ArielStand","ArielStand",0.15f);
	ArielRender->CreateAnimation("ArielDie", "ArielDie",0.15f);
	ArielRender->CreateAnimation("ArielSkill1", "ArielSkill1",0.15f);
	ArielRender->CreateAnimation("ArielSkill2", "ArielSkill2",0.15f);
	ArielRender->CreateAnimation("ArielAttack1Effect", "ArielAttack1Effect",0.15f);
	ArielRender->CreateAnimation("ArielAttack2Effect", "ArielAttack2Effect",0.15f);
	ArielRender->AutoSpriteSizeOn();
	std::shared_ptr<GameEngineFrameAnimation> _Animation;
	//_Animation->Loop = false;
	//_Animation = ArielRender->FindAnimation("ArielSkill1");
	//_Animation->Loop = false;
	//_Animation = ArielRender->FindAnimation("ArielSkill2");
	//_Animation->Loop = false;
	//_Animation = ArielRender->FindAnimation("ArielAttack1Effect");
	//_Animation->Loop = false;
	//_Animation = ArielRender->FindAnimation("ArielAttack2Effect");
	//_Animation->Loop = false;
	

	ArielRender->ChangeAnimation("ArielStand");

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineSpriteRenderer> SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
		SkillRenderer->CreateAnimation("ArielAttack1Hit","ArielAttack1Hit",0.15f);
		SkillRenderer->Transform.AddLocalPosition({ 0.0f, 90.0f });
		SkillRenderer->AutoSpriteSizeOn();
		SkillRenderer->ChangeAnimation("ArielAttack1Hit");
		_Animation = SkillRenderer->FindAnimation("ArielAttack1Hit");
		_Animation->Loop = false;
		SkillRenderer->Off();
		ArielGenesis.push_back(SkillRenderer);
		
	}

	BodyCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetWorldScale({ 124.0f, 144.0f });

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineCollision> Collision0 = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
		Collision0->SetCollisionType(ColType::AABBBOX2D);
		Collision0->Transform.SetWorldScale({ 45.0f, 847.0f });
		Collision0->Off();
		
		GenesisCollisions.push_back(Collision0);
	}

	for (size_t i = 0; i < 5; i++)
	{
		std::shared_ptr< GameEngineSpriteRenderer> SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
		SkillRenderer->CreateAnimation("ArielAttack2Hit", "ArielAttack2Hit", 0.15f);
		SkillRenderer->Transform.AddLocalPosition({ 0.0f, 90.0f });
		SkillRenderer->AutoSpriteSizeOn();
		SkillRenderer->ChangeAnimation("ArielAttack2Hit");
		_Animation = SkillRenderer->FindAnimation("ArielAttack2Hit");
		_Animation->Loop = false;
		SkillRenderer->Off();
		ArielMteor.push_back(SkillRenderer);
	}

	
}
void Ariel::RenderDifCheck()
{
	if (ArielRender->IsCurAnimationEnd() == true)
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
}
void Ariel::Genesis()
{
	SkillOn = true;

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
	//ArielRender->SetFrameEvent("ArielAttack1Effect", 15, {});
}

void Ariel::Mteor()
{
	SkillOn = true;

	for (size_t i = 0; i < 5; i++)
	{

		int RandomNum = Random.RandomInt(-385, 385);
		ArielMteor[i]->On();
		ArielMteor[i]->ChangeAnimation("ArielAttack2Hit");
		ArielMteor[i]->Transform.SetLocalPosition({ 0.0f, -105.0f,1.0f });
		ArielMteor[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f });
	}

	ChangeState("ArielAttack2Effect");
}

void Ariel::SetHP(int _HP)
{
	int a = 0;
}

void Ariel::Damage(int _Damge)
{
	std::shared_ptr<DamageNumber>Object = GetLevel()->CreateActor<DamageNumber>(ContentsObjectType::Object);
	Object->Transform.SetLocalPosition(Transform.GetWorldPosition());

	HP -= _Damge;

	if (HP <= 0)
	{
		ChangeState("ArielDie");
	}
}

void Ariel::RendererSetting()
{
}
