#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;
class Status : public GameEngineActor
{
public:
	// constrcuter destructer
	Status();
	~Status();

	// delete Function
	Status(const Status& _Other) = delete;
	Status(Status&& _Other) noexcept = delete;
	Status& operator=(const Status& _Other) = delete;
	Status& operator=(Status&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineUIRenderer> StatusBack;
	std::shared_ptr<GameEngineUIRenderer> HPBar;
	std::shared_ptr<GameEngineUIRenderer> MPBar;
	std::shared_ptr<GameEngineUIRenderer> BackHP;
	std::shared_ptr<GameEngineUIRenderer> BackMP;
};

