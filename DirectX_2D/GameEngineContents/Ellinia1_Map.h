#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Ellinia1_Map :public GameEngineActor
{
public:
	// constrcuter destructer
	Ellinia1_Map();
	~Ellinia1_Map();

	// delete Function
	Ellinia1_Map(const Ellinia1_Map& _Other) = delete;
	Ellinia1_Map(Ellinia1_Map&& _Other) noexcept = delete;
	Ellinia1_Map& operator=(const Ellinia1_Map& _Other) = delete;
	Ellinia1_Map& operator=(Ellinia1_Map&& _Other) noexcept = delete;

	float4 MapScale;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Ellinia1_Map1 = nullptr;
	
};

