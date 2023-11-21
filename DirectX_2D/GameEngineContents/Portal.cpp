#include "PreCompile.h"
#include "Portal.h"

#include "BasicObjectElement.h"
#include "BasicLevel.h"
#include <GameEngineCore/FadePostEffect.h>




Portal::Portal() 
{
}

Portal::~Portal() 
{
}

void Portal::Start()
{
	GameEngineInput::AddInputObject(this);
	
	{
		Render0 = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Object);
		Render0->CreateAnimation( "Portal", "Portal" );
		Render0->AutoSpriteSizeOn();
		Render0->ChangeAnimation("Portal");
		Render0->SetPivotType(PivotType::Bottom);
	}

	{
		float4 PortalScale = { 97.0f , 256.0f , 1.0f };
		ColToPlayer = CreateComponent<GameEngineCollision>();
		ColToPlayer->SetOrder(static_cast<int>(ContentsObjectType::Object));
		ColToPlayer->Transform.SetWorldScale({ PortalScale.hX(), 5.0f, 1.0f});
		ColToPlayer->Transform.AddWorldPosition({ 0.0f,10.0f });
		ColToPlayer->SetCollisionType(ColType::AABBBOX2D);
		//ColToPlayer->Transform.AddWorldPosition({ 0, - PortalScale.hY() + 2 ,0.0f});
	}
	if (FadeEffect == nullptr)
	{
		FadeEffect = GetLevel()->GetLevelRenderTarget()->CreateEffect<FadePostEffect>();
		FadeEffect->Off();
	}
	//float4 PortalSize = Render0->Transform.GetWorldScale();
	//PortalSize.hX();
	//PortalSize;
	//ColToPlayer = CreateComponent<GameEngineCollision>(static_cast<int>(ObjectCollision::Portal));
	//ColToPlayer->SetCollisionType(ColType::AABBBOX2D);
	//ColToPlayer->Transform.SetWorldScale(PortalSize);

}

void Portal::Update(float _Delta)
{
	if (GameEngineInput::IsDown(VK_UP,this))
	{
		if (false != ColToPlayer->Collision(ObjectCollision::PlayerBody))
		{
			FadeEffect->On();
			ChageLevelStart = true;
		}
	}
	if (ChageLevelStart == true)
	{
		TimeCheck += _Delta;

		if (TimeCheck > 1.0f)
		{
			GameEngineCore::ChangeLevel(LevelName);
		}
	}

}

void Portal::SetLevelName(const std::string_view& _LevelName)
{
	LevelName = _LevelName;
}

void Portal::SetPlayerMovePos(float4 _Pos)
{
	//ContentsCore::PlayerMovePos = _Pos;
}

void Portal::SetCoordinate(float4 _Pos)
{
	Coordinate = _Pos;
}

