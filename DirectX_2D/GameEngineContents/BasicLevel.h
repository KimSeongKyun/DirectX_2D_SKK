#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class BasicLevel : public GameEngineLevel
{
	friend class Portal;

public:
	// constrcuter destructer
	BasicLevel();
	~BasicLevel();

	// delete Function
	BasicLevel(const BasicLevel& _Other) = delete;
	BasicLevel(BasicLevel&& _Other) noexcept = delete;
	BasicLevel& operator=(const BasicLevel& _Other) = delete;
	BasicLevel& operator=(BasicLevel&& _Other) noexcept = delete;

	//static void FadeOutStart();
	
	static std::shared_ptr<class GameEngineTexture> CurMiniMap;
	static std::shared_ptr<class GameEngineTexture> CurMap;
	static std::string CurMapName;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void DebugSwitch();
	//std::shared_ptr<class FadePostEffect> FadeEffect;

private:

	bool FadeOut = false;
};

