#include "PreCompile.h"
#include "Inventory.h"
#include "Item.h"

std::map<EItemType, std::vector<std::shared_ptr<Item>>> Inventory::ItemList;

Inventory::Inventory() 
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	GameEngineInput::AddInputObject(this);
	ComponentSetting();
}

void Inventory::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('I',this))
	{
		if (true == OnOff)
		{
			InventoryUI->Off();
			OnOff = false;
			return;
		}
		InventoryUI->On();
		OnOff = true;
	}
}

void Inventory::ComponentSetting()
{
	InventoryUI = CreateComponent<GameEngineUIRenderer>();
	InventoryUI->SetSprite("Inventory0.png");
	InventoryUI->AutoSpriteSizeOn();
	InventoryUI->Off();
}