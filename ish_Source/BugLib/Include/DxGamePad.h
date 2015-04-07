#ifndef _DX_GAME_PAD
#define _DX_GAME_PAD

#include <dinput.h>
#include "DxUtil.h"
#include "DxInput.h"

class DxGamePad
{
	protected:
		struct EnumData  
		{  
			LPDIRECTINPUT8 pInput;
			LPDIRECTINPUTDEVICE8 *ppPadDevice; 
		};  

	// constructor
	protected:
		DxGamePad(void);
	
	// destructor
	public:
		~DxGamePad(void);

	// Asscessors
	public:
		static DxGamePad*	GetInstance();
		DIJOYSTATE2&		GetStates();
		DIJOYSTATE2&		GetPrevStates();
		bool HasPad();

	// Framework method
	public:
		void Initialize	(HWND hWnd);
		void Update		(void);
		void ShutDown	(void);

		//button state methods
		bool IsButtonDown		(int button);
		bool IsButtonPressed	(int button); 
		bool IsButtonReleased	(int button); 

	// Call back method
	protected:
		static BOOL CALLBACK EnumJoypad			(const DIDEVICEINSTANCE* pInstance, LPVOID pContext);  
		static BOOL CALLBACK EnumAxesCallback	(const DIDEVICEOBJECTINSTANCE* pInstance, LPVOID pContext);

	// member variables
	protected:
		static DxGamePad*		_instance;
		LPDIRECTINPUTDEVICE8	_pad;
		DIJOYSTATE2				_padState,  _lastPadState;
		bool					_isActive;
		bool					_hasPad;
};

#endif