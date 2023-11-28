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

protected:
	void Start();
	void Update(float _Delta) override;
	void SetHP(int _HP) override;
	void Damage(int _Damge) override;
	void RendererSetting() override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> SolomonRender = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> SolomonThunder;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> SolomonMteor;

	std::shared_ptr<class GameEngineCollision> BodyCollision;
	std::shared_ptr<class GameEngineCollision> ThunderCollision;

	float4 SolomonDif;
	bool DifCheck = false;

	std::string SolomonState;
	float Timeh = 0.0f;
	void ChangeState(std::string _State);
	void ComponentSetting();
	void RenderDifCheck();

	ESolomonState SolomonStateE = ESolomonState::Stand;
};

