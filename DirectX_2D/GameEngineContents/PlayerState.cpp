#include "PreCompile.h"
#include "Player.h"

void Player::SetState(StateType _StateName)
{
	if (Attack_Ing == true)
	{
		return;
	}

	if (State == _StateName)
	{
		return;
	}

	State = _StateName;

	switch (State)
	{
	case StateType::Idle:
		PlayerBody->ChangeAnimation("Idle");
		return;
	case StateType::Move:
		PlayerBody->ChangeAnimation("Move");
		return;
	case StateType::Jump:
		PlayerBody->ChangeAnimation("Jump");
		return;
	case StateType::Attack:
		PlayerBody->ChangeAnimation("Attack");
		return;
	case StateType::Ladder:
		PlayerBody->ChangeAnimation("Ladder");
		return;
	case StateType::Rope:
		PlayerBody->ChangeAnimation("Rope");
		return;
	default:
		break;
	}
}

void Player::StateUpdate()
{
	switch (State)
	{
	case StateType::Idle:
		PlayerBody->ChangeAnimation("Idle");
		return;
	case StateType::Move:
		PlayerBody->ChangeAnimation("Move");
		return;
	case StateType::Jump:
		PlayerBody->ChangeAnimation("Jump");
		return;
	case StateType::Attack:
		PlayerBody->ChangeAnimation("Attack");
		return;
	case StateType::Ladder:
		PlayerBody->ChangeAnimation("Ladder");
		return;
	case StateType::Rope:
		PlayerBody->ChangeAnimation("Rope");
		return;
	default:
		break;
	}
}

void Player::Move(float _Delta)
{
	if (IsGravity == true || Attack_Ing == true)
	{
		return;
	}

	SetState(StateType::Move);

	if (true == GameEngineInput::IsPress(VK_RIGHT,this))
	{
		Transform.AddLocalPosition(float4::RIGHT * Speed * _Delta);
	}

	if (true == GameEngineInput::IsPress(VK_LEFT,this))
	{
		Transform.AddLocalPosition(float4::LEFT * Speed * _Delta);
	}
}

void Player::IdleUpdate(float _DeltaTime)
{

}
void Player::MoveUpdate(float _DeltaTime)
{
	//IsGravity = true;

	////GravityCheck(_DeltaTime);


	//if (State != StateType::Attack)
	//{
	//	if (true == GameEngineInput::IsPress(VK_LEFT))
	//	{
	//		LRColCheck(_DeltaTime, float4::LEFT);
	//		Transform.SetLocalPositiveScaleX();
	//		CurDirection = PlayerDirection::Left;
	//	}

	//	if (true == GameEngineInput::IsPress(VK_RIGHT))
	//	{

	//		LRColCheck(_DeltaTime, float4::RIGHT);
	//		//Transform.SetLocalNegativeScaleX();
	//		CurDirection = PlayerDirection::Right;
	//	}

	//	if (true == GameEngineInput::IsPress("X"))
	//	{
	//		IsGravity = true;
	//		SetState(StateType::Jump)
	//	}

	//	/*if (true == GameEngineInput::IsDown("Up"))
	//	{
	//		RopeCheck();
	//	}*/


	//	if (false == GameEngineInput::IsPress(VK_LEFT) &&
	//		false == GameEngineInput::IsPress(VK_RIGHT) &&
	//		false == GameEngineInput::IsPress(VK_UP) &&
	//		false == GameEngineInput::IsPress(VK_DOWN) &&
	//		false == GameEngineInput::IsPress('Z') &&
	//		false == GameEngineInput::IsPress('X'))
	//	{
	//		SetState(StateType::Idle)
	//	}
	//}


	////if (true == GameEngineInput::IsDown('Z'))
	////{
	////	RendererStateChange("Swing");
	////	Attack();
	////}

	//if (CurPlayerState == "Swing")
	//{
	//	if (Body->IsAnimationEnd())
	//	{
	//		RendererStateChange("Idle");
	//	}
	//}

	//float4 Pos = GetTransform()->GetLocalPosition();

	//Pos.z -= 100;


	//GetLevel()->GetMainCamera()->GetTransform()->SetLocalPosition(Pos);
}
void Player::JumpUpdate()
{

}
void Player::AttackUpdate()
{

}
void Player::LadderUpdate()
{

}
void Player::RopeUpdate()
{

}

void Player::LRColCheck(float _DeltaTime, float4 _LeftOrRight)
{
	
		/*float4 CurPosition = Transform.GetWorldPosition();
		float4 ColMapDif = { ColMap->GetScale().hx(),ColMap->GetScale().hy() };

		Transform.AddLocalPosition(_LeftOrRight * Speed * _DeltaTime);

		float4 NextPosition = CurPosition + _LeftOrRight * Speed * _DeltaTime;
		if (ColMap->GetPixel(ColMapDif.iX() + NextPosition.iX(), ColMapDif.iY() + (int)PlayerSize.hy() - NextPosition.iY()) == ColColor)
		{
			for (float i = 1.0f; i <= 5.0f; i += _DeltaTime)
			{
				NextPosition += float4::UP * i;
				if (ColMap->GetPixel(ColMapDif.iX() + NextPosition.iX(), ColMapDif.iY() - i + (int)PlayerSize.hy() - NextPosition.iY()) != ColColor)
				{
					Transform.SetLocalPosition(NextPosition);
					break;
				}

				if (ColMap->GetPixel(ColMapDif.iX() + NextPosition.iX(), ColMapDif.iY() - i + (int)PlayerSize.hy() - NextPosition.iY()) == ColColor)
				{
					if (i == 5.0f)
					{
						Transform.SetLocalPosition(CurPosition);
					}
					continue;
				}
			}
		}
	*/
}

