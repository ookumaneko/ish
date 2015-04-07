#ifndef _DX_WAVE_
#define _DX_WAVE_

#include "DxSound.h"

class DxWave
{
	// constructors
	public:
		DxWave(void);
		DxWave(const DxWave& rhs);
		~DxWave(void);

	// operators
	public:
		DxWave& operator =(const DxWave& rhs);

	// Accessor
	public:
		const LPDIRECTSOUNDBUFFER GetBuffer(void) const { return _buffer; }

	// wave file controls
	public:
		bool Load		(LPCTSTR fileName);
		void Release	(void);
		void Play		(void);
		void Stop		(void);
		void SetVolume	(LONG volume);
		void SetPan		(LONG pan);

	// private members
	private:
		LPDIRECTSOUNDBUFFER _buffer;
};

#endif