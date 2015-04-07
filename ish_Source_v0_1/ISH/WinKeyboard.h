#ifndef _WIN_KEYBOARD_H
#define _WIN_KEYBOARD_H

#include "LibDef.h"
#include "IDevice.h"

namespace ish
{

enum DECLSPEC VIRTUAL_KEYS
{
	V_NONE = 0,
	V_A = 65,	//A key
	V_B = 66,	//B key
	V_C = 67,	//C key
	V_D = 68,	//D key
	V_E = 69,	//E key
	V_F = 70,	//F key
	V_G = 71,	//G key
	V_H = 72,	//H key
	V_I = 73,	//I key
	V_J = 74,	//J key
	V_K = 75,	//K key
	V_L = 76,	//L key
	V_M = 77,	//M key
	V_N = 78,	//N key
	V_O = 79,	//O key
	V_P = 80,	//P key
	V_Q = 81,	//Q key
	V_R = 82,	//R key
	V_S = 83,	//S key
	V_T = 84,	//T key
	V_U = 85,	//U key
	V_V = 86,	//V key
	V_W = 87,	//W key
	V_X = 88,	//X key
	V_Y = 89,	//Y key
	V_Z = 90,	//Z key 

	V_0 = 0x30,
	V_1,
	V_2,
	V_3,
	V_4,
	V_5,
	V_6,
	V_7,
	V_8,
	V_9,

	V_ESCAPE = 0x1B,
	V_CLEAR = 0x0C,
	V_ENTER = 0x0D,

	V_SHIFT = 0x10,
	V_CONTROL = 0x11,
	V_MENU = 0x12,
	V_PAUSE = 0x13,
	V_CAPITAL = 0x14,

	V_SPACE = 0x20,
	V_PRIOR = 0x21,
	V_NEXT = 0x22,
	V_END = 0x23,
	V_HOME = 0x24,

	V_LEFT = 0x25,
	V_UP = 0x26,
	V_RIGHT = 0x27,
	V_DOWN = 0x28,

	V_SELECT = 0x29,
	V_PRINT = 0x2A,
	V_EXECUTE = 0x2B,
	V_SNAPSHOT = 0x2C,
	V_INSERT = 0x2D,
	V_DELETE = 0x2E,
	V_HELP = 0x2F,

	V_NUMPAD0 = 0x60,
	V_NUMPAD1 = 0x61,
	V_NUMPAD2 = 0x62,
	V_NUMPAD3 = 0x63,
	V_NUMPAD4 = 0x64,
	V_NUMPAD5 = 0x65,
	V_NUMPAD6 = 0x66,
	V_NUMPAD7 = 0x67,
	V_NUMPAD8 = 0x68,
	V_NUMPAD9 = 0x69,

	V_MULTIPLY =0x6A,
	V_ADD = 0x6B,
	V_SEPARATOR = 0x6C,
	V_SUBTRACT =0x6D,
	V_DECIMAL = 0x6E,
	V_DIVIDE =  0x6F,

	V_F1 = 0x70,
	V_F2 = 0x71,
	V_F3 = 0x72,
	V_F4 = 0x73,
	V_F5 = 0x74,
	V_F6 = 0x75,
	V_F7 = 0x76,
	V_F8 = 0x77,
	V_F9 = 0x78,
	V_F10 = 0x79,
	V_F11 = 0x7A,
	V_F12 = 0x7B,
	V_F13 = 0x7C,
	V_F14 = 0x7D,
	V_F15 = 0x7E,
	V_F16 = 0x7F,
	V_F17 = 0x80,
	V_F18 = 0x81,
	V_F19 = 0x82,
	V_F20 = 0x83,
	V_F21 = 0x84,
	V_F22 = 0x85,
	V_F23 = 0x86,
	V_F24 = 0x87,
};	// end of virtual keys enum

class DECLSPEC WinKeyboard : public IDevice<WinKeyboard, VIRTUAL_KEYS>
{
	protected:
		//WinKeyboard(void);

	public:
		WinKeyboard(void);
		~WinKeyboard(void);
		
		enum { KEY_SIZE = 256, };

		void Initialize	(void);
		void Update		(void);
		void Shutdown	(void);

		float IsDown	(VIRTUAL_KEYS key);
		float IsUp		(VIRTUAL_KEYS key);
		float IsPressed	(VIRTUAL_KEYS key);
		float IsReleased(VIRTUAL_KEYS key);

		const unsigned char* GetState(void) const { return _state; }
		const unsigned char* GetPreviousState(void) const { return _prevState; }

	private:
		unsigned char _state[KEY_SIZE], _prevState[KEY_SIZE];
};

} // end of namespace ish

#endif	// end of _WIN_KEYBOARD_H