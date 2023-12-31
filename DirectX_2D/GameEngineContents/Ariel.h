#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Monster.h"

// ���� :
enum class EArielState
{
	None,
	Skill1,
	Genesis,
	Mteor,
	

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

	void Damage(int _Damge) override;
	void SetHP(int _HP) override;
protected:
	void Start();
	void Update(float _Delta) override;
	void RendererSetting() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> ArielRender = nullptr;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> ArielGenesis;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> ArielMteor;
	std::vector<std::shared_ptr<class GameEngineCollision>> GenesisCollisions;
	std::vector<std::shared_ptr<class GameEngineCollision>> MteorCollisions;
	
	std::shared_ptr<class GameEngineCollision> CognitiveRange;
	std::shared_ptr<class GameEngineCollision> BodyCollision;
	std::shared_ptr<class Collision> SkillCol = nullptr;

	std::string ArielState;

	float4 ArielDif;

	void ChangeState(std::string _State);
	void ComponentSetting();
	void RenderDifCheck();
	void Genesis();
	void Mteor();
	void Reflect();


	
	void GenesisUpdate(float _Delta);
	void MteorUpdate(float _Delta);
	
	void CoolTimeCheck(float _Delta);

	int HP = 1000000;

	int SkillRange = 385;
	float SkillTime = 0.0f;

	float HitTime = 0.0f;

	bool SkillOn = false;
	bool DifCheck = false;

	bool GenesisOn = false;
	bool MteorOn = false;
	bool ReflectOn = false;

	float GenesisCoolTime= false;
	float MteorCoolTime = false;
	float ReflectCoolTime = false;
	EArielState ArielStateE = EArielState::None;

	GameEngineRandom Random;
};

