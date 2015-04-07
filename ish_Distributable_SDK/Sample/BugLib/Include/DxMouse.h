#ifndef _DX_MOUSE
#define _DX_MOUSE

#include <dinput.h>
#include "DxInput.h"
class DxVector2;

class DxMouse
{
	//Constructor and Destructor
	protected:
		DxMouse(void);
	public:
		~DxMouse(void);

	// buttons
	public:
		static enum Buttons
		{
			Left = 0,
			Right,
			MouseWheel,
			LeftSide,
			RightSide,
		};

	//Accessor
	public:
		static DxMouse* GetInstance(void);

	//methods
	public:
		void		Initialize		(HWND hWnd, DWORD mouseFlag);
		void		Update			(float delta);
		void		Shutdown		(void);
		bool		IsMouseDown		(int button);
		bool		IsMousePressed	(int button);
		bool		IsMouseReleased	(int button);
		float		GetMouseX		(void);
		float		GetMouseY		(void);
		float		GetMouseZ		(void);
		POINT		GetPosition		(void);
		void		GetPosition		(DxVector2& out);

	//members
	private:
		static DxMouse*			_instance;
		LPDIRECTINPUTDEVICE8	_mouse;
		DIMOUSESTATE2			_mouseState, _prevMouseState;
		bool					_isActive;
};

#endif