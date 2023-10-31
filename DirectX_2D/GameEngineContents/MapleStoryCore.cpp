#include "PreCompile.h"
#include "MapleStoryCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderTarget.h>

#include "PlayLevel.h"
#include "TitleLevel.h"


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
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("PlayLevel");

	// �ڱ� �ؽ�ó �ε��ؾ� �Ѵ�.

}

void MapleStoryCore::Update(float _Delta)
{

}

void MapleStoryCore::Release()
{

}