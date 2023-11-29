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
	std::shared_ptr<class GameEngineSpriteRenderer> RexThunder = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> RexSkill1 = nullptr;

	std::vector<std::shared_ptr<class GameEngineSpriteRenderer>> RexMteor;
	std::vector<std::shared_ptr<class GameEngineCollision>> MteorCollisions;

	std::shared_ptr<class GameEngineCollision> BodyCollision;
	std::shared_ptr<class GameEngineCollision> CognitiveRange;

	float4 RexDif;
	bool DifCheck = false;

	int HP = 10;

	std::string RexState;
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

	ERexState RexStateE = ERexState::Stand;

	GameEngineRandom Random;
};

