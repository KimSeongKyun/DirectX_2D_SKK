#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :


class MagicBolt :public GameEngineActor
{
public:
	// constrcuter destructer
	MagicBolt();
	~MagicBolt();

	// delete Function
	MagicBolt(const MagicBolt& _Other) = delete;
	MagicBolt(MagicBolt&& _Other) noexcept = delete;
	MagicBolt& operator=(const MagicBolt& _Other) = delete;
	MagicBolt& operator=(MagicBolt&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	
	


private:
	void ComponentSetting();

	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer0;
	std::shared_ptr<class GameEngineSpriteRenderer> SkillRenderer1;
	std::shared_ptr<class GameEngineCollision> ColSkill;

	float TickTime = 0.0f;
	float SkillTime = 0.0f;
	float Speed = 500.0f;

	float4 MagicBoltScale = { 45.0f, 45.0f, 1.0f };
	
	bool DirectionSet = true;
	bool MagicBoltShoot = false;
	int CurPlayerDirection = 0;


public:
	void MagicBoltUpdate(float _Delta);
	void MagicBoltColCheck();
	
	

};	

