#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Monster.h"

// Ό³Έν :
enum class SnaleState
{
	Idle,
	Move
};

class Snale :public Monster
{
public:
	// constrcuter destructer
	Snale();
	~Snale();

	// delete Function
	Snale(const Snale& _Other) = delete;
	Snale(Snale&& _Other) noexcept = delete;
	Snale& operator=(const Snale& _Other) = delete;
	Snale& operator=(Snale&& _Other) noexcept = delete;

	void Damage(int _Damage) override;
	void SetHP(int _HP) override;


protected:
	void Start();
	void Update(float _Delta) override;
	void RendererSetting() override;
	

private:
	std::shared_ptr<class GameEngineCollision> ColBody;
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::string StateString;
	float4 SnaleSize = { 37.0f ,26.0f };
	float StackTime = 0.0f;
	float Speed = 40.0f;
	float TickTime = 0.0f;
	int HP = 100;

	void ComponetSetting();

public:
	void ChangeState(const std::string& _State);



};

