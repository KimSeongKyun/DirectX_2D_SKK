#include "PreCompile.h"
#include "Ellinia0_Level.h"
#include "Player.h"
#include "Ellinia0_Map.h"
#include "Snale.h"


Ellinia0_Level::Ellinia0_Level()
{
}

Ellinia0_Level::~Ellinia0_Level()
{
}

void Ellinia0_Level::Start()
{
	OffDebug();
}

void Ellinia0_Level::Update(float _Delta)
{
	DebugSwitch();
}

void Ellinia0_Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	ResourceLoad();
	ActorSetting();
	CameraSetting();
	
}

void Ellinia0_Level::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}

void Ellinia0_Level::ResourceLoad()
{	
	// �÷��̾� �ε�
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
				// ���������� �� �����ϰ� �ִ����� �ڽ��� ��Ȯ�ϰ� �����ϱ� ���ؼ�
				GameEngineFile& File = Files[i];
				GameEngineTexture::Load(File.GetStringPath());
			}

			GameEngineSprite::CreateSingle("Ellinia0.png");
			GameEngineSprite::CreateSingle("ElliniaBackGround.png");
		}
	}
}

void Ellinia0_Level::ActorSetting()
{
	
	if (nullptr == Player0)
	{
		Player0 = CreateActor<Player>(static_cast<int>(ContentsObjectType::Player));
		Player0->SetColMap("ColEllinia0.png");
		Player0->Transform.SetLocalPosition({ 500.0f, -1000.0f });
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
}


void Ellinia0_Level::CameraSetting()
{
	GetMainCamera()->Transform.AddLocalPosition({ 793.0f,1371.0f,0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}