#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include "XboxPad.h"
#include "WinKeyboard.h"
#include "HashTable.h"
#include <string>
#include <vector>

namespace ish
{

enum SaveOption;

class DECLSPEC InputManager
{
	private:
		InputManager(void);

		// return value options
		enum VALUE_TYPE
		{
			VT_POSITIVE = 0,
			VT_NEGATIVE,
			VT_DEFAULT,
		};

		// input check options
		enum INPUT_OPTIONS
		{
			KO_DOWN = 0,
			KO_UP,
			KO_PRESSED,
			KO_RELEASED,
			KO_NONE,
		};

		// operator options
		enum INPUT_OPERATORS
		{
			OP_AND = 0,
			OP_OR,
			OP_NONE,
		};

		// type of setting to read from file
		enum SETTING_COMMAND
		{
			SC_XBOX,
			SC_KEYBOARD,
			SC_OPTION,
			SC_OPERATOR,
			SC_INDEX,
			SC_VALUE,
		};

		// type of table
		enum TABLE_TYPE
		{
			TT_SETTING,
			TT_XBOX,
			TT_KEYBOARD,
			TT_OPTION,
			TT_OPERATOR,
			TT_VALUE,
		};

		// represent a [key] in ini file
		struct InputData
		{
			std::vector<float>			Values;
			std::vector<XboxButtons>	Buttons;
			std::vector<VIRTUAL_KEYS>	Keys;
			std::vector<INPUT_OPTIONS>	Options;
			INPUT_OPERATORS				Operator;

			~InputData(void)
			{
				Buttons.clear();
				Keys.clear();
				Values.clear();
				Options.clear();
			}

			InputData& operator =(const InputData& rhs)
			{
				Buttons = rhs.Buttons;
				Keys	= rhs.Keys;
				Options	= rhs.Options;
				Operator= rhs.Operator;
				Values	= rhs.Values;
				return *this;
			}
		};

	public:
		~InputManager(void);

		// Accessors
		static InputManager* GetInstance(void);
		XboxPad&			 GetPad(unsigned int index) { return _xboxPad[index]; }
		unsigned int		 GetNumberOfPlayers(void)	{ return _numPlayers; }

		bool Initialize	(const char* fileName, unsigned int numberOfPlayers);
		void Update		(void);
		void Shutdown	(void);

		bool LoadKeyConfig(const char* fileName, unsigned int index);

		float	GetValue(const std::string& name, unsigned int playerIndex);
		std::string	SetInput(const char* fileName, const char* name, unsigned int option, 
							 unsigned int playerIndex, bool isPositive, SaveOption saveOption);

	private:

		void CheckForInput(unsigned int option, unsigned int playerIndex, std::string& message, std::string& valueName);

		void ClearTables(void);
		void SetupTables(void);
		void AddElement (char* path, std::string key, std::string element, unsigned int input, TABLE_TYPE type);

		//--Members--//
		static InputManager*	_instance;
		WinKeyboard				_winKeyboard;
		XboxPad					_xboxPad[4];
		unsigned int			_numPlayers;
		bool					_isActive;
		bool					_firstFrame;
		char					_settingFile[MAX_PATH];

		// function pointers to xbox pad and keyboard input test
		float (XboxPad::* XboxCheck[KO_NONE])(XboxButtons button);
		float (WinKeyboard::* KeyCheck[KO_NONE])(VIRTUAL_KEYS key);

		// table to read in from setting.ini file
		HashTable<SETTING_COMMAND, std::string>	_settingTable;
		HashTable<std::string, XboxButtons>		_xboxTable;
		HashTable<std::string, VIRTUAL_KEYS>	_keyboardTable;
		HashTable<std::string, INPUT_OPTIONS>	_optionTable;
		HashTable<std::string, INPUT_OPERATORS> _operatorTable;
		HashTable<std::string, float>			_valueTable;

		// input data for each players
		HashTable<std::string, InputData>		_inputData[PLAYER_MAX];

		// text output for runtime config
		HashTable<unsigned int, std::string>	_xboxText;
		HashTable<unsigned int, std::string>	_keyboardText;
		HashTable<unsigned int, std::string>	_optionText;
		HashTable<unsigned int, std::string>	_valueText;
};

} // namespace ish

#endif