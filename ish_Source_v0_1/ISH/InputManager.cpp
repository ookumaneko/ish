#include "InputManager.h"
#include "IniHandler.h"
#include <algorithm>
#include <cctype> 
#include <vector>
#include <fstream>
#include <sstream>
#include "enums.h"
using namespace ish;

InputManager* InputManager::_instance = 0;

InputManager::InputManager(void)
: _settingTable(), _xboxTable(), _keyboardTable(), _optionTable(), _operatorTable(), _valueTable(),
  _xboxText(), _keyboardText(), _valueText(), _optionText(), _winKeyboard()
{
	_isActive = false;
	_firstFrame = true;
	_numPlayers = 4;
	_settingFile[MAX_PATH] = 0;
	
	// initialize xbox controllers and player input data
	for ( unsigned int i = 0; i < PLAYER_MAX; ++i )
	{
		_xboxPad[i] = XboxPad( (PlayerIndex)i );
		_inputData[i] = HashTable<std::string, InputData>();
	}

	// initialize function pointers to NULL
	for ( unsigned int i = 0; i < KO_NONE; ++i )
	{
		( XboxCheck[i] ) = 0;
		( KeyCheck[i] ) = 0;
	}
}

InputManager::~InputManager(void)
{
	if ( _isActive )
	{
		Shutdown();
	}
}

InputManager* InputManager::GetInstance()
{
	if ( _instance == 0 )
	{
		_instance = new InputManager();
	}

	return _instance;
}

bool InputManager::Initialize(const char* fileName, unsigned int numberOfPlayers)
{
	char path[MAX_PATH];
	
	_isActive = true;
	_winKeyboard.Initialize();
	_numPlayers = numberOfPlayers;

	// get directory
	if ( strcmp( fileName, "keyConfig.ini" ) == 0 )
	{
		GetCurrentDirectoryA( MAX_PATH, path );
		lstrcatA( path, "\\" );
		lstrcatA( path, fileName );
	}
	else
	{
		strcpy( path, fileName );
	}

	// initialize xbox controllers
	for ( int i = 0; i < PLAYER_MAX; ++i )
	{
		_xboxPad[i].Initialize( i );
	}

	// load settings
	SetupTables();

	// load config for each players
	for ( int i = 0; i < numberOfPlayers; ++i )
	{
		if ( !LoadKeyConfig( path, i ) )
		{
			// failed to load config, shutdown
			Shutdown();
			return false;
		}
	}

	// initialize function pointers
	( XboxCheck[KO_DOWN] )		= &XboxPad::IsDown;
	( XboxCheck[KO_PRESSED] )	= &XboxPad::IsPressed;
	( XboxCheck[KO_UP] )		= &XboxPad::IsUp;
	( XboxCheck[KO_RELEASED] )	= &XboxPad::IsReleased;
	( KeyCheck[KO_DOWN] )		= &WinKeyboard::IsDown;
	( KeyCheck[KO_PRESSED] )	= &WinKeyboard::IsPressed;
	( KeyCheck[KO_UP] )			= &WinKeyboard::IsUp;
	( KeyCheck[KO_RELEASED] )	= &WinKeyboard::IsReleased;

	return true;
}

