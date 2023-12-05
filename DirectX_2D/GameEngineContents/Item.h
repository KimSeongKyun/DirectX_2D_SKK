#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class Item :public GameEngineActor
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	std::string ItmeName = "";

private:
	std::shared_ptr<class GameEngineUIRenderer> ItemBody;
	std::shared_ptr<class GameEngineCollision> ItemCollision;

	void ComponentSetting();

	bool IsClick = false;
	int EA = 0;


public:
	void SetItem(std::string_view _ItemName);
	void AddEA(int _EA);
	std::string GetName() { return  ItmeName; };

};

