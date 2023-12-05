#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
enum class EItemType
{
	Equip,
	Use,
	Etc,
	Setup,
	Cash
};

class Inventory :public GameEngineActor
{
public:
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

	static std::map<EItemType,std::vector<std::shared_ptr<class Item>>>ItemList;


protected:
	void Start() override;
	void Update(float _Delta) override;
	void InsertItem(EItemType _ItemType, std::shared_ptr<class DropItem> _DropItem);


private:
	std::shared_ptr<class GameEngineSpriteRenderer> InventoryUI;

	void ComponentSetting();

	bool OnOff = false;
};

