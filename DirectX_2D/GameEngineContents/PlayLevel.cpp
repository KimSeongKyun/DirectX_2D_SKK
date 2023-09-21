#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Ellinia0_Map.h"


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

	//맵 이미지 로드
	{
		if (nullptr == GameEngineSprite::Find("Ellinia0"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Map");
			Dir.MoveChild("ElliniaMap0");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("Ellinia0.png");
			GameEngineSprite::CreateSingle("ElliniaBackGround.png");
		}
	}
}

void PlayLevel::ActorSetting()
{
	if (nullptr == Player0)
	{
		Player0 = CreateActor<Player>(1);
	}

	if (nullptr == Map0)
	{
		Map0 = CreateActor<Ellinia0_Map>(0);
	}
}
