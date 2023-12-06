#include "PreCompile.h"
#include "ItemList.h"
#include "Item.h"
#include "Inventory.h"



ItemList::ItemList() 
{
}

ItemList::~ItemList() 
{
}

void ItemList::Start()
{
	GameEngineInput::AddInputObject(this);
	MyItemList[static_cast<int>(EItemType::Equip)].reserve(24);
	MyItemList[static_cast<int>(EItemType::Use)].reserve(24);
	MyItemList[static_cast<int>(EItemType::Etc)].reserve(24);
	MyItemList[static_cast<int>(EItemType::Setup)].reserve(24);
	MyItemList[static_cast<int>(EItemType::Cash)].reserve(24);

	for (int i = 0; i < 24; i++)
	{
		MyItemList[static_cast<int>(EItemType::Equip)].push_back(nullptr);
		MyItemList[static_cast<int>(EItemType::Use)].push_back(nullptr);
		MyItemList[static_cast<int>(EItemType::Etc)].push_back(nullptr);
		MyItemList[static_cast<int>(EItemType::Setup)].push_back(nullptr);
		MyItemList[static_cast<int>(EItemType::Cash)].push_back(nullptr);
	}
	if (Inventory::MainInventory != nullptr)
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int a = 4 * i + j;
				MyItemList[static_cast<int>(Inventory::MainInventory->GetCurType())][4 * i + j] = GetLevel()->CreateActor<Item>();
				MyItemList[static_cast<int>(Inventory::MainInventory->GetCurType())][4 * i + j]->SetParent(this, 0);
				MyItemList[static_cast<int>(Inventory::MainInventory->GetCurType())][4 * i + j]->Transform.SetLocalPosition({ 36.0f * j, 34.0f * i });

			}
		}
	}
}

void ItemList::Update(float _Delta)
{
	
}