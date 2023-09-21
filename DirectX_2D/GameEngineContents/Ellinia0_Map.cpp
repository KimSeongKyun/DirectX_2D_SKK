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
	Ellinia0_BackGround = CreateComponent< GameEngineSpriteRenderer>(0);
	Ellinia0_BackGround->SetSprite("ElliniaBackGround.png");
	Ellinia0_BackGround->AutoSpriteSizeOn();

	Ellinia0_Map0 = CreateComponent<GameEngineSpriteRenderer>(0);
	Ellinia0_Map0->SetSprite("Ellinia0.png");
	Ellinia0_Map0->AutoSpriteSizeOn();
}
