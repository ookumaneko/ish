#ifndef _DX_SOUND_
#define _DX_SOUND_

#include "DxLibraryDef.h"

#include <dsound.h>  
#pragma comment(lib, "dsound.lib")  
#pragma comment(lib, "dxguid.lib")

class DxSound
{
	public:
		DxSound(void);
		~DxSound(void);

	public:
		static DxSound*			GetInstance	(void);
		static LPDIRECTSOUND8	GetSound	(void)	{ return _sound; }

	public:
		void Initialize	(HWND hWnd);
		void Shutdown	(void);

	private:
		static DxSound*			_instance;
		static LPDIRECTSOUND8	_sound;

};

#endif