#include "PreCompile.h"
#include "Monster.h"
#include "BasicObjectElement.h"
#include <GameEngineCore/GameEngineTexture.h>

Monster::Monster() 
{
}

Monster::~Monster() 
{
}


void Monster::RendererSetting()
{
}

void Monster::Start()
{

}
void Monster::Update(float _Delta)
{

}



void Monster::GravityCheck(float _Delta)
{
	BasicObjectElement::GravityCheck(_Delta);
}
void Monster::SetCurMap(const std::string_view& _ColMap)
{
	CurMap = GameEngineTexture::Find(_ColMap);
}

float4 Monster::GetMonsterSize()
{
	return MonsterScale;
}
void Monster::SetMonsterSize(float4 _Size)
{
	MonsterScale = _Size;
}
 
void  Monster::Damage(int _Damge)
{

}

void Monster::SetKnockBack()	
{
	KnockBack = true;
}
