#include "PreCompile.h"
#include "Ellinia0_Level.h"
#include "Player.h"
#include "Ellinia0_Map.h"
#include "Snale.h"
#include "Status.h"
#include "QuickSlot.h"
#include "MiniMap.h"
#include "Ladder.h"
#include "Portal.h"
#include "MapleStoryCore.h"


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
	GameEngineInput::AddInputObject(this);
	ReSpawn(_Delta);
	if (true == GameEngineInput::IsDown(VK_F2, this))
	{
		for (size_t i = 0; i < Snales.size(); i++)
		{
			if (false == Snales[i]->IsUpdate())
			{
				Snales[i] = CreateActor<Snale>(20);
				Snales[i]->SetColMap("ColEllinia0.png");
				Snales[i]->Transform.SetLocalPosition(SnalePoses[i]);
			}

		}
	}
	
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
	BasicLevel::FadeIn();
	Player0->Transform.SetWorldPosition(MapleStoryCore::PlayerPos);
	
}

void Ellinia0_Level::LevelEnd(GameEngineLevel* _NextLevel)
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

	for (size_t i = 0; i < Snales.size(); i++)
	{
		Snales[i]->Release();
		Snales[i] = nullptr;
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

	if (nullptr != Ladder2)
	{
		Ladder2->Death();
		Ladder2 = nullptr;
	}

	if (nullptr != Ladder3)
	{
		Ladder3->Death();
		Ladder3 = nullptr;
	}

	if (nullptr != Ladder4)
	{
		Ladder4->Death();
		Ladder4 = nullptr;
	}
	
	if (nullptr != Ladder5)
	{
		Ladder5->Death();
		Ladder5 = nullptr;
	}

	if (nullptr != Ladder6)
	{
		Ladder6->Death();
		Ladder6 = nullptr;
	}

	if (nullptr != Portal0)
	{
		Portal0->Death();
		Portal0 = nullptr;
	}
}

