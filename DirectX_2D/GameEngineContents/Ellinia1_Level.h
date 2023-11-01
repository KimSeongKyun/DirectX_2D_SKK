#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class Ellinia1_Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Ellinia1_Level();
	~Ellinia1_Level();

	// delete Function
	Ellinia1_Level(const Ellinia1_Level& _Other) = delete;
	Ellinia1_Level(Ellinia1_Level&& _Other) noexcept = delete;
	Ellinia1_Level& operator=(const Ellinia1_Level& _Other) = delete;
	Ellinia1_Level& operator=(Ellinia1_Level&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class Player> Player0 = nullptr;
	std::shared_ptr<class Ellinia1_Map> Map0 = nullptr;
	std::shared_ptr<class Snale> Snale0 = nullptr;

	void ResourceLoad();
	void ActorSetting();
	void CameraSetting();
};