bool InputManager::LoadKeyConfig(const char* fileName, unsigned int index)
{
	std::vector<std::string> keys;
	std::string buff = "";
	std::string name = "";
	
	std::ifstream f( fileName );
	char temp[64];

	// clear all data
	if ( PLAYER_MAX > index )
	{
		_inputData[index].Clear();
	}
	else
	{
		// error, the send player does not exist in this game
		return false;
	}

	// read out every [keys] from ini file
	while ( f.getline( temp, 64 ) )
	{
		if ( temp[0] == '[' )
		{
			buff = temp;
			buff.erase( buff.begin() );
			buff.erase( buff.find("]") );
			keys.push_back( buff );
		}
	}
	f.close();

	// search through every [Groups] in a file
	int size = keys.size();
	for ( int i = 0; i < size; ++i )
	{	
		InputData data;
		int cnt = 1;
		buff = "";
		_settingTable.TryGetValue( SC_XBOX, name );
		XboxButtons button = XB_NONE;

		// loop to get each xbox buttons
		while ( buff != "ERROR" )
		{
			std::stringstream ss;
			ss << cnt;
			std::string t = name + ss.str();
			IniHandler::ReadString( fileName, keys[i].c_str(), t.c_str(), "Error", buff );
			std::transform( buff.begin(), buff.end(), buff.begin(), toupper );
			
			if ( _xboxTable.TryGetValue( buff, button ) )
			{
				cnt++;
				data.Buttons.push_back( button );
			}
		}

		// read keyboard input data
		buff = "";
		_settingTable.TryGetValue( SC_KEYBOARD, name );
		cnt = 1;
		VIRTUAL_KEYS vk = V_NONE;
		while ( buff != "ERROR" )
		{
			std::stringstream ss;
			ss << cnt;
			std::string t = name + ss.str();
			IniHandler::ReadString( fileName, keys[i].c_str(), t.c_str(), "Error", buff );
			std::transform( buff.begin(), buff.end(), buff.begin(), toupper );
			
			if ( _keyboardTable.TryGetValue( buff, vk ) )
			{
				cnt++;
				data.Keys.push_back( vk );
			}
		}

		// read option
		buff = "";
		_settingTable.TryGetValue( SC_OPTION, name );
		cnt = 1;
		INPUT_OPTIONS ip = KO_NONE;
		while ( buff != "ERROR" )
		{
			std::stringstream ss;
			ss << cnt;
			std::string t = name + ss.str();
			IniHandler::ReadString( fileName, keys[i].c_str(), t.c_str(), "Error", buff );
			std::transform( buff.begin(), buff.end(), buff.begin(), toupper );
			
			if ( _optionTable.TryGetValue( buff, ip ) )
			{
				cnt++;
				data.Options.push_back( ip );
			}
		}

		// read value
		buff = "";
		_settingTable.TryGetValue( SC_VALUE, name );
		cnt = 1;
		float value = 1.0f;
		while ( buff != "ERROR" )
		{
			std::stringstream ss;
			ss << cnt;
			std::string t = name + ss.str();
			IniHandler::ReadString( fileName, keys[i].c_str(), t.c_str(), "Error", buff );
			std::transform( buff.begin(), buff.end(), buff.begin(), toupper );
			
			if ( _valueTable.TryGetValue( buff, value ) )
			{
				cnt++;
				data.Values.push_back( value );
			}
		}

		// read operator
		_settingTable.TryGetValue( SC_OPERATOR, name );
		IniHandler::ReadString( fileName, keys[i].c_str(), name.c_str(), "Error", buff );
		std::transform( buff.begin(), buff.end(), buff.begin(), toupper );
		if ( buff != "ERROR" )
		{
			_operatorTable.TryGetValue( buff, data.Operator );
		}
		else
		{
			data.Operator = OP_NONE;
		}

		// add input data
		_inputData[index].Add( keys[i], data );
	}
	return true;
}