void Ellinia0_Level::ResourceLoad()
{	
	BasicLevel::ResourceLoad();
	
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

	
	std::shared_ptr<Snale> Snale0 = CreateActor<Snale>(20);
	Snale0->SetColMap("ColEllinia0.png");
	Snale0->Transform.SetLocalPosition({ 420.0f, -320.0f });
	Snales.push_back(Snale0);
	SnalePoses.push_back({ 420.0f, -320.0f });
	
	std::shared_ptr<Snale> Snale1 = CreateActor<Snale>(20);
	Snale1->SetColMap("ColEllinia0.png");
	Snale1->Transform.SetLocalPosition({ 780.0f, -320.0f });
	Snales.push_back(Snale1);
	SnalePoses.push_back({ 780.0f, -320.0f });

	std::shared_ptr<Snale> Snale2 = CreateActor<Snale>(20);
	Snale2->SetColMap("ColEllinia0.png");
	Snale2->Transform.SetLocalPosition({ 1060.0f, -220.0f });
	Snales.push_back(Snale2);
	SnalePoses.push_back({ 1060.0f, -220.0f });

	std::shared_ptr<Snale> Snale3 = CreateActor<Snale>(20);
	Snale3->SetColMap("ColEllinia0.png");
	Snale3->Transform.SetLocalPosition({ 160.0f, -610.0f });
	Snales.push_back(Snale3);
	SnalePoses.push_back({ 160.0f, -610.0f });

	std::shared_ptr<Snale> Snale4 = CreateActor<Snale>(20);
	Snale4->SetColMap("ColEllinia0.png");
	Snale4->Transform.SetLocalPosition({ 420.0f, -610.0f });
	Snales.push_back(Snale4);
	SnalePoses.push_back({ 420.0f, -610.0f });

	std::shared_ptr<Snale> Snale5 = CreateActor<Snale>(20);
	Snale5->SetColMap("ColEllinia0.png");
	Snale5->Transform.SetLocalPosition({ 1060.0f, -610.0f });
	Snales.push_back(Snale5);
	SnalePoses.push_back({ 1060.0f, -610.0f });

	std::shared_ptr<Snale> Snale6 = CreateActor<Snale>(20);
	Snale6->SetColMap("ColEllinia0.png");
	Snale6->Transform.SetLocalPosition({ 160.0f, -920.0f });
	Snales.push_back(Snale6);
	SnalePoses.push_back({ 160.0f, -920.0f });

	std::shared_ptr<Snale> Snale7 = CreateActor<Snale>(20);
	Snale7->SetColMap("ColEllinia0.png");
	Snale7->Transform.SetLocalPosition({ 300.0f, -920.0f });
	Snales.push_back(Snale7);
	SnalePoses.push_back({ 300.0f, -920.0f });

	std::shared_ptr<Snale> Snale8 = CreateActor<Snale>(20);
	Snale8->SetColMap("ColEllinia0.png");
	Snale8->Transform.SetLocalPosition({ 420.0f, -920.0f });
	Snales.push_back(Snale8);
	SnalePoses.push_back({ 420.0f, -920.0f });

	std::shared_ptr<Snale> Snale9 = CreateActor<Snale>(20);
	Snale9->SetColMap("ColEllinia0.png");
	Snale9->Transform.SetLocalPosition({ 160.0f, -1640.0f });
	Snales.push_back(Snale9);
	SnalePoses.push_back({ 160.0f, -1640.0f });

	std::shared_ptr<Snale> Snale10 = CreateActor<Snale>(20);
	Snale10->SetColMap("ColEllinia0.png");
	Snale10->Transform.SetLocalPosition({ 420.0f, -1640.0f });
	Snales.push_back(Snale10);
	SnalePoses.push_back({ 420.0f, -1640.0f });

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

		Ladder0->Transform.SetWorldPosition({ 717.0f, -583.0f });
		Ladder0->SetLadderScale({ 36.0f,237.0f });

	}
	if (Ladder1 == nullptr)
	{
		Ladder1 = CreateActor<Ladder>(12);

		Ladder1->Transform.SetWorldPosition({ 514.0f,-774.0f });
		Ladder1->SetLadderScale({ 36.0f,243.0f });

	}

	if (Ladder2 == nullptr)
	{
		Ladder2 = CreateActor<Ladder>(12);

		Ladder2->Transform.SetWorldPosition({ 1067.0f, -774.0f });
		Ladder2->SetLadderScale({ 36.0f,243.0f });

	}

	if (Ladder3 == nullptr)
	{
		Ladder3 = CreateActor<Ladder>(12);

		Ladder3->Transform.SetWorldPosition({ 70.0f, -1019.0f });
		Ladder3->SetLadderScale({ 36.0f,131.0f });

	}

	if (Ladder4 == nullptr)
	{
		Ladder4 = CreateActor<Ladder>(12);

		Ladder4->Transform.SetWorldPosition({ 127.0f, -1199.0f });
		Ladder4->SetLadderScale({ 36.0f,134.0f });

	}

	if (Ladder5 == nullptr)
	{
		Ladder5 = CreateActor<Ladder>(12);

		Ladder5->Transform.SetWorldPosition({ 76.0f, -1380.0f });
		Ladder5->SetLadderScale({ 36.0f,134.0f });

	}

	if (Ladder6 == nullptr)
	{
		Ladder6 = CreateActor<Ladder>(12);

		Ladder6->Transform.SetWorldPosition({ 131.0f, -1563.0f });
		Ladder6->SetLadderScale({ 36.0f,134.0f });

	}

	if (Portal0 == nullptr)
	{
		Portal0 = CreateActor<Portal>(12);

		Portal0->Transform.SetWorldPosition({ 1480.0f, -1806.0f });
		Portal0->SetLevelName("Ellinia1_Level");
		Portal0->SetPlayerMovePos({ 48.0f , -736.0f });


	}
}


void Ellinia0_Level::CameraSetting()
{
	GetMainCamera()->Transform.SetWorldPosition(MapleStoryCore::PlayerPos);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition({ WindowScale.X, -WindowScale.Y });
}

void Ellinia0_Level::ReSpawn(float _Delta)
{
	RespawnTime += _Delta;

	if (RespawnTime >= 30.0f)
	{
		RespawnTime = 0.0f;
		for (size_t i = 0; i < Snales.size(); i++)
		{
			if (false == Snales[i]->IsUpdate())
			{
				Snales[i] = CreateActor<Snale>(20);
				Snales[i]->SetColMap("ColEllinia0.png");
				Snales[i]->Transform.SetLocalPosition(SnalePoses[i]);
			}

		}

	}
}