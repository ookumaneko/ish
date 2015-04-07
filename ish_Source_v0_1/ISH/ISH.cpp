#include "ISH.h"
#include "InputManager.h"
using namespace ish;

InputManager* _input;

bool ISH::Initialize(const char *fileName, PlayerIndexs numberOfPlayers)
{
	_input = InputManager::GetInstance();
	if ( numberOfPlayers != PlayerMax )
	{
		_input->Initialize( fileName, numberOfPlayers + 1);
	}
	else
	{
		_input->Initialize( fileName, numberOfPlayers );
	}
	return true;
}

bool ISH::LoadKeyData(const char *fileName, PlayerIndexs playerToApplySetting)
{
	if ( playerToApplySetting == PlayerMax )
	{
		return false;
	}

	_input->LoadKeyConfig( fileName, playerToApplySetting );
	return true;
}

void ISH::Shutdown()
{
	_input->Shutdown();
	delete _input;
	_input = 0;
}

void ISH::Update()
{
	_input->Update();
}

float ISH::GetInputValue(const char *name, PlayerIndexs playerIndex)
{
	if ( playerIndex == PlayerMax )
	{
		return false;
	}
	return _input->GetValue( name, playerIndex );
}

std::string ISH::SetInput(const char *fileName, const char *name, InputOption option, PlayerIndexs index, bool isPositive, SaveOption saveOption)
{
	if ( index == PlayerMax )
	{
		return false;
	}
	return _input->SetInput( fileName, name, option, index, isPositive, saveOption );
}