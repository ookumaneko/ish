#ifndef _DX_360_PAD
#define _DX_360_PAD

#include "DxLibraryDef.h"

class DxGamePad;
class DxVector2;

class Dx360Pad
{
	//buttons
	public:
		static enum Buttons
		{
			A = 0,
			B = 1,
			X = 2,
			Y = 3,
			Start = 7,
			Back = 6,
			LeftBumper = 4,
			RightBumper = 5,
			DPadUp = 20,
			DPadDown = 21,
			DPadLeft = 22,
			DPadRight = 23,
			LeftThumb = 8,
			RightThumb = 9
		};

		static enum DpadDir
		{
			Up = 1,
			UpRight,
			Right,
			RightDown,
			Down,
			LeftDown,
			Left,
			UpLeft,
		};


	//constructor and destructor
	protected:
		Dx360Pad(void);

	public:
		~Dx360Pad(void);

	// Accessors
	public:
		static Dx360Pad* GetInstance(void);
		
	// State Accessors
	public:
		bool IsButtonDown		(int button);
		bool IsButtonPressed	(int button); 
		bool IsButtonReleased	(int button); 

		DxVector2 GetLeftThumbStick	(void);
		DxVector2 GetRightThumbStick(void);
		float	GetLeftTrigger		(void);
		float	GetRightTrigger		(void);

	protected:
		int GetDpadDIr(int button, int dir);

	// member variables
	protected:
		static Dx360Pad* _instance;
		DxGamePad* _pads;

};

#endif