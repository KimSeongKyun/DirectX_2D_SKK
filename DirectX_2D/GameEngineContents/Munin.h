#include "Monster.h"
#pragma once


// Ό³Έν :
class Munin : public Monster
{
public:
	// constrcuter destructer
	Munin();
	~Munin();

	// delete Function
	Munin(const Munin& _Other) = delete;
	Munin(Munin&& _Other) noexcept = delete;
	Munin& operator=(const Munin& _Other) = delete;
	Munin& operator=(Munin&& _Other) noexcept = delete;

	void Damage(int _Damge) override;
protected:
	void Start();
	void Update(float _Delta) override;
	void SetHP(int _HP) override;
	void RendererSetting() override;
private:
	std::shared_ptr<class GameEngineSpriteRenderer> MuninRender = nullptr;	

	std::shared_ptr<class GameEngineCollision> BodyCollision;
	std::shared_ptr<class GameEngineCollision> CognitiveRange;
	

	float4 MuninDif;
	bool DifCheck = false;
	bool ReflectOn = false;
	bool AmorOn = false;


	std::string MuninState;

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

