#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Monster.h"

// Ό³Έν :
enum class EArielState
{
	Stand,
	Genesis,
	Mteor,
	Die,

};

class Ariel : public Monster
{
public:
	// constrcuter destructer
	Ariel();
	~Ariel();

	// delete Function
	Ariel(const Ariel& _Other) = delete;
	Ariel(Ariel&& _Other) noexcept = delete;
	Ariel& operator=(const Ariel& _Other) = delete;
	Ariel& operator=(Ariel&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void SetHP(int _HP) override;
	void Damage(int _Damge) override;
	void RendererSetting() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ArielRender = nullptr;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> ArielGenesis;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> ArielMteor;
	std::vector<std::shared_ptr<class GameEngineCollision>> GenesisCollisions;
	std::shared_ptr<class GameEngineCollision> BodyCollision;
	std::shared_ptr<class Collision> SkillCol = nullptr;

	std::string ArielState;

	float4 ArielDif;

	void ChangeState(std::string _State);
	void ComponentSetting();
	void RenderDifCheck();
	void Genesis();
	void Mteor();


	void StandUpdate(float _Delta);
	void GenesisUpdate(float _Delta);

	int HP = 0;

	int SkillRange = 385;
	float SkillTime = 0.0f;

	bool SkillOn = false;
	bool DifCheck = false;

	EArielState ArielStateE = EArielState::Stand;

	GameEngineRandom Random;
};

