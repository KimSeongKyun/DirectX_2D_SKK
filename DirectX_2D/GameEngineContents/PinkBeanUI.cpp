#include "PreCompile.h"
#include "PinkBeanUI.h"
#include "PinkBean.h"

PinkBeanUI::PinkBeanUI() 
{
}

PinkBeanUI::~PinkBeanUI() 
{

}

void PinkBeanUI::Start()
{
	ComponentSetting();
}
void PinkBeanUI::Update(float _Delta)
{
	if (nullptr == PinkBean::MainPinkBean)
	{
		return;
	}
	float PinkBeanHP = static_cast<float>(PinkBean::MainPinkBean->HP);

	if (PinkBeanHP < 0.0f)
	{
		PinkBeanHP = 0.0f;
	}
	float Ratio = PinkBeanHP / PinkBeanHPMax;

	HPBar->Transform.SetWorldScale({ Ratio ,1.0f });
	HPBar->Transform.SetLocalPosition({ 39.0f, -4.0f });
}

void PinkBeanUI::ComponentSetting()
{
	//HPBack = CreateComponent<GameEngineUIRenderer>(0);
	//HPBack->SetSprite("PinkHPBarBack.png");
	//HPBack->AutoSpriteSizeOn();
	//HPBack->SetPivotType(PivotType::LeftTop);
	//HPBack->Transform.SetLocalPosition({ 39.0f, -4.0f });

	HPBar = CreateComponent<GameEngineUIRenderer>(1);
	HPBar->SetSprite("PinkBeanHPBar.png");
	HPBar->Transform.SetWorldScale({ 1.0f,1.0f });
	HPBar->SetPivotType(PivotType::LeftTop);
	HPBar->Transform.SetLocalPosition({ 39.0f, -4.0f });

	Panel0 = CreateComponent<GameEngineUIRenderer>(0);
	Panel0->SetSprite("PinkBeanHPUI.png");
	Panel0->AutoSpriteSizeOn();
	Panel0->SetPivotType(PivotType::LeftTop);

	
}