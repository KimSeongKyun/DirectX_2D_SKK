#include "PreCompile.h"
#include "DamageNumber.h"

DamageNumber::DamageNumber() 
{
}

DamageNumber::~DamageNumber() 
{
}
void DamageNumber::Start()
{

}

void DamageNumber::Update(float _Delta)
{
	LiveTime += _Delta;
	if (NumberLists.size() != 0)
	{
		for (size_t i = 0; i < NumberLists.size(); i++)
		{
			NumberLists[i]->Transform.AddLocalPosition(float4::UP * 100 * _Delta);

		}
	}
	
	if (LiveTime >= 0.7f)
	{
		Death();
	}
}
void DamageNumber::Damage(int _Damage)
{
	std::vector<int> DamageList;

	int Damage = _Damage;

	while (Damage > 0)
	{
		DamageList.push_back(Damage % 10);
		int a = Damage % 10;
		Damage /= 10;
	}

	int a = 0;
	for (int i = static_cast<int>(DamageList.size() - 1); 0 <= i; --i)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Number;
		Number = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::DamageNumber);
		Number->SetSprite(std::to_string(DamageList[i]) + ".png");
		Number->Transform.SetLocalPosition({ static_cast<float>(20 * a), 0.0f });
		NumberLists.push_back(Number);
		a++;
	}


}