float InputManager::GetValue(const std::string& name, unsigned int playerIndex)
{
	InputData data;

	// find the given input data
	if ( _inputData[playerIndex].TryGetValue( name, data ) )
	{
		int size = data.Keys.size(); 
		int count = 0;
		int total = size;
		int funcIndex = 0;
		float value = 0.0f;

		// go through keyboard input set to check states
		for ( int i = 0; i < size; ++i )
		{
			// check input
			value = ( _winKeyboard.*KeyCheck[ data.Options[funcIndex] ] )( data.Keys[i] );
			funcIndex++;

			// check conditions
			if ( value && ( data.Operator == OP_OR || data.Operator == OP_NONE ) )
			{
				return value * data.Values[funcIndex-1];
			}
			else if ( !value && data.Operator == OP_AND )
			{
				return 0.0f;
			}
			else if ( value && data.Operator == OP_AND )
			{
				count++;
			}
		}

		// go through the buttons set to check input
		size = data.Buttons.size();
		total += size;
		for ( int i = 0; i < size; ++i )
		{
			// check input
			value = ( _xboxPad[playerIndex].*XboxCheck[ data.Options[funcIndex] ] )( data.Buttons[i] );
			funcIndex++;

			// check conditions
			if ( value && ( data.Operator == OP_OR || data.Operator == OP_NONE ) )
			{
				return value * data.Values[funcIndex-1];
			}
			else if ( !value && data.Operator == OP_AND )
			{
				return 0.0f;
			}
			else if ( value && data.Operator == OP_AND )
			{
				count++;
			}
		}

		// if AND operator was used and was sccesful
		if ( count == total )
		{
			return 1.0f * data.Values[0];
		}
	}

	return 0.0f;
}


std::string InputManager::SetInput(const char *fileName, const char *name, unsigned int option, 
								   unsigned int playerIndex, bool isPositive, SaveOption saveOption)
{
	// if this method was called for the first time, do nothing so
	// that input can get reset. Otherwise, it well always return
	// the button that was used to call this method
	if ( _firstFrame )
	{
		_firstFrame = false;
		return "";
	}
	
	std::string mes, valueName, returnMessage;

	// check if there was a valid input this frame
	CheckForInput( option, playerIndex, mes, valueName );
	
	if ( mes != "" )
	{
		// set text message to send back
		returnMessage = mes;

		// reset
		_firstFrame = true;

		if ( saveOption != NoSave )
		{
			char temp[64];
			std::string dName, dOption, dValue;

			// delete the given input name if it already exists
			IniHandler::DeleteSection( fileName, name );

			// write input value e.g. xbox1 = A
			IniHandler::WriteSection( fileName, name, valueName.c_str(), mes.c_str() );
			dName = mes;
			bool isXbox = ( valueName[0] == 'x' );

			// write input option e.g. option1 = down
			assert( _settingTable.TryGetValue( SC_OPTION, valueName ) );			
			valueName += "1";
			assert( _optionText.TryGetValue( option, mes ) );
			IniHandler::WriteSection( fileName, name, valueName.c_str(), mes.c_str() );
			dOption = mes;

			// write operator option e.g. operator = OR
			assert( _settingTable.TryGetValue( SC_OPERATOR, valueName ) );
			mes = "OR";
			IniHandler::WriteSection( fileName, name, valueName.c_str(), mes.c_str() );
			
			// write value option e.g. value1 = negative
			assert( _settingTable.TryGetValue( SC_VALUE, valueName ) );			
			valueName += "1";
			if ( isPositive )
			{
				mes = "positive";
			}
			else
			{
				mes = "negative";
			}

			// write to file
			assert( IniHandler::WriteSection( fileName, name, valueName.c_str(), mes.c_str() ) );
			dValue = mes;

			if ( saveOption == SaveReload )
			{
				// load new setting for this player
				assert( LoadKeyConfig( fileName, playerIndex ) );
			}

			// add (or replace) new input to current setting
			else if ( saveOption == SaveAdd )
			{
				std::string key = name;
				InputData data, check;

				// add new input button or key
				if ( isXbox )
				{
					data.Buttons.push_back( A );
					assert( _xboxTable.TryGetValue( dName, data.Buttons[0] ) ); 
				}
				else
				{
					data.Keys.push_back( V_A );
					assert( _keyboardTable.TryGetValue( dName, data.Keys[0] ) ); 
				}

				// add operator
				assert( _operatorTable.TryGetValue( "OR", data.Operator ) );
				
				// add option
				data.Options.push_back( KO_NONE );
				std::transform( dOption.begin(), dOption.end(), dOption.begin(), toupper ); 
				assert( _optionTable.TryGetValue( dOption, data.Options[0] ) );

				// add value option
				data.Values.push_back( VT_DEFAULT );
				std::transform( dValue.begin(), dValue.end(), dValue.begin(), toupper ); 
				assert( _valueTable.TryGetValue( dValue, data.Values[0] ) );

				// if the newly set input already exists, replace it. Otherwise add it
				if ( _inputData[playerIndex].TryGetValue( key, check ) )
				{
					check = data;
				}
				else
				{
					_inputData[playerIndex].Add( key, data );
				}
			}
		}

		// return input as a string
		return returnMessage;
	}

	// return string for no input 
	return "";
}

