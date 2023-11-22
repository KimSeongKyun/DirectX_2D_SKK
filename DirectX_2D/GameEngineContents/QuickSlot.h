#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;
class QuickSlot : public GameEngineActor

{
public:
	// constrcuter destructer
	QuickSlot();
	~QuickSlot();

	// delete Function
	QuickSlot(const QuickSlot& _Other) = delete;
	QuickSlot(QuickSlot&& _Other) noexcept = delete;
	QuickSlot& operator=(const QuickSlot& _Other) = delete;
	QuickSlot& operator=(QuickSlot&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> Back;
	std::shared_ptr<GameEngineUIRenderer> Cover;
	std::shared_ptr<GameEngineUIRenderer> Render;
};

