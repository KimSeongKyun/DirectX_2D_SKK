#include "PreCompile.h"
#include "Ellinia1_Level.h"
#include "Player.h"
#include "Snale.h"
#include "Ellinia1_Map.h"
#include "Ellinia0_Map.h"

Ellinia1_Level::Ellinia1_Level() 
{
}

Ellinia1_Level::~Ellinia1_Level() 
{
}

void Ellinia1_Level::Start()
{
	OffDebug();
}

void Ellinia1_Level::Update(float _Delta)
{
	DebugSwitch();
}

void Ellinia1_Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	CameraSetting();
	ResourceLoad();
	ActorSetting();

}
void Ellinia1_Level::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}

void Ellinia1_Level::ResourceLoad()
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
	//������ ���ҽ� �ε�
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

	//�� �̹��� �ε�
	{
		if (nullptr == GameEngineSprite::Find("Ellinia1,png"))
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
				// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("Ellinia1.png");
			
		}
		
	}
}

void Ellinia1_Level::ActorSetting()
{
	if (nullptr == Player0)
	{
		Player0 = CreateActor<Player>(static_cast<int>(ContentsObjectType::Player));
		Player0->SetColMap("ColEllinia1.png");
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
}
void Ellinia1_Level::CameraSetting()
{
	GetMainCamera()->Transform.AddLocalPosition({ 793.0f,1371.0f,0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}