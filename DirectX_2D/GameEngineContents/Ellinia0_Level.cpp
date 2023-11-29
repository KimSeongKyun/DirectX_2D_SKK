#include "PreCompile.h"
#include "Ellinia0_Level.h"
#include "Player.h"
#include "Ellinia0_Map.h"
#include "Snale.h"
#include "Status.h"
#include "QuickSlot.h"
#include "MiniMap.h"


Ellinia0_Level::Ellinia0_Level()
{
}

Ellinia0_Level::~Ellinia0_Level()
{
	
}

void Ellinia0_Level::Start()
{
	BasicLevel::Start();
	OffDebug();
}

void Ellinia0_Level::Update(float _Delta)
{
	DebugSwitch();
}

void Ellinia0_Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	BasicLevel::LevelStart(_PrevLevel);
	ResourceLoad();
	CurMiniMap = GameEngineTexture::Find("Ellinia0MiniMap.png");
	CurMap = GameEngineTexture::Find("Ellinia0.png");
	CurMapName = "Ellinia0MiniMap.png";
	ActorSetting();
	CameraSetting();
	
}

void Ellinia0_Level::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}

void Ellinia0_Level::ResourceLoad()
{	
	BasicLevel::ResourceLoad();
	// 플레이어 로드
	{
		if (nullptr == GameEngineSprite::Find("Idle0"))
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

				GameEngineSprite::CreateSingle("ReflectIcon.png");
			}
		}
	}
	// 스킬 리소스 로드
	{
		if (nullptr == GameEngineSprite::Find("MagicBoltBall0"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Player");
			Dir.MoveChild("Skill");
			Dir.MoveChild("MagicBolt");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}
	//UI Status 리소스 로드
	{
		if (nullptr == GameEngineSprite::Find("AniGauge,png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("UI");
			Dir.MoveChild("Status");


			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("AniGauge.png");
			GameEngineSprite::CreateSingle("HPBar.png");
			GameEngineSprite::CreateSingle("MPBar.png");
			GameEngineSprite::CreateSingle("StatusLayer.png");
			GameEngineSprite::CreateSingle("StatusLayer.png");
		}

	}

	//QuickSlot UI 리소스
	{
		if (nullptr == GameEngineSprite::Find("QuickBack,png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("UI");
			Dir.MoveChild("Quick");


			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("QuickBack.png");
			GameEngineSprite::CreateSingle("QuickButton.png");
			GameEngineSprite::CreateSingle("QuickCover.png");

		}

	}

	//MiniMap 리소스 로드
	{
		if (nullptr == GameEngineSprite::Find("QuickBack,png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("UI");
			Dir.MoveChild("MiniMap");


			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("MinMapLeft.png");
			GameEngineSprite::CreateSingle("MiniMapBottom.png");
			GameEngineSprite::CreateSingle("MiniMapLeft.png");
			GameEngineSprite::CreateSingle("MiniMapLeftBottom.png");
			GameEngineSprite::CreateSingle("MiniMapLeftTop.png");
			GameEngineSprite::CreateSingle("MiniMapRight.png");
			GameEngineSprite::CreateSingle("MiniMapRightBottom.png");
			GameEngineSprite::CreateSingle("MiniMapRightTop.png");
			GameEngineSprite::CreateSingle("MiniMapTop.png");
			GameEngineSprite::CreateSingle("MiniMapUser.png");


		}

	}

	{
		if (nullptr == GameEngineSprite::Find("0.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Number");


			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("0.png");
			GameEngineSprite::CreateSingle("1.png");
			GameEngineSprite::CreateSingle("2.png");
			GameEngineSprite::CreateSingle("3.png");
			GameEngineSprite::CreateSingle("4.png");
			GameEngineSprite::CreateSingle("5.png");
			GameEngineSprite::CreateSingle("6.png");
			GameEngineSprite::CreateSingle("7.png");
			GameEngineSprite::CreateSingle("8.png");
			GameEngineSprite::CreateSingle("9.png");
		}
	}
	//달팽이 리소스 로드
	{
		if (nullptr == GameEngineSprite::Find("SnaleDie0"))
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
		if (nullptr == GameEngineSprite::Find("Ellinia0,png"))
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
			GameEngineSprite::CreateSingle("Ellinia0MiniMap.png");
		}
	}

	
}

void Ellinia0_Level::ActorSetting()
{
	
	if (nullptr == Player0)
	{
		Player0 = CreateActor<Player>(static_cast<int>(ContentsObjectType::Player));
		Player0->SetColMap("ColEllinia0.png");
		Player0->Transform.SetLocalPosition({ 500.0f, -400.0f });
		Player0->SetCurMap("Ellinia0.png");
	}

	if (nullptr == Map0)
	{
		Map0 = CreateActor<Ellinia0_Map>(11);
		Map0->Transform.SetLocalPosition({ 793.0f,-935.0f });
	}

	if (nullptr == Snale0)
	{
		Snale0 = CreateActor<Snale>(20);
		Snale0->SetColMap("ColEllinia0.png");
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


void Ellinia0_Level::CameraSetting()
{
	GetMainCamera()->Transform.AddLocalPosition({ 793.0f,1371.0f,0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition({ WindowScale.X, -WindowScale.Y });
}