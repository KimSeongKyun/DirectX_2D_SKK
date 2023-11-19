#include "PreCompile.h"
#include "Ariel.h"

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
	RenderDifCheck();

	SkillTime += _Delta;

	if (SkillTime >= 5.0f)
	{
		Genesis();
		SkillTime = 0.0f;
	}

	if (SkillOn == true && ArielGenesis[1]->IsCurAnimationEnd() == true)
	{
		int a = 0;
	}
}

void Ariel::ChangeState(std::string _State)
{
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
		ArielRender->Transform.AddLocalPosition({ 0.0f, 0.0f });
		ArielDif = { 0.0f, 0.0f };
	}

	if (ArielState == "ArielAttack2Effect")
	{
		ArielRender->Transform.AddLocalPosition({ 9.0f, -12.0f });
		ArielDif = { 9.0f, -12.0f };
	}

	ArielRender->ChangeAnimation(ArielState);
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
	std::shared_ptr<GameEngineFrameAnimation> _Animation = ArielRender->FindAnimation("ArielDie");
	_Animation->Loop = false;
	_Animation = ArielRender->FindAnimation("ArielSkill1");
	_Animation->Loop = false;
	_Animation = ArielRender->FindAnimation("ArielSkill2");
	_Animation->Loop = false;
	_Animation = ArielRender->FindAnimation("ArielAttack1Effect");
	_Animation->Loop = false;
	_Animation = ArielRender->FindAnimation("ArielAttack2Effect");
	_Animation->Loop = false;
	

	ArielRender->ChangeAnimation("ArielStand");

	for (size_t i = 0; i < 5; i++)
	{
	
		
		std::shared_ptr< GameEngineSpriteRenderer> SkillRenderer = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
		SkillRenderer->CreateAnimation("ArielAttack1Hit","ArielAttack1Hit",0.15f);
		SkillRenderer->CreateAnimation("ArielAttack2Hit","ArielAttack2Hit",0.15f);
		SkillRenderer->Transform.AddLocalPosition({ 0.0f, 90.0f });
		SkillRenderer->AutoSpriteSizeOn();
		SkillRenderer->ChangeAnimation("ArielAttack1Hit");
		_Animation = SkillRenderer->FindAnimation("ArielAttack1Hit");
		_Animation->Loop = false;
		_Animation = SkillRenderer->FindAnimation("ArielAttack2Hit");
		_Animation->Loop = false;
		SkillRenderer->Off();
		ArielGenesis.push_back(SkillRenderer);
	}

	

	
}
void Ariel::RenderDifCheck()
{
	if (ArielRender->IsCurAnimationEnd() == true)
	{
		if (ArielState != "ArielStand")
		{
			ArielRender->Transform.AddLocalPosition(-ArielDif);
		}
	}
}
void Ariel::Genesis()
{
	SkillOn = true;

	for (size_t i = 0; i < 5; i++)
	{
		GameEngineRandom Random;
		int RandomNum = Random.RandomInt(-385, 385);
		ArielGenesis[i]->On();
		ArielGenesis[i]->ChangeAnimation("ArielAttack1Hit");
		ArielGenesis[i]->Transform.SetLocalPosition({ 0.0f, 55.0f,1.0f });
		ArielGenesis[i]->Transform.AddLocalPosition({ static_cast<float>(RandomNum), 0.0f ,0.0f });
	}

	ArielRender->ChangeAnimation("ArielAttack1Effect");
	//ArielRender->SetFrameEvent("ArielAttack1Effect", 15, {});
}

void Ariel::SetHP(int _HP)
{
	int a = 0;
}

void Ariel::Damage(int _Damge)
{
	int a = 0;
}