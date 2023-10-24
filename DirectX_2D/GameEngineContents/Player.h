#pragma once
#include "BasicObjectElement.h"
#include "GameEngineFSM.h"

enum class StateType
{
	Idle,
	Move,
	Jump,
	Attack,
	Ladder,
	Rope,
};

enum class PlayerDirection
{
	Left,
	Right
};


class Player : public BasicObjectElement
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetColMap(const std::string_view& _ColMap) { ColMap = GameEngineTexture::Find(_ColMap); };
	

protected:
	void Start() override;
	void Update(float _Delta) override;
	void StateInit();

private:
	GameEngineFSM FSM;
	void RendererSetting() override;


	std::string CurPlayerState;

	float Speed = 100.0f;
	float Gravity = 0.0f;

	bool Attack_Ing = false;
	bool IsGravity = false;

	float4 PlayerSize = { 39.0f, 82.0f };
	float4 JumpPower = { 0.0f, 4.5f, 1.0f };

	PlayerDirection CurDirection = PlayerDirection::Left;

	std::shared_ptr<class GameEngineTexture> ColMap;
	
	void SetState(StateType _StateName);
	//void KeySetting();
	void RendererStateChange(std::string_view _State);
	std::shared_ptr<class GameEngineSpriteRenderer> PlayerBody;

	void LRColCheck(float _DeltaTime, float4 _LeftOrRight);
};

