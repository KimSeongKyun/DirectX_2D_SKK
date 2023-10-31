#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"
#include "PlayerSkill.h"
#include "Monster.h"

float4 Player::PlayerPos = { 0.0f, 0.0f, 0.0f };
PlayerDirection Player::CurDirection = PlayerDirection::Left;

Player::Player() 
{
	
}

Player::~Player() 
{
}

void Player::Start()
{
	SetObjectSize( PlayerSize );
	GameEngineInput::AddInputObject(this);
	RendererSetting();
	StateInit();

}

void Player::Update(float _Delta)
{
	PlayerPos = Transform.GetWorldPosition();
	FSM.Update(_Delta);
	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Transform.GetLocalPosition());

	if (GameEngineInput::IsDown('A',this))
	{
		MagicBolt();
	}

	if (SkillOn == true)
	{
		SkillTime += _Delta;

		if (SkillTime >= MaxSkillTime != 0.0f)
		{
			Skill0->Death();
			Skill0 = nullptr;
			SkillTime = 0.0f;
			SkillOn = false;
		}
	}
}


void Player::RendererSetting()
{	
	if (nullptr == PlayerBody)
	{
		PlayerBody = CreateComponent<GameEngineSpriteRenderer>(4);
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

void Player::Attack()
{
	//std::shared_ptr<GameEngineCollision> Attack = ColAttack->Collision(static_cast<int>(ContentsObjectType::Monster), );
	//
	//if (Attack == nullptr)
	//{
	//	return;
	//}
	//
	//if (Attack != nullptr)
	//{
	//	std::shared_ptr<Monster> ColMonster = Attack->GetActor()->GetDynamic_Cast_This<Monster>();
	//
	//	ColMonster->Damage(10);
	//}
}

	void Player::MagicBolt()
	{
		if (Skill0 == nullptr)
		{
			Skill0 = GetLevel()->CreateActor<PlayerSkill>(5);
			Skill0->Transform.SetWorldPosition(Transform.GetWorldPosition());
			Skill0->SetSkillName(SkillList::MagicBolt);
			RendererStateChange("Swing");
			MaxSkillTime = 1.0f;
			SkillOn = true;
		}
	}