void InputManager::CheckForInput(unsigned int option, unsigned int playerIndex, std::string& message, std::string& valueName)
{
	const unsigned char* keyState = _winKeyboard.GetState();
	const XINPUT_STATE padState = _xboxPad[ playerIndex ].GetState();
	message = "";

	// check for xbox controller input
	if ( padState.Gamepad.wButtons != 0 )
	{
		// there was an input from 360
		if ( _xboxText.TryGetValue( padState.Gamepad.wButtons, message ) )
		{
			assert( _settingTable.TryGetValue( SC_XBOX, valueName ) );	
			valueName += "1";
			return;
		}
		else
		{
			message = "";
		}
	}
	else if ( _xboxPad[ playerIndex ].GetRightTrigger() != 0.0f )
	{
		// there was an input from right trigger
		if ( _xboxText.TryGetValue( XboxButtons::RightTrigger, message ) )
		{
			assert( _settingTable.TryGetValue( SC_XBOX, valueName ) );	
			valueName += "1";
			return;
		}
		else
		{
			message = "";
		}
	}
	
	else if ( _xboxPad[ playerIndex ].GetLeftTrigger() != 0.0f )
	{
		// there was an input from left trigger
		if ( _xboxText.TryGetValue( XboxButtons::LeftTrigger, message ) )
		{
			assert( _settingTable.TryGetValue( SC_XBOX, valueName ) );	
			valueName += "1";
			return;
		}
		else
		{
			message = "";
		}
	}

	// loop through each keys to see if any keys are pressed
	for ( unsigned int i = 0; i < WinKeyboard::KEY_SIZE; i++ )
	{
		if ( _winKeyboard.IsPressed( (VIRTUAL_KEYS)i ) )
		{
			// there was an input from keyboard
			if ( _keyboardText.TryGetValue( i, message ) )
			{
				assert( _settingTable.TryGetValue( SC_KEYBOARD, valueName ) );	
				valueName += "1";
				return;
			}
			else
			{
				message = "";
			}
		}
	}
}

