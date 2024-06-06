#include "PreCompile.h"
#include "MapleStoryCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderTarget.h>

#include "Ellinia0_Level.h"
#include "TitleLevel.h"
#include "Ellinia1_Level.h"
#include "PinkBeanLevel.h"

float4 MapleStoryCore::PlayerPos = float4::ZERO;
MapleStoryCore::MapleStoryCore()
{
}

MapleStoryCore::~MapleStoryCore()
{
}

void MapleStoryCore::Start()
{
	//기본적으로 SpriteRenderer를 만들때 넣어줄 샘플러를 지정합니다.
	//GameEngineSpriteRenderer::SetDefaultSampler("POINT");
	GameEngineRenderTarget::IsDepth = false;
	GameEngineCore::CreateLevel<Ellinia0_Level>("Ellinia0_Level");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<Ellinia1_Level>("Ellinia1_Level");
	GameEngineCore::CreateLevel<PinkBeanLevel>("PinkBeanLevel");
	GameEngineCore::ChangeLevel("Ellinia0_Level");

	// 자기 텍스처 로드해야 한다.

}

void MapleStoryCore::Update(float _Delta)
{

}

void MapleStoryCore::Release()
{

}