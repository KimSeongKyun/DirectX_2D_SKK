#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"



Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	GameEngineInput::AddInputObject(this);
	RendererSetting();
	StateInit();

}

void Player::Update(float _Delta)
{
	FSM.Update(_Delta);
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Transform.GetLocalPosition());
}


void Player::RendererSetting()
{	
	if (nullptr == PlayerBody)
	{
		PlayerBody = CreateComponent<GameEngineSpriteRenderer>(1);
		PlayerBody->CreateAnimation("Idle", "Idle", 0.2f);
		PlayerBody->CreateAnimation("Move", "Move", 0.2f);
		PlayerBody->CreateAnimation("Jump", "Jump", 0.2f);
		PlayerBody->CreateAnimation("Swing0", "Swing0", 0.2f);
		PlayerBody->CreateAnimation("Swing1", "Swing1", 0.2f);
		PlayerBody->CreateAnimation("Swing2", "Swing2", 0.2f);
		PlayerBody->CreateAnimation("Rope", "Rope", 0.2f);
		PlayerBody->CreateAnimation("Ladder", "Ladder", 0.2f);
		PlayerBody->AutoSpriteSizeOn();
		PlayerBody->ChangeAnimation("Idle");
	}
	
}

void Player::RendererStateChange(std::string_view _State)
{
	if (CurPlayerState == _State)
	{
		return;
	}

	CurPlayerState = _State;



	if (_State == "Swing")
	{
		GameEngineRandom Random;
		int SwingNum = Random.RandomInt(0, 2);
		std::string Text = _State.data();

		if (SwingNum == 0)
		{
			PlayerBody->ChangeAnimation(Text + "0");
		}

		if (SwingNum == 1)
		{
			PlayerBody->ChangeAnimation(Text + "1");
		}

		if (SwingNum == 2)
		{
			PlayerBody->ChangeAnimation(Text + "2");
		}
	}
	if (_State != "Swing")
	{
		PlayerBody->ChangeAnimation(_State);
	}
}

void  Player::LRColCheck(float _DeltaTime, float4 _LeftOrRight)
{
	float4 CurPosition = Transform.GetWorldPosition();

	Transform.AddWorldPosition(_LeftOrRight * Speed * _DeltaTime);

	float4 NextPosition = CurPosition + _LeftOrRight * Speed * _DeltaTime;
	if (ColMap->GetColor({ NextPosition.X, -PlayerSize.hY() - NextPosition.Y}, ColColor) == ColColor)
	{
		for (float i = 1.0f; i <= 5.0f; i += _DeltaTime)
		{
			NextPosition += float4::UP * i;
			if (ColMap->GetColor({ NextPosition.X, -PlayerSize.hY() - NextPosition.Y }, ColColor) != ColColor)
			{
				Transform.SetWorldPosition(NextPosition);
				break;
			}

			if (ColMap->GetColor({ NextPosition.X, -PlayerSize.hY() - NextPosition.Y }, ColColor) == ColColor)
			{
				if (i == 5.0f)
				{
					Transform.SetWorldPosition(CurPosition);
				}
				continue;
			}
		}
	}
}



