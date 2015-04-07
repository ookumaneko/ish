#ifndef _DX_KEYBOARD
#define _DX_KEYBOARD

//#include <dinput.h>
#include "DxUtil.h"
#include "DxInput.h"
#include "DxKeys.h"

class DxKeyboard
{
	//constructors and destructor
	protected:
		DxKeyboard(void);

	public:
		~DxKeyboard(void);

	//Accessors
	public:
		static DxKeyboard* GetInstance(void);

	//key states
	public:
		void Initialize		(HWND hWnd, DWORD keyboardFlag);
		void Update			(float delta);
		void Shutdown		(void);
		bool IsDown			(DxKeys::Keys key);
		bool IsPressed		(DxKeys::Keys key);
		bool IsReleased		(DxKeys::Keys key);

	//static methods
	//public:
	//	static void Initialize			(HWND hWnd, DWORD keyboardFlag);
	//	static void Update				(float delta);
	//	static void Shutdown			(void);
	//	static bool IsDown			(int key);
	//	static bool IsKeyPressed		(int key);
	//	static bool IsKeyReleased		(int key);

	//private members
	private:
		static DxKeyboard*		_instance;
		LPDIRECTINPUTDEVICE8	_keyboard;
		BYTE					_keyState[256],	_prevKeyState[256];
		bool					_isActive;
};

#endif