#include "PreCompile.h"
#include "BasicLevel.h"

BasicLevel::BasicLevel() 
{
}

BasicLevel::~BasicLevel() 
{
}

void BasicLevel::DebugSwitch()
{
	if (GameEngineInput::IsDown('O',this))
	{
		OnDebug();
	}

	if (GameEngineInput::IsDown('P', this))
	{
		OffDebug();
	}
}