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
	static Player* MainPlayer;
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
	void Damage(int _Damage) override;
	bool GetReflect() { return ReflectOn; };
	void SetReflect(bool _bool) { ReflectOn = _bool; };
	void SuperKnockBack();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void StateInit();
	static int HP;

private:
	GameEngineFSM FSM;
	void RendererSetting() override;
	void CameraMove(float _Delta);
	void ColSetting();



	std::string CurPlayerState;

	float Speed = 100.0f;
	float KnockBackPower = 100.0f;
	
	bool ReflectOn = false;
	bool Attack_Ing = false;
	bool MagicBoltOn = false;
	bool ColdBimOn = false;
	bool TeleportOn = false;
	bool Invincibility = false;
	bool IsKnockBack = false;

	//ÄðÅ¸ÀÓ
	float TeleportCoolTime = 0.0f;
	float InvincibilityCoolTime = 0.0f;
	float ReflectAliveTime = 0.0f;

	float SkillTime = 0.0f;
	float MaxSkillTime = 0.0f;

	float4 PlayerSize = { 39.0f, 82.0f };
	float4 JumpPower = { 0.0f, 4.5f, 1.0f };
	float4 Directionfloat = { 0.0f,0.0f };

	std::shared_ptr<class GameEngineCollision> ColAttack;
	std::shared_ptr<class GameEngineCollision> ColBody;
	std::shared_ptr<class GameEngineCollision> ColLadder;
	std::shared_ptr<class MagicBolt> MagicBolt0;
	std::shared_ptr<class ColdBim> ColdBim0;
	std::shared_ptr<class GameEngineTexture> CurMap;
	//std::shared_ptr<class DamageNumber> Test;
	
	void RendererStateChange(std::string_view _State);
	std::shared_ptr<class GameEngineSpriteRenderer> PlayerBody;
	std::shared_ptr<class GameEngineSpriteRenderer> Teleport0;
	std::shared_ptr<class GameEngineSpriteRenderer> ReflectIcon;

	void LRColCheck(float _DeltaTime, float4 _LeftOrRight);
	void RopeCheck();
	void ReflectCheck();
	void knockBack();
	



	void Attack();
	void MagicBolt();
	void ColdBim();
	void Teleport();
	void CoolTimeCount(float _Delta);
};

