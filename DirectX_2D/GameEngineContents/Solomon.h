#include "Monster.h"
#pragma once

enum class ESolomonState
{
	Stand,
	Thunder,
	Mteor,
	Die,

};
// Ό³Έν :
class Solomon : public Monster
{
public:
	// constrcuter destructer
	Solomon();
	~Solomon();

	// delete Function
	Solomon(const Solomon& _Other) = delete;
	Solomon(Solomon&& _Other) noexcept = delete;
	Solomon& operator=(const Solomon& _Other) = delete;
	Solomon& operator=(Solomon&& _Other) noexcept = delete;

	void Damage(int _Damge) override;
protected:
	void Start();
	void Update(float _Delta) override;
	void SetHP(int _HP) override;
	void RendererSetting() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> SolomonRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SolomonThunder = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> SolomonSkill1 = nullptr;

	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> SolomonMteor;
	std::vector<std::shared_ptr<class GameEngineCollision>> MteorCollisions;

	std::shared_ptr<class GameEngineCollision> BodyCollision;
	std::shared_ptr<class GameEngineCollision> CognitiveRange1;

	float4 SolomonDif;
	bool DifCheck = false;

	int HP = 100;

	std::string SolomonState;
	float Timeh = 0.0f;
	void ChangeState(std::string _State);
	void ComponentSetting();
	void RenderDifCheck();

	bool ThunderOn = false;
	bool MteorOn = false;
	bool Skill1On = false;

	float SkillTime = 0.0f;
	float ThunderCoolTime = 0.0f;
	float MteorCoolTime = 0.0f;
	float Skill1CoolTime = 0.0f;

	void Thunder();
	void Mteor();
	void Skill1();

	void MteorUpdate(float _Delta);
	
	void CoolTimeCheck(float _Delta);

	ESolomonState SolomonStateE = ESolomonState::Stand;

	GameEngineRandom Random;
};

