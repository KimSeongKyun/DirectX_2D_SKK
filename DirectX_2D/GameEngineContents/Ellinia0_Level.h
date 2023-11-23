#pragma once
#include "BasicLevel.h"
// Ό³Έν :
class Ellinia0_Level : public BasicLevel
{
public:
	// constrcuter destructer
	Ellinia0_Level();
	~Ellinia0_Level();

	// delete Function
	Ellinia0_Level(const Ellinia0_Level& _Other) = delete;
	Ellinia0_Level(Ellinia0_Level&& _Other) noexcept = delete;
	Ellinia0_Level& operator=(const Ellinia0_Level& _Other) = delete;
	Ellinia0_Level& operator=(Ellinia0_Level&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void ResourceLoad();
	void ActorSetting();
	void CameraSetting();
	

	std::shared_ptr<class Player> Player0 = nullptr;
	std::shared_ptr<class Ellinia0_Map> Map0 = nullptr;
	std::shared_ptr<class Snale> Snale0 = nullptr;

	//UI
	std::shared_ptr<class Status> Status0 = nullptr;
	std::shared_ptr<class QuickSlot> QuickSlot0 = nullptr;
	std::shared_ptr<class MiniMap> MiniMap0 = nullptr;
};

