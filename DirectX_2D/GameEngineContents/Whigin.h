#include "Monster.h"
#pragma once


// Ό³Έν :
class Whigin : public Monster
{
public:
	// constrcuter destructer
	Whigin();
	~Whigin();

	// delete Function
	Whigin(const Whigin& _Other) = delete;
	Whigin(Whigin&& _Other) noexcept = delete;
	Whigin& operator=(const Whigin& _Other) = delete;
	Whigin& operator=(Whigin&& _Other) noexcept = delete;

	void Damage(int _Damge) override;
protected:
	void Start();
	void Update(float _Delta) override;
	void SetHP(int _HP) override;
	void RendererSetting() override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> WhiginRender = nullptr;	

	std::shared_ptr<class GameEngineCollision> BodyCollision;
	std::shared_ptr<class GameEngineCollision> CognitiveRange;
	

	float4 WhiginDif;
	bool DifCheck = false;
	bool ReflectOn = false;
	bool AmorOn = false;


	std::string WhiginState;

	float Timeh = 0.0f;
	float ReflectCoolTime = 0.0f;
	float AmorCoolTime = 0.0f;

	int HP = 100;

	void ChangeState(std::string _State);
	void ComponentSetting();

	void RenderDifCheck();
	void CoolTimeCheck(float _Delta);

	void Reflect();
	void Amor();

	

	GameEngineRandom Random;
};

