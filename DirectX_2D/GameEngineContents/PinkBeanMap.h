#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PinkBeanMap : public GameEngineActor
{
public:
	// constrcuter destructer
	PinkBeanMap();
	~PinkBeanMap();

	// delete Function
	PinkBeanMap(const PinkBeanMap& _Other) = delete;
	PinkBeanMap(PinkBeanMap&& _Other) noexcept = delete;
	PinkBeanMap& operator=(const PinkBeanMap& _Other) = delete;
	PinkBeanMap& operator=(PinkBeanMap&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Map0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BackGround = nullptr;
	
};

