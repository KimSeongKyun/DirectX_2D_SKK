#include "PreCompile.h"
#include "Player.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include "PlayMap.h"
#include "MagicBolt.h"
#include "Monster.h"
#include "ColdBim.h"
#include "DamageNumber.h"
#include "FrozenOrb.h"

float4 Player::PlayerPos = { 0.0f, 0.0f, 0.0f };
PlayerDirection Player::CurDirection = PlayerDirection::Left;
int Player::HP = 100000;
Player* Player::MainPlayer;
Player::Player() 
{
	MainPlayer = this;
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
	CameraMove(_Delta);
	CoolTimeCount(_Delta);
	ReflectCheck();

	if (GameEngineInput::IsDown('A',this))
	{
		MagicBolt();
	}

	if (GameEngineInput::IsDown('S', this))
	{
		ColdBim();
	}

	if (GameEngineInput::IsDown('V', this))
	{
		Teleport();
	}

	if (GameEngineInput::IsDown('D', this))
	{
		FrozenOrb();
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
		PlayerBody->CreateAnimation("Swing0", "Swing0", 0.1f);
		PlayerBody->CreateAnimation("Swing1", "Swing1", 0.1f);
		PlayerBody->CreateAnimation("Swing2", "Swing2", 0.1f);
		PlayerBody->CreateAnimation("Rope", "Rope", 0.2f);
		PlayerBody->CreateAnimation("RopeMove", "RopeMove");
		PlayerBody->CreateAnimation("Ladder", "Ladder", 0.2f);
		PlayerBody->CreateAnimation("LadderMove", "LadderMove", 0.2f);
		PlayerBody->AutoSpriteSizeOn();
		PlayerBody->ChangeAnimation("Idle");
	}

	if (nullptr == Teleport0)
	{
		Teleport0 = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Skill));
		Teleport0->CreateAnimation("Teleport", "Teleport", 0.05f);
		Teleport0->AutoSpriteSizeOn();
		Teleport0->ChangeAnimation("Teleport");
		Teleport0->SetEndEvent("Teleport", [&](GameEngineSpriteRenderer*) {
			Teleport0->Off();
			});
		Teleport0->Off();
	}
	if (nullptr == ReflectIcon)
	{
		ReflectIcon = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Skill));
		ReflectIcon->SetSprite("ReflectIcon.png");
		ReflectIcon->AutoSpriteSizeOn();
		ReflectIcon->Transform.SetLocalPosition({ 20.0f,40.0f });
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
		float4 ColLadderSize;
		ColLadderSize.X = PlayerSize.hX();
		ColLadderSize.Y = PlayerSize.hY();
		ColLadder->Transform.SetLocalScale(ColLadderSize);
		ColLadder->SetCollisionType(ColType::AABBBOX2D);
		ColLadder->Transform.AddLocalPosition({ 0.0f,-ColLadderSize.hY() });
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
	//std::function<void(std::vector<GameEngineCollision*>& _Collisions)> Collisions;
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
	if (MagicBolt0 == nullptr)
	{
		MagicBolt0 = GetLevel()->CreateActor<class MagicBolt>(5);
		MagicBolt0->Transform.SetWorldPosition(Transform.GetWorldPosition());
		RendererStateChange("Swing");
		MaxSkillTime = 1.0f;
		MagicBoltOn = true;
	}
}

void Player::ColdBim()
{
	if (ColdBim0 == nullptr)
	{
		ColdBim0 = GetLevel()->CreateActor<class ColdBim>(5);
		ColdBim0->Transform.SetWorldPosition(Transform.GetWorldPosition());
		RendererStateChange("Swing");
		MaxSkillTime = 1.0f;
		ColdBimOn = true;
	}
}

