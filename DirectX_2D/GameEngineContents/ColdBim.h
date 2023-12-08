#include <GameEngineCore/GameEngineActor.h>
#pragma once

// Ό³Έν :
class ColdBim :public GameEngineActor
{
public:
	// constrcuter destructer
	ColdBim();
	~ColdBim();

	// delete Function
	ColdBim(const ColdBim& _Other) = delete;
	ColdBim(ColdBim&& _Other) noexcept = delete;
	ColdBim& operator=(const ColdBim& _Other) = delete;
	ColdBim& operator=(ColdBim&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	void ComponentSetting();
	void ColdBimUpdate(float _Delta);
	void ColdBimColCheck();

	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer1;
	std::shared_ptr<class GameEngineCollision> ColSkill;

	float TickTime = 0.0f;
	float Speed = 500.0f;

	float4 MagicBoltScale = { 45.0f, 45.0f, 1.0f };

	bool DirectionSet = true;
	bool MagicBoltShoot = false;
	int CurPlayerDirection = 0;

	GameEngineRandom Random;
};

