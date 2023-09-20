#pragma once
#include "BasicObjectElement.h"

// Ό³Έν :
class Player : public BasicObjectElement
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	void RendererSetting() override;

	std::shared_ptr<class GameEngineSpriteRenderer> PlayerBody;
};