void InputManager::SetupTables()
{
	// get directory
	GetCurrentDirectoryA( MAX_PATH, _settingFile );
	lstrcatA( _settingFile, "\\ish_setting.ini" );
	
	//std::string buff, temp;
	//IniHandler::ReadString( path, "KeyNames", 0, "Error", buff );
	//temp = buff;
	//IniHandler::ReadString( path, "KeyNames", 0, "Error", buff );

	// add key name settings
	AddElement( _settingFile, "KeyNames", "XboxInput", SC_XBOX, TT_SETTING );
	AddElement( _settingFile, "KeyNames", "KeyboardInput", SC_KEYBOARD, TT_SETTING );
	AddElement( _settingFile, "KeyNames", "InputCheckOption", SC_OPTION, TT_SETTING );
	AddElement( _settingFile, "KeyNames", "OperatorOption", SC_OPERATOR, TT_SETTING );
	AddElement( _settingFile, "KeyNames", "PlayerIndex", SC_INDEX, TT_SETTING );
	AddElement( _settingFile, "KeyNames", "Value", SC_VALUE, TT_SETTING );

	// add 360 Buttongs
	AddElement( _settingFile, "XBOX", "A", XboxButtons::A, TT_XBOX );
	AddElement( _settingFile, "XBOX", "B", XboxButtons::B, TT_XBOX );
	AddElement( _settingFile, "XBOX", "X", XboxButtons::X, TT_XBOX );
	AddElement( _settingFile, "XBOX", "Y", XboxButtons::Y, TT_XBOX );
	AddElement( _settingFile, "XBOX", "START", XboxButtons::Start, TT_XBOX );
	AddElement( _settingFile, "XBOX", "BACK", XboxButtons::Back, TT_XBOX );
	AddElement( _settingFile, "XBOX", "LeftThumb", XboxButtons::LeftThumb, TT_XBOX );
	AddElement( _settingFile, "XBOX", "RightThumb", XboxButtons::RightThumb, TT_XBOX );
	AddElement( _settingFile, "XBOX", "DpadUP", XboxButtons::DpadUp, TT_XBOX );
	AddElement( _settingFile, "XBOX", "DpadDown", XboxButtons::DpadDown, TT_XBOX );
	AddElement( _settingFile, "XBOX", "DpadLeft", XboxButtons::DpadLeft, TT_XBOX );
	AddElement( _settingFile, "XBOX", "DpadRight", XboxButtons::DpadRight, TT_XBOX );
	AddElement( _settingFile, "XBOX", "LeftShoulder", XboxButtons::LeftShoulder, TT_XBOX );
	AddElement( _settingFile, "XBOX", "RightShoulder", XboxButtons::RightShoulder, TT_XBOX );

	AddElement( _settingFile, "XBOX", "RightTrigger", XboxButtons::RightTrigger, TT_XBOX );
	AddElement( _settingFile, "XBOX", "LeftTrigger", XboxButtons::LeftTrigger, TT_XBOX );
	AddElement( _settingFile, "XBOX", "LeftThumbX", XboxButtons::LeftThumbX, TT_XBOX );
	AddElement( _settingFile, "XBOX", "LeftThumbY", XboxButtons::LeftThumbY, TT_XBOX );
	AddElement( _settingFile, "XBOX", "RightThumbX", XboxButtons::RightThumbX, TT_XBOX );
	AddElement( _settingFile, "XBOX", "RightThumbY", XboxButtons::RightThumbY, TT_XBOX );

	// read keyboard input setting
	AddElement( _settingFile, "Keyboard", "A", V_A, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "B", V_B, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "C", V_C, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "D", V_D, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "E", V_E, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F", V_F, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "G", V_G, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "H", V_H, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "I", V_I, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "J", V_J, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "K", V_K, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "L", V_L, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "M", V_M, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "N", V_N, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "O", V_O, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "P", V_P, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Q", V_Q, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "R", V_R, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "S", V_S, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "T", V_T, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "U", V_U, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "V", V_V, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "W", V_W, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "X", V_X, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Y", V_Y, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Z", V_Z, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F1", V_F1, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F2", V_F2, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F3", V_F3, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F4", V_F4, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F5", V_F5, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F6", V_F6, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F7", V_F6, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F8", V_F7, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F8", V_F8, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F9", V_F9, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F10", V_F10, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F11", V_F11, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F12", V_F12, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "F13", V_F13, TT_KEYBOARD );

	AddElement( _settingFile, "Keyboard", "Space", V_SPACE, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Enter", V_ENTER, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Escape", V_ESCAPE, TT_KEYBOARD );
	//AddElement( _settingFile, "Keyboard", "Equal", v_equ, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Shift", V_SHIFT, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Ctrl", V_CONTROL, TT_KEYBOARD );

	AddElement( _settingFile, "Keyboard", "Up", V_UP, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Down", V_DOWN, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Left", V_LEFT, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Right", V_RIGHT, TT_KEYBOARD );

	AddElement( _settingFile, "Keyboard", "Key0", V_0, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Key1", V_1, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Key2", V_2, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Key3", V_3, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Key4", V_4, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Key5", V_5, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Key6", V_6, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Key7", V_7, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Key8", V_8, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "Key9", V_9, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad0", V_NUMPAD0, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad1", V_NUMPAD1, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad2", V_NUMPAD2, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad3", V_NUMPAD3, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad4", V_NUMPAD4, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad5", V_NUMPAD5, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad6", V_NUMPAD6, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad7", V_NUMPAD7, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad8", V_NUMPAD8, TT_KEYBOARD );
	AddElement( _settingFile, "Keyboard", "NumPad9", V_NUMPAD9, TT_KEYBOARD );

	// read input options
	AddElement( _settingFile, "Options", "Down", INPUT_OPTIONS::KO_DOWN, TT_OPTION );
	AddElement( _settingFile, "Options", "Up", INPUT_OPTIONS::KO_UP, TT_OPTION );
	AddElement( _settingFile, "Options", "Pressed", INPUT_OPTIONS::KO_PRESSED, TT_OPTION );
	AddElement( _settingFile, "Options", "Released", INPUT_OPTIONS::KO_RELEASED, TT_OPTION );

	// read operator options
	AddElement( _settingFile, "Operators", "AND", OP_AND, TT_OPERATOR );
	AddElement( _settingFile, "Operators", "OR", OP_OR, TT_OPERATOR );
	AddElement( _settingFile, "Operators", "Nothing", OP_NONE, TT_OPERATOR );

	// read value options
	AddElement( _settingFile, "Values", "Positive", VT_POSITIVE, TT_VALUE );
	AddElement( _settingFile, "Values", "Negative", VT_NEGATIVE, TT_VALUE );
	AddElement( _settingFile, "Values", "Default", VT_DEFAULT, TT_VALUE );
}

// key = [Group] to search for, element = value to get input from
void InputManager::AddElement(char* path, std::string key, std::string element, unsigned int input, TABLE_TYPE type)
{
	std::string buff;

	IniHandler::ReadString( path, key.c_str(), element.c_str(), "Error", buff );
	assert( buff != "Error" );

	if ( type == TT_OPTION )
	{
		_optionText.Add( input, buff );
	}

	if ( type != TT_SETTING )
	{
		std::transform( buff.begin(), buff.end(), buff.begin(), toupper ); 
	}

	switch ( type )
	{
		case TT_SETTING:
			_settingTable.Add( (SETTING_COMMAND)input, buff );
			break;
		case TT_XBOX:
			_xboxTable.Add( buff, (XboxButtons)input );
			_xboxText.Add( input, buff );
			break;
		case TT_KEYBOARD:
			_keyboardTable.Add( buff, (VIRTUAL_KEYS)input );
			_keyboardText.Add( input, buff );
			break;
		case TT_OPTION:
			_optionTable.Add( buff, (INPUT_OPTIONS)input );
			break;
		case TT_OPERATOR:
			_operatorTable.Add( buff, (INPUT_OPERATORS)input );
			break;
		case TT_VALUE:
			float value = 1.0f;
			if ( (VALUE_TYPE)input == VT_NEGATIVE )
			{
				value = -1.0f;
			}
			_valueTable.Add( buff, value );
			break;
	}
}

void InputManager::Update()
{
	_winKeyboard.Update();
	for ( int i = 0; i < _numPlayers; ++i )
	{
		_xboxPad[i].Update( );
	}
}

void InputManager::Shutdown()
{
	ClearTables();
	_isActive = false;

	_winKeyboard.Shutdown();

	// clear function pointers
	for ( unsigned int i = 0; i < KO_NONE; ++i )
	{
		( XboxCheck[i] ) = 0;
		( KeyCheck[i] ) = 0;
	}
}

void InputManager::ClearTables()
{
	_xboxTable.Clear();
	_keyboardTable.Clear();
	_operatorTable.Clear();
	_optionTable.Clear();
	_valueTable.Clear();
	_settingTable.Clear();
	_xboxText.Clear();

	for ( int i = 0; i < PLAYER_MAX; ++i )
	{
		_inputData[i].Clear();
	}
}