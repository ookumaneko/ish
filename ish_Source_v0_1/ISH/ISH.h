#ifndef _ISH_H_
#define _ISH_H_

#include "enums.h"
#include <string>

// add .lib file
#if defined(DEBUG) | defined(_DEBUG)
	#pragma comment(lib, "ish_d.lib")
#else
	#pragma comment(lib, "ish.lib")
#endif

namespace ish
{

/**
* @brief
* The main class to use features in ish.
* The user will interact through this class
*/
class DECLSPEC ISH
{
	public:
		
		/**-------------------------------------------------------------------------------
		*
		* @brief Initialization of the system. 
		*		 This method MUST be called at the start of the application before other input methods are called.
		*
		* @param  fileName			The full path to the key config (.ini) file you want to load. 
		*							it searches in current directory by default if no parameter is given
		*
		* @param  numberOfPlayers	Number of Players (controllers) to be used in the application
		*
		* @return returns true if sucesfully initialized, otherwise returns false (e.g. when failed to load key config file).
		*
		**-------------------------------------------------------------------------------*/
		static bool Initialize(const char* fileName = "keyConfig.ini", PlayerIndexs numberOfPlayers = PlayerMax);

		/**-------------------------------------------------------------------------------
		* @brief Loads new setting for key mapping and deletes the current settings.
		*		 This methods gets called during Initialize() method 
		*		 so only call this method when you want to reload new file and settings
		*
		* @param	fileName The full path to the key config (.ini) file you want to load. 
		*					 it searches in current directory by default if no parameter is given
		*
		* @param	playerToApplySetting	player (and controller) to load and apply new setting to
		*
		* @return	returns true if sucesfully loaded, otherwise returns false (e.g. when failed to load key config file).
		*
		**-------------------------------------------------------------------------------*/
		static bool LoadKeyData(const char* fileName, PlayerIndexs playerToApplySetting = PlayerOne);
		
		/**
		*  @brief Updates the input system, call this once per frame
		*/
		static void Update(void);

		/**
		*  @brief Call this method at the end of application to shutdown the input system.
				  This method MUST be called to close down ish safly and to avoid chance of memory leaks
		*/
		static void Shutdown(void);



		/**-------------------------------------------------------------------------------
		*
		* @brief Check for input (and value) in given key map setting
		*
		* @param	name		name of the key map/group setting to get e.g. "Fire"
		* @param	playerIndex	player and xbox controller to check input for
		*
		* @return	returns		0.0f for no input, 1.0f or -1.0f for valid input and 
		*						appropiate value for axis input (e.g. triggers or thumbstick on 360 controller)
		*
		**-------------------------------------------------------------------------------*/
		static float GetInputValue(const char* name, PlayerIndexs playerIndex = PlayerOne);


		/**-------------------------------------------------------------------------------
		*
		* @brief Sets an input option, suggested to use for run-time configuration / key mapping
		*
		* @param 	fileName	full path to the file you want to save to or create
		* @param	name		name of the input group (or key) to be used in GetInputValue() function
		* @param	option		option to choose how you want it to take input e.g. check when its pressed
		* @param	index		index of the player you want to apply new setting to
		* @param	isPositive  true if you want new setting to return positive value, otherwise false
		* @param	saveOption  set how you want to save new setting. Refere to enum.h for options
		*
		* @return	returns		string of the input value if any, or returns "" if there was no valid input
		*
		**-------------------------------------------------------------------------------*/
		static std::string SetInput(const char* fileName, const char* name, InputOption option, 
									PlayerIndexs index, bool isPositive, SaveOption saveOption);
};

} // end of namespace ish

#endif // end of _ISH_H_