#include "WinKeyboard.h"
#include <windows.h>
#include <assert.h>
using namespace ish;

//WinKeyboard* WinKeyboard::_instance = 0;

WinKeyboard::WinKeyboard(void) //: IDevice()
{
	ZeroMemory( &_state, sizeof( unsigned char ) * KEY_SIZE );
	ZeroMemory( &_prevState, sizeof( unsigned char ) * KEY_SIZE );

	GetKeyboardState( _prevState );
	GetKeyboardState( _state );
}

WinKeyboard::~WinKeyboard(void)
{
}

//WinKeyboard* WinKeyboard::GetInstance()
//{
//	if ( _instance == 0 )
//	{
//		_instance = new WinKeyboard();
//	}
//
//	return _instance;
//}

void WinKeyboard::Initialize()
{
	ZeroMemory( &_state, sizeof( unsigned char ) * KEY_SIZE );
	ZeroMemory( &_prevState, sizeof( unsigned char ) * KEY_SIZE );
	assert( GetKeyboardState( _prevState ) );
	assert( GetKeyboardState( _state ) );
}

void WinKeyboard::Shutdown()
{
	ZeroMemory( &_state, sizeof( unsigned char ) * KEY_SIZE );
	ZeroMemory( &_prevState, sizeof( unsigned char ) * KEY_SIZE );
}

void WinKeyboard::Update()
{
	// copy state from previous frame to previous state
	memcpy( _prevState, _state, sizeof( unsigned char ) * KEY_SIZE );
	ZeroMemory( &_state, sizeof( unsigned char ) * KEY_SIZE );

	// get keyboard states
	GetKeyboardState( _state ); //assert(  );
}

float WinKeyboard::IsDown(VIRTUAL_KEYS key)
{
	if ( key == VIRTUAL_KEYS::V_NONE )
	{
		return 0.0f; //false;
	}

	if ( _state[key] & 0x80 )
	{
		return 1.0f;
	}
	else
	{
		return 0.0f;
	}
}

float WinKeyboard::IsUp(VIRTUAL_KEYS key)
{
	if ( key == VIRTUAL_KEYS::V_NONE )
	{
		return 0.0f; //false;
	}

	if ( !( _state[key] & 0x80 ) )
	{
		return 1.0f;
	}
	else
	{
		return 0.0f;
	}
}

float WinKeyboard::IsPressed(VIRTUAL_KEYS key)
{
	if ( key == VIRTUAL_KEYS::V_NONE )
	{
		return 0.0f; //false;
	}

	if ( ( _state[key] & 0x80) && !( _prevState[key] & 0x80) )
	{
		return 1.0f;
	}
	else
	{
		return 0.0f;
	}
}

float WinKeyboard::IsReleased(VIRTUAL_KEYS key)
{
	if ( key == VIRTUAL_KEYS::V_NONE )
	{
		return 0.0f; //false;
	}

	if ( !( _state[key] & 0x80 ) && ( _prevState[key] & 0x80 ) )
	{
		return 1.0f;
	}
	else
	{
		return 0.0f;
	}
}