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
}
void PinkBeanLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	
}

void PinkBeanLevel::ResourceLoad()
{
	// �÷��̾� �ε�
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
			}
		}
	}
	// ��ų ���ҽ� �ε�
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

	//��Ż ���ҽ� �ε�
	{
		if (nullptr == GameEngineSprite::Find("Portal0"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("GameEngineResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("Texture");
			Dir.MoveChild("Portal");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}
	
	

	//�� �̹��� �ε�
	{
		if (nullptr == GameEngineSprite::Find("PinkBeanMap,png"))
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
		if (nullptr == GameEngineSprite::Find("ArielAttack1Effect01"))
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
		if (nullptr == GameEngineSprite::Find("PinkBeanSkill1_01"))
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

	//UI Status ���ҽ� �ε�
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
				// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
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

	//QuickSlot UI ���ҽ�
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
				// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("QuickBack.png");
			GameEngineSprite::CreateSingle("QuickButton.png");
			GameEngineSprite::CreateSingle("QuickCover.png");

		}

	}

	//MiniMap ���ҽ� �ε�
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
				// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
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
		Ariel0->Transform.SetWorldPosition({ 894.0f, -340.0f, 1.0f });
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
}

void PinkBeanLevel::CameraSetting()
{
	GetMainCamera()->Transform.AddLocalPosition({ 793.0f,1371.0f,0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);


	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	std::shared_ptr<GameEngineCamera> UICamera = GetCamera(static_cast<int>(ECAMERAORDER::UI));
	UICamera->Transform.SetLocalPosition({ WindowScale.X, -WindowScale.Y });
}

