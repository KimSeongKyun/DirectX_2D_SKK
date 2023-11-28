#include "PreCompile.h"
#include "Rex.h"

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
	Timeh += _Delta;
	
	if (Timeh >= 5.0f)
	{
		ChangeState("RexAttack3Effect");
		Timeh = 0.0f;
	}
}
void Rex::SetHP(int _HP)
{

}
void Rex::Damage(int _Damge)
{

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
		RexRender->Transform.AddLocalPosition({ 1.0f, -10.0f });
		RexDif = { 1.0f, -10.0f };
	}

	if (RexState == "RexAttack1Effect")
	{
		RexStateE = ERexState::Thunder;
		RexRender->Transform.AddLocalPosition({ 66.0f, -60.0f });
		RexDif = { 67.0f, -60.0f };
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
		RexDif = { -45.0f, -16.0f };
	}

	RexRender->ChangeAnimation(RexState);
	DifCheck = true;
}

void Rex::ComponentSetting()
{
	RexRender = CreateComponent <GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	RexRender->CreateAnimation("RexStand", "RexStand", 0.15f);
	RexRender->CreateAnimation("RexDie", "RexDie", 0.15f);
	RexRender->CreateAnimation("RexHit", "RexHit", 0.15f);
	RexRender->CreateAnimation("RexAttack1Effect", "RexAttack1Effect", 0.15f);
	RexRender->CreateAnimation("RexAttack2Effect", "RexAttack2Effect", 0.15f);
	RexRender->CreateAnimation("RexAttack3Effect", "RexAttack3Effect", 0.15f);
	RexRender->AutoSpriteSizeOn();
	RexRender->SetPivotType(PivotType::Bottom);
	RexRender->ChangeAnimation("RexStand");


	std::shared_ptr<GameEngineFrameAnimation> _Animation = RexRender->FindAnimation("RexAttack1Effect");;
	_Animation->Loop = false;
	_Animation = RexRender->FindAnimation("RexAttack1Effect");
	_Animation->Loop = false;
	_Animation = RexRender->FindAnimation("RexAttack2Effect");
	_Animation->Loop = false;
	_Animation = RexRender->FindAnimation("RexDie");
	_Animation->Loop = false;



	
	RexThunder = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	RexThunder->CreateAnimation("RexAttack1Hit", "RexAttack1Hit", 0.15f);
	RexThunder->Transform.AddLocalPosition({ 0.0f, 90.0f });
	RexThunder->AutoSpriteSizeOn();
	RexThunder->ChangeAnimation("RexAttack1Hit");
	_Animation = RexThunder->FindAnimation("RexAttack1Hit");
	_Animation->Loop = false;
	RexThunder->Off();
		

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
		RexMteor.push_back(SkillRenderer);
	}

}

void Rex::RenderDifCheck()
{
	if (RexRender->IsCurAnimationEnd() == true)
	{
		if (RexState != "ArielStand")
		{
			if (DifCheck == true)
			{
				RexRender->Transform.AddLocalPosition(-RexDif);
				DifCheck = false;
			}
		}
	}
}