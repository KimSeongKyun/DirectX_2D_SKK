#include "PreCompile.h"
#include "PinkBeanMap.h"

PinkBeanMap::PinkBeanMap() 
{
}

PinkBeanMap::~PinkBeanMap() 
{
}

void PinkBeanMap::Start()
{
	Map0 = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Ground));
	Map0->SetSprite("PinkBeanMap.png");
	Map0->AutoSpriteSizeOn();

	BackGround= CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::BackGround));
	BackGround->SetSprite("PinkBeanBackGround.png");
	BackGround->AutoSpriteSizeOn();
}