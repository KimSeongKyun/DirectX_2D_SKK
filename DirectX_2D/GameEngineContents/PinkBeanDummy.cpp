#include "PreCompile.h"
#include "PinkBeanDummy.h"

PinkBeanDummy::PinkBeanDummy() 
{
}

PinkBeanDummy::~PinkBeanDummy() 
{
}

void PinkBeanDummy::Start()
{
	ComponetSetting();
}
void PinkBeanDummy::Update(float _Delta)
{
	if (PinkBeanDummyRender->IsCurAnimationEnd() == true)
	{
		if (PinkBeanState == "Stand")
		{
			++StateNumber;
			ChangeState(StateNumber);
			return;
		}

		if (PinkBeanState != "Stand")
		{
			PinkBeanDummyRender->ChangeAnimation("PinkBeanStand0");
			PinkBeanDummyRender->Transform.AddLocalPosition({ -ResourceDif.X, -ResourceDif.Y });
			PinkBeanState = "Stand";

			if (StateNumber == 12)
			{
				StateNumber = 0;
			}
		}
	}
}
void PinkBeanDummy::SetHP(int _HP)
{

}
void PinkBeanDummy::Damage(int _Damge)
{

}

void PinkBeanDummy::ComponetSetting()
{
	if (PinkBeanDummyRender == nullptr)
	{
		PinkBeanDummyRender = CreateComponent<GameEngineSpriteRenderer>(static_cast<int>(ContentsObjectType::Monster));
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill1", "PinkBeanSkill1",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill2", "PinkBeanSkill2",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill3", "PinkBeanSkill3",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill4", "PinkBeanSkill4",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill5", "PinkBeanSkill5",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill6", "PinkBeanSkill6",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill7", "PinkBeanSkill7",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill8", "PinkBeanSkill8",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill9", "PinkBeanSkill9",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill10", "PinkBeanSkill10",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill11", "PinkBeanSkill11",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanSkill12", "PinkBeanSkill12",0.15f);
		PinkBeanDummyRender->CreateAnimation("PinkBeanStand0", "PinkBeanStand0",0.15f);
		PinkBeanDummyRender->AutoSpriteSizeOn();
		PinkBeanDummyRender->ChangeAnimation("PinkBeanStand0");
	}
}
void PinkBeanDummy::ChangeState(int _StateNum)
{
	std::string CurState = "PinkBeanSkill";
	CurState += std::to_string(_StateNum);
	PinkBeanState = CurState;

	if (CurState == "PinkBeanSkill1")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -16.0f,-5.0f });
		ResourceDif = { -16.0f,-5.0f };
	}

	if (CurState == "PinkBeanSkill2")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -48.0f,0.0f });
		ResourceDif = { -48.0f,0.0f };
	}

	if (CurState == "PinkBeanSkill3")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -30.0f, -8.0f });
		ResourceDif = { -30.0f, -8.0f };
	}

	if (CurState == "PinkBeanSkill4")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -3.0f, 2.0f });
		ResourceDif = { -3.0f, 2.0f };
	}

	if (CurState == "PinkBeanSkill5")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -1.0f, 26.0f });
		ResourceDif = { -1.0f, 26.0f };
	}

	if (CurState == "PinkBeanSkill6")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -5.0f, 7.0f });
		ResourceDif = { -5.0f, 7.0f };
	}

	if (CurState == "PinkBeanSkill7")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -34.0f, 21.0f });
		ResourceDif = { -34.0f, 21.0f };
	}

	if (CurState == "PinkBeanSkill8")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -20.0f, -5.0f });
		ResourceDif = { -20.0f, -5.0f };
	}

	if (CurState == "PinkBeanSkill9")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -20.0f, -5.0f });
		ResourceDif = { -20.0f, -5.0f };
	}

	if (CurState == "PinkBeanSkill10")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -35.0f, 21.0f });
		ResourceDif = { -35.0f, 21.0f };
	}

	if (CurState == "PinkBeanSkill11")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -30.0f, -8.0f });
		ResourceDif = { -30.0f, -8.0f };
	}
	if (CurState == "PinkBeanSkill12")
	{
		PinkBeanDummyRender->Transform.AddLocalPosition({ -5.0f, 7.0f });
		ResourceDif = { -5.0f, 7.0f };
	}

	PinkBeanDummyRender->ChangeAnimation(CurState);
}