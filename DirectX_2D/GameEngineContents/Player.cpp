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
	RendererSetting();
}

void Player::Update(float _Delta)
{
	StateUpdate();
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




