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

}

void Player::Move(float _Delta)
{
	if (IsGravity == true || Attack_Ing == true)
	{
		return;
	}

	SetState(StateType::Move);

	if (true == GameEngineInput::IsPress(VK_RIGHT))
	{
		Transform.AddLocalPosition(float4::RIGHT * Speed * _Delta);
	}

	if (true == GameEngineInput::IsPress(VK_LEFT))
	{
		Transform.AddLocalPosition(float4::LEFT * Speed * _Delta);
	}
}

