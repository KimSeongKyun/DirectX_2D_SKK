#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BasicObjectElement : public GameEngineActor
{
public:
	// constrcuter destructer
	BasicObjectElement();
	virtual ~BasicObjectElement();

	// delete Function
	BasicObjectElement(const BasicObjectElement& _Other) = delete;
	BasicObjectElement(BasicObjectElement&& _Other) noexcept = delete;
	BasicObjectElement& operator=(const BasicObjectElement& _Other) = delete;
	BasicObjectElement& operator=(BasicObjectElement&& _Other) noexcept = delete;

protected:
	virtual void RendererSetting();


private:

};

