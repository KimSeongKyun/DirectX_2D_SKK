#pragma once
#include "Monster.h"

// Ό³Έν :
class PinkBeanDummy : public Monster
{
public:
	// constrcuter destructer
	PinkBeanDummy();
	~PinkBeanDummy();

	// delete Function
	PinkBeanDummy(const PinkBeanDummy& _Other) = delete;
	PinkBeanDummy(PinkBeanDummy&& _Other) noexcept = delete;
	PinkBeanDummy& operator=(const PinkBeanDummy& _Other) = delete;
	PinkBeanDummy& operator=(PinkBeanDummy&& _Other) noexcept = delete;


	static bool Ariel;
	static bool Munin;
	static bool Rex;
	static bool Solomon;
	static bool Whigin;

protected:
	void Start();
	void Update(float _Delta) override;
	void SetHP(int _HP) override;
	void Damage(int _Damge) override;

private:
	void ComponetSetting();
	void ChangeState(int _StateNum);
	void RendererSetting() override;

	int StateNumber = 11;

	float4 ResourceDif;
	std::string PinkBeanState;
	std::shared_ptr<class GameEngineSpriteRenderer> PinkBeanDummyRender = nullptr;



};

