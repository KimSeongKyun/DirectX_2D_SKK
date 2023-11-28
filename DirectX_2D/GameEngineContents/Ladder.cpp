#include "PreCompile.h"
#include "Ladder.h"

Ladder::Ladder() 
{
}

Ladder::~Ladder() 
{
}

void Ladder::Start()
{
	RenderSetting();
}
void Ladder::Update(float _delta)
{

}

void Ladder::RenderSetting()
{
	LadderCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Ladder);
	LadderCollision->SetCollisionType(ColType::AABBBOX2D);
	
}

void Ladder::SetLadderScale(float4 _Scale)
{
	LadderCollision->Transform.SetWorldScale(_Scale);
}
