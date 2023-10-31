#include "PreCompile.h"
#include "PlayLevel.h"
#include "Player.h"
#include "Ellinia0_Map.h"


PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Start()
{

}

void PlayLevel::Update(float _Delta)
{
	
}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	ResourceLoad();
	ActorSetting();
	CameraSetting();
	
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}

void PlayLevel::ResourceLoad()
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
		if (nullptr == GameEngineSprite::Find("MagicBoltBall"))
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

void PlayLevel::ActorSetting()
{
	
	if (nullptr == Player0)
	{
		Player0 = CreateActor<Player>(10);
		Player0->SetColMap("ColEllinia0.png");
	}

	if (nullptr == Map0)
	{
		Map0 = CreateActor<Ellinia0_Map>(11);
		Map0->Transform.SetLocalPosition({ 793.0f,-935.0f });
	}
}


void PlayLevel::CameraSetting()
{
	GetMainCamera()->Transform.AddLocalPosition({ 793.0f,1371.0f,0.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);
}