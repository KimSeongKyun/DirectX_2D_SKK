#include "PreCompile.h"
#include "Ellinia1_Map.h"

Ellinia1_Map::Ellinia1_Map() 
{
}

Ellinia1_Map::~Ellinia1_Map() 
{

}
void Ellinia1_Map::Start()
{
	Ellinia1_Map1 = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Ground));
	Ellinia1_Map1->SetSprite("Ellinia1.png");
	Ellinia1_Map1->AutoSpriteSizeOn();

	MapScale = Ellinia1_Map1->Transform.GetWorldScale();
}

