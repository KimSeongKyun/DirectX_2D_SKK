#include "PreCompile.h"
#include "Inventory.h"
#include "Item.h"
#include "ItemList.h"


Inventory* Inventory::MainInventory;
Inventory::Inventory() 
{
	MainInventory = this;
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	GameEngineInput::AddInputObject(this);
	ComponentSetting();
	ItmeList0 = GetLevel()->CreateActor<ItemList>();
}

void Inventory::Update(float _Delta)
{

	PosUpdate();
	
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
	InventoryUI->SetSprite("Inventory3.png");
	InventoryUI->AutoSpriteSizeOn();
	InventoryUI->SetPivotType(PivotType::LeftTop);
	InventoryUI->Off();

	
	EtcCol = CreateComponent<GameEngineCollision>(ObjectCollision::UI);
	EtcCol->SetCollisionType(ColType::AABBBOX2D);
	//EtcCol->Transform.SetWorldScale({ 500.0f, 500.0f });
	EtcCol->Transform.SetWorldScale({ 35.0f, 18.0f });
	EtcCol->SetParent(InventoryUI);
	
}

void Inventory::PosUpdate()
{

	float4 ColDif = { 88.0f, -34.0f };
	float4 CurCameraPos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 WindowScale = { 640.0f, -360.0f };

	float4 Test = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 CurWindowPos = CurCameraPos - WindowScale;
	float4 Curinventorypos = InventoryUI->Transform.GetWorldPosition();
	EtcCol->Transform.SetLocalPosition(Curinventorypos + CurWindowPos + ColDif);
}
