#include "PreCompile.h"
#include "MiniMap.h"
#include "BasicLevel.h"
#include "PinkBeanLevel.h"
#include "Player.h"



MiniMap::MiniMap() 
{
}

MiniMap::~MiniMap() 
{
}

void MiniMap::Start()
{
	RenderSetting();
}
void MiniMap::Update(float _Delta)
{
	float4 CurPlayerPos = { Player::PlayerPos.X, Player::PlayerPos.Y + 42.0f};
	float4 MiniMapScale = BasicLevel::CurMiniMap->GetScale();
	float4 CurMapScale = BasicLevel::CurMap->GetScale();

	float ScaleRatio = MiniMapScale.X / CurMapScale.X;

	float4 MiniMapPlayerPos = { ScaleRatio * CurPlayerPos.X, ScaleRatio * CurPlayerPos.Y };


	User0->Transform.SetLocalPosition({ MiniMapPlayerPos.X + 12.0f, MiniMapPlayerPos.Y - 22.0f });


}

void MiniMap::RenderSetting()
{
	if (PinkBeanLevel::CurMiniMap == nullptr)
	{
		MsgBoxAssert("CurMap을 셋팅하지 않았습니다");
	}
	float4 MiniMapScale = BasicLevel::CurMiniMap->GetScale();

	
	Top0 = CreateComponent<GameEngineUIRenderer>();
	Top0->SetSprite("MiniMapTop.png");
	Top0->AutoSpriteSizeOff();
	Top0->SetPivotType(PivotType::LeftTop);
	Top0->Transform.SetLocalPosition({ 64.0f, 0.0f });
	Top0->Transform.SetWorldScale({ MiniMapScale.X -104.0f, 1.0f });

	Bottom0 = CreateComponent<GameEngineUIRenderer>();
	Bottom0->SetSprite("MiniMapBottom.png");
	Bottom0->AutoSpriteSizeOff();
	Bottom0->SetPivotType(PivotType::LeftBottom);
	Bottom0->Transform.SetLocalPosition({ 64.0f, -MiniMapScale.Y -34.0f});
	Bottom0->Transform.SetWorldScale({ MiniMapScale.X - 104.0f , 1.0f });
	
	Left0 = CreateComponent<GameEngineUIRenderer>();
	Left0->SetSprite("MiniMapLeft.png");
	Left0->AutoSpriteSizeOff();
	Left0->SetPivotType(PivotType::LeftTop);
	Left0->Transform.SetLocalPosition({ 0.0f, -27.0f });
	Left0->Transform.SetWorldScale({ 1.0f, MiniMapScale.Y});
	
	Right0 = CreateComponent<GameEngineUIRenderer>();
	Right0->SetSprite("MiniMapRight.png");
	Right0->AutoSpriteSizeOff();
	Right0->SetPivotType(PivotType::RightUp);
	Right0->Transform.SetLocalPosition({24.0f+ MiniMapScale.X, -27.0f });
	Right0->Transform.SetWorldScale({ 1.0f, MiniMapScale.Y});
	
	LeftTop0 = CreateComponent<GameEngineUIRenderer>();
	LeftTop0->SetSprite("MiniMapLeftTop.png");
	LeftTop0->AutoSpriteSizeOn();
	LeftTop0->SetPivotType(PivotType::LeftTop);
	LeftTop0->Transform.SetLocalPosition({ 0.0f,0.0f });
	
	LeftBottom0 = CreateComponent<GameEngineUIRenderer>();
	LeftBottom0->SetSprite("MiniMapLeftBottom.png");
	LeftBottom0->AutoSpriteSizeOn();
	LeftBottom0->SetPivotType(PivotType::LeftBottom);
	LeftBottom0->Transform.SetLocalPosition({ 0.0f,-MiniMapScale.Y -34.0f});
	
	RightTop0 = CreateComponent<GameEngineUIRenderer>();
	RightTop0->SetSprite("MiniMapRightTop.png");
	RightTop0->AutoSpriteSizeOn();
	RightTop0->SetPivotType(PivotType::RightUp);
	RightTop0->Transform.SetLocalPosition({ MiniMapScale.X + 24.0f, 0.0f});
	
	RightBottom0 = CreateComponent<GameEngineUIRenderer>();
	RightBottom0->SetSprite("MiniMapRightBottom.png");
	RightBottom0->AutoSpriteSizeOn();
	RightBottom0->SetPivotType(PivotType::RightBottom);
	RightBottom0->Transform.SetLocalPosition({ MiniMapScale.X + 24.0f,-MiniMapScale.Y - 34.0f });

	MiniMap1 = CreateComponent<GameEngineUIRenderer>();
	MiniMap1->SetSprite(BasicLevel::CurMapName);
	MiniMap1->AutoSpriteSizeOn();
	MiniMap1->SetPivotType(PivotType::LeftTop);
	MiniMap1->Transform.SetLocalPosition({ 12.0f,-22.0f });

	User0 = CreateComponent<GameEngineUIRenderer>();
	User0->SetSprite("MiniMapUser.png");
	User0->AutoSpriteSizeOn();
	User0->SetPivotType(PivotType::Bottom);
	User0->Transform.SetLocalPosition({ 12.0f,-22.0f });

}

void MiniMap::ResourceLoad()
{

}