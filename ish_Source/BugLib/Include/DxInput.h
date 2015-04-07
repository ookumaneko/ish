#ifndef _DXINPUT
#define _DXINPUT

#include "DxLibraryDef.h"
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#ifndef DIRECTINPUT_VERSION
	#define DIRECTINPUT_VERSION 0x0800
#endif

class DxKeyboard;
class DxMouse;
class DxGamePad;

class DxInput
{
	//constructor and destructor
	public:
		DxInput(void);
		~DxInput(void);

	//Framework methods
	public:
		void Initialize	(HWND hWnd, HINSTANCE hInstance, DWORD keyboardFlag, DWORD mouseFlag);
		void Update		(float delta);
		void Shutdown	(void);

	//Accessor
	public:
		static DxInput* GetInstance	(void);
		LPDIRECTINPUT8  GetInput	(void);
	
	//members
	private:

		static DxInput*			_instance;
		LPDIRECTINPUT8			_input;

		DxKeyboard*				_keyboards;
		DxMouse*				_mouse;
		DxGamePad*				_gamePads;
		bool					_isActive;
};

#endif 