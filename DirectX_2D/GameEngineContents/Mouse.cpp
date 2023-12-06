#include "PreCompile.h"
#include "Mouse.h"


Mouse::Mouse() 
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{
	ComponentSetting();
	GameEngineInput::AddInputObject(this);
}

void Mouse::Update(float _Delta)
{
	MousePosUpdate();
	MouseClickCheck( _Delta);
	
	

	if (DoubleClick == true)
	{
		int a = 0;
	}


}

void Mouse::ComponentSetting()
{
	
	MouseImage = CreateComponent<GameEngineUIRenderer>();
	MouseImage->SetSprite("Cursor.png");
	MouseImage->AutoSpriteSizeOn();

	MouseCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Mouse);
	MouseCollision->Transform.SetWorldScale({ 7.0f,7.0f });
	MouseCollision->SetCollisionType(ColType::AABBBOX2D);
	MouseCollision->On();

}

void Mouse::MousePosUpdate()
{
	MousePosSet = GetLevel()->GetMainCamera()->GetScreenMousePos();
	MousePosSet.Y = -MousePosSet.Y;
	float4 Test = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WindowScale = { 640.0f, -360.0f };
	float4 CurWindow = GetLevel()->GetMainCamera()->Transform.GetWorldPosition() - WindowScale;

	
	MouseImage->Transform.SetWorldPosition(MousePosSet + MouseImageDif);
	MouseCollision->Transform.SetLocalPosition(CurWindow + MousePosSet);
}

void Mouse::MouseClickCheck(float _Delta)
{
	if (Click == true)
	{
		ClickTime += _Delta;
	}

	if (ClickTime >= 0.5f)
	{
		Click = false;
		ClickTime = 0.0f;
	}

	if (DoubleClick == true)
	{
		DoubleClick = false;
		ClickTime = 0.0f;

	}

	if (true == GameEngineInput::IsDown(VK_LBUTTON,this))
	{
		if (Click == false)
		{
			Click = true;
			return;
		}

		if (Click == true )
		{
			DoubleClick = true;
			Click = false;
			ClickTime = 0.0f;
			return;
		}

	}

	if (Click == true)
	{
		MouseCollision->On();
	}

	if (Click == false)
	{
		MouseCollision->Off();
	}
}
