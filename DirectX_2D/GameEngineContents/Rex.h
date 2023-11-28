#include "Monster.h"
#pragma once

enum class ERexState
{
	Stand,
	Thunder,
	Mteor,
	Die,

};
// Ό³Έν :
class Rex : public Monster
{
public:
	// constrcuter destructer
	Rex();
	~Rex();

	// delete Function
	Rex(const Rex& _Other) = delete;
	Rex(Rex&& _Other) noexcept = delete;
	Rex& operator=(const Rex& _Other) = delete;
	Rex& operator=(Rex&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	void SetHP(int _HP) override;
	void Damage(int _Damge) override;
	void RendererSetting() override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> RexRender = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> RexThunder;
	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> RexMteor;

	std::shared_ptr<class GameEngineCollision> BodyCollision;
	std::shared_ptr<class GameEngineCollision> ThunderCollision;

	float4 RexDif;
	bool DifCheck = false;

	std::string RexState;
	float Timeh = 0.0f;
	void ChangeState(std::string _State);
	void ComponentSetting();
	void RenderDifCheck();

	ERexState RexStateE = ERexState::Stand;
};

