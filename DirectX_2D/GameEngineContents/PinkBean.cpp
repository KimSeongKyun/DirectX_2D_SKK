#include "PreCompile.h"
#include "PinkBean.h"
#include "Player.h"
#include "PinkBeanUI.h"
#include "DamageNumber.h"

PinkBean* PinkBean::MainPinkBean = nullptr;
PinkBean::PinkBean() 
{
	MainPinkBean = this;
}

PinkBean::~PinkBean() 
{
}

void PinkBean::Start()
{
	RendererSetting();
	GameEngineInput::AddInputObject(this);
	std::shared_ptr< PinkBeanUI> UI = GetLevel()->CreateActor<PinkBeanUI>();
	UI->Transform.AddWorldPosition(float4::RIGHT * 240.0f + float4::DOWN*100.0f);
	ChangeState("PinkBeanApear0");
}
void PinkBean::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_F3, this))
	{
		HP = 1.0f;
		Damage(100);
		
	}
	
	if (PinkBeanState == "PinkBeanDie")
	{
		PinkBeanRender->GetColorData().PlusColor.A -= 0.5f * _Delta;
		return;
	}

	if (PinkBeanState == "PinkBeanMove")
	{
		float4 PlayerPos = Player::MainPlayer->Transform.GetWorldPosition();
		float4 CurPinkBeanPos = Transform.GetWorldPosition();
		float Direction = PlayerPos.X - CurPinkBeanPos.X;
		if (Direction >= 0)
		{
			PinkBeanRender->LeftFlip();
			Transform.AddWorldPosition(float4::RIGHT * 50.0f * _Delta);
		}

		if (Direction < 0)
		{
			PinkBeanRender->RightFlip();
			Transform.AddWorldPosition(float4::LEFT * 50.0f * _Delta);
		}
	}

	SkillTime += _Delta;

	CoolTimeCheck(_Delta);
	GenesisColCheck();

}
void PinkBean::SetHP(int _HP)
{

}
void PinkBean::Damage(int _Damge)
{
	std::shared_ptr<DamageNumber>Object = GetLevel()->CreateActor<DamageNumber>();
	Object->Transform.SetWorldPosition(Transform.GetWorldPosition());
	Object->Damage(_Damge);
	
	HP -= _Damge;
	
	if (HP <= 0)
	{
		PinkBeanCollision->Off();
		ChangeState("PinkBeanDie");
	}
}

void PinkBean::Genesis()
{
	GenesisOn = true;
	ChangeState("PinkBeanGenesis");
	GenesisRender->On();
	AllCoolTimeOn = true;

}

void PinkBean::Reflect()
{
	ReflectOn = true;
	ChangeState("PinkBeanReflect");
	Player::MainPlayer->SetReflect(true);
	AllCoolTimeOn = true;

}

void PinkBean::SuperKnockBack()
{
	KnockBackOn = true;
	ChangeState("PinkBeanSuperKnockBack");
	AllCoolTimeOn = true;
}

void PinkBean::ChangeState(std::string _State)
{

	if (PinkBeanState == _State)
	{
		return;
	}

	RenderDifCheck();
	PinkBeanState = _State;
	PinkBeanRender->ChangeAnimation(PinkBeanState);
	if (PinkBeanState == "PinkBeanDie")
	{
		PinkBeanRender->Transform.AddLocalPosition({ 1.0f, 42.0f });
		PinkBeanDif = { 1.0f, 42.0f };
	}

	if (PinkBeanState == "PinkBeanSuperKnockBack")
	{
		PinkBeanRender->Transform.AddLocalPosition({ -71.0f, 29.0f });
		PinkBeanDif = { -71.0f, 29.0f };
	}

	if (PinkBeanState == "PinkBeanApear0")
	{
		PinkBeanRender->Transform.AddLocalPosition({ -15.0f, 11.0f });
		PinkBeanDif = { -15.0f, 11.0f };
	}

	if (PinkBeanState == "PinkBeanGenesis")
	{
		PinkBeanRender->Transform.AddLocalPosition({ -63.0f, 52.0f });
		PinkBeanDif = { -63.0f, 52.0f };
	}

	if (PinkBeanState == "PinkBeanReflect")
	{

		PinkBeanRender->Transform.AddLocalPosition({ -29.0f, 75.0f });
		PinkBeanDif = { -29.0f, 75.0f };
	}

	if (PinkBeanState == "PinkBeanMove")
	{

		PinkBeanRender->Transform.AddLocalPosition({ 3.0f, 2.0f });
		PinkBeanDif = { 3.0f, 2.0f };
	}

	
	PinkBeanRender->AutoSpriteSizeOn();
	DifCheck = true;
}

void PinkBean::RenderDifCheck()
{

	if (PinkBeanState != "PinkBeanStand")
	{
		if (DifCheck == true)
		{
			PinkBeanRender->Transform.AddLocalPosition(-PinkBeanDif);
			DifCheck = false;
		}
	}

}

