#include "Monster.h"
#pragma once

// Ό³Έν :
class PinkBean :public Monster
{
	friend class PinkBeanUI;
public:
	static PinkBean* MainPinkBean;
	// constrcuter destructer
	PinkBean();
	~PinkBean();

	// delete Function
	PinkBean(const PinkBean& _Other) = delete;
	PinkBean(PinkBean&& _Other) noexcept = delete;
	PinkBean& operator=(const PinkBean& _Other) = delete;
	PinkBean& operator=(PinkBean&& _Other) noexcept = delete;

	
protected:
	void Start();
	void Update(float _Delta) override;
	void SetHP(int _HP) override;
	void Damage(int _Damge) override;
	void RendererSetting() override;

	int HP = 1000000;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> PinkBeanRender = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> GenesisRender = nullptr;


	std::shared_ptr<class GameEngineCollision> GenesisCollision = nullptr;
	std::shared_ptr<class GameEngineCollision> PinkBeanCollision = nullptr;

	std::string PinkBeanState = "PinkBeanApear";

	bool DifCheck = false;
	bool GenesisOn = false;
	bool ReflectOn = false;
	bool KnockBackOn = false;
	bool AllCoolTimeOn = false;

	float GenesisCoolTime = 0.0f;
	float ReflectCoolTime = 0.0f;
	float KnockBackCoolTime = 0.0f;
	float AllCoolTime = 0.0f;

	float SkillTime = 0.0f;
	float4 PinkBeanDif;

	void ChangeState(std::string _State);
	void RenderDifCheck();

	void Genesis();
	void Reflect();
	void SuperKnockBack();

	void CoolTimeCheck(float _Delta);

	void GenesisColCheck();

	GameEngineRandom Random;
};