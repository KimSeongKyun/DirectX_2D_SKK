#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"


PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start()
{
	ResourceLoad();
	ActorSetting();
}

void PlayLevel::Update(float _Delta)
{
	
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}

void PlayLevel::ResourceLoad()
{	
	// 플레이어 로드
	{
		if( nullptr == GameEngineSprite::Find("Idle0") )
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Player");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}
		
	
}

void PlayLevel::ActorSetting()
{
	if (nullptr == Player0)
	{
		Player0 = CreateActor<Player>(1);
	}
}
