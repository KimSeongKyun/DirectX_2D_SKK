#pragma once
#include <GameEngineCore/GameEngineActor.h>



class ItemList :public GameEngineActor
{
public:
	// constrcuter destructer
	ItemList();
	~ItemList();

	// delete Function
	ItemList(const ItemList& _Other) = delete;
	ItemList(ItemList&& _Other) noexcept = delete;
	ItemList& operator=(const ItemList& _Other) = delete;
	ItemList& operator=(ItemList&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::map <int, std::vector<std::shared_ptr<class Item>> > MyItemList;

};

