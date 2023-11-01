#include "PreCompile.h"
#include "Ellinia0_Map.h"

Ellinia0_Map::Ellinia0_Map() 
{
}

Ellinia0_Map::~Ellinia0_Map() 
{
}

void Ellinia0_Map::Start()
{
	Ellinia0_BackGround = CreateComponent< GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::BackGround));
	Ellinia0_BackGround->SetSprite("ElliniaBackGround.png");
	Ellinia0_BackGround->AutoSpriteSizeOn();


	Ellinia0_Map0 = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Ground));
	Ellinia0_Map0->SetSprite("Ellinia0.png");
	Ellinia0_Map0->AutoSpriteSizeOn();

	float4 MapScale = Ellinia0_Map0->Transform.GetWorldScale();
	//Transform.AddLocalPosition({ MapScale.hX(), MapScale.hY()});
}
