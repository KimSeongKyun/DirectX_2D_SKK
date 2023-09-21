#pragma once
#include "BasicObjectElement.h"

enum class StateType
{
	Idle,
	Move,
	Jump,
	Attack,
	Ladder,
	Rope,
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

	

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	void RendererSetting() override;


	StateType State = StateType::Idle;

	float Speed = 100.0f;

	bool Attack_Ing = false;
	bool IsGravity = false;
	
	void SetState(StateType _StateName);
	void StateUpdate();
	void Move(float _Delta);
	//void KeySetting();

	std::shared_ptr<class GameEngineSpriteRenderer> PlayerBody;


};

