#include <GameEngineCore/GameEngineActor.h>
#pragma once

// Ό³Έν :
class PinkBeanUI :public GameEngineActor
{
public:
	// constrcuter destructer
	PinkBeanUI();
	~PinkBeanUI();

	// delete Function
	PinkBeanUI(const PinkBeanUI& _Other) = delete;
	PinkBeanUI(PinkBeanUI&& _Other) noexcept = delete;
	PinkBeanUI& operator=(const PinkBeanUI& _Other) = delete;
	PinkBeanUI& operator=(PinkBeanUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<class GameEngineUIRenderer> Panel0 = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> HPBar = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> HPBack = nullptr;

	float PinkBeanHPMax = 1000000.0f;

	void ComponentSetting();
};

