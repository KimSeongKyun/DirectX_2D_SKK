#include "PreCompile.h"
#include "BasicLevel.h"
//#include <GameEngineCore/FadePostEffect.h>

BasicLevel::BasicLevel() 
{
}

BasicLevel::~BasicLevel() 
{
}

void BasicLevel::Start()
{
	GameEngineInput::AddInputObject(this);
}

void BasicLevel::Update(float _Delta)
{
	
}

void BasicLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	//if (FadeEffect == nullptr)
	//{
	//	FadeEffect = GetLevelRenderTarget()->CreateEffect<FadePostEffect>();
	//	FadeEffect->Off();
	//}
}

void BasicLevel::DebugSwitch()
{
	if (GameEngineInput::IsDown('O',this))
	{
		OnDebug();
	}

	if (GameEngineInput::IsDown('P', this))
	{
		OffDebug();
	}
}

//void BasicLevel::FadeOutStart()
//{
//	FadeOut = true;
//}