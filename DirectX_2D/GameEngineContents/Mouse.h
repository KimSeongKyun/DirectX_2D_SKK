#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Mouse :public GameEngineActor
{
public:
	// constrcuter destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameEngineCollision> MouseCollision;
	std::shared_ptr<GameEngineUIRenderer> MouseImage;


	void ComponentSetting();
	void MousePosUpdate();
	void MouseClickCheck(float _Delta);

	float4 MousePosSet;
	float4 MouseImageDif = { 10.0f , -12.0f };
	float4 MouseColDif;
	bool DoubleClick = false;
	bool Click = false;

	float ClickTime = 0.0f;
};

