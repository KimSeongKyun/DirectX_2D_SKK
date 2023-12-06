#include "PreCompile.h"
#include "FadeInOut.h"

FadeInOut::FadeInOut() 
{
}

FadeInOut::~FadeInOut() 
{
}

void FadeInOut::Start()
{
	FadeOutObject = CreateComponent<GameEngineUIRenderer>();
	FadeOutObject->SetSprite("FadeOut.png");
	FadeOutObject->AutoSpriteSizeOn();
	FadeOutObject->Off();
	
	
}
void FadeInOut::Update(float _Delta)
{
	FadeOutObject->Transform.SetWorldPosition({640.0f,-360.0f});

	if (IsFadeIn == true)
	{
		FadeOutObject->GetColorData().PlusColor.A -= _Delta;
		Timeh += _Delta;
	}

	if (IsFadeOut == true)
	{
		FadeOutObject->GetColorData().PlusColor.A += _Delta;
		Timeh += _Delta;
	}

	if (Timeh >= 1.0f)
	{
		if (IsFadeOut == true)
		{
			FadeOutObject->GetColorData().PlusColor.A += 1.0f;
		}

		if (IsFadeIn == true)
		{
			FadeOutObject->GetColorData().PlusColor.A -= 1.0f;
		}
		Timeh = 0.0f;
		FadeOutObject->GetColorData().PlusColor = 0.0f;
		FadeOutObject->Off();
		IsFadeOut = false;
		IsFadeIn = false;
	}
}

void FadeInOut::FadeIn()
{
	FadeOutObject->On();
	IsFadeIn = true;
}
void FadeInOut::FadeOut()
{
	FadeOutObject->GetColorData().PlusColor.A -= 1.0f;
	FadeOutObject->On();
	IsFadeOut = true;
}