#include "PreCompile.h"
#include "Ellinia1_Level.h"
#include "Player.h"
#include "Snale.h"
#include "Ellinia1_Map.h"
#include "Ellinia0_Map.h"
#include "Status.h"
#include "QuickSlot.h"
#include "MiniMap.h"

Ellinia1_Level::Ellinia1_Level() 
{
}

Ellinia1_Level::~Ellinia1_Level() 
{
	
}

void Ellinia1_Level::Start()
{
	BasicLevel::Start();
	OffDebug();
}

void Ellinia1_Level::Update(float _Delta)
{
	DebugSwitch();
}

void Ellinia1_Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	BasicLevel::LevelStart(_PrevLevel);
	ResourceLoad();
	CurMiniMap = GameEngineTexture::Find("Ellinia1MiniMap.png");
	CurMap = GameEngineTexture::Find("Ellinia1.png");
	CurMapName = "Ellinia1MiniMap.png";
	ActorSetting();
	CameraSetting();


}
void Ellinia1_Level::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}

void Ellinia1_Level::ResourceLoad()
{
	BasicLevel::ResourceLoad();


	
	//달팽이 리소스 로드
	{
		if (nullptr == GameEngineSprite::Find("SnaleDie0.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("Snale");

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
		if (nullptr == GameEngineSprite::Find("Ellinia1.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Map");
			Dir.MoveChild("ElliniaMap1");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("Ellinia1.png");
			GameEngineSprite::CreateSingle("Ellinia1MiniMap.png");
			
		}
		
	}
	
}

void Ellinia1_Level::ActorSetting()
{
	if (nullptr == Player0)
	{
		Player0 = CreateActor<Player>(static_cast<int>(ContentsObjectType::Player));
		Player0->SetColMap("ColEllinia1.png");
		Player0->SetCurMap("Ellinia1.png");
		Player0->Transform.SetLocalPosition({ 500.0f, -1000.0f });
	}

	if (nullptr == Map0)
	{
		Map0 = CreateActor<Ellinia1_Map>(11);
		//float4 HScale = Map0->MapScale.Half();
		Map0->Transform.SetLocalPosition({ 648.0f , -1024.0f });
	}

	if (nullptr == Snale0)
	{
		Snale0 = CreateActor<Snale>(20);
		Snale0->SetColMap("ColEllinia1.png");
		Snale0->SetHP(100);
		Snale0->Transform.SetLocalPosition({ 500.0f, -1000.0f });
	}

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	if (Status0 == nullptr)
	{

		Status0 = CreateActor<Status>(12);
		Status0->Transform.SetWorldPosition({ WindowScale.hX(), -690.0f });
	}
	if (QuickSlot0 == nullptr)
	{
		QuickSlot0 = CreateActor<QuickSlot>(12);
		QuickSlot0->Transform.SetWorldPosition({ WindowScale.hX() + 400.0f, -685.0f });
	}

	if (MiniMap0 == nullptr)
	{
		MiniMap0 = CreateActor<MiniMap>(12);

		MiniMap0->Transform.SetWorldPosition({ 0.0f, 0.0f });

	}
}
void Ellinia1_Level::CameraSetting()
{
	GetMainCamera()->Transform.AddLocalPosition(Player0->Transform.GetWorldPosition());
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition({ WindowScale.X, -WindowScale.Y });
}