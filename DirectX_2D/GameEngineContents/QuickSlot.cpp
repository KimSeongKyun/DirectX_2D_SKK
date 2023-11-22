#include "PreCompile.h"
#include "QuickSlot.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

QuickSlot::QuickSlot() 
{
}

QuickSlot::~QuickSlot() 
{
}

void QuickSlot::Start()
{
	/*std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	Camera->SetProjectionType(EPROJECTIONTYPE::Orthographic);
	Camera->Transform.SetLocalPosition({ 0, 0, -1000.0f });*/

	

	Back = CreateComponent<GameEngineUIRenderer>(15);
	Back->SetSprite("QuickBack.png");
	Back->AutoSpriteSizeOn();

	Cover = CreateComponent<GameEngineUIRenderer>(15);
	Cover->SetSprite("QuickCover.png");
	Cover->AutoSpriteSizeOn();

	
	Render = CreateComponent<GameEngineUIRenderer>(15);
	Render->AutoSpriteSizeOn();
	Render->SetSprite("QuickButton.png");
	Render->Transform.AddLocalPosition({ -88.0f, 0.0f});
}

void QuickSlot::Update(float _Delta)
{

}