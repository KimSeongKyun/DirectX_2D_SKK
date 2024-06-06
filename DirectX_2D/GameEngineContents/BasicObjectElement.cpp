#include "PreCompile.h"
#include "BasicObjectElement.h"


BasicObjectElement::BasicObjectElement() 
{
}

BasicObjectElement::~BasicObjectElement() 
{
	
}

void BasicObjectElement::RendererSetting()
{

}

void BasicObjectElement::GravityCheck(float _DeltaTime)
{
	if (IsGravity == true)
	{
		Gravity += 5   * _DeltaTime;

		if (Gravity > 5.0f)
		{
			Gravity = 5.0f;
		}

		float4 CurPosition = Transform.GetWorldPosition();
		Transform.AddWorldPosition(float4::DOWN * Gravity);

		float4 NextPosition = CurPosition + (float4::DOWN * Gravity);

		if (ColMap->GetColor({ CurPosition.X, ObjectSize.hY() - CurPosition.Y}, ColColor) == ColColor)
		{
			while (ColMap->GetColor({ CurPosition.X, ObjectSize.hY() - CurPosition.Y}, ColColor) != ColColor)
			{
				CurPosition.Y -= 1.0f;
			}

			Transform.SetWorldPosition(CurPosition);
			IsGravity = false;
			Gravity = 0.0f;
			/*Transform.SetWorldPosition(CurPosition);
			IsGravity = false;
			Gravity = 0.0f;*/
		}
	}
}

void BasicObjectElement::Damage(int _Damge)
{

}

