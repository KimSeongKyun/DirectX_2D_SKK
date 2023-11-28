#include "PreCompile.h"
#include "Solomon.h"

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
	Timeh += _Delta;
	
	if (Timeh >= 5.0f)
	{
		ChangeState("SolomonAttack3Effect");
		Timeh = 0.0f;
	}
}
void Solomon::SetHP(int _HP)
{

}
void Solomon::Damage(int _Damge)
{

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
		SolomonRender->Transform.AddLocalPosition({- 67.0f, -60.0f });
		SolomonDif = { 0.0f, 0.0f };
	}

	if (SolomonState == "SolomonAttack2Effect")
	{
		SolomonStateE = ESolomonState::Mteor;
		SolomonRender->Transform.AddLocalPosition({ 56.0f, -0.0f });
		SolomonDif = { 9.0f, -12.0f };
	}

	if (SolomonState == "SolomonAttack3Effect")
	{
		SolomonStateE = ESolomonState::Mteor;
		SolomonRender->Transform.AddLocalPosition({ 46.0f, -16.0f });
		SolomonDif = { 9.0f, -12.0f };
	}

	SolomonRender->ChangeAnimation(SolomonState);
	DifCheck = true;
}

void Solomon::ComponentSetting()
{
	SolomonRender = CreateComponent <GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	SolomonRender->CreateAnimation("SolomonStand", "SolomonStand", 0.15f);
	SolomonRender->CreateAnimation("SolomonDie", "SolomonDie", 0.15f);
	SolomonRender->CreateAnimation("SolomonHit", "SolomonHit", 0.15f);
	SolomonRender->CreateAnimation("SolomonAttack1Effect", "SolomonAttack1Effect", 0.15f);
	SolomonRender->CreateAnimation("SolomonAttack2Effect", "SolomonAttack2Effect", 0.15f);
	SolomonRender->CreateAnimation("SolomonAttack3Effect", "SolomonAttack3Effect", 0.15f);
	SolomonRender->AutoSpriteSizeOn();
	SolomonRender->SetPivotType(PivotType::Bottom);
	SolomonRender->ChangeAnimation("SolomonStand");


	std::shared_ptr<GameEngineFrameAnimation> _Animation = SolomonRender->FindAnimation("SolomonAttack1Effect");;
	_Animation->Loop = false;
	_Animation = SolomonRender->FindAnimation("SolomonAttack1Effect");
	_Animation->Loop = false;
	_Animation = SolomonRender->FindAnimation("SolomonAttack2Effect");
	_Animation->Loop = false;
	_Animation = SolomonRender->FindAnimation("SolomonDie");
	_Animation->Loop = false;



	
	SolomonThunder = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	SolomonThunder->CreateAnimation("SolomonAttack1Hit", "SolomonAttack1Hit", 0.15f);
	SolomonThunder->Transform.AddLocalPosition({ 0.0f, 90.0f });
	SolomonThunder->AutoSpriteSizeOn();
	SolomonThunder->ChangeAnimation("SolomonAttack1Hit");
	_Animation = SolomonThunder->FindAnimation("SolomonAttack1Hit");
	_Animation->Loop = false;
	SolomonThunder->Off();
		

	BodyCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetWorldScale({ 124.0f, 144.0f });


	ThunderCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	ThunderCollision->SetCollisionType(ColType::AABBBOX2D);
	ThunderCollision->Transform.SetWorldScale({ 45.0f, 847.0f });
	ThunderCollision->Off();

		
	

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
		SolomonMteor.push_back(SkillRenderer);
	}

}

void Solomon::RenderDifCheck()
{
	if (SolomonRender->IsCurAnimationEnd() == true)
	{
		if (SolomonState != "ArielStand")
		{
			if (DifCheck == true)
			{
				SolomonRender->Transform.AddLocalPosition(-SolomonDif);
				DifCheck = false;
			}
		}
	}
}