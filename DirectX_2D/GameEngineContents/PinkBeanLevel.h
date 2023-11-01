#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class PinkBeanLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PinkBeanLevel();
	~PinkBeanLevel();

	// delete Function
	PinkBeanLevel(const PinkBeanLevel& _Other) = delete;
	PinkBeanLevel(PinkBeanLevel&& _Other) noexcept = delete;
	PinkBeanLevel& operator=(const PinkBeanLevel& _Other) = delete;
	PinkBeanLevel& operator=(PinkBeanLevel&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class Player> Player0 = nullptr;
	std::shared_ptr<class PinkBeanMap> Map0 = nullptr;
	std::shared_ptr<class Ariel> Ariel0 = nullptr;
	std::shared_ptr<class PinkBeanDummy> PinkBeanDummy0 = nullptr;

	void ResourceLoad();
	void CameraSetting();
	void ActorSetting();
};

