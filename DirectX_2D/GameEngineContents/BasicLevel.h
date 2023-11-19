#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class BasicLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BasicLevel();
	~BasicLevel();

	// delete Function
	BasicLevel(const BasicLevel& _Other) = delete;
	BasicLevel(BasicLevel&& _Other) noexcept = delete;
	BasicLevel& operator=(const BasicLevel& _Other) = delete;
	BasicLevel& operator=(BasicLevel&& _Other) noexcept = delete;

protected:
	void DebugSwitch();
private:

};

