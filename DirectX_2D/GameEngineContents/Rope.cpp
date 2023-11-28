#include "PreCompile.h"
#include "Rope.h"

Rope::Rope() 
{
}

Rope::~Rope() 
{
}
void Rope::Start()
{
	RenderSetting();
}
void Rope::Update(float _delta)
{

}

void Rope::RenderSetting()
{
	RopeCollision = CreateComponent<GameEngineCollision>(ObjectCollision::Rope);
	RopeCollision->SetCollisionType(ColType::AABBBOX2D);

}

void Rope::SetLadderScale(float4 _Scale)
{
	RopeCollision->Transform.SetWorldScale(_Scale);
}