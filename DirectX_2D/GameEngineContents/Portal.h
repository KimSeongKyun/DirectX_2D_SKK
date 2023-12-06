#pragma once
#include <GameEngineCore/GameEngineActor.h>



// Ό³Έν :
class Portal : public GameEngineActor
{
	friend class BasicLevel;
	
public:
	// constrcuter destructer
	Portal();
	~Portal();

	// delete Function
	Portal(const Portal& _Other) = delete;
	Portal(Portal&& _Other) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _Delta) override;
	

private:
	std::shared_ptr<class GameEngineSpriteRenderer> Render0;
	std::shared_ptr<class GameEngineCollision> ColToPlayer;
	std::string LevelName;
	float4 Coordinate;
	float4 PortalSize = {};

	float4 PlayerMovePos;

	bool ChageLevelStart = false;
	float TimeCheck = 0.0f;
	std::shared_ptr<class FadePostEffect> FadeEffect;

public:
	void SetLevelName(const std::string_view& _LevelName);
	void SetPlayerMovePos(float4 _Pos);
	void SetCoordinate(float4 _Pos);

};

