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
	//�⺻������ SpriteRenderer�� ���鶧 �־��� ���÷��� �����մϴ�.
	//GameEngineSpriteRenderer::SetDefaultSampler("POINT");
	GameEngineRenderTarget::IsDepth = false;
	GameEngineCore::CreateLevel<Ellinia0_Level>("Ellinia0_Level");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<Ellinia1_Level>("Ellinia1_Level");
	GameEngineCore::CreateLevel<PinkBeanLevel>("PinkBeanLevel");
	GameEngineCore::ChangeLevel("Ellinia0_Level");

	// �ڱ� �ؽ�ó �ε��ؾ� �Ѵ�.

}

void MapleStoryCore::Update(float _Delta)
{

}

void MapleStoryCore::Release()
{

}