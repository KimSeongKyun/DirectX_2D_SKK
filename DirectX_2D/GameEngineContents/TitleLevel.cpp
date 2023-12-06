#include "PreCompile.h"
#include "TitleLevel.h"
#include "TitleScene.h"
#include "MapleStoryCore.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	MapleStoryCore::PlayerPos = { 147.0f,-890.0f };
}


void TitleLevel::Update(float _Delta)
{
	
}


void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ResourceLoad();
	if (TitleScene0 == nullptr)
	{
		TitleScene0 = CreateActor<TitleScene>();
	}


	
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	

}

void TitleLevel::ResourceLoad()
{
	{
		if (nullptr == GameEngineSprite::Find("Wizet00.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Title");

			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}

	{
		if (nullptr == GameEngineSprite::Find("TitleBack,png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Title");
			Dir.MoveChild("TitleBack");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("TitleBack.png");
		
		}
	}
}

void TitleLevel::CameraSetting()
{
	GetMainCamera()->Transform.AddLocalPosition({ 640.0f, -360.0f});
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition({ WindowScale.X, -WindowScale.Y });
}