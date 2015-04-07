#ifndef _DX_AUDIO_
#define _DX_AUDIO_

#include "DxLibraryDef.h"

#include <strmif.h>  
#include <control.h>  
#include <uuids.h>  
#pragma comment (lib,"strmiids.lib") // replacement for direct show

class DxAudio
{
	private:
		DxAudio(void);
		DxAudio(LPCTSTR fileName);

	public:
		~DxAudio(void);

	public:
		static void Initialize	(void);
		static void Release		(void);

	public:
		static void Update		(float delta);
		static void Load		(LPCTSTR fileName);
		static void Play		(bool loop);
		static void Stop		(void);

	private:
		static IGraphBuilder*	_builder;
		static IMediaControl*	_mediaCtrl;
		static IMediaSeeking*	_mediaSeeking;
		static IBasicAudio*		_audio;

		static bool				_loop;
		static bool				_fadeing;
		static float			_timeS;
		static float			_timeE;
		static float			_volS;
		static float			_delta;
};

#endif