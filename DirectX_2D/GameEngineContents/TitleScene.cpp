#include "PreCompile.h"
#include "TitleScene.h"

TitleScene::TitleScene() 
{
}

TitleScene::~TitleScene() 
{
}

void TitleScene::Start()
{
	TitleBack = CreateComponent<GameEngineSpriteRenderer>();
	TitleBack->SetSprite("TitleBack.png");
	TitleBack->AutoSpriteSizeOn();

	TitleScenes = CreateComponent<GameEngineSpriteRenderer>();
	TitleScenes->CreateAnimation("Wizet", "Wizet");
	TitleScenes->ChangeAnimation("Wizet");
	TitleScenes->AutoSpriteSizeOn();

	TitleScenes->SetEndEvent("Wizet", [&](GameEngineSpriteRenderer*) {

		GameEngineCore::ChangeLevel("PinkBeanLevel");
	});

}

void TitleScene::Update(float _delta)
{

}