void PinkBean::CoolTimeCheck(float _Delta)
{
	if (GenesisOn == true && KnockBackOn == true && ReflectOn == true)
	{
		ChangeState("PinkBeanMove");
	}

	if (GenesisOn == true)
	{
		if (PinkBeanState == "PinkBeanGenesis" )
		{

			if (4.0f <= GenesisCoolTime)
			{
				int a = 0;
				ChangeState("PinkBeanStand");

			}
		}

		GenesisCoolTime += _Delta;

		if (GenesisCoolTime >= 10.0f)
		{
			
			GenesisCoolTime = 0.0f;
			GenesisOn = false;
			
		}
		
	}

	if (KnockBackOn == true)
	{
		if (PinkBeanState == "PinkBeanSuperKnockBack")
		{

			if (3.45f <= KnockBackCoolTime)
			{
				int a = 0;
				ChangeState("PinkBeanStand");
			}
			
		}
		KnockBackCoolTime += _Delta;

		if (KnockBackCoolTime >= 10.0f)
		{
			
			KnockBackCoolTime = 0.0f;
			KnockBackOn = false;
		}
		
	}

	if (ReflectOn == true)
	{
		if (PinkBeanState == "PinkBeanReflect")
		{

			if (2.9f <= ReflectCoolTime )
			{
				int a = 0;
				ChangeState("PinkBeanStand");
			}
		
		}
		ReflectCoolTime += _Delta;


		if (ReflectCoolTime >= 10.0f)
		{
			
			ReflectCoolTime = 0.0f;
			ReflectOn = false;
			return;
		}
		
	}


	

	if (AllCoolTimeOn == true)
	{
		AllCoolTime += _Delta;

		if (AllCoolTime > 5.0f)
		{
			AllCoolTime = 0.0f;
			AllCoolTimeOn = false;
		}
		return;
	}

	if (PinkBeanState == "PinkBeanStand")
	{
		int RandomNum = Random.RandomInt(0, 2);

		if (RandomNum == 0)
		{
			if (GenesisOn == true)
			{
				return;
			}
			Genesis();
		}
		if (RandomNum == 1)
		{
			if (KnockBackOn == true)
			{
				return;
			}
			SuperKnockBack();
		}
		if (RandomNum == 2)
		{
			if (ReflectOn == true)
			{
				return;
			}
			Reflect();
		}
	}
}

void PinkBean::GenesisColCheck()
{
	if ( true == GenesisCollision->Collision(ObjectCollision::PlayerBody))
	{
		int RandomNum = Random.RandomInt(100, 200);
		Player::MainPlayer->Damage(RandomNum);
	}
}

void PinkBean::RendererSetting()
{
	PinkBeanRender = CreateComponent <GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	PinkBeanRender->CreateAnimation("PinkBeanStand", "PinkBeanStand", 0.15f);
	PinkBeanRender->CreateAnimation("PinkBeanDie", "PinkBeanDie", 0.15f, -1, -1, false);
	PinkBeanRender->CreateAnimation("PinkBeanApear0", "PinkBeanApear", 0.15f, -1, -1, false);
	PinkBeanRender->CreateAnimation("PinkBeanGenesis", "PinkBeanGenesis", 0.15f, -1, -1, false);
	PinkBeanRender->CreateAnimation("PinkBeanMove", "PinkBeanMove", 0.15f);
	PinkBeanRender->CreateAnimation("PinkBeanReflect", "PinkBeanReflect", 0.15f, -1, -1, false);
	PinkBeanRender->CreateAnimation("PinkBeanSuperKnockBack", "PinkBeanSuperKnockBack", 0.15f, -1, -1, false);
	PinkBeanRender->AutoSpriteSizeOn();
	PinkBeanRender->ChangeAnimation("PinkBeanStand");

	PinkBeanRender->SetFrameEvent("PinkBeanSuperKnockBack", 17, [&](GameEngineSpriteRenderer*)
		{
			Player::MainPlayer->SuperKnockBack();
		});

	PinkBeanRender->SetFrameEvent("PinkBeanApear0",12, [&](GameEngineSpriteRenderer*)
		{
			//PinkBeanRender->ChangeAnimation("PinkBeanStand");
			ChangeState("PinkBeanStand");
		});

	//PinkBeanRender->SetEndEvent("PinkBeanGenesis", [&](GameEngineSpriteRenderer*)
	//	{
	//		//PinkBeanRender->ChangeAnimation("PinkBeanStand");
	//		ChangeState("PinkBeanStand");
	//	});

	//PinkBeanRender->SetFrameEvent("PinkBeanReflect",18, [&](GameEngineSpriteRenderer*)
	//	{
	//		//PinkBeanRender->ChangeAnimation("PinkBeanStand");
	//		ChangeState("PinkBeanStand");
	//	});

	//PinkBeanRender->SetFrameEvent("PinkBeanSuperKnockBack",22, [&](GameEngineSpriteRenderer*)
	//	{
	//		//PinkBeanRender->ChangeAnimation("PinkBeanStand");
	//		ChangeState("PinkBeanStand");
	//	});

	GenesisRender = CreateComponent <GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Skill));
	GenesisRender->CreateAnimation("PinkBeanGenesisHit", "PinkBeanGenesisHit", 0.15f);
	GenesisRender->ChangeAnimation("PinkBeanGenesisHit");
	GenesisRender->AutoSpriteSizeOn();
	GenesisRender->Transform.AddLocalPosition(float4::UP * 330.0f);
	GenesisRender->Off();

	GenesisRender->SetFrameEvent("PinkBeanGenesisHit", 11, [&](GameEngineSpriteRenderer*) 
		{
			GenesisCollision->On();
		});
	GenesisRender->SetEndEvent("PinkBeanGenesisHit", [&](GameEngineSpriteRenderer*)
		{
			GenesisCollision->Off();
			GenesisRender->Off();
			//PinkBeanRender->ChangeAnimation("PinkBeanStand");
			//ChangeState("PinkBeanStand");
		});

	GenesisCollision = CreateComponent<GameEngineCollision>(ObjectCollision::MonsterSkill);
	GenesisCollision->Transform.SetWorldScale({ 844.0f, 100.0f });
	GenesisCollision->SetCollisionType(ColType::AABBBOX2D);
	GenesisCollision->Off();

	PinkBeanCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	PinkBeanCollision->Transform.SetWorldScale({ 86.0f, 86.0f });
	PinkBeanCollision->SetCollisionType(ColType::AABBBOX2D);
	
}

