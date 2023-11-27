#include "PreCompile.h"
#include "Player.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameEngineFSM.h"




void Player::StateInit() 
{
	FSM.CreateState(
		{
			.Name = "Move",
			.Start = [this]()
		{
			RendererStateChange("Move");
		},
			.Update = [this](float _DeltaTime)
		{

			IsGravity = true;
			GravityCheck(_DeltaTime);


			if (CurPlayerState != "Swing")
			{
				if (true == GameEngineInput::IsPress(VK_LEFT,this))
				{
					LRColCheck(_DeltaTime, float4::LEFT);
					PlayerBody->RightFlip();
					CurDirection = PlayerDirection::Left;
				}

				if (true == GameEngineInput::IsPress(VK_RIGHT,this))
				{

					LRColCheck(_DeltaTime, float4::RIGHT);
					PlayerBody->LeftFlip();
					CurDirection = PlayerDirection::Right;
				}

				if (true == GameEngineInput::IsPress('X',this))
				{
					IsGravity = true;
					FSM.ChangeState("Jump");
				}

				if (true == GameEngineInput::IsDown(VK_UP,this))
				{
					RopeCheck();
				}


				if (false == GameEngineInput::IsPress(VK_LEFT,this) &&
					false == GameEngineInput::IsPress(VK_RIGHT,this) &&
					false == GameEngineInput::IsPress(VK_UP, this) &&
					false == GameEngineInput::IsPress(VK_DOWN, this) &&
					false == GameEngineInput::IsPress('Z',this) &&
					false == GameEngineInput::IsPress('X',this))
				{
					FSM.ChangeState("Idle");
				}
			}


			if (true == GameEngineInput::IsDown('Z', this))
			{
				RendererStateChange("Swing");
				//Attack();
			}

			if (CurPlayerState == "Swing")
			{
				if (PlayerBody->IsCurAnimationEnd())
				{
					RendererStateChange("Idle");
				}
			}

			float4 Pos = Transform.GetLocalPosition();

			Pos.Z -= 100;


			//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Pos);

		

		},
			.End = [this]()
		{
		},

		}
	);


	FSM.CreateState(
		{
			.Name = "Idle",
			.Start = [this]()
			{
				RendererStateChange("Idle");
			},
			.Update = [this](float _DeltaTime)
			{				
				
				IsGravity = true;
				GravityCheck(_DeltaTime);

				if (true == GameEngineInput::IsPress(VK_LEFT,this))
				{
					PlayerBody->RightFlip();
					CurDirection = PlayerDirection::Left;
					FSM.ChangeState("Move");
					
				}
				if (true == GameEngineInput::IsPress(VK_RIGHT,this))
				{
					PlayerBody->LeftFlip();
					CurDirection = PlayerDirection::Right;
					FSM.ChangeState("Move");
					
				}
				if (true == GameEngineInput::IsDown(VK_UP,this))
				{					
					RopeCheck();
				}

				if (true == GameEngineInput::IsPress(VK_DOWN,this))
				{
					return;
				}

				if (true == GameEngineInput::IsDown('Z',this))
				{
					RendererStateChange("Swing");
					//Attack();
				}
				if (true == GameEngineInput::IsPress('X',this))
				{
					IsGravity = true;
					FSM.ChangeState("Jump");
				}

				if (CurPlayerState == "Swing")
				{
					if (PlayerBody->IsCurAnimationEnd())
					{
						RendererStateChange("Idle");
						FSM.ChangeState("Idle");
					}
				}

				float4 Pos = Transform.GetLocalPosition();

				Pos.Z -= 100;
				//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Pos);
			}
		}

	);

	FSM.CreateState(
		{
			.Name = "Swing",
			.Start = [this]()
			{
				RendererStateChange("Swing");
			},
			.Update = [this](float _DeltaTime)
			{
				IsGravity = true;

				GravityCheck(_DeltaTime);

				if (PlayerBody->IsCurAnimationEnd())
				{
					RendererStateChange("Idle");
					FSM.ChangeState("Idle");
				}

				float4 Pos = Transform.GetLocalPosition();

				Pos.Z -= 100;
				//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Pos);
			}
		}

	);

	FSM.CreateState(
		{
			.Name = "Jump",
			.Start = [this]()
			{
				RendererStateChange("Jump");
			},
			.Update = [this](float _DeltaTime)
			{
				if (IsGravity == true)
				{
					Gravity += 10 * _DeltaTime;
					if (Gravity > 9.0f)
					{
						Gravity = 9.0f;
					}

					float4 PlayerGravityValue = JumpPower + (float4::DOWN * Gravity);
					float4 CurPosition = Transform.GetWorldPosition();
					Transform.AddWorldPosition(PlayerGravityValue);
					
					
					float4 NextPosition = CurPosition + PlayerGravityValue;

					if (true == GameEngineInput::IsPress(VK_LEFT,this))
					{

						PlayerBody->RightFlip();
						Transform.AddWorldPosition(float4::LEFT * Speed * _DeltaTime);						
						
						NextPosition += float4::LEFT * Speed * _DeltaTime;												
					}

					if (true == GameEngineInput::IsPress(VK_RIGHT,this))
					{
						PlayerBody->LeftFlip();
						Transform.AddWorldPosition(float4::RIGHT * Speed * _DeltaTime);					
						
						NextPosition += float4::RIGHT * Speed * _DeltaTime;
					}
					if (true == GameEngineInput::IsDown('Z',this))
					{
						RendererStateChange("Swing");
					}

					if (true == GameEngineInput::IsDown(VK_UP, this))
					{
						RopeCheck();
					}

					if (PlayerGravityValue.Y <= 0)
					{
						
						if (ColMap->GetColor({ NextPosition.X, PlayerSize.hY() - NextPosition.Y }, {0,0,0}) == ColColor)
						{

							
							GameEngineColor PixelColor = ColMap->GetColor({ NextPosition.X, PlayerSize.hY() - NextPosition.Y }, ColColor);
							while (ColMap->GetColor({ NextPosition.X, PlayerSize.hY() - NextPosition.Y }, ColColor) != ColColor)
							{
								NextPosition.Y -= 1.0f;
							}

							Transform.SetWorldPosition(NextPosition);
							IsGravity = false;
							Gravity = 0.0f;
							JumpPower = { 0,4.5f ,0 };
							if (CurPlayerState != "Swing")
							{
								FSM.ChangeState("Move");
								return;
							}


						}

					}

					if (true == GameEngineInput::IsDown(VK_UP,this))
					{
						//RopeCheck();
					}
				}

				float4 Pos = Transform.GetLocalPosition();

				Pos.Z -= 100;
				//GetLevel()->GetMainCamera()->Transform.SetLocalPosition(Pos);

				

				if (CurPlayerState == "Swing")
				{

					if (true == PlayerBody->IsCurAnimationEnd())
					{
						FSM.ChangeState("Idle");
					}
				}
			}
		}

	);
	 
	FSM.CreateState(
		{
			.Name = "Rope",
			.Start = [this]()
		{
			RendererStateChange("Rope");
		},
			.Update = [this](float _DeltaTime)
		{
			IsGravity = false;

			if (true == GameEngineInput::IsPress(VK_UP,this))
			{
				RendererStateChange("RopeMove");
				Transform.AddWorldPosition(float4::UP* Speed* _DeltaTime);
			}
			if (true == GameEngineInput::IsPress(VK_DOWN,this))
			{
				RendererStateChange("RopeMove");
				Transform.AddWorldPosition(float4::DOWN* Speed * _DeltaTime);
			}

			if (true == GameEngineInput::IsUp(VK_UP, this))
			{
				RendererStateChange("Rope");
			}
			if (true == GameEngineInput::IsUp(VK_DOWN, this))
			{
				RendererStateChange("Rope");
			}

			if (true == GameEngineInput::IsDown('X',this))
			{
				
				
				IsGravity = true;
				FSM.ChangeState("Jump");
			}

		}
		}
	);
	
	FSM.CreateState(
		{
			.Name = "Ladder",
			.Start = [this]()
		{
			RendererStateChange("Ladder");
		},
			.Update = [this](float _DeltaTime)
		{
			IsGravity = false;

			if (true == GameEngineInput::IsPress(VK_UP,this))
			{
				RendererStateChange("LadderMove");
				Transform.AddWorldPosition(float4::UP * Speed * _DeltaTime);
			}
			if (true == GameEngineInput::IsPress(VK_DOWN,this))
			{
				RendererStateChange("LadderMove");
				Transform.AddWorldPosition(float4::DOWN * Speed * _DeltaTime);
			}

			if (true == GameEngineInput::IsUp(VK_UP, this))
			{
				RendererStateChange("Ladder");
			}
			if (true == GameEngineInput::IsUp(VK_DOWN, this))
			{
				RendererStateChange("Ladder");
			}

			if (true == GameEngineInput::IsDown('X',this))
			{
				if (true == GameEngineInput::IsPress(VK_RIGHT, this))

				IsGravity = true;
				FSM.ChangeState("Jump");
			}

		}
		}
	);
	FSM.ChangeState("Idle");
}





