#include "PreCompile.h"
#include "Whigin.h"
#include "Player.h"
#include "DamageNumber.h"
#include "PinkBeanDummy.h"

Whigin::Whigin() 
{
}

Whigin::~Whigin() 
{
}

void Whigin::Start()
{
	ComponentSetting();
}
void Whigin::Update(float _Delta)
{
	
	if (WhiginState == "WhiginDie")
	{
		WhiginRender->GetColorData().PlusColor.A -= 0.5f * _Delta;
		PinkBeanDummy::Whigin = false;
		return;
	}

	if (false == CognitiveRange->Collision(ObjectCollision::PlayerBody))
	{
		return;
	}

	CoolTimeCheck(_Delta);


}
void Whigin::SetHP(int _HP)
{

}
void Whigin::Damage(int _Damge)
{
	int Damage0 = _Damge;

	if (AmorOn == true)
	{
		Damage0 = 1;
	}
	std::shared_ptr<DamageNumber>Object = GetLevel()->CreateActor<DamageNumber>();
	Object->Transform.SetWorldPosition(Transform.GetWorldPosition());
	Object->Damage(Damage0);

	HP -= Damage0;

	if (HP <= 0)
	{
		BodyCollision->Off();
		ChangeState("WhiginDie");
	}
}
void Whigin::RendererSetting()
{

}

void Whigin::ChangeState(std::string _State)
{

	if (WhiginState == _State)
	{
		return;
	}

	RenderDifCheck();
	WhiginState = _State;


	if (WhiginState == "WhiginDie")
	{
		WhiginRender->Transform.AddLocalPosition({ -2.0f, 5.0f });
		WhiginDif = { -2.0f, 5.0f };
	}

	if (WhiginState == "WhiginAttack1Effect")
	{
		
		WhiginRender->Transform.AddLocalPosition({0.0f, 0.0f });
		WhiginDif = { 0.0f, 0.0f };
	}

	if (WhiginState == "WhiginAttack2Effect")
	{
		
		WhiginRender->Transform.AddLocalPosition({ -11.0f, -0.0f });
		WhiginDif = { -11.0f, -0.0f };
	}

	WhiginRender->ChangeAnimation(WhiginState);
	DifCheck = true;
}

void Whigin::ComponentSetting()
{
	WhiginRender = CreateComponent <GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	WhiginRender->CreateAnimation("WhiginStand", "WhiginStand", 0.15f,-1,-1,false);
	WhiginRender->CreateAnimation("WhiginDie", "WhiginDie", 0.15f, -1, -1, false);
	WhiginRender->CreateAnimation("WhiginAttack1Effect", "WhiginAttack1Effect", 0.15f, -1, -1, false);
	WhiginRender->CreateAnimation("WhiginAttack2Effect", "WhiginAttack2Effect", 0.15f, -1, -1, false);
	
	WhiginRender->AutoSpriteSizeOn();
	WhiginRender->SetPivotType(PivotType::Bottom);
	WhiginRender->ChangeAnimation("WhiginStand");		

	BodyCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetWorldScale({ 158, 216.0f });
	BodyCollision->Transform.AddLocalPosition(float4::UP * 120.0f +  float4::LEFT * 10);

	CognitiveRange = CreateComponent<GameEngineCollision>(ObjectCollision::Range);
	CognitiveRange->SetCollisionType(ColType::AABBBOX2D);
	CognitiveRange->Transform.SetWorldScale({ 660.0f, 300.0f });
	CognitiveRange->Transform.AddLocalPosition(float4::UP * 75.0f);

}

void Whigin::RenderDifCheck()
{
	
	if (WhiginState != "WhiginStand")
	{
		if (DifCheck == true)
		{
			WhiginRender->Transform.AddLocalPosition(-WhiginDif);
			DifCheck = false;
		}
	}

}

void Whigin::Reflect()
{
	ReflectOn = true;
	ChangeState("WhiginAttack1Effect");
	Player::MainPlayer->SetReflect(true);
}

void Whigin::Amor()
{
	AmorOn = true;
	ChangeState("WhiginAttack2Effect");
	Player::MainPlayer->SetReflect(true);
}

void Whigin::CoolTimeCheck(float _Delta)
{

	if (ReflectOn == true)
	{
		ReflectCoolTime += _Delta;

		if (ReflectCoolTime >= 10.0f)
		{
			ChangeState("WhiginStand");
			ReflectCoolTime = 0.0f;
			ReflectOn = false;
		}
		return;
	}
	if (AmorOn == true)
	{
		AmorCoolTime += _Delta;

		if (AmorCoolTime >= 10.0f)
		{
			ChangeState("WhiginStand");
			AmorCoolTime = 0.0f;
			AmorOn = false;
		}
		return;
	}

	int RandomNum = Random.RandomInt(0, 1);

	if (RandomNum == 0)
	{
		Reflect();
	}

	if (RandomNum == 1)
	{
		Amor();
	}
}