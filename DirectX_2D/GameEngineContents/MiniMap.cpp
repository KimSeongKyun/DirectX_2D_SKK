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
	float4 CurPlayerPos = { Player::PlayerPos.X, Player::PlayerPos.Y - 42.0f};
	float4 MiniMapScale = BasicLevel::CurMiniMap->GetScale();
	float4 CurMapScale = BasicLevel::CurMap->GetScale();

	float4 ScaleDif = {9.0f, 22.0f};

	if (MiniMapScale.X <= 128.0f)
	{
		ScaleDif.X = (128.0f - MiniMapScale.X) / 2 + 1.0f;
	}

	if (MiniMapScale.Y <= 54.0f)
	{
		ScaleDif.Y = (54.0f - MiniMapScale.Y) / 2 + 18.0f;
	}

	float ScaleRatioX = MiniMapScale.X / CurMapScale.X;
	float ScaleRatioY = MiniMapScale.Y / CurMapScale.Y;

	float4 MiniMapPlayerPos = { ScaleRatioX * CurPlayerPos.X, ScaleRatioY * CurPlayerPos.Y };


	User0->Transform.SetLocalPosition({ MiniMapPlayerPos.X + ScaleDif.X, MiniMapPlayerPos.Y - ScaleDif.Y });
	int a = 0;
}

void MiniMap::RenderSetting()
{
	if (PinkBeanLevel::CurMiniMap == nullptr)
	{
		MsgBoxAssert("CurMap을 셋팅하지 않았습니다");
	}
	
	float4 MiniMapScale = BasicLevel::CurMiniMap->GetScale();
	float4 Top0Pos = { 64.0f, 0.0f };
	float4 Bottom0Pos = { 64.0f, -MiniMapScale.Y - 34.0f };
	float4 Left0Pos = { 0.0f, -27.0f };
	float4 Right0Pos = { 24.0f + MiniMapScale.X, -27.0f };
	float4 LeftTop0Pos = { 0.0f,0.0f };
	float4 LeftBottom0Pos = { 0.0f,-MiniMapScale.Y - 34.0f };
	float4 RightTop0Pos = { MiniMapScale.X + 24.0f, 0.0f };
	float4 RightBottom0Pos = { MiniMapScale.X + 24.0f,-MiniMapScale.Y - 34.0f };
	float4 MiniMap1Pos = { 12.0f,-22.0f };

	Top0 = CreateComponent<GameEngineUIRenderer>();
	Top0->SetSprite("MiniMapTop.png");
	Top0->AutoSpriteSizeOff();
	Top0->SetPivotType(PivotType::LeftTop);

	Bottom0 = CreateComponent<GameEngineUIRenderer>();
	Bottom0->SetSprite("MiniMapBottom.png");
	Bottom0->AutoSpriteSizeOff();
	Bottom0->SetPivotType(PivotType::LeftBottom);
	
	Left0 = CreateComponent<GameEngineUIRenderer>();
	Left0->SetSprite("MiniMapLeft.png");
	Left0->AutoSpriteSizeOff();
	Left0->SetPivotType(PivotType::LeftTop);
	
	Right0 = CreateComponent<GameEngineUIRenderer>();
	Right0->SetSprite("MiniMapRight.png");
	Right0->AutoSpriteSizeOff();
	Right0->SetPivotType(PivotType::RightUp);

	LeftTop0 = CreateComponent<GameEngineUIRenderer>();
	LeftTop0->SetSprite("MiniMapLeftTop.png");
	LeftTop0->AutoSpriteSizeOn();
	LeftTop0->SetPivotType(PivotType::LeftTop);
	
	LeftBottom0 = CreateComponent<GameEngineUIRenderer>();
	LeftBottom0->SetSprite("MiniMapLeftBottom.png");
	LeftBottom0->AutoSpriteSizeOn();
	LeftBottom0->SetPivotType(PivotType::LeftBottom);
	
	RightTop0 = CreateComponent<GameEngineUIRenderer>();
	RightTop0->SetSprite("MiniMapRightTop.png");
	RightTop0->AutoSpriteSizeOn();
	RightTop0->SetPivotType(PivotType::RightUp);
	

	float4 RightBottomPos;
	RightBottom0 = CreateComponent<GameEngineUIRenderer>();
	RightBottom0->SetSprite("MiniMapRightBottom.png");
	RightBottom0->AutoSpriteSizeOn();
	RightBottom0->SetPivotType(PivotType::RightBottom);

	

	MiniMap1 = CreateComponent<GameEngineUIRenderer>();
	MiniMap1->SetSprite(BasicLevel::CurMapName);
	MiniMap1->AutoSpriteSizeOn();
	MiniMap1->SetPivotType(PivotType::LeftTop);
	

	User0 = CreateComponent<GameEngineUIRenderer>();
	User0->SetSprite("MiniMapUser.png");
	User0->AutoSpriteSizeOn();
	User0->SetPivotType(PivotType::Bottom);
	

	if (MiniMapScale.X <= 104.0f)
	{
		Top0->Off();
		Bottom0->Off();
		RightTop0Pos.X = 128.0f;
		RightBottom0Pos.X = 128.0f;
		Right0Pos.X = 128.0f;
		MiniMap1Pos.X = 64.0f - MiniMapScale.hX();
	}

	if (MiniMapScale.Y <= 27.0f)
	{
		Left0->Off();
		Right0->Off();
		LeftBottom0Pos.Y = 54.0f;
		RightBottom0Pos.Y = 54.0f;
		Bottom0Pos.Y = 54.0f;
		MiniMap1Pos.Y = 27.0f - MiniMapScale.hY();
	}
	///////////

	Top0->Transform.SetLocalPosition(Top0Pos);
	Top0->Transform.SetWorldScale({ MiniMapScale.X -104.0f, 1.0f });

	Bottom0->Transform.SetLocalPosition(Bottom0Pos);
	Bottom0->Transform.SetWorldScale({ MiniMapScale.X - 104.0f , 1.0f });

	Left0->Transform.SetLocalPosition(Left0Pos);
	Left0->Transform.SetWorldScale({ 1.0f, MiniMapScale.Y});

	Right0->Transform.SetLocalPosition(Right0Pos);
	Right0->Transform.SetWorldScale({ 1.0f, MiniMapScale.Y});

	LeftTop0->Transform.SetLocalPosition(LeftTop0Pos);

	LeftBottom0->Transform.SetLocalPosition(LeftBottom0Pos);

	RightTop0->Transform.SetLocalPosition(RightTop0Pos);

	RightBottom0->Transform.SetLocalPosition(RightBottom0Pos);

	MiniMap1->Transform.SetLocalPosition(MiniMap1Pos);

	User0->Transform.SetLocalPosition({ 12.0f,-22.0f });
}

void MiniMap::ResourceLoad()
{

}