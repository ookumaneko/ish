#ifndef _XBOX_PAD_H
#define _XBOX_PAD_H

#include <windows.h>
#include <XInput.h>
#include "LibDef.h"

// link Xinput
#pragma comment(lib, "XInput.lib")

namespace ish
{

enum DECLSPEC PlayerIndex
{
	PLAYER_ONE = 0,
	PLAYER_TWO,
	PLAYER_THREE,
	PLAYER_FOUR,
	PLAYER_MAX = 4,
};

enum DECLSPEC XboxButtons
{
	DpadUp			= XINPUT_GAMEPAD_DPAD_UP,
	DpadDown		= XINPUT_GAMEPAD_DPAD_DOWN,
	DpadLeft		= XINPUT_GAMEPAD_DPAD_LEFT,
	DpadRight		= XINPUT_GAMEPAD_DPAD_RIGHT,
	Start			= XINPUT_GAMEPAD_START,
	Back			= XINPUT_GAMEPAD_BACK,
	LeftThumb		= XINPUT_GAMEPAD_LEFT_THUMB,
	RightThumb		= XINPUT_GAMEPAD_RIGHT_THUMB,
	LeftShoulder	= XINPUT_GAMEPAD_LEFT_SHOULDER,
	RightShoulder	= XINPUT_GAMEPAD_RIGHT_SHOULDER,
	A				= XINPUT_GAMEPAD_A,
	B				= XINPUT_GAMEPAD_B,
	X				= XINPUT_GAMEPAD_X,
	Y				= XINPUT_GAMEPAD_Y,
	RightTrigger	= XINPUT_GAMEPAD_Y + 1,
	LeftTrigger,
	LeftThumbX,
	LeftThumbY,
	RightThumbX,
	RightThumbY,
	XB_NONE,
};

class DECLSPEC XboxPad
{
	public:
		XboxPad();
		XboxPad(PlayerIndex playerIndex);
		~XboxPad(void);

		XboxPad& operator=(const XboxPad& rhs);

		void Initialize	(unsigned int playerIndex);
		void Update		(void);
		void Shutdown	(void) {};

		inline bool IsConnected(void) const { return ( _isConnected != 0 ); }

		const XINPUT_STATE& GetState(void) const { return _state; }
		const XINPUT_STATE& GetPreviousState(void) const { return _prevState; }

		float IsDown	(XboxButtons button);
		float IsUp		(XboxButtons button);
		float IsPressed	(XboxButtons button);
		float IsReleased(XboxButtons button);

		inline float GetLeftX(void);
		inline float GetLeftY(void);
		inline float GetRightX(void);
		inline float GetRightY(void);
	 	float GetRightTrigger(void);
		float GetLeftTrigger(void);

	private:

		inline float GetLeftX(XINPUT_STATE& state);
		inline float GetLeftY(XINPUT_STATE& state);
		inline float GetRightX(XINPUT_STATE& state);
		inline float GetRightY(XINPUT_STATE& state);
		float GetRightTrigger(XINPUT_STATE& state);
		float GetLeftTrigger(XINPUT_STATE& state);

		XINPUT_STATE	_state, _prevState;
		unsigned int	_index;
		DWORD			_isConnected;
};

}

#endif