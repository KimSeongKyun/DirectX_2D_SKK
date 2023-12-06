#include "PreCompile.h"
#include "Status.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "Player.h"

Status::Status()
{
}

Status::~Status()
{
}

void Status::Start()
{
	/*std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	Camera->Transform.SetLocalPosition({ 0, 0, -1000.0f });*/

	{
		{
			BackHP = CreateComponent<GameEngineUIRenderer>(15);
			BackHP->SetSprite("AniGauge.png");
			BackHP->AutoSpriteSizeOn();
			BackHP->Transform.SetLocalPosition({ 10.0f, -2.0f, 1.0f });
			
		}

		{
			BackMP = CreateComponent<GameEngineUIRenderer>(15);
			BackMP->SetSprite("AniGauge.png");
			BackMP->AutoSpriteSizeOn();
			BackMP->Transform.SetLocalPosition({ 10.0f, -17.0f, 1.0f });
		}

		{
			//34
			HPBar = CreateComponent<GameEngineUIRenderer>(15);
			HPBar->SetSprite("HPBar.png");
			HPBar->AutoSpriteSizeOn();
			HPBar->Transform.SetLocalPosition({ 10.0f, -2.0f, 1.0f });
			
		}

		{
			//51
			MPBar = CreateComponent<GameEngineUIRenderer>(15);
			MPBar->SetSprite("MPBar.png");
			MPBar->AutoSpriteSizeOn();
			MPBar->Transform.SetLocalPosition({ 10.0f, -17.0f, 1.0f });
		}

		{
			// Status 백그라운드
			StatusBack = CreateComponent<GameEngineUIRenderer>(15);
			StatusBack->SetSprite("StatusLayer.png");
			StatusBack->AutoSpriteSizeOn();
		}

	}
	//{
	//	// HPBar
	//	ButtonDeath = CreateComponent<GameEngineUIRenderer>();
	//	ButtonDeath->GetTransform()->SetLocalPosition({ 500.0f, 300.0f });
	//	ButtonDeath->GetTransform()->SetLocalScale({ 150.0f, 150.0f, 1.0f });
	//}

	//{
	//	std::shared_ptr<GameEngineButton> Button = GetLevel()->CreateActor<GameEngineButton>(520);
	//	Button->GetTransform()->SetLocalPosition({ -300, 200, 1 });
	//	Button->GetTransform()->SetLocalScale({100, 100, 1});

	//	Button->SetEvent([this]() 
	//		{
	//			// nullptr 까지 다해줘야 합니다.
	//			if (nullptr != ButtonDeath)
	//			{
	//				this->ButtonDeath->Death();
	//				ButtonDeath = nullptr;
	//			}
	//			// Player::MainPlayer->TestCallBack();
	//		});
	//}


}

void Status::Update(float _Delta)
{

}