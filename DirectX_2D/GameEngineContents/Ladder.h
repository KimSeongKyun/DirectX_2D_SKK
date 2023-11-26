#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Ladder : public GameEngineActor
{
public:
	// constrcuter destructer
	Ladder();
	~Ladder();

	// delete Function
	Ladder(const Ladder& _Other) = delete;
	Ladder(Ladder&& _Other) noexcept = delete;
	Ladder& operator=(const Ladder& _Other) = delete;
	Ladder& operator=(Ladder&& _Other) noexcept = delete;


	void SetLadderScale(float4 _Scale);

protected:
	void Start() override;
	void Update(float _delta) override;
private:
	void RenderSetting();

	std::shared_ptr<class GameEngineCollision> LadderCollision;

};

