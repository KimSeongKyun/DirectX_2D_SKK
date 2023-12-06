#include "PreCompile.h"
#include "DropItem.h"
#include "Item.h"

DropItem::DropItem() 
{
}

DropItem::~DropItem() 
{
}

void DropItem::Start()
{
	ComponentSetting();
}

void DropItem::Update(float _Delta)
{
	if (MoveTime <= 1.0f)
	{
		DropMotion(_Delta);
	}

	if (MoveTime > 1.0f)
	{
		StandardMotion(_Delta);
	}
}

void DropItem::ComponentSetting()
{
	ItemBody = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::DamageNumber);
	ItemBody->SetSprite("GreenShellIcon.png");

	ItemCollision = CreateComponent<GameEngineCollision>(ObjectCollision::DropItem);
	ItemCollision->Transform.SetWorldScale({ 26.0f,27.0f });
	ItemCollision->SetCollisionType(ColType::AABBBOX2D);


}

void DropItem::SettingPos(int _EA, int _Number)
{
	float StartPos = -(ItemSize * _EA) / 2 + (ItemSize / 2);
	ResultPos = StartPos + (_Number * ItemSize);
}

void DropItem::DropMotion(float _Delta)
{
	MoveTime += _Delta;

	if (MoveTime <= 0.5f)
	{
		ItemBody->Transform.SetLocalPosition(float4::LerpClamp(float4::ZERO, { ResultPos / 2, 100.0f }, 2 * MoveTime));
	}
	if (MoveTime > 0.5f)
	{
		ItemBody->Transform.SetLocalPosition(float4::LerpClamp({ ResultPos / 2, 100.0f }, { ResultPos, 0.0f }, 2 * (MoveTime - 0.5f)));
	}

	ItemBody->Transform.AddWorldRotation({ 0,0,10 });
	
}

void DropItem::StandardMotion(float _Delta)
{
	StandardTime += _Delta;
	if (StandardTime <= 0.5f)
	{
		ItemBody->Transform.SetLocalPosition(float4::LerpClamp({ ResultPos, 0.0f }, { ResultPos, 12.0f }, 2 * StandardTime));
	}
	if (StandardTime > 0.5f)
	{
		ItemBody->Transform.SetLocalPosition(float4::LerpClamp({ ResultPos, 12.0f }, { ResultPos, 0.0f }, 2 * (StandardTime - 0.5f)));
	}

	if (StandardTime > 1.0f)
	{
		StandardTime = 0.0f;
	}
}