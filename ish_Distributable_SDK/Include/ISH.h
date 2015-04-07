#ifndef _ISH_H_
#define _ISH_H_

#include "enums.h"
#include <string>

/* 
	This file provides interface to interact with the 
	input system provided by ISH library
*/

// add .lib file
#if defined(DEBUG) | defined(_DEBUG)
	#pragma comment(lib, "ish_d.lib")
#else
	#pragma comment(lib, "ish.lib")
#endif

namespace ish
{

class DECLSPEC ISH
{
	public:

		//-----------------------------------------------------------------------------
		//
		//	Initialization for the system, this MUST be called at the start
		//	of the application before other input methods are called.
		//	
		//	fileName:		 The full path to the .ini you want to load. it searches 
		//					 in current directory by default if no parameter is given
		//
		//	numberOfPlayers: number of players in the game
		//
		//----------------------------------------------------------------------------
		static bool Initialize(const char* fileName = "keyConfig.ini", PlayerIndexs numberOfPlayers = PlayerMax);

		//-----------------------------------------------------------------------------
		//
		//	Loads new setting for key mapping and deletes the current settings.
		//	
		//	fileName:				The full path to the .ini you want to load
		//	playerToApplySetting:	player to load and apply new setting to
		//
		//	Note - This methods also gets called during Initialize() method
		//
		//-----------------------------------------------------------------------------
		static bool LoadKeyData(const char* fileName, PlayerIndexs playerToApplySetting = PlayerOne);

		// Updates the input system, call this once per frame
		static void Update(void);

		// Call this method at the end of application to shutdown the input system
		static void Shutdown(void);

		//------------------------------------------------------------------------------
		//
		//	Check for input value in given key map setting
		//
		//	name:			name of the key map/group setting to get e.g. "Fire"
		//	playerIndex:	player and xbox controller to check input for
		//
		//	return:			0.0f for no input, 1.0f or -1.0f for valid key and button input and 
		//					appropiate value for axis input (e.g. triggers on 360 controller)
		//
		//------------------------------------------------------------------------------
		static float GetInputValue(const char* name, PlayerIndexs playerIndex = PlayerOne);

		//------------------------------------------------------------------------------
		//
		//	Sets an input option, suggested to use for run-time configuration / key mapping
		//
		//	fileName:	full path to the file you want to save to or create
		//	name:		name of the input group (or key) to be used in GetInputValue() function
		//	option:		option to choose how you want it to take input e.g. check when its pressed
		//	index:		index of the player you want to apply new setting to
		//	isPositive: true if you want new setting to return positive value, otherwise false
		//	saveOption: set how you want to save new setting. Refere to enum.h for options
		//
		//	return:		string of the input value if any, or returns "" if there was no valid input
		//
		//-------------------------------------------------------------------------------
		static std::string SetInput(const char* fileName, const char* name, InputOption option, 
									PlayerIndexs index, bool isPositive, SaveOption saveOption);
};

} // end of namespace ish

#endif // end of _ISH_H_