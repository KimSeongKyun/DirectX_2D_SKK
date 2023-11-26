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

	void GravityCheck(float _DeltaTime);
	void SetColMap(const std::string_view& _ColMap) { ColMap = GameEngineTexture::Find(_ColMap); };
	void SetObjectSize(float4 _Size) { ObjectSize = _Size; };
	virtual void Damage(int _Damge) = 0;
	

	std::shared_ptr<class GameEngineTexture> ColMap;
	GameEngineColor ColColor = { 255, 0, 255 , 255 };


	bool IsGravity = false;
	float Gravity = 0.0f;
	float4 ObjectSize;



protected:
	virtual void RendererSetting() = 0;
	

private:
};

