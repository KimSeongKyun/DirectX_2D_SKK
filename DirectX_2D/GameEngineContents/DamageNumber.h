#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class DamageNumber :public GameEngineActor
{
public:
	// constrcuter destructer
	DamageNumber();
	~DamageNumber();

	// delete Function
	DamageNumber(const DamageNumber& _Other) = delete;
	DamageNumber(DamageNumber&& _Other) noexcept = delete;
	DamageNumber& operator=(const DamageNumber& _Other) = delete;
	DamageNumber& operator=(DamageNumber&& _Other) noexcept = delete;
	void Damage(int _Damage);

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::vector<std::shared_ptr<GameEngineSpriteRenderer>>NumberLists;
	std::shared_ptr< GameEngineSpriteRenderer>Test0;

	bool IsStart = false;
};

