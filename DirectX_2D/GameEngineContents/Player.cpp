#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"
#include "PlayerSkill.h"
#include "Monster.h"
#include "DamageNumber.h"

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
	ColSetting();
	StateInit();
	
	/*Test = GetLevel()->CreateActor<DamageNumber>();
	Test->Transform.SetWorldPosition({ 720.0f, -560.0f });
	Test->Damage(100);*/

}

void Player::Update(float _Delta)
{
	
	
	FSM.Update(_Delta);
	CameraMove();
	

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
		PlayerBody = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Player));
		PlayerBody->CreateAnimation("Idle", "Idle", 0.2f);
		PlayerBody->CreateAnimation("Move", "Move", 0.2f);
		PlayerBody->CreateAnimation("Jump", "Jump", 0.2f);
		PlayerBody->CreateAnimation("Swing0", "Swing0", 0.2f);
		PlayerBody->CreateAnimation("Swing1", "Swing1", 0.2f);
		PlayerBody->CreateAnimation("Swing2", "Swing2", 0.2f);
		PlayerBody->CreateAnimation("Rope", "Rope", 0.2f);
		PlayerBody->CreateAnimation("RopeMove", "RopeMove");
		PlayerBody->CreateAnimation("Ladder", "Ladder", 0.2f);
		PlayerBody->AutoSpriteSizeOn();
		PlayerBody->ChangeAnimation("Idle");
	}
	
}

void Player::ColSetting()
{
	if (ColBody == nullptr)
	{
		ColBody = CreateComponent<GameEngineCollision>(ObjectCollision::PlayerBody);
		ColBody->Transform.SetLocalScale(PlayerSize);
		ColBody->SetCollisionType(ColType::AABBBOX2D);
	}
	if (ColLadder == nullptr)
	{
		ColLadder = CreateComponent<GameEngineCollision>(ObjectCollision::PlayerBodyToLadder);
		PlayerSize.X = PlayerSize.hX();
		ColLadder->Transform.SetLocalScale(PlayerSize);
		ColLadder->SetCollisionType(ColType::AABBBOX2D);
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
		for (float i = 1.0f; i < 6.0f; i += _DeltaTime)
		{
			NextPosition += float4::UP * i;
			if (ColMap->GetColor({ NextPosition.X, -PlayerSize.hY() - NextPosition.Y }, ColColor) != ColColor)
			{
				Transform.SetWorldPosition(NextPosition);
				continue;
			}

			if (ColMap->GetColor({ NextPosition.X, -PlayerSize.hY() - NextPosition.Y }, ColColor) == ColColor)
			{
				if (i >= 5.0f)
				{
					int a = 0;
					Transform.SetWorldPosition(CurPosition);
					return;
				}
				
			}
		}
	}

	if (NextPosition.X > CurMap->GetScale().X || NextPosition.X < 0)
	{

	}
}

void Player::RopeCheck()
{	
	std::function<void(std::vector<GameEngineCollision*>& _Collisions)> Collisions;
	ColLadder->Collision(ObjectCollision::Ladder, [&](std::vector<GameEngineCollision*>& _Collisions) {

		float4 PlayerPos1 = Transform.GetWorldPosition();
		PlayerPos1.X = _Collisions[0]->Transform.GetWorldPosition().X;

		Transform.SetWorldPosition(PlayerPos1);

		FSM.ChangeState("Ladder");
	});
	
	ColLadder->Collision(ObjectCollision::Rope, [&](std::vector<GameEngineCollision*>& _Collisions) {
		
		float4 PlayerPos1 = Transform.GetWorldPosition();
		PlayerPos1.X = _Collisions[0]->Transform.GetWorldPosition().X;
		
		Transform.SetWorldPosition(PlayerPos1);

		FSM.ChangeState("Rope");
	});
	
}

void Player::Attack()
{
	ColAttack->Collision(static_cast<int>(ContentsObjectType::Monster), [&](std::vector<GameEngineCollision*>&_Collisions) {
		
			std::shared_ptr<Monster> ColMonster = _Collisions[0]->GetActor()->GetDynamic_Cast_This<Monster>();

			ColMonster->Damage(10);
		
	});
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

void Player::Damage(int Damage)
{

}
void Player::CameraMove()
{
	
	PlayerPos = Transform.GetLocalPosition();
	float4 CurCameraPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();
	float4 CameraScale = { 1280.0f,720.0f };
	float4 MapScale = CurMap->GetScale();
	float LeftEnd = CameraScale.hX();
	float RightEnd = MapScale.X - CameraScale.hX();
	float UpEnd = -CameraScale.hY();
	float DownEnd = -MapScale.Y + CameraScale.hY();

	GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Transform.GetLocalPosition());
	
	float4 NextCameraPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();

	if (RightEnd < NextCameraPos.X || NextCameraPos.X < LeftEnd)
	{
		NextCameraPos = { CurCameraPos.X, NextCameraPos.Y, NextCameraPos.Z };
		GetLevel()->GetMainCamera()->Transform.SetLocalPosition(NextCameraPos);
	}

	if (UpEnd < NextCameraPos.Y || NextCameraPos.Y < DownEnd)
	{
		NextCameraPos = { NextCameraPos.X,  CurCameraPos.Y, NextCameraPos.Z };
		GetLevel()->GetMainCamera()->Transform.SetLocalPosition(NextCameraPos);
	}
}

