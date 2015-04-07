#include "MyGame.h"
#include <mmsystem.h>
#include <tchar.h>
#include <crtdbg.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif
	
	//initialize application
	MyGame* game = new MyGame();
	game->Initialize( hInstance );
	
	//run the application
	int ret = game->Run();

	//finish application
	game->ShutDown();
	delete game;
	game = 0;

	return ret;
}