void Player::Teleport()
{
	if (TeleportOn == true)
	{
		return;
	}

	Teleport0->On();

	if (GameEngineInput::IsPress(VK_LEFT, this))
	{
		Transform.AddLocalPosition(float4::LEFT * 200);
	}

	if (GameEngineInput::IsPress(VK_RIGHT, this))
	{
		Transform.AddLocalPosition(float4::RIGHT * 200);
	}

	if (GameEngineInput::IsPress(VK_UP, this))
	{
		Transform.AddLocalPosition(float4::UP * 200);
	}

	if (GameEngineInput::IsPress(VK_DOWN, this))
	{
		Transform.AddLocalPosition(float4::DOWN * 150);
	}


	float4 CurPlayerPos = Transform.GetWorldPosition();
	CurPlayerPos.Y = PlayerSize.hY() - CurPlayerPos.Y;
	CurPlayerPos;
	if (ColColor != ColMap->GetColor(CurPlayerPos, ColColor))
	{
		while (ColColor != ColMap->GetColor(CurPlayerPos, ColColor))
		{
			GameEngineColor Test = ColMap->GetColor(CurPlayerPos, ColColor);
			Transform.AddWorldPosition(float4::DOWN);
			CurPlayerPos += float4::UP;
		}
	}
	if (ColColor == ColMap->GetColor(CurPlayerPos, ColColor))
	{
		while (ColColor == ColMap->GetColor(CurPlayerPos, ColColor))
		{
			Transform.AddWorldPosition(float4::UP);
			CurPlayerPos += float4::DOWN;
		}
	}

	TeleportOn = true;
}
void Player::FrozenOrb()
{
	if (FrozenOrb0 == nullptr)
	{
		FrozenOrb0 = GetLevel()->CreateActor<class FrozenOrb>(5);
		FrozenOrb0->Transform.SetWorldPosition(Transform.GetWorldPosition());
		RendererStateChange("Swing");
		MaxSkillTime = 2.0f;
		FrozenOrbOn = true;
	}
}
void Player::ReflectCheck()
{
	if (ReflectOn == true)
	{
		ReflectIcon->On();
	}
	if (ReflectOn == false)
	{
		ReflectIcon->Off();
	}
}

void Player::CoolTimeCount(float _Delta)
{

	if (TeleportOn == true)
	{
		TeleportCoolTime += _Delta;
	}

	if (TeleportCoolTime >= 0.7f)
	{
		TeleportOn = false;
		TeleportCoolTime = 0.0f;
	}

	if (ReflectOn == true)
	{
		ReflectAliveTime += _Delta;
	}

	if (ReflectAliveTime >= 5.0f)
	{
		ReflectAliveTime = 0.0f;
		ReflectOn = false;
	}

	if (Invincibility == true)
	{
		InvincibilityCoolTime += _Delta;
	}

	if (InvincibilityCoolTime >= 1.5f)
	{
		Invincibility = false;
		InvincibilityCoolTime = 0.0f;
	}
	if (ColdBimOn == true)
	{
		SkillTime += _Delta;

		if (SkillTime >= MaxSkillTime != 0.0f)
		{
			ColdBim0->Death();
			ColdBim0 = nullptr;
			SkillTime = 0.0f;
			ColdBimOn = false;
		}
	}

	if (MagicBoltOn == true)
	{
		SkillTime += _Delta;

		if (SkillTime >= MaxSkillTime != 0.0f)
		{
			MagicBolt0->Death();
			MagicBolt0 = nullptr;
			SkillTime = 0.0f;
			MagicBoltOn = false;
		}
	}

	if (FrozenOrbOn == true)
	{
		SkillTime += _Delta;

		if (SkillTime >= MaxSkillTime != 0.0f)
		{
			FrozenOrb0->Death();
			FrozenOrb0 = nullptr;
			SkillTime = 0.0f;
			FrozenOrbOn = false;
		}
	}
}

void Player::Damage(int _Damage)
{
	if (Invincibility == true)
	{
		return;
	}

	HP -= _Damage;

	std::shared_ptr<DamageNumber>Object = GetLevel()->CreateActor<DamageNumber>();
	Object->Transform.SetWorldPosition(Transform.GetWorldPosition());
	Object->Damage(_Damage);
	knockBack();
	Invincibility = true;
}

void Player::knockBack()
{
	JumpPower = { 0.0f, 2.5f, 1.0f };
	IsGravity = true;
	IsKnockBack = true;
	KnockBackPower = 100.0f;
	if (CurDirection == PlayerDirection::Left)
	{
		Directionfloat = float4::LEFT;
	}
	if (CurDirection == PlayerDirection::Right)
	{
		Directionfloat = float4::RIGHT;
	}
	FSM.ChangeState("Jump");
	

}

void Player::SuperKnockBack()
{
	IsKnockBack = true;
	KnockBackPower = 1000.0f;
	JumpPower = { 0.0f, 2.5f, 1.0f };
	if (CurDirection == PlayerDirection::Left)
	{
		Directionfloat = float4::RIGHT;
	}
	if (CurDirection == PlayerDirection::Right)
	{
		Directionfloat = float4::LEFT;
	}
	IsGravity = true;
	FSM.ChangeState("Jump");
}



void Player::CameraMove(float _Delta)
{
	
	PlayerPos = Transform.GetLocalPosition();
	float4 CurCameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 CameraScale = { 1280.0f,720.0f };
	float4 MapScale = CurMap->GetScale();
	float LeftEnd = CameraScale.hX();
	float RightEnd = MapScale.X - CameraScale.hX();
	float UpEnd = -CameraScale.hY();
	float DownEnd = -MapScale.Y + CameraScale.hY();

	GetLevel()->GetMainCamera()->Transform.SetWorldPosition(Transform.GetWorldPosition());
	
	float4 NextCameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

	
	
	float4 LerpValue = float4::LerpClamp(CurCameraPos, NextCameraPos,2* _Delta);

	if (LerpValue.X > RightEnd)
	{
		LerpValue.X = RightEnd;
		CurCameraPos.X = RightEnd;
		
	}

	if (LerpValue.X < LeftEnd)
	{
		LerpValue.X = LeftEnd;
		CurCameraPos.X = LeftEnd;
		
	}

	if (LerpValue.Y > UpEnd)
	{
		LerpValue.Y = UpEnd;
		CurCameraPos.Y = UpEnd;
	
	}

	if (LerpValue.Y < DownEnd)
	{
		LerpValue.Y = DownEnd;
		CurCameraPos.Y = DownEnd;
		
	}

	CurCameraPos;

	GetLevel()->GetMainCamera()->Transform.SetWorldPosition(LerpValue);

	/*if (RightEnd < NextCameraPos.X || NextCameraPos.X < LeftEnd)
	{
		if (UpEnd < NextCameraPos.Y || NextCameraPos.Y < DownEnd)
		{
			NextCameraPos = CurCameraPos;
			GetLevel()->GetMainCamera()->Transform.SetWorldPosition(NextCameraPos);
		}
		else
		{
			NextCameraPos = { CurCameraPos.X, NextCameraPos.Y, NextCameraPos.Z };
			GetLevel()->GetMainCamera()->Transform.SetWorldPosition(NextCameraPos);
		}
	}

	if (UpEnd < NextCameraPos.Y || NextCameraPos.Y < DownEnd)
	{
		if (RightEnd < NextCameraPos.X || NextCameraPos.X < LeftEnd)
		{
			NextCameraPos = CurCameraPos;
			GetLevel()->GetMainCamera()->Transform.SetWorldPosition(NextCameraPos);
		}
		else
		{
			NextCameraPos = { NextCameraPos.X,  CurCameraPos.Y, NextCameraPos.Z };
			GetLevel()->GetMainCamera()->Transform.SetWorldPosition(NextCameraPos);
		}
	}*/
}

