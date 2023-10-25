#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineTexture.h>

Monster::Monster() 
{
}

Monster::~Monster() 
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
	//GravityOn = true;
	//
	//if (GravityOn == true)
	//{
	//	Gravity += 10 *_Delta;
	//
	//	if (Gravity > 5.0f)
	//	{
	//		Gravity = 5.0f;
	//	}
	//
	//	float4 PlayerGravityValue = float4::DOWN * Gravity;
	//	float4 CurPosition = Transform.GetWorldPosition();
	//	Transform.AddWorldPosition(float4::DOWN * Gravity);
	//
	//	float4 ColMapDif = { ColMap->GetScale().hx(),ColMap->GetScale().hy() };
	//	float4 NextPosition = CurPosition + float4::Down * Gravity;
	//	if (ColMap->GetPixel(ColMapDif.ix() + NextPosition.ix(), ColMapDif.iy() + (int)MonsterScale.hy() - NextPosition.iy(), ColGroundColor) == ColGroundColor)
	//	{
	//		GetTransform()->SetWorldPosition(CurPosition);
	//		GravityOn = false;
	//	}
	//}
}
void Monster::SetColMap(const std::string_view _ColMap)
{
	 ColMap = GameEngineTexture::Find(_ColMap); 
	
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
 
void Monster::Damage(int _Damge)
{	
}

void Monster::SetKnockBack()	
{
	KnockBack = true;
}
