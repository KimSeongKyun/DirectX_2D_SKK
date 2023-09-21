#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Ellinia0_Map :public GameEngineActor
{
public:
	// constrcuter destructer
	Ellinia0_Map();
	~Ellinia0_Map();

	// delete Function
	Ellinia0_Map(const Ellinia0_Map& _Other) = delete;
	Ellinia0_Map(Ellinia0_Map&& _Other) noexcept = delete;
	Ellinia0_Map& operator=(const Ellinia0_Map& _Other) = delete;
	Ellinia0_Map& operator=(Ellinia0_Map&& _Other) noexcept = delete;

protected:
	void Start() override;
	

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Ellinia0_Map0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Ellinia0_BackGround = nullptr;
};

