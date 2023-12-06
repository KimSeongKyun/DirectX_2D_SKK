#include <GameEngineCore/GameEngineActor.h>
#pragma once

// Ό³Έν :
class FadeInOut :public GameEngineActor
{
public:
	// constrcuter destructer
	FadeInOut();
	~FadeInOut();

	// delete Function
	FadeInOut(const FadeInOut& _Other) = delete;
	FadeInOut(FadeInOut&& _Other) noexcept = delete;
	FadeInOut& operator=(const FadeInOut& _Other) = delete;
	FadeInOut& operator=(FadeInOut&& _Other) noexcept = delete;

	void FadeIn();
	void FadeOut();

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> FadeOutObject = nullptr;
	
	bool IsFadeIn = false;
	bool IsFadeOut = false;
	bool SetAlpha = false;
	float Timeh = 0.0f;

};

