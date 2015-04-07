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
	NoSave = 0,	// do nt save and only get input string 
	SaveOnly,	// do save to file but do not reload or add new input setting
	SaveReload,	// do save and reload input setting with given file
	SaveAdd		// do save and add or replace new input option from the current settings
};

}	// end of namespace ish

#endif // end of _ENUMS_H_