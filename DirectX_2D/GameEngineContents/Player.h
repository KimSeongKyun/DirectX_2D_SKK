#pragma once
#include "BasicObjectElement.h"
#include "GameEngineFSM.h"

enum class StateType
{
	Idle,
	Move,
	Jump,
	Attack,
	Ladder,
	Rope,
};

enum class PlayerDirection
{
	Left,
	Right
};


class Player : public BasicObjectElement
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	
	static PlayerDirection CurDirection;
	static float4 PlayerPos;
	void SetCurMap(const std::string_view& _ColMap) { CurMap = GameEngineTexture::Find(_ColMap); };
	
	

protected:
	void Start() override;
	void Update(float _Delta) override;
	void StateInit();
	void Damage(int Damage) override;

private:
	GameEngineFSM FSM;
	void RendererSetting() override;
	void CameraMove();
	void ColSetting();


	std::string CurPlayerState;

	float Speed = 100.0f;
	

	bool Attack_Ing = false;
	bool MagicBoltOn = false;
	bool ColdBimOn = false;
	

	float SkillTime = 0.0f;
	float MaxSkillTime = 0.0f;

	float4 PlayerSize = { 39.0f, 82.0f };
	float4 JumpPower = { 0.0f, 4.5f, 1.0f };

	std::shared_ptr<class GameEngineCollision> ColAttack;
	std::shared_ptr<class GameEngineCollision> ColBody;
	std::shared_ptr<class GameEngineCollision> ColLadder;
	std::shared_ptr<class MagicBolt> MagicBolt0;
	std::shared_ptr<class ColdBim> ColdBim0;
	std::shared_ptr<class GameEngineTexture> CurMap;
	//std::shared_ptr<class DamageNumber> Test;
	
	void RendererStateChange(std::string_view _State);
	std::shared_ptr<class GameEngineSpriteRenderer> PlayerBody;

	void LRColCheck(float _DeltaTime, float4 _LeftOrRight);
	void RopeCheck();


	void Attack();
	void MagicBolt();
	void ColdBim();
	
};

