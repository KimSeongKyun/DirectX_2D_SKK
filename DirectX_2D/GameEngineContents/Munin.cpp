#include "PreCompile.h"
#include "Munin.h"
#include "Player.h"
#include "DamageNumber.h"

Munin::Munin() 
{
}

Munin::~Munin() 
{
}

void Munin::Start()
{
	ComponentSetting();
}
void Munin::Update(float _Delta)
{

	if (MuninState == "MuninDie")
	{
		return;
	}
	if (false == CognitiveRange->Collision(ObjectCollision::PlayerBody))
	{
		return;
	}
	
	CoolTimeCheck(_Delta);

}
void Munin::SetHP(int _HP)
{

}
void Munin::Damage(int _Damge)
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
		ChangeState("MuninDie");
	}
}
void Munin::RendererSetting()
{

}

void Munin::ChangeState(std::string _State)
{

	if (MuninState == _State)
	{
		return;
	}

	RenderDifCheck();
	MuninState = _State;

	if (MuninState == "MuninStand")
	{
		
	}

	if (MuninState == "MuninDie")
	{
		MuninRender->Transform.AddLocalPosition({ 8.0f, 6.0f });
		MuninDif = { 8.0f, 6.0f };
	}

	if (MuninState == "MuninAttack1Effect")
	{
		
		MuninRender->Transform.AddLocalPosition({0.0f, 0.0f });
		MuninDif = { 0.0f, 0.0f };
	}

	if (MuninState == "MuninAttack2Effect")
	{
		
		MuninRender->Transform.AddLocalPosition({ 11.0f, 7.0f });
		MuninDif = { 11.0f, 7.0f };
	}

	MuninRender->ChangeAnimation(MuninState);
	DifCheck = true;
}

void Munin::ComponentSetting()
{
	MuninRender = CreateComponent <GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	MuninRender->CreateAnimation("MuninStand", "MuninStand", 0.15f,-1,-1,false);
	MuninRender->CreateAnimation("MuninDie", "MuninDie", 0.15f, -1, -1, false);
	MuninRender->CreateAnimation("MuninAttack1Effect", "MuninAttack1Effect", 0.15f, -1, -1, false);
	MuninRender->CreateAnimation("MuninAttack2Effect", "MuninAttack2Effect", 0.15f, -1, -1, false);
	
	MuninRender->AutoSpriteSizeOn();
	MuninRender->SetPivotType(PivotType::Bottom);
	MuninRender->ChangeAnimation("MuninStand");		

	BodyCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetWorldScale({ 158.0f, 216.0f });
	BodyCollision->Transform.AddLocalPosition(float4::UP * 120.0f +  float4::RIGHT * 10);

	CognitiveRange = CreateComponent<GameEngineCollision>(ObjectCollision::Range);
	CognitiveRange->SetCollisionType(ColType::AABBBOX2D);
	CognitiveRange->Transform.SetWorldScale({ 660.0f, 300.0f });
	CognitiveRange->Transform.AddLocalPosition(float4::UP * 75.0f);

}

void Munin::RenderDifCheck()
{
	
	if (MuninState != "MuninStand")
	{
		if (DifCheck == true)
		{
			MuninRender->Transform.AddLocalPosition(-MuninDif);
			DifCheck = false;
		}
	}

}

void Munin::Reflect()
{
	ReflectOn = true;
	ChangeState("MuninAttack1Effect");
	Player::MainPlayer->SetReflect(true);
}

void Munin::Amor()
{
	AmorOn = true;
	ChangeState("MuninAttack2Effect");
	Player::MainPlayer->SetReflect(true);
}

void Munin::CoolTimeCheck(float _Delta)
{

	if (ReflectOn == true)
	{
		ReflectCoolTime += _Delta;

		if (ReflectCoolTime >= 10.0f)
		{
			ChangeState("MuninStand");
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
			ChangeState("MuninStand");
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
