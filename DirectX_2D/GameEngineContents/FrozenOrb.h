#include <GameEngineCore/GameEngineActor.h>
#pragma once

// Ό³Έν :
class FrozenOrb :public GameEngineActor
{
public:
	// constrcuter destructer
	FrozenOrb();
	~FrozenOrb();

	// delete Function
	FrozenOrb(const FrozenOrb& _Other) = delete;
	FrozenOrb(FrozenOrb&& _Other) noexcept = delete;
	FrozenOrb& operator=(const FrozenOrb& _Other) = delete;
	FrozenOrb& operator=(FrozenOrb&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
private:
	void ComponentSetting();
	void FrozenOrbColCheck();

	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer1;
	std::shared_ptr<class GameEngineCollision> ColSkill;

	float TickTime = 0.0f;
	float SkillTime = 0.0f;
	float Speed = 500.0f;
	float ColCheckTime = 0.0f;

	//float4 MagicBoltScale = { 45.0f, 45.0f, 1.0f };

	bool DirectionSet = true;
	bool FrozenOrbShoot = false;
	int CurPlayerDirection = 0;

	GameEngineRandom Random;
};

