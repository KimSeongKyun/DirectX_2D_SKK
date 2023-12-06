#pragma once
#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :


class Inventory :public GameEngineActor
{
public:
	static Inventory* MainInventory;
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void InsertItem(EItemType _ItemType, std::shared_ptr<class DropItem> _DropItem);


private:
	std::shared_ptr<class ItemList> ItmeList0 = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> InventoryUI;
	
	std::shared_ptr<class GameEngineCollision> EtcCol;
	std::shared_ptr<class GameEngineCollision> EquipCol;
	std::shared_ptr<class GameEngineCollision> CashCol;
	std::shared_ptr<class GameEngineCollision> UseCol;
	std::shared_ptr<class GameEngineCollision> SetupCol;
	
	
	void ComponentSetting();
	void PosUpdate();
	EItemType CurInventoryType = EItemType::Equip;
	bool OnOff = false;

public:
	EItemType GetCurType() { return CurInventoryType; };
};

