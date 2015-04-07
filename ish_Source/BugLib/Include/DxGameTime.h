#ifndef _GAME_TIME
#define _GAME_TIME

#include "DxLibraryDef.h"
#include <windows.h>

class DxGameTime
{
	// constructor and destructor
	public:
		DxGameTime(void);
		~DxGameTime(void);

	// Framework methods
	public:
		static void Initialize(void);
		static void Start	(void);
		static void Pause	(void);
		static void Update	(void);

	// Accessors
	public:
		static bool  IsStopped		(void) { return _timerStopped; }
		static float GetFPS			(void) { return _fps; }
		static float GetTotalTime	(void) { return _runningTime; }
		static float GetElapsedTime	(void) { return _timerStopped ? 0.0f : _timeElapsed; }

		static void SetTickPerSec	(INT64 tick) { _ticksPerSecond = tick; }

	// member variables
	private:
		static INT64 _ticksPerSecond;
		static INT64 _currentTime;
		static INT64 _lastTime;
		static INT64 _lastFPSUpdate;
		static INT64 _FPSUpdateInterval;
		static UINT  _numFrames;
		static float _runningTime;
		static float _timeElapsed;
		static float _fps;
		static bool  _timerStopped;
};

#endif