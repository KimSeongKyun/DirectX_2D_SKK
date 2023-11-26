#include <GameEngineCore/GameEngineActor.h>
#pragma once


// Ό³Έν :
class Damage :public GameEngineActor
{
public:
	// constrcuter destructer
	Damage();
	~Damage();

	// delete Function
	Damage(const Damage& _Other) = delete;
	Damage(Damage&& _Other) noexcept = delete;
	Damage& operator=(const Damage& _Other) = delete;
	Damage& operator=(Damage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> Numbers;

};

