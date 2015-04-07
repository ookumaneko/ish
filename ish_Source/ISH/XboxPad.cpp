#include "XboxPad.h"
using namespace ish;

XboxPad::XboxPad()
{
	_index = 0;
	ZeroMemory( &_state, sizeof( XINPUT_STATE ) );
	ZeroMemory( &_prevState, sizeof( XINPUT_STATE ) );
}

XboxPad::XboxPad(PlayerIndex playerIndex)
{
	Initialize( playerIndex );
}

XboxPad::~XboxPad(void)
{
}

XboxPad& XboxPad::operator =(const XboxPad& rhs)
{
	_state = rhs._state;
	_prevState = rhs._prevState;
	_index = rhs._index;
	return *this;
}

void XboxPad::Initialize(unsigned int playerIndex)
{
	_index = playerIndex;
	ZeroMemory( &_state, sizeof( XINPUT_STATE ) );
	ZeroMemory( &_prevState, sizeof( XINPUT_STATE ) );
	_isConnected = XInputGetState( _index, &_state );
}

void XboxPad::Update()
{
	memcpy( &_prevState, &_state, sizeof( XINPUT_STATE ) );
	ZeroMemory( &_state, sizeof( XINPUT_STATE ) );
	_isConnected = XInputGetState( _index, &_state );

	// Check to make sure we are not moving during the dead zone
	if ( (_state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		  _state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		 (_state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		  _state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ) )
		{    
			_state.Gamepad.sThumbLX = 0;
			_state.Gamepad.sThumbLY = 0;
		}

	if ( ( _state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		   _state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		 ( _state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		   _state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) )
		{
			_state.Gamepad.sThumbRX = 0;
			_state.Gamepad.sThumbRY = 0;
		}

	if ( _state.Gamepad.bRightTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD )
	{
		_state.Gamepad.bRightTrigger = 0;
	}

	if ( _state.Gamepad.bLeftTrigger < XINPUT_GAMEPAD_TRIGGER_THRESHOLD )
	{
		_state.Gamepad.bLeftTrigger = 0;
	}
}

float XboxPad::IsDown(XboxButtons button)
{
	bool flag = false;

	if ( _isConnected != 0 )
	{
		return 0.0f;
	}

	switch ( button )
	{
		case RightTrigger:
			return GetRightTrigger();
		case LeftTrigger:
			return GetLeftTrigger();
		case LeftThumbX:
			return GetLeftX();
		case LeftThumbY:
			return GetLeftY();
		case RightThumbX:
			return GetRightX();
		case RightThumbY:
			return GetRightY();
		default:
			flag = ( _state.Gamepad.wButtons & button );
			break;
	}

	if ( flag ) return 1.0f; 
	else return 0.0f;
}

float XboxPad::IsUp(ish::XboxButtons button)
{
	bool flag = false;

	if ( _isConnected != 0 )
	{
		return 0.0f;
	}

	switch ( button )
	{
		case RightTrigger:
			return (float)( GetRightTrigger() == 0.0f );
		case LeftTrigger:
			return (float)( GetLeftTrigger() == 0.0f );
		case LeftThumbX:
			return (float)( GetLeftX() == 0.0f );
		case LeftThumbY:
			return (float)( GetLeftY() == 0.0f );
		case RightThumbX:
			return (float)( GetRightX() == 0.0f );
		case RightThumbY:
			return (float)( GetRightY() == 0.0f );
		default:
			flag = ( !( _state.Gamepad.wButtons & button ) );
			break;
	}

	if ( flag ) return 1.0f; 
	else return 0.0f;
}

float XboxPad::IsPressed(ish::XboxButtons button)
{
	float val = 0.0f;
	bool flag = false;

	if ( _isConnected != 0 )
	{
		return 0.0f;
	}

	switch ( button )
	{
		case RightTrigger:
			val = GetRightTrigger( );
			if ( GetRightTrigger( _prevState ) == 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case LeftTrigger:
			val = GetLeftTrigger( _state );
			if ( GetLeftTrigger( _prevState ) == 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case LeftThumbX:
			val = GetLeftX();
			if ( GetLeftX( _prevState ) == 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case LeftThumbY:
			val = GetLeftY();
			if ( GetLeftY( _prevState ) == 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case RightThumbX:
			val = GetRightX();
			if ( GetRightX( _prevState ) == 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case RightThumbY:
			val = GetRightY();
			if ( GetRightY( _prevState ) == 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		default:
			flag = ( _state.Gamepad.wButtons & button && !( _prevState.Gamepad.wButtons & button ) );
			break;
	}

	if ( flag ) return 1.0f; 
	else return 0.0f;
}

float XboxPad::IsReleased(ish::XboxButtons button)
{
	float val = 0.0f;
	bool flag = false;

	if ( _isConnected != 0 )
	{
		return 0.0f;
	}

	switch ( button )
	{
		case RightTrigger:
			val = GetRightTrigger( );
			if ( GetRightTrigger( _prevState ) != 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case LeftTrigger:
			val = GetLeftTrigger( _state );
			if ( GetLeftTrigger( _prevState ) != 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case LeftThumbX:
			val = GetLeftX();
			if ( GetLeftX( _prevState ) != 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case LeftThumbY:
			val = GetLeftY();
			if ( GetLeftY( _prevState ) != 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case RightThumbX:
			val = GetRightX();
			if ( GetRightX( _prevState ) != 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		case RightThumbY:
			val = GetRightY();
			if ( GetRightY( _prevState ) != 0.0f && val != 0.0f ) return val;
			else return 0.0f;

		default:
			flag = ( !( _state.Gamepad.wButtons & button ) && ( _prevState.Gamepad.wButtons & button ) );
			break;
	}

	if ( flag ) return 1.0f; 
	else return 0.0f;
}

inline float XboxPad::GetLeftX()
{
	return ( (float)_state.Gamepad.sThumbLX / (float)32767.0f );
}

inline float XboxPad::GetLeftY()
{
	return -(float)( (float)_state.Gamepad.sThumbLY / 32767.0f );
}

inline float XboxPad::GetRightX()
{
	return (float)( (float)_state.Gamepad.sThumbRX / 32767.0f );
}

inline float XboxPad::GetRightY()
{
	return -(float)( (float)_state.Gamepad.sThumbRY / 32767.0f );
}

float XboxPad::GetRightTrigger()
{
	return ( (float)_state.Gamepad.bRightTrigger / 256.0f );		
}

float XboxPad::GetLeftTrigger()
{
	return ( (float)_state.Gamepad.bLeftTrigger / 256.0f );	
}

inline float XboxPad::GetLeftX(XINPUT_STATE& state)
{
	return (float)( (float)state.Gamepad.sThumbLX / 32767.0f );
}

inline float XboxPad::GetLeftY(XINPUT_STATE& state)
{
	return (float)( (float)state.Gamepad.sThumbLY / 32767.0f );
}

inline float XboxPad::GetRightX(XINPUT_STATE& state)
{
	return (float)( (float)state.Gamepad.sThumbRX / 32767.0f );
}

inline float XboxPad::GetRightY(XINPUT_STATE& state)
{
	return (float)( (float)state.Gamepad.sThumbRY / 32767.0f );
}

float XboxPad::GetRightTrigger(XINPUT_STATE& state)
{
	return ( (float)state.Gamepad.bRightTrigger / 256.0f );		
}

float XboxPad::GetLeftTrigger(XINPUT_STATE& state)
{
	return ( (float)state.Gamepad.bLeftTrigger / 256.0f );	
}