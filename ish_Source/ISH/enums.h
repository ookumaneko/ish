#ifndef _ENUMS_H_
#define _ENUMS_H_

#include "LibDef.h"

namespace ish
{

/** 
* @brief Index of a player and a xbox controller
*/
enum PlayerIndexs
{
	PlayerOne = 0,
	PlayerTwo,
	PlayerThree,
	PlayerFour,
	PlayerMax = 4,	/**< Maximum number of players, do not use this for a parameter in a funtion */ 
};

/** 
*	@brief different options to used to check input
*/
enum InputOption
{
	IsDown,		/**< if key or button is down/used				*/ 
	IsUp,		/**< if key or button is not used				*/ 
	IsPressed,	/**< if key or button was pressed this frame	*/ 
	IsReleased,	/**< if key or button was released this frame	*/ 
};

/** 
*	@brief Sifferent saving option for runtime configuration
*/
enum SaveOption
{
	NoSave = 0,	/**< do not save and only get input string									*/
	SaveOnly,	/**< do save to a file but do not reload or add new input setting			*/
	SaveReload,	/**< do save and reload input setting with given file						*/
	SaveAdd		/**< do save and add or replace new input option from the current settings	*/
};

}	// end of namespace ish

#endif // end of _ENUMS_H_