#ifndef _ENUMS_H_
#define _ENUMS_H_

#include "LibDef.h"

namespace ish
{

// index of a player and xbox controller
enum PlayerIndexs
{
	PlayerOne = 0,
	PlayerTwo,
	PlayerThree,
	PlayerFour,
	PlayerMax = 4,	// max number of players, do not use this for a parameter in a funtion
};

// different options to use to check input
enum InputOption
{
	IsDown,		// if key or button is down/used
	IsUp,		// if key or button is not used
	IsPressed,	// if key or button was pressed this frame
	IsReleased,	// if key or button was released this frame
};

// different saving option for runtime configuration
enum SaveOption
{
	NoSave = 0,	// do not save and only get input string 
	SaveOnly,	// do save to file but do not reload setting or add new input to current setting
	SaveReload,	// do save to file and reload input setting with the given file
	SaveAdd		// do save to file and add (or replace) new input option to the current settings
};

}	// end of namespace ish

#endif // end of _ENUMS_H_