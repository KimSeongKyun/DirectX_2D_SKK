#include "PreCompile.h"
#include "Snale.h"
#include <GameEngineBase/GameEngineRandom.h>

#include "Monster.h"
#include "Player.h"
#include "DamageNumber.h"
#include "ContentsEnum.h"


Snale::Snale()
{
}

Snale::~Snale()
{
}

void Snale::Start()
{
	ComponetSetting();
	SetObjectSize(SnaleSize);
}

void Snale::Update(float _Delta)
{


	StackTime += _Delta;

	if (IsKnockBack() == false)
	{
		IsGravity = true;
		BasicObjectElement::GravityCheck(_Delta);

		if (IsGravity == false)
		{
			if (StackTime < 1.5f)
			{
				float4 CurPos = Transform.GetWorldPosition();
				

				if (StateString == "SnaleLeftMove")
				{
					float4 NextPosition = CurPos + (float4::LEFT * Speed * _Delta);
					Render0->RightFlip();
					Transform.AddWorldPosition(float4::LEFT * Speed * _Delta);

					if (ColMap->GetColor({ NextPosition.X, SnaleSize.hY() - NextPosition.Y }, GetWallColor()) == GetWallColor())
					{
						Transform.SetWorldPosition(CurPos);

					}

				}

				if (StateString == "SnaleRightMove")
				{
					float4 NextPosition = CurPos + (float4::RIGHT * Speed * _Delta);
					Render0->LeftFlip();
					Transform.AddWorldPosition(float4::RIGHT * Speed * _Delta);

					if (ColMap->GetColor(static_cast<unsigned int>(NextPosition.X), static_cast<unsigned int>(GetMonsterSize().hY() - NextPosition.Y), GetWallColor()) == GetWallColor())
					{
						Transform.SetWorldPosition(CurPos);

					}
				}
			}
			if (IsGravity == false && StackTime >= 1.5f)
			{
				
				int RandomNum = Random.RandomInt(0, 2);

				if (RandomNum == 0)
				{
					ChangeState("SnaleIdle");
				}

				if (RandomNum == 1)
				{
					ChangeState("SnaleLeftMove");
				}


				if (RandomNum == 2)
				{
					ChangeState("SnaleRightMove");
				}

				StackTime = 0.0f;
			}

		}
	}

	if (IsKnockBack() == true)
	{
		
		ChangeState("SnaleHit");

		TickTime += _Delta;

		if (TickTime >= 1.0f)
		{
			ChangeState("SnaleIdle");
			ChangeKnockBack();
				
			StackTime = 1.5f;
			TickTime = 0.0f;
		}

		float4 PlayerPos = Player::PlayerPos;
		float4 SnalePos = Transform.GetWorldPosition();

		float KnockBackDirection = SnalePos.X - PlayerPos.X;

		if (TickTime < 0.5f)
		{
			if (KnockBackDirection > 0.0f)
			{
				Render0->RightFlip();
				Transform.AddWorldPosition(float4::RIGHT * Speed * _Delta);
			}

			if (KnockBackDirection <= 0.0f)
			{
				Render0->LeftFlip();
				Transform.AddWorldPosition(float4::LEFT * Speed * _Delta);
			}
		}


	}


}

void Snale::RendererSetting()
{
}


void Snale::Damage(int _Damage)
{
	if(IsKnockBack() == false)
	{
		ChangeKnockBack();
	}
	
	std::shared_ptr<DamageNumber>Object = GetLevel()->CreateActor<DamageNumber>();
	Object->Transform.SetWorldPosition(Transform.GetWorldPosition());
	Object->Damage(_Damage);

	HP -= _Damage;

	if (HP <= 0)
	{
		ChangeState("SnaleDie");

		Death();
	}
}

void Snale::SetHP(int _HP)
{
	HP = _HP;
}

void Snale::ChangeState(const std::string& _State)
{
	if (StateString == _State)
	{
		return;
	}

	if (_State == "SnaleLeftMove" || _State == "SnaleRightMove")
	{
		Render0->ChangeAnimation("SnaleMove");
	}
	else
	{
		Render0->ChangeAnimation(_State);
	}
	StateString = _State;
}
void Snale::ComponetSetting()
{
	Render0 = CreateComponent< GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
	Render0->CreateAnimation("SnaleDie", "SnaleDie", 0.2f);
	Render0->CreateAnimation("SnaleHit", "SnaleHit", 0.2f);
	Render0->CreateAnimation("SnaleIdle", "SnaleIdle", 0.2f);
	Render0->CreateAnimation("SnaleMove", "SnaleMove", 0.2f);
	Render0->ChangeAnimation("SnaleIdle");
	Render0->AutoSpriteSizeOn();

	BodyCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Monster);
	BodyCollision->SetCollisionType(ColType::AABBBOX2D);
	BodyCollision->Transform.SetWorldScale(SnaleSize);
}
