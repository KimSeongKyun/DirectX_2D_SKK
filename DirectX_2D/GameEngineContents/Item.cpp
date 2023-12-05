#include "PreCompile.h"
#include "Item.h"


Item::Item() 
{
}

Item::~Item() 
{
}

void Item::Start()
{
	GameEngineInput::AddInputObject(this);
}

void Item::Update(float _Delta)
{
}



void Item::SetItem(std::string_view _ItemName)
{
	ItmeName = _ItemName;
	ItemBody->SetSprite(_ItemName);
}


void Item::ComponentSetting()
{
	ItemBody = CreateComponent<GameEngineUIRenderer>();
	ItemBody->SetSprite("GreenShellIcon.png");

	ItemCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Item);
	ItemCollision->Transform.SetWorldScale({ 40.0f,40.0f });
	ItemCollision->SetCollisionType(ColType::AABBBOX2D);


}

void Item::AddEA(int _EA)
{
	EA += _EA;
}

