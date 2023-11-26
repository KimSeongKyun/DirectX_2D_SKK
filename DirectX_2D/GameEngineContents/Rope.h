#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Rope : public GameEngineActor
{
public:
	// constrcuter destructer
	Rope();
	~Rope();

	// delete Function
	Rope(const Rope& _Other) = delete;
	Rope(Rope&& _Other) noexcept = delete;
	Rope& operator=(const Rope& _Other) = delete;
	Rope& operator=(Rope&& _Other) noexcept = delete;

	void SetLadderScale(float4 _Scale);

protected:
	void Start() override;
	void Update(float _delta) override;
private:
	void RenderSetting();

	std::shared_ptr<class GameEngineCollision> RopeCollision;

};

