#include "PreCompile.h"
#include "Ellinia1_Level.h"
#include "Player.h"
#include "Snale.h"
#include "Ellinia1_Map.h"
#include "Ellinia0_Map.h"
#include "Status.h"
#include "QuickSlot.h"
#include "MiniMap.h"
#include "Ladder.h"
#include "Portal.h"
#include "MapleStoryCore.h"

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
	Player0->Transform.SetWorldPosition(MapleStoryCore::PlayerPos);
	BasicLevel::FadeIn();

}
void Ellinia1_Level::LevelEnd(GameEngineLevel* _NextLevel)
{
	BasicLevel::LevelEnd(_NextLevel);
	if (nullptr != Player0)
	{
		Player0->Death();
		Player0 = nullptr;
	}

	if (nullptr != Map0)
	{
		Map0->Death();
		Map0 = nullptr;
	}

	if (nullptr != Snale0)
	{
		Snale0->Death();
		Snale0 = nullptr;
	}

	if (nullptr != Status0)
	{
		Status0->Death();
		Status0 = nullptr;
	}
	if (nullptr != QuickSlot0)
	{
		QuickSlot0->Death();
		QuickSlot0 = nullptr;
	}

	if (nullptr != MiniMap0)
	{
		MiniMap0->Death();
		MiniMap0 = nullptr;
	}

	if (nullptr != Ladder0)
	{
		Ladder0->Death();
		Ladder0 = nullptr;
	}
	if (nullptr != Ladder1)
	{
		Ladder1->Death();
		Ladder1 = nullptr;
	}

	if (nullptr != Portal0)
	{
		Portal0->Death();
		Portal0 = nullptr;
	}

	if (nullptr != Portal1)
	{
		Portal1->Death();
		Portal1 = nullptr;
	}
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

	if (Ladder0 == nullptr)
	{
		Ladder0 = CreateActor<Ladder>(12);

		Ladder0->Transform.SetWorldPosition({ 855.0f, -1303.0f });
		Ladder0->SetLadderScale({ 36.0f,700.0f });

	}
	if (Ladder1 == nullptr)
	{
		Ladder1 = CreateActor<Ladder>(12);

		Ladder1->Transform.SetWorldPosition({ 1069.0f,-736.0f });
		Ladder1->SetLadderScale({ 36.0f,287.0f });
		
	}
	if (Portal0 == nullptr)
	{
		Portal0 = CreateActor<Portal>(12);

		Portal0->Transform.SetWorldPosition({ 48.0f, -1862.0f });
		Portal0->SetLevelName("PinkBeanLevel");
		Portal0->SetPlayerMovePos({ 100.0f , -630.0f });
		
		
	}

	if (Portal1 == nullptr)
	{
		Portal1 = CreateActor<Portal>(12);

		Portal1->Transform.SetWorldPosition({ 48.0f, -782.0f });
		Portal1->SetLevelName("Ellinia0_Level");
		Portal1->SetPlayerMovePos({ 1480.0f ,-1770.0f });
	}

		
}
void Ellinia1_Level::CameraSetting()
{
	GetMainCamera()->Transform.SetWorldPosition(MapleStoryCore::PlayerPos);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition({ WindowScale.X, -WindowScale.Y });
}