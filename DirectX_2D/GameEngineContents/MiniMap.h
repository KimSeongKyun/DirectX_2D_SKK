#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;

class MiniMap : public GameEngineActor
{
public:
	// constrcuter destructer
	MiniMap();
	~MiniMap();

	// delete Function
	MiniMap(const MiniMap& _Other) = delete;
	MiniMap(MiniMap&& _Other) noexcept = delete;
	MiniMap& operator=(const MiniMap& _Other) = delete;
	MiniMap& operator=(MiniMap&& _Other) noexcept = delete;

	
	

protected:
	void Start();
	void Update(float _Delta) override;

private:
	void RenderSetting();
	void ResourceLoad();
	

	std::shared_ptr<GameEngineUIRenderer> Top0 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Bottom0 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Left0 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> Right0 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> LeftTop0 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> LeftBottom0 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> RightTop0 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> RightBottom0 = nullptr;
	std::shared_ptr<GameEngineUIRenderer> MiniMap1 = nullptr;
};

