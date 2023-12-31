#pragma once
#include "BasicLevel.h"
// ���� :
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
	void ReSpawn(float _Delta);
	
	float RespawnTime = 0.0f;
	std::vector<float4> SnalePoses;

	std::shared_ptr<class Player> Player0 = nullptr;
	std::shared_ptr<class Ellinia0_Map> Map0 = nullptr;
	std::vector<std::shared_ptr<class Snale>> Snales;
	std::shared_ptr<class Ladder> Ladder0 = nullptr;
	std::shared_ptr<class Ladder> Ladder1 = nullptr;
	std::shared_ptr<class Ladder> Ladder2 = nullptr;
	std::shared_ptr<class Ladder> Ladder3 = nullptr;
	std::shared_ptr<class Ladder> Ladder4 = nullptr;
	std::shared_ptr<class Ladder> Ladder5 = nullptr;
	std::shared_ptr<class Ladder> Ladder6 = nullptr;
	std::shared_ptr<class Portal> Portal0 = nullptr;


	//UI
	std::shared_ptr<class Status> Status0 = nullptr;
	std::shared_ptr<class QuickSlot> QuickSlot0 = nullptr;
	std::shared_ptr<class MiniMap> MiniMap0 = nullptr;
};

