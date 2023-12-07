#include "PreCompile.h"
#include "PinkBeanLevel.h"

#include "Player.h"
#include "PinkBeanMap.h"
#include "Ariel.h"
#include "PinkBeanDummy.h"
#include "Portal.h"
#include "Status.h"
#include "QuickSlot.h"
#include "MiniMap.h"
#include "Ladder.h"
#include "DamageNumber.h"
#include "Solomon.h"
#include "Rex.h"
#include "Whigin.h"
#include "Munin.h"
#include "Mouse.h"
#include "Inventory.h"
#include "Rope.h"
#include "MapleStoryCore.h"
#include "PinkBean.h"




PinkBeanLevel::PinkBeanLevel() 
{
}

PinkBeanLevel::~PinkBeanLevel() 
{
	
}

void PinkBeanLevel::Start()
{
	BasicLevel::Start();
}
void PinkBeanLevel::Update(float _Delta)
{
	DebugSwitch();
	if (GameEngineInput::IsDown(VK_F1,this))
	{
		Ariel0->Damage(1000000);
		Rex0->Damage(1000000);
		Solomon0->Damage(1000000);
		Whigin0->Damage(1000000);
		Munin0->Damage(1000000);

	}

}
void PinkBeanLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BasicLevel::LevelStart(_PrevLevel);
	ResourceLoad();
	CurMiniMap = GameEngineTexture::Find("PinkBeanMiniMap.png");
	CurMap = GameEngineTexture::Find("PinkBeanMap.png");
	CurMapName = "PinkBeanMiniMap.png";
	CameraSetting();
	ActorSetting();
	//Player0->Transform.SetWorldPosition(MapleStoryCore::PlayerPos);
	//std::shared_ptr< DamageNumber> Test0 = CreateActor< DamageNumber>();
	//Test0->Transform.SetLocalPosition({ 720.0f, -500.0f });
	//Test0->Damage(100);
	BasicLevel::FadeIn();
}


void PinkBeanLevel::ResourceLoad()
{

	BasicLevel::ResourceLoad();

	//맵 이미지 로드
	{
		if (nullptr == GameEngineSprite::Find("PinkBeanMap.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Map");
			Dir.MoveChild("PinkBeanMap");
			std::vector<GameEngineFile> Files = Dir.GetAllFile();

			for (size_t i = 0; i < Files.size(); i++)
			{
				// 구조적으로 잘 이해하고 있는지를 자신이 명확하게 인지하기 위해서
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("PinkBeanMap.png");
			GameEngineSprite::CreateSingle("PinkBeanBackGround.png");
			GameEngineSprite::CreateSingle("PinkBeanMiniMap.png");
		}
	}

	//아리엘 이미지 로드
	{
		if (nullptr == GameEngineSprite::Find("ArielAttack1Effect01.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("Ariel");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}
	//핑크빈 이미지 로드
	{
		if (nullptr == GameEngineSprite::Find("PinkBeanSkill1_01.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("PinkBeanDummy");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}

	{
		if (nullptr == GameEngineSprite::Find("PinkBeanGenesis00.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("PinkBean");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}
	//솔로몬 이미지 로드

	{
		if (nullptr == GameEngineSprite::Find("SolomonAttack1Effect00.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("Solomon");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}

	{
		if (nullptr == GameEngineSprite::Find("RexAttack1Effect00.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("Rex");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}

	// 휘긴 리소스 로드
	{
		if (nullptr == GameEngineSprite::Find("WhiginAttack1Effect0.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("Whigin");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}

	// 무닌 리소스 로드
	{
		if (nullptr == GameEngineSprite::Find("MuninAttack1Effect0.png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Monster");
			Dir.MoveChild("Munin");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}
}

void PinkBeanLevel::ActorSetting()
{
	if (Player0 == nullptr)
	{
		Player0 = CreateActor<Player>(static_cast<int>(ContentsObjectType::Player));
		Player0->SetColMap("ColPinkBean.png");
		Player0->Transform.SetLocalPosition({ 894.0f, -425.0f });
		Player0->SetCurMap("PinkBeanBackGround.png");
	}

	if (Map0 == nullptr)
	{
		Map0 = CreateActor<PinkBeanMap>(11);
		Map0->Transform.SetLocalPosition({ 894.0f , -424.0f });
	}
	if (Ariel0 == nullptr)
	{
		Ariel0 = CreateActor<Ariel>();
		Ariel0->Transform.SetWorldPosition({ 903.0f, -340.0f, 1.0f });
	}
	
	if (PinkBeanDummy0 == nullptr)
	{
		PinkBeanDummy0 = CreateActor<PinkBeanDummy>(11);
		PinkBeanDummy0->Transform.SetWorldPosition({ 920.0f, -530.0f, 1.0f });
	}

	if (Portal0 == nullptr)
	{
		Portal0 = CreateActor<Portal>(11);
		Portal0->Transform.SetWorldPosition({ 100.0f, -700.0f, 1.0f });
		Portal0->SetLevelName("Ellinia1_Level");
	}

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	if (Status0 == nullptr)
	{
		
		Status0 = CreateActor<Status>(12);
		Status0->Transform.SetWorldPosition({ WindowScale.hX(), -690.0f});
	}
	if (QuickSlot0 == nullptr)
	{
		QuickSlot0 = CreateActor<QuickSlot>(12);
		QuickSlot0->Transform.SetWorldPosition({ WindowScale.hX()+400.0f, -685.0f });
	}

	if (MiniMap0 == nullptr)
	{
		MiniMap0 = CreateActor<MiniMap>(12);
		
		MiniMap0->Transform.SetWorldPosition({ 0.0f, 0.0f });
		
	}

	if (Rope0 == nullptr)
	{
		Rope0 = CreateActor<Rope>(12);

		Rope0->Transform.SetWorldPosition({ 1383.0f, -336.0f });
		Rope0->SetLadderScale({ 9.0f, 126.0f });

	}
	if (Rope1 == nullptr)
	{
		Rope1 = CreateActor<Rope>(12);

		Rope1->Transform.SetWorldPosition({ 437.0f,-336.0f });
		Rope1->SetLadderScale({ 9.0f,126.0f });

	}

	if (Rope2 == nullptr)
	{
		Rope2 = CreateActor<Rope>(12);

		Rope2->Transform.SetWorldPosition({ 1393, -522.0f });
		Rope2->SetLadderScale({ 9.0f,100.0f });

	}

	if (Rope3 == nullptr)
	{
		Rope3 = CreateActor<Rope>(12);

		Rope3->Transform.SetWorldPosition({ 358.0f, -512.0f });
		Rope3->SetLadderScale({ 9.0f,120.0f });

	}

	if (Solomon0 == nullptr)
	{
		Solomon0 = CreateActor<Solomon>();
		Solomon0->Transform.SetWorldPosition({ 235.0f, -648.0f, 1.0f });
	}

	if (Rex0 == nullptr)
	{
		Rex0 = CreateActor<Rex>();
		Rex0->Transform.SetWorldPosition({ 1577.0f, -648.0f, 1.0f });
	}

	if (Whigin0 == nullptr)
	{
		Whigin0 = CreateActor<Whigin>();
		Whigin0->Transform.SetWorldPosition({ 590.0f, -622.0f, 1.0f });
	}

	if (Munin0 == nullptr)
	{
		Munin0 = CreateActor<Munin>();
		Munin0->Transform.SetWorldPosition({1217.0f, -622.0f, 1.0f });
	}

	if (Mouse0 == nullptr)
	{
		Mouse0 = CreateActor<Mouse>(12);

		//Mouse0->Transform.SetWorldPosition({ 0.0f, 0.0f });

	}


	if (Inventory0 == nullptr)
	{
		Inventory0 = CreateActor<Inventory>(12);
		Inventory0->Transform.SetWorldPosition({ 0.0f ,0.0f });
		//Mouse0->Transform.SetWorldPosition({ 0.0f, 0.0f });

	}
	//if (PinkBean0 == nullptr)
	//{
	//	PinkBean0 = CreateActor<PinkBean>(12);
	//	//PinkBean0->Transform.SetWorldPosition({ 0.0f ,0.0f });
	//	PinkBean0->Transform.SetWorldPosition({ 920.0f, -650.0f, 1.0f });
	//	
	//
	//}

}
void PinkBeanLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BasicLevel::LevelEnd(_NextLevel);
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

	if (nullptr != Ariel0)
	{
		Ariel0->Death();
		Ariel0 = nullptr;
	}

	if (nullptr != PinkBeanDummy0)
	{
		PinkBeanDummy0->Death();
		PinkBeanDummy0 = nullptr;
	}

	if (nullptr != Rope0)
	{
		Rope0->Death();
		Rope0 = nullptr;
	}
	if (nullptr != Rope1)
	{
		Rope1->Death();
		Rope1 = nullptr;
	}

	if (nullptr != Rope2)
	{
		Rope2->Death();
		Rope2 = nullptr;
	}

	if (nullptr != Rope3)
	{
		Rope3->Death();
		Rope3 = nullptr;
	}

	if (nullptr != Portal0)
	{
		Portal0->Death();
		Portal0 = nullptr;
	}

	if (nullptr != Solomon0)
	{
		Solomon0->Death();
		Solomon0 = nullptr;
	}

	if (nullptr != Rex0)
	{
		Rex0->Death();
		Rex0 = nullptr;
	}

	if (nullptr != Whigin0)
	{
		Whigin0->Death();
		Whigin0 = nullptr;
	}


	if (nullptr != Munin0)
	{
		Munin0->Death();
		Munin0 = nullptr;
	}

	if (nullptr != Mouse0)
	{
		Mouse0->Death();
		Mouse0 = nullptr;
	}

	if (nullptr != Inventory0)
	{
		Inventory0->Death();
		Inventory0 = nullptr;
	}
}
void PinkBeanLevel::CameraSetting()
{
	GetMainCamera()->Transform.SetWorldPosition(MapleStoryCore::PlayerPos);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition({ WindowScale.X, -WindowScale.Y });
}

