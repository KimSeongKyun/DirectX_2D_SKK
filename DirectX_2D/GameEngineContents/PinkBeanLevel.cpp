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
#include <GameEngineCore/FadePostEffect.h>



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

	std::shared_ptr< DamageNumber> Test0 = CreateActor< DamageNumber>();
	Test0->Transform.SetLocalPosition({ 720.0f, -500.0f });
	Test0->Damage(100);
}
void PinkBeanLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

void PinkBeanLevel::ResourceLoad()
{

	BasicLevel::ResourceLoad();

	//�� �̹��� �ε�
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
				// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("PinkBeanMap.png");
			GameEngineSprite::CreateSingle("PinkBeanBackGround.png");
			GameEngineSprite::CreateSingle("PinkBeanMiniMap.png");
		}
	}

	//�Ƹ��� �̹��� �ε�
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
	//��ũ�� �̹��� �ε�
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
	//�ַθ� �̹��� �ε�

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

	// �ֱ� ���ҽ� �ε�
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

	// ���� ���ҽ� �ε�
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
		Portal0->SetLevelName("Ellinia0_Level");
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

	if (Ladder0 == nullptr)
	{
		Ladder0 = CreateActor<Ladder>(ContentsObjectType::Object);
		Ladder0->Transform.SetWorldPosition({ 894.0f, -425.0f });
		Ladder0->SetLadderScale({50.0f, 100.0f});
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
	

}

void PinkBeanLevel::CameraSetting()
{
	GetMainCamera()->Transform.AddLocalPosition({ 793.0f,1371.0f,0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition({ WindowScale.X, -WindowScale.Y });
}

