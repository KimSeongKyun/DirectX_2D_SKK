#pragma once
#include "BasicLevel.h"

// Ό³Έν :
class PinkBeanLevel : public BasicLevel
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
	std::shared_ptr<class PinkBeanMap> Map0 = nullptr;
	
	std::shared_ptr<class Player> Player0 = nullptr;
	std::shared_ptr<class Ariel> Ariel0 = nullptr;
	std::shared_ptr<class PinkBeanDummy> PinkBeanDummy0 = nullptr;
	std::shared_ptr<class Portal> Portal0 = nullptr;
	std::shared_ptr<class Portal> Portal1 = nullptr;
	
	//UI
	std::shared_ptr<class Status> Status0 = nullptr;
	std::shared_ptr<class QuickSlot> QuickSlot0 = nullptr;
	std::shared_ptr<class MiniMap> MiniMap0 = nullptr;

	
	void ResourceLoad();
	void CameraSetting();
	void ActorSetting();
};

