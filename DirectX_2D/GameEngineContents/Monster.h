#pragma once
#include <GameEngineCore/GameEngineActor.h>



// Ό³Έν :
class Monster :public GameEngineActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;


	void GravityCheck(float _Delta);

	void SetColMap(const std::string_view _ColMap);
	void SetCurMap(const std::string_view& _ColMap);
	std::shared_ptr<class GameEngineTexture>  GetColMap() { return ColMap; };
	std::shared_ptr<class GameEngineTexture>  GetCurMap() { return CurMap; };
	GameEngineColor GetGroundColor() { return ColGroundColor; };
	GameEngineColor GetWallColor() { return ColWallColor; };
	float4 GetMonsterSize();
	void SetMonsterSize(float4 _Size);

	float GetGravity() { return Gravity; };
	void SetGravity(float _value) { Gravity = _value; };
	bool IsGravity() { return GravityOn; }
	virtual void SetHP(int _HP) = 0;
	bool IsKnockBack() { return KnockBack; };
	void ChangeKnockBack() { KnockBack = !KnockBack; };

	


protected:
	void Start();
	void Update(float _Delta) override;
	

private:
	std::shared_ptr<class GameEngineTexture> ColMap;
	std::shared_ptr<class GameEngineTexture> CurMap;

	GameEngineColor ColGroundColor = { 255, 0, 255, 255 };
	GameEngineColor ColWallColor = { 0, 255, 255, 255 };

	float4 MonsterScale;
	float Gravity = 0.0f;
	bool GravityOn = true;
	bool KnockBack = false;

public:
	virtual void Damage(int _Damge) = 0;
	void SetKnockBack();
	
	